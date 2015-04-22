/*******************************************************************************
    Copyright: 2007-2008 Hangzhou Hikvision Digital Technology Co.,Ltd.
     Filename:  dvrNet.c
  Description:  Network program for DVR/DVS
      Version:  1.0
      Created:  01/02/2008 00 CST
       Author:  xmq <xiemq@hikvision.com>
 ******************************************************************************/
//#include <sys/time.h>
#include "./netLogin.h"
#include "encrypt/base64.h"
#include "encrypt/d3des.h"
#include "encrypt/md5.h"
#include "encrypt/hmac.h"
#include "encrypt/cryptomisc.h"



#define NETPRT(x)   printf x

#define CHECK_CLIENT_IP			/* check peer's client IP address */
#define CHECK_MAC_ADDR		/* check peer's MAC address */
//#define PWD_LEN     32

/* extern variables */
//zss++IMPORT pthread_mutex_t usrMutex;
//zss++IMPORT USER_INFO *pGlobalUserInfo;

/* extern functions */
UINT32 checkByteSum(char *pBuf, int len)
{
	int i;
	UINT32 sum = 0;

	for (i = 0; i < len; i++)
	{
		sum += (UINT8)*pBuf++;
	}

	return sum;
}

IMPORT int writen(int connfd, void *vptr, size_t n);


#ifndef SUPPORT_IPV6
IMPORT void handleIllegalAccess(char *username, struct in_addr *clientIp, time_t currTime, UINT32 sdkVersion);
#else
IMPORT void handleIllegalAccess(char *username, U_IN_ADDR *clientIp, time_t currTime, UINT32 sdkVersion);
#endif
#ifndef SUPPORT_IPV6
IMPORT void handleLegalAccess(
	int userIdx,
	char *username,
	struct in_addr *clientIp,
	struct in_addr *socketIp,
	char *macAddr,
   	int *userID,
	time_t currTime,
	UINT32 sdkVersion
);
#else
IMPORT void handleLegalAccess(
	int userIdx,
	char *username,
	U_IN_ADDR *clientIp,
	U_IN_ADDR *socketIp,
	char *macAddr,
   	int *userID,
	time_t currTime,
	UINT32 sdkVersion
);
#endif
/* local variables */

/* local functions */
#ifndef SUPPORT_IPV6
STATUS challenge_login(int connfd, NET_LOGIN_REQ *reqdata, int *userid,
        struct sockaddr_in *pClientSockAddr);
#else
STATUS challenge_login(int connfd, NET_LOGIN_REQ_V6 *reqdata, int *userid,
        U_IN_ADDR *pClientIp);
extern void convertNetLoginReqByteOrder(NET_LOGIN_REQ_V6 *pLoginReq);

#endif
STATUS genRandom(void);

LOCAL STATUS genChallenge(UINT32 clientIp, char **out); 
LOCAL STATUS verifyUser(char *username, char *chanllenge);
#ifndef SUPPORT_IPV6
LOCAL STATUS verifyChallengePassword(int *userIdx,  char *username , char *pwd, char *challenge, struct in_addr *clientIp, char *macAddr);
#else
 extern const struct in6_addr gLoop6Addr;
extern const struct in6_addr gAny6Addr;
LOCAL STATUS verifyChallengePassword(int *userIdx, char *username , char *pwd, char *challenge, U_IN_ADDR *clientIp, char *macAddr);

#endif

#ifndef WIN32
/*******************************************************************************
 *         Name: genRandom
 *  Description: 生成随机数函数
 *
 *       Mode   Type            Name         Description
 * -----------------------------------------------------------------------------
 *        in:   无
 *    in-out:   无
 *       out:   无
 *    return:   int                         生成的随机数
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/02/2008 00 CST
 *  Revision: none
 ******************************************************************************/
