#include "netUtil.h"

void bzero(char  *buffer,  /* buffer to be zeroed*/int   nbytes  /* number of bytes in buffer */ )
{
    if (((int)buffer & 0x3) == 0)
	{
		while (nbytes >= 4)
		{
		    *(int *)buffer = 0;
		    buffer += 4;
		    nbytes -= 4;
		}
	}

    while (nbytes >= 1)
	{
		*buffer = 0;
		buffer += 1;
		nbytes -= 1;
	}
 }

#ifndef OEM_SUPPORT_IPV6
/***********************************************************************
 * Function: get_peer_name
 * Description:
 * Input:  
 * Output:  N/A
 * Return: 
 ***********************************************************************/
int get_peer_name(int fd, struct sockaddr_in *peer)
{

 	socklen_t namelen = sizeof(struct sockaddr_in);

	return getpeername(fd,(struct sockaddr*)peer,&namelen);
}
#endif


/***********************************************************************
 * Function: convertNetCmdHeaderByteOrder
 * Description:convert network byte order
 * Input:  pHeader:pointer point to NETCMD_HEADER
 * Output:  N/A
 * Return:  NONE 
 ***********************************************************************/
void convertNetCmdHeaderByteOrder(NETCMD_HEADER *pHeader)
{
	pHeader->length 	= ntohl(pHeader->length);
	pHeader->checkSum 	= ntohl(pHeader->checkSum);
	pHeader->netCmd 	= ntohl(pHeader->netCmd);
	pHeader->userID		= ntohl(pHeader->userID);
	pHeader->clientIp	= ntohl(pHeader->clientIp);

	return;
}

#ifndef SUPPORT_IPV6
/***********************************************************************
 * Function: convertNetLoginReqByteOrder
 * Description:convert network login request byte order
 * Input:  pHeader:pointer point to NETCMD_HEADER
 * Output:  N/A
 * Return:  NONE 
 ***********************************************************************/
void convertNetLoginReqByteOrder(NET_LOGIN_REQ *pLoginReq)
{
	pLoginReq->length 	= ntohl(pLoginReq->length);
	pLoginReq->checkSum = ntohl(pLoginReq->checkSum);
	pLoginReq->netCmd 	= ntohl(pLoginReq->netCmd);
	pLoginReq->version  = ntohl(pLoginReq->version);
	pLoginReq->clientIp	= ntohl(pLoginReq->clientIp); 

	return;
}
#else
/***********************************************************************
 * Function: convertNetLoginReqByteOrder
 * Description:convert network login request byte order
 * Input:  pHeader:pointer point to NETCMD_HEADER
 * Output:  N/A
 * Return:  NONE 
 ***********************************************************************/
void convertNetLoginReqByteOrder(NET_LOGIN_REQ_V6 *pLoginReq)
{
    pLoginReq->length   = ntohl(pLoginReq->length);
    pLoginReq->checkSum = ntohl(pLoginReq->checkSum);
    pLoginReq->netCmd   = ntohl(pLoginReq->netCmd);
    pLoginReq->version  = ntohl(pLoginReq->version);
    pLoginReq->clientIp = ntohl(pLoginReq->clientIp); 

    return;
}

#endif

#ifdef WIN32
int gettimeofday(struct timeval *tp, void *tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year     = wtm.wYear - 1900;
    tm.tm_mon     = wtm.wMonth - 1;
    tm.tm_mday     = wtm.wDay;
    tm.tm_hour     = wtm.wHour;
    tm.tm_min     = wtm.wMinute;
    tm.tm_sec     = wtm.wSecond;
    tm. tm_isdst    = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}
#endif