STATUS genRandom(void)
{
    int fd = -1;
    int l = 0;
    unsigned int ticks = 0;
    struct timeval tv;
    static int random_seed_set = 0;

    if(random_seed_set == 0)
    {
        gettimeofday(&tv, NULL);
        ticks = tv.tv_sec + tv.tv_usec;

        fd = open("/dev/urandom", O_RDONLY);
        if (fd > 0)
        {
            int i;
            unsigned int r;

            for(i = 0; i < 256; i++)
            {
                l = read(fd, &r, sizeof(r));
                if (l != sizeof(r))
                {
                    NETPRT(("Cannot read random data, errno=%d\n", errno));
                    break;
                }
                else
                {
                    ticks += r;
                }
            }
            close(fd);
        }

        srand(ticks);
    }

    return (rand());
}
#else
STATUS genRandom(void)
{  
	srand( (unsigned)time( NULL ) );  
	return rand()*rand();  
}  
#endif
/*******************************************************************************
 *         Name: genChallenge
 *  Description: 使用设备当前时间、客户端连接IP等参数生成随机挑战串
 *
 *       Mode   Type            Name         Description
 * -----------------------------------------------------------------------------
 *        in:   unsigned int    clientIp    客户端连接IP地址
 *    in-out:   无
 *       out:   char **         out         生成的随机挑战串
 *    return:   int                         成功返回挑战串的长度，失败返回-1
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/02/2008 00 CST
 *  Revision: none
 ******************************************************************************/
LOCAL STATUS genChallenge(UINT32 clientIp, char **out)
{
    time_t  t;
    char    tmp[40] = {0};
    unsigned int    i = 0;
    unsigned int    ran = 0;
    unsigned char   hash[16] = {0};
    struct timeval  tv;

    if((NULL == out) || (NULL == *out))
    {
        return (-1);
    }

    gettimeofday(&tv, 0);
    t = tv.tv_sec + tv.tv_usec;
    i += sprintf(tmp, "%lx", t);
    ran = genRandom();
    NETPRT(("random number: %u\n", ran));
    i += sprintf((tmp + i), "%x", ran);
    i += sprintf((tmp + i), "%x", clientIp);

    /* MD5 generated challenge string */
    MD5String(tmp, i, hash);
    MD5toStr(hash, 16, *out);
    NETPRT(("Original challenge string: %s\n", *out));

    return (32);
}


/*******************************************************************************
 *         Name: verifyUser
 *  Description: 判断客户端发送的用户名是否有效
 *
 *       Mode   Type         Name         Description
 * -----------------------------------------------------------------------------
 *        in:   char *      username    从客户端接收到经过Magic加密之后的用户名
 *    in-out:   无
 *       out:   无
 *    return:   int                     成功则返回该用户在设备配置文件中的位置
 *                                      索引值，失败返回-1
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/03/2008 00 CST
 *  Revision: none
 ******************************************************************************/
LOCAL STATUS verifyUser(char *username, char *challenge)
{
	#if 0
	int     i = 0;
    int     len = 0;
    int     clen = 0;
    int     ret = -1;
    int     inlen = 0;
    char    tmp[NAME_LEN] = {0};
    char    usr[NAME_LEN] = {0};

    if(NULL == username)
    {
        return (-1);
    }
	
    inlen = strlen(username);
    for(i = 0; i < MAX_USERNUM; i++)
    {
        memset(tmp, 0, NAME_LEN);

        strncpy(usr, (char *)pDevCfgParam->user[i].username, NAME_LEN);
        len = strlen(usr);
        if(len == 0)
        {
            continue;
        }
		
        clen = strlen(challenge);
        /* encrypt user name */
        encryptHMAC((unsigned char *)usr, len, (unsigned char *)challenge, clen, (unsigned char *)tmp);
        if(strncmp(username, tmp, inlen))
        {
            continue;
        }
        else
        {
            NETPRT(("Match user: %s\n", usr));
	     memcpy(username, usr, len+1);
            return (i);
        }
    }

    strcpy(username, "illegal username");
    NETPRT(("No user matched, challenge failed\n"));

    return (-1);
	#endif
	return 1;
}

#ifndef SUPPORT_IPV6
/*******************************************************************************
 *         Name: verifyChallengePassword
 *  Description: 判断客户端使用挑战串对密码加密之后的结果是否与本地保存的密码
 *              进行相同的加密匹配
 *
 *       Mode   Type            Name         Description
 * -----------------------------------------------------------------------------
 *        in:   int             index       要验证的用户在配置文件中的索引，用来
 *                                          获取对应的密码
 *              char *          pwd         从客户端接收到的加密之后的密码值
 *              char *          challenge   加密用的挑战串
 *              struct in_addr* clientIp    连接的客户端IP地址
 *              char *          macAddr     客户端连接的对端MAC地址
 *    in-out:   无
 *       out:    无
 *    return:   int                         成功返回0，失败返回-1
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/03/2008 00 CST
 *  Revision: none
 ******************************************************************************/
LOCAL STATUS verifyChallengePassword(int *userIdx, char *username , char *pwd, char *challenge, struct in_addr *clientIp, char *macAddr)
{
	#if 0
	int     i = 0;
    int     len = 0;
    int     clen = 0;
    int     id = NO_USER, index;
    unsigned char digest[PASSWD_LEN] = {0};
    unsigned char tmp[PASSWD_LEN] = {0};
    time_t  currTime;
    UINT32  priority;
    UINT32  permission, localPlayPermission;
    UINT32  netPrevPermission, netPlayPermission;
    USER_INFO *pUserInfo;
    USER	userCfg;
    DEVICECONFIG *pDevCfg = pDevCfgParam;

    if((NULL == pwd) || (NULL == challenge) || (NULL == userIdx))
    {
        return (NETRET_ERRORPASSWD);
    }

    currTime = time(NULL);
    clen = strlen(challenge);

    index = verifyUser((char *)username, challenge);
    if(index < 0)
    {
        return (NETRET_ERRORPASSWD);
    }
    *userIdx = index;
	
    /*检查SDK登录的挑战串密码*/
    memcpy(tmp, pDevCfgParam->user[index].password, PASSWD_LEN);
    len = strlen((char *)tmp);
    NETPRT(("original password: %s\n", tmp));

    encryptHMAC(tmp, len, (unsigned char *)challenge, clen, digest);
    if(memcmp(pwd, digest, PASSWD_LEN))
    {
        NETPRT(("Incorrect user password, challenge failed\n"));
        return (NETRET_ERRORPASSWD);
    }

    userCfg = pDevCfgParam->user[index];
    #ifdef CHECK_CLIENT_IP
    if(clientIp!=NULL && userCfg.ipAddr.v4.s_addr!=0 &&
		clientIp->s_addr!=userCfg.ipAddr.v4.s_addr)
    {
		return NETRET_IP_MISMATCH;
    }
    #endif

    #ifdef CHECK_MAC_ADDR
     if(macAddr!=NULL && (userCfg.macAddr[0]!=0 || userCfg.macAddr[1]!=0
			|| userCfg.macAddr[2]!=0 || userCfg.macAddr[3]!=0
			|| userCfg.macAddr[4]!=0 || userCfg.macAddr[5]!=0)
		&& memcmp(macAddr, userCfg.macAddr, MACADDR_LEN)!=0)
      {
		return NETRET_MAC_MISMATCH;
      }
      #endif
	  
    NETPRT(("Correct user password, challenge success\n"));
	#endif
    return (OK);
}
#else

/*******************************************************************************
 *         Name: verifyChallengePassword
 *  Description: 判断客户端使用挑战串对密码加密之后的结果是否与本地保存的密码
 *              进行相同的加密匹配
 *
 *       Mode   Type            Name         Description
 * -----------------------------------------------------------------------------
 *        in:   int             index       要验证的用户在配置文件中的索引，用来
 *                                          获取对应的密码
 *              char *          pwd         从客户端接收到的加密之后的密码值
 *              char *          challenge   加密用的挑战串
 *              struct in_addr* clientIp    连接的客户端IP地址
 *              char *          macAddr     客户端连接的对端MAC地址
 *    in-out:   无
 *       out:    无
 *    return:   int                         成功返回0，失败返回-1
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/03/2008 00 CST
 *  Revision: none
 ******************************************************************************/
LOCAL STATUS verifyChallengePassword(int *userIdx, char *username , char *pwd, char *challenge, U_IN_ADDR *clientIp, char *macAddr)
{
	int     len = 0;
	int     clen = 0;
	int     index;
	unsigned char digest[PASSWD_LEN] = {0};
	unsigned char tmp[PASSWD_LEN] = {0};
	time_t  currTime;
	USER    userCfg;

	if((NULL == pwd) || (NULL == challenge) || (NULL == userIdx))
	{
	    return (NETRET_ERRORPASSWD);
	}

	currTime = time(NULL);
	clen = strlen(challenge);

	index = verifyUser((char *)username, challenge);
	if(index < 0)
	{
	    return (NETRET_ERRORPASSWD);
	}
	*userIdx = index;

	/*检查SDK登录的挑战串密码*/
	memcpy(tmp, pDevCfgParam->user[index].password, PASSWD_LEN);
	len = strlen((char *)tmp);
	NET_INFO(("original password: %s\n", tmp));

	encryptHMAC(tmp, len, (unsigned char *)challenge, clen, digest);

	//NET_INFO(("pwd %s, digest %s.\n", pwd, digest));
	if(memcmp(pwd, digest, PASSWD_LEN))
	{
	    NET_ERR(("Incorrect user password, challenge failed\n"));
	    return (NETRET_ERRORPASSWD);
	}

	userCfg = pDevCfgParam->user[index];
	#ifdef CHECK_CLIENT_IP
		if(clientIp!=NULL)
		{
		    if((userCfg.ipAddr.v4.s_addr!=0 && clientIp->v4.s_addr!=userCfg.ipAddr.v4.s_addr)
		        || (memcmp(&userCfg.ipAddr.v6, &gAny6Addr, sizeof(struct in6_addr)) && memcmp(&userCfg.ipAddr.v6, &clientIp->v6, sizeof(struct in6_addr))))
		    {
		        return NETRET_IP_MISMATCH;
		    }
		}
	#endif

	#ifdef CHECK_MAC_ADDR
		 if(macAddr!=NULL && (userCfg.macAddr[0]!=0 || userCfg.macAddr[1]!=0
		        || userCfg.macAddr[2]!=0 || userCfg.macAddr[3]!=0
		        || userCfg.macAddr[4]!=0 || userCfg.macAddr[5]!=0)
		    && memcmp(macAddr, userCfg.macAddr, MACADDR_LEN)!=0)
		  {
		    return NETRET_MAC_MISMATCH;
		  }
	#endif  
	NET_INFO(("Correct user password, challenge success\n"));
	return (OK);
}

#endif

#ifndef SUPPORT_IPV6
/*******************************************************************************
 *         Name: challenge_login
 *  Description: 客户端采用挑战串模式登录设备的入口函数
 *
 *       Mode   Type                    Name            Description
 * -----------------------------------------------------------------------------
 *        in:   int                     connfd          客户端与设备连接的socket
 *              NET_LOGIN_REQ *         reqdata         客户端发送的登录请求数据
 *              struct sockaddr_in *    pClientSockAddr 客户端连接地址信息
 *    in-out:   无
 *       out:   int *                   userid          登录成功后设备返回给客户
 *                                                      端的用户ID
 *    return:   int                     成功返回0，失败返回设备指定的错误号
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 02/28/2008 08 CST
 *  Revision: none
 ******************************************************************************/
STATUS challenge_login(StreamSocket  &connfd, NET_LOGIN_REQ *reqdata, int *userid,
        struct sockaddr_in *pClientSockAddr)
{
    int     ret = -1;
    int     userIdx = -1;
    char    buf[64] = {0};
    char    *p = &buf[0];
    char    cbuf[1024] = {0};
    char    username[NAME_LEN] = {0};
    fd_set  rset; 
    struct timeval      tv;
    struct in_addr      clientIpAddr;
    NET_LOGIN_REQ       login_req;
    NET_LOGIN_CHALLENGE login_cha;
    NET_LOGIN_RET       login_ret;
	
    time_t currTime;

    //zss++if((connfd < 0) || (NULL == reqdata))
	if((NULL == reqdata))
    {
        return NETRET_OPER_NOPERMIT;
    }

    memset(&login_cha, 0, sizeof(NET_LOGIN_CHALLENGE));

    /* generate challenge string */
    ret = genChallenge(reqdata->clientIp, &p);
    if(ret < 0)
    {
        NETPRT(("Gengrate challenge string failed\n"));
        return (NETRET_OPER_NOPERMIT);
    }

    /* BASE64 encoding challenge string */
    ret = base64_encode(p, ret, cbuf);
    NETPRT(("Base64 challenge string: [%s] len:%d\n", cbuf, ret));

    login_cha.length = htonl(sizeof(NET_LOGIN_CHALLENGE));
    login_cha.retVal = htonl(100); /* !!! 9000 specified,需要SDK再次发送加密的用户名和密码 */
    login_cha.devSdkVer = htonl(CURRENT_NETSDK_VERSION);
    memcpy(login_cha.challenge, cbuf, ret);
    login_cha.checkSum = checkByteSum((char *)&(login_cha.retVal),sizeof(NET_LOGIN_CHALLENGE) - 8);

	
    /* send challenged data */
	//zss++ret = writen(connfd, &login_cha, sizeof(login_cha));
	ret = connfd.sendBytes((const void *) &login_cha,sizeof(login_cha),0);
    if(ret != sizeof(login_cha))
    {
        NETPRT(("send challenge to client failed\n"));
        return (NETRET_OPER_NOPERMIT);
    }

	NETPRT(("send challenge success, waitting to recv response\n"));
	Poco::Timespan timeOut(10,0);
	connfd.setReceiveTimeout(timeOut);
	ret=connfd.receiveBytes(cbuf, 1024,0);
	if(ret>0)
	{

		NETPRT(("recv response %d\n",ret));  	   
		/*接收到新的登录信息*/
		memcpy(&login_req, cbuf, sizeof(NET_LOGIN_REQ));
		currTime = time(NULL);
		clientIpAddr.s_addr = reqdata->clientIp;
		memcpy(username,(char *)login_req.username, NAME_LEN);
		ret = verifyChallengePassword(&userIdx, username, (char *)login_req.password, buf, &clientIpAddr, (char *)reqdata->clientMac);
		if(ret != OK)
		{
		   /* illegal access */
			//handleIllegalAccess(username, &clientIpAddr, currTime, reqdata->version);
			return (ret);
		}
		else
		{
			/* legal access */
			//handleLegalAccess(userIdx, username, &clientIpAddr, &(pClientSockAddr->sin_addr),
			//	(char *)reqdata->clientMac, userid, currTime, reqdata->version);
			//if(*userid == NO_USER)
			//{
				/* can't find slot, 128 users logined */
			//	NETPRT(("Too many users logined.\n"));
			//	return NETRET_EXCEED_MAX_USER;
			//}
			//zss++writeOperationLogEntry(*userid, MINOR_REMOTE_LOGIN, 0);
		} 
	}
	
    return OK;
}
#else

/*******************************************************************************
 *         Name: challenge_login
 *  Description: 客户端采用挑战串模式登录设备的入口函数
 *
 *       Mode   Type                    Name            Description
 * -----------------------------------------------------------------------------
 *        in:   int                     connfd          客户端与设备连接的socket
 *              NET_LOGIN_REQ *         reqdata         客户端发送的登录请求数据
 *              struct sockaddr_in *    pClientSockAddr 客户端连接地址信息
 *    in-out:   无
 *       out:   int *                   userid          登录成功后设备返回给客户
 *                                                      端的用户ID
 *    return:   int                     成功返回0，失败返回设备指定的错误号
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 02/28/2008 08 CST
 *  Revision: none
 ******************************************************************************/
STATUS challenge_login(int connfd, NET_LOGIN_REQ_V6 *reqdata, int *userid,
        U_IN_ADDR *pClientIp)
{
    int     ret = -1;
    int     userIdx = -1;
    char    buf[64] = {0};
    char    *p = &buf[0];
    char    cbuf[1024] = {0};
    char    username[NAME_LEN] = {0};
    char	password[PASSWD_LEN];
    fd_set  rset; 
    struct timeval      tv;
    U_IN_ADDR clientIpAddr;
    NET_LOGIN_REQ_V6 *pNetLoginReq;
    NET_LOGIN_CHALLENGE login_cha;
    time_t currTime;

    if((connfd < 0) || (NULL == reqdata))
    {
        return NETRET_OPER_NOPERMIT;
    }

    memset(&login_cha, 0, sizeof(NET_LOGIN_CHALLENGE));

    /* generate challenge string */
    ret = genChallenge(reqdata->clientIp, &p);
    if(ret < 0)
    {
        NET_ERR(("Gengrate challenge string failed\n"));
        return (NETRET_OPER_NOPERMIT);
    }

    /* BASE64 encoding challenge string */
    ret = base64_encode(p, ret, cbuf);
    NET_INFO(("Base64 challenge string: [%s] len:%d\n", cbuf, ret));

    login_cha.length = htonl(sizeof(NET_LOGIN_CHALLENGE));
    login_cha.retVal = htonl(100); /* !!! 9000 specified,需要SDK再次发送加密的用户名和密码 */
    login_cha.devSdkVer = htonl(CURRENT_NETSDK_VERSION);
    memcpy(login_cha.challenge, cbuf, ret);
    login_cha.checkSum = checkByteSum((char *)&(login_cha.retVal),sizeof(NET_LOGIN_CHALLENGE) - 8);

    /* send challenged data */
    ret = writen(connfd, &login_cha, sizeof(login_cha));
    if(ret != sizeof(login_cha))
    {
        NET_ERR(("send challenge to client failed\n"));
        return (NETRET_OPER_NOPERMIT);
    }

    NET_INFO(("send challenge success, waitting to recv response\n"));

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    FD_ZERO(&rset);
    FD_SET(connfd, &rset);

    ret = select(connfd+1, &rset, NULL, NULL, &tv);
    if(ret <= 0)
    {
        NET_ERR(("Waitting for client challenge password failed\n"));
        return (NETRET_OPER_NOPERMIT);
    }
    else
    {
        if(FD_ISSET(connfd, &rset))
        {
            ret = read(connfd, cbuf, 1024);
            if(ret > 0)
            {
                /*接收到新的登录信息*/
                pNetLoginReq = (NET_LOGIN_REQ_V6 *)cbuf;
                convertNetLoginReqByteOrder(pNetLoginReq);
                if(pNetLoginReq->ipVer)
                {
                    memcpy(username, (cbuf+sizeof(NET_LOGIN_REQ_V6)), sizeof(username));
                    memcpy(password, (cbuf+sizeof(NET_LOGIN_REQ_V6))+sizeof(username), sizeof(password));
               }
                else
                {
                    memcpy(username, (cbuf+sizeof(NET_LOGIN_REQ)), sizeof(username));
                    memcpy(password, (cbuf+sizeof(NET_LOGIN_REQ))+sizeof(username), sizeof(password));
                }
                currTime = time(NULL);
                clientIpAddr.v4.s_addr = reqdata->clientIp;
                if(reqdata->ipVer)
                {
                    memcpy(&clientIpAddr.v6, &reqdata->clientIp6, sizeof(struct in6_addr));
                }
                ret = verifyChallengePassword(&userIdx, username, password, buf, &clientIpAddr, (char *)reqdata->clientMac);
                if(ret != OK)
                {
                    /* illegal access */
                    handleIllegalAccess(username, &clientIpAddr, currTime, reqdata->version);
                    return (ret);
                }
                else
                {
                    /* legal access */
                    handleLegalAccess(userIdx, username, &clientIpAddr, pClientIp,
                        (char *)reqdata->clientMac, userid, currTime, reqdata->version);
                    if(*userid == NO_USER)
                    {
                        /* can't find slot, 128 users logined */
                        NET_ERR(("Too many users logined.\n"));
                        return NETRET_EXCEED_MAX_USER;
                    }
                    writeOperationLogEntry(*userid, MINOR_REMOTE_LOGIN, 0);
                }
            }
        }
    }

    return OK;
}


#endif


