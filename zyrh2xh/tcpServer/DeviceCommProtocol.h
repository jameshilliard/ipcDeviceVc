#ifndef _INCnetCommand_h
#define _INCnetCommand_h


#include "Poco/Net/SocketReactor.h"
#include "Poco/Net/SocketAcceptor.h"
#include "Poco/Net/SocketNotification.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/NObserver.h"
#include "Poco/Exception.h"
#include "Poco/Thread.h"
#include "Poco/FIFOBuffer.h"
#include "Poco/Delegate.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"


#define 	RTSP	1  //zss++


using Poco::Net::StreamSocket;

#ifndef STATUS
#define STATUS	int
#endif

#ifndef IMPORT
#define IMPORT	extern
#endif

#ifndef LOCAL
#define LOCAL	static
#endif

#ifndef FOREVER
#define FOREVER for(;;)
#endif

#ifndef ERROR 
#define ERROR	-1
#endif

#ifndef OK
#define OK	0
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define	FALSE	0
#endif




#define PRODDATELEN         8			/* 生产日期 */
#define PRODNUMLEN          9			/* 9位数的序列号 */
#define SERIALNO_LEN        48			/* 序列号长度 */




#define NAME_LEN				32				/* 用户名长度 */
#define PASSWD_LEN				16				/* 密码长度 */
#define MAX_DOMAIN_NAME			64				/* 最大域名长度 */
#define MACADDR_LEN				6				/* MAC地址长度 */
#define PATHNAME_LEN			128				/* 路径名长度 */
#define PRODUCT_MODEL_LEN		64				/* 产品型号长度(国标型号>16位) */

#define MAX_VIDEOOUT			4				/* 最大CVBS个数 */
#define MAX_VIDEOOUT_8000		2				/* 最大CVBS个数 */
#define MAX_VGA					4				/* 最大VGA个数 */
#define MAX_VGA_8000			1				/* 最大VGA个数 */
#define MAX_AUXOUT				16				/* 最大模拟矩阵输出个数 */
#define MAX_ETHERNET			2				/* 网口个数 */
#define MAX_ANALOG_CHANNUM		32				/* maximum analog channel count */
#define MAX_CHANNUM				32				/* 最大输入通道数 */
#define MAX_CHANNUM_8000	    16				/* 最大输入通道数 */
#define	MAX_DECODE_CHAN     	16				/* 最大解码通道数 */
#define MAX_ALARMIN				32				/* 最大报警输入 */
#define MAX_ALARMIN_8000	    16				/* 最大报警输入 */
#define MAX_ALARMOUT			32				/* 最大报警输出 */
#define MAX_ALARMOUT_8000		4				/* 最大报警输出 */
#define MAX_SERIAL_PORT			8				/* 最大串口个数 */
#define MAX_USB_NUM         	2				/* USB外设最大个数 */

#define MAX_IPCHANNUM       	32				/* IPC最大个数 */
#define MAX_IPC_ALARMIN     	6				/* IPC最大报警输入个数 */
#define MAX_IPC_ENCCHAN     	4				/* IPC最大报编码通道个数 */
#define MAX_IPC_ALARMOUT    	2				/* IPC最大报警输出个数 */

#define MAX_USERNUM				32				/* 最大用户数 */
#define MAX_USERNUM_8000		16				/* 最大用户数 */
#define MAX_EXCEPTIONNUM		32				/* 最大异常个数 */
#define MAX_EXCEPTIONNUM_8000	16				/* 最大异常个数 */
#define MAX_TIMESEGMENT			8				/* 一天最大8个时间段 */
#define MAX_TIMESEGMENT_8000    4				/* 8000一天最大4个时间段 */
#define MAX_DAYS				7				/* 1周7天 */
#define PHONENUMBER_LEN			32				/* 电话号码长度 */


/*net client debug define*/
#define NET_INFO(x)  printf x
#define NET_ERR(x)   printf x
#define NET_FATAL(x) printf x

#define MAX_IP_DEVICE		32
#define MAX_IP_CHANNUM      32
#define MAX_IP_ALARMIN		128
#define MAX_IP_ALARMOUT		64


/*analog + IP*/
#define MAX_ANALOG_ALARMIN			MAX_ALARMIN 
#define MAX_ANALOG_ALARMOUT			MAX_ALARMOUT 
#define MAX_CHANNUM_V30   				(MAX_ANALOG_CHANNUM + MAX_IP_CHANNUM)
#define MAX_ALARMOUT_V30  				(MAX_ANALOG_ALARMOUT + MAX_IP_ALARMOUT)
#define MAX_ALARMIN_V30   				(MAX_ANALOG_ALARMIN + MAX_IP_ALARMIN)
#define MAX_DISKNUM_V30                 MAX_HD_COUNT 
#define MAX_DISKNUM_8000				16 

#define  ONESECOND       1000/*单位:毫秒*/
/* network SDK version
	day  : bit 0 - 5
	month: bit 6 - 9
	year : bit 10 - 15
	minor: bit 16 - 23
	major: bit 24 - 31
*/
#define MAKE_NETSDK_VERSION(_major, _minor, _year, _month, _day)	\
	(	\
	(((_major)&0xff)<<24) | 	\
	(((_minor)&0xff)<<16) |	\
	((((_year)-2000)&0x3f)<<10)	|	\
	(((_month)&0xf)<<6) |	\
	((_day)&0x3f)	\
	)

#define GET_NETSDK_MAJOR(version)	(((version)>>24)&0xff)
#define GET_NETSDK_MINOR(version)	(((version)>>16)&0xff)
#define GET_NETSDK_YEAR(version)	((((version)>>10)&0x3f)+2000)
#define GET_NETSDK_MONTH(version)	(((version)>>6)&0xf)
#define GET_NETSDK_DAY(version)		((version)&0x3f)

#define GET_NETSDK_BUILDDATE(version)	((version)&0xffff)
#define RELOGIN_FLAG					0x80000000
#define NETSDK_VERSION1_0	MAKE_NETSDK_VERSION(1, 0, 2004, 10, 4)
#define NETSDK_VERSION1_2	MAKE_NETSDK_VERSION(1, 2, 2005, 3, 15)		/* 用户名/密码加密，硬盘数为16 */
#define NETSDK_VERSION1_3	MAKE_NETSDK_VERSION(1, 3, 2005, 4, 1)		/* 移动侦测/视频丢失/遮挡报警布防时间段 */
#define NETSDK_VERSION1_4	MAKE_NETSDK_VERSION(1, 4, 2005, 5, 30)		/* 预置点数目 16 -> 128 */
#define NETSDK_VERSION1_5	MAKE_NETSDK_VERSION(1, 5, 2005,12, 28)		/* 用户的权限细化到通道(本地回放、远程回放、远程预览)*/
#define NETSDK_VERSION2_0   MAKE_NETSDK_VERSION(2, 0, 2006,4, 27)
#define NETSDK_VERSION2_1	MAKE_NETSDK_VERSION(2, 1, 2006,8, 14)		/* 这个版本以上的SDK需要二次认证 */
#define NETSDK_VERSION3_0	MAKE_NETSDK_VERSION(3, 0, 2008,2, 28)		
#define NETSDK_VERSION3_1	MAKE_NETSDK_VERSION(3, 1, 2009,7, 30)		
#define NETSDK_VERSION4_0   MAKE_NETSDK_VERSION(4, 0, 2010,3, 1)

#ifdef HI3515
#define CURRENT_NETSDK_VERSION  NETSDK_VERSION4_0
#define CURRENT_NETSDK_VERSION	0x040028C1
#else
//#define CURRENT_NETSDK_VERSION	NETSDK_VERSION3_1
#define CURRENT_NETSDK_VERSION	0x040028C1
#endif

/* network command defines */
/* 新、老网络SDK的接口 */
#define NEW_NETSDK_INTERFACE	90
#define OLD_NETSDK_INTERFACE	60
#ifdef NET3G_SDK
#define FOR3G_NETSDK_INTERFACE	30
#define FOR3G_NETSDK_SDK_INTERFACE   99
#endif

//login/logout 
#define NETCMD_LOGIN				0x010000	/* login */
#define NETCMD_RELOGIN				0x010010	/* verify username/password again */
#define NETCMD_LOGOUT				0x010100	/* logout */
#define NETCMD_USEREXCHANGE		0x010200	/* user keep alive */

//parameter 
#define NETCMD_GET_DEVICECFG		0x020000	/* device parameter */
#define NETCMD_SET_DEVICECFG		0x020001

#define NETCMD_GET_DEVICECFG_V40	0x1110c2     /* 获取扩展设备参数 */
#define NETCMD_SET_DEVICECFG_V40	0x1110c3     /* 获取扩展设备参数 */

#define NETCMD_GET_NETCFG			0x020100	/* network parameter */
#define NETCMD_SET_NETCFG			0x020101
#define NETCMD_GET_NETCFG_V30   	0x110000
#define NETCMD_SET_NETCFG_V30   	0x110001

#define NETCMD_GET_NETCFG_MULTI	0x111082 /*获取多网口参数*/
#define NETCMD_SET_NETCFG_MULTI	0x111083 /*设置多网口参数*/
#define NETCMD_GET_NETAPPCFG    	0x020110
#define NETCMD_SET_NETAPPCFG    	0x020111
#define NETCMD_GET_NTPCFG			0x020112  /*获取网络应用参数 NTP*/
#define NETCMD_SET_NTPCFG			0x020113  /*设置网络应用参数 NTP*/
#define NETCMD_GET_DDNSCFG		0x020114  /*获取网络应用参数 DDNS*/
#define NETCMD_SET_DDNSCFG		0x020115  /*设置网络应用参数 DDNS*/
#define NETCMD_GET_DDNSCFG_EX   	0x02011a  /*获取网络应用参数扩展DDNS*/
#define NETCMD_SET_DDNSCFG_EX   	0x02011b  /*设置网络应用参数扩展DDNS*/
#define NETCMD_GET_DDNSCFG_V30 	0x110140  /*获取网络应用参数9000 DDNS*/
#define NETCMD_SET_DDNSCFG_V30  	0x110141  /*设置网络应用参数9000 DDNS*/
#define NETCMD_GET_EMAILCFG		0x020116  /*获取网络应用参数 EMAIL*/
#define NETCMD_SET_EMAILCFG		0x020117  /*设置网络应用参数 EMAIL*/
#define NETCMD_GET_EMAILCFG_V30  	0x1100b0
#define NETCMD_SET_EMAILCFG_V30 	0x1100b1



#define NETCMD_EMAIL_TEST		0x111081 	/*Email测试接口*/
#define NETCMD_GET_NFSCFG       0x020120
#define NETCMD_SET_NFSCFG       0x020121
#define NETCMD_GET_NASCFG_V30   	0x110090
#define NETCMD_SET_NASCFG_V30   	0x110091

#define NETCMD_GET_PICCFG		0x020200	/* picture parameter */
#define NETCMD_SET_PICCFG		0x020201
#define NETCMD_GET_PICCFG_EX	0x020232
#define NETCMD_SET_PICCFG_EX	0x020233
#define NETCMD_GET_PICCFG_V30   	0x110010
#define NETCMD_SET_PICCFG_V30   	0x110011

#define NETCMD_SET_PICCFG_ENHANCE	0x020234

#define NETCMD_GET_HDCFG_NEW    0x10001a
#define NETCMD_SET_HDCFG_NEW    0x10001b

#define NETCMD_GET_COMPRESSCFG_AUD		0x110042
#define NETCMD_SET_COMPRESSCFG_AUD		0x110043
#define NETCMD_GET_COMPRESSCFG_AUD_CURRENT	0x110044

#define NETCMD_GET_COMPRESSCFG		0x020210	/* compression parameter */
#define NETCMD_SET_COMPRESSCFG		0x020211
#define NETCMD_GET_COMPRESSCFG_EX	0x020218	/* compression parameter */
#define NETCMD_SET_COMPRESSCFG_EX	0x020219
#define NETCMD_GET_COMPRESSCFG_V30	0x110040	/* compression parameter */
#define NETCMD_SET_COMPRESSCFG_V30 	0x110041
#define NETCMD_GET_EVENTCOMPCFG		0x020212	/* compression parameter */
#define NETCMD_SET_EVENTCOMPCFG		0x020213

#define NETCMD_GET_RELATIONCFG		0x020214	/* relation between alarm and motion */
#define NETCMD_SET_RELATIONCFG		0x020215

#define NETCMD_GET_RECORDCFG		0x020220	/* record parameter */
#define	NETCMD_SET_RECORDCFG		0x020221
#define NETCMD_GET_RECORDCFG_V30		0x110020
#define NETCMD_SET_RECORDCFG_V30		0x110021

#define NETCMD_GET_DECODERCFG		0x020230	/* decoder parameter */
#define NETCMD_SET_DECODERCFG		0x020231
#define NETCMD_GET_PTZPROTOCOL      	0x111080
#define NETCMD_GET_DECODERCFG_V30	0x110070	/* decoder parameter */
#define NETCMD_SET_DECODERCFG_V30	0x110071

#define NETCMD_GET_SHOWSTRING		0x020234	/* 获取叠加字符参数 */
#define NETCMD_SET_SHOWSTRING		0x020235	/* 设置叠加字符参数 */
#define NETCMD_GET_SHOWSTRING_V30	0x110130	/* 获取叠加字符参数 */
#define NETCMD_SET_SHOWSTRING_V30	0x110131	/* 设置叠加字符参数 */
#define NETCMD_GET_RS232CFG			0x020310	/* rs232 parameter */
#define NETCMD_SET_RS232CFG			0x020311
#define NETCMD_GET_RS232CFG_V30		0x110060	/* rs232 parameter */
#define NETCMD_SET_RS232CFG_V30		0x110061
#define NETCMD_GET_ALARMINCFG		0x020410	/* alarm in parameter */
#define NETCMD_SET_ALARMINCFG		0x020411
#define NETCMD_GET_ALARMINCFG_V30	0x110050	/* alarm in parameter */
#define NETCMD_SET_ALARMINCFG_V30	0x110051
#define NETCMD_GET_ALARMOUTCFG		0x020420	/* alarm out parameter */
#define NETCMD_SET_ALARMOUTCFG		0x020421
#define NETCMD_GET_ALARMOUTCFG_V30	0x1100a0	/* alarm out parameter */
#define NETCMD_SET_ALARMOUTCFG_V30	0x1100a1


#define NETCMD_GET_TIMECFG			0x020500	/* DVR date/time */
#define NETCMD_SET_TIMECFG			0x020501
#define NETCMD_GET_DSTCFG           0x090009
#define NETCMD_SET_DSTCFG           0x09000a
#define NETCMD_GET_RTCTYPE			0x090352	/*rtc 时钟类型0 no rtc;1 has */

#define NETCMD_GET_PREVIEWCFG		0x020600	/* preview parameter */
#define NETCMD_SET_PREVIEWCFG		0x020601
#define NETCMD_GET_PREVIEWCFG_V30	0x110100	/* preview parameter */
#define NETCMD_SET_PREVIEWCFG_V30	0x110101
#define NETCMD_GET_AUXPREVCFG		0x020602	/* aux Vout preview parameter,for HF-S */
#define NETCMD_SET_AUXPREVCFG		0x020603
#define NETCMD_GET_AUXPREVCFG_V30	0x110102	/* aux Vout preview parameter,for HF-S */
#define NETCMD_SET_AUXPREVCFG_V30	0x110103

#define NETCMD_GET_AUXVOUTCFG		0x020610	/* aux video out parameter */
#define NETCMD_SET_AUXVOUTCFG		0x020611
#define NETCMD_GET_VIDEOOUTCFG		0x020700	/* video out parameter */
#define NETCMD_SET_VIDEOOUTCFG		0x020701
#define NETCMD_GET_VIDEOOUTCFG_V30	0x110110	/* video out parameter */
#define NETCMD_SET_VIDEOOUTCFG_V30	0x110111

#define NETCMD_GET_MATRIXPARA_V30   0x100008
#define NETCMD_SET_MATRIXPARA_V30   0x100009

#define NETCMD_GET_USERCFG			0x020800	/* user parameter */
#define NETCMD_SET_USERCFG			0x020801
#define NETCMD_GET_USERCFG_EX		0x020802  	/* user parameter */
#define NETCMD_SET_USERCFG_EX		0x020803
#define NETCMD_GET_USERCFG_V30		0x110030
#define NETCMD_SET_USERCFG_V30		0x110031

#define NETCMD_GET_EXCEPTIONCFG		0x020900	/* exception parameter */
#define NETCMD_SET_EXCEPTIONCFG		0x020901
#define NETCMD_GET_EXCEPTIONCFG_V30	0x110120	/* exception parameter */
#define NETCMD_SET_EXCEPTIONCFG_V30	0x110121



#define NETCMD_GET_FRAMEFORMAT_V30  0x110080
#define NETCMD_SET_FRAMEFORMAT_V30  0x110081

/*add by xijw*/
#define NETCMD_GET_ATMPROTOCOL          0x110082

#define NETCMD_GET_HDCFG			0x100018
#define NETCMD_SET_HDCFG			0x100019
#define NETCMD_GET_AUTOBOOTCFG		    0x1100c0
#define NETCMD_SET_AUTOBOOTCFG		    0x1100c1
#define NETCMD_GET_CRUISECFG			0x1100e0
#define NETCMD_SET_CRUISECFG			0x1100e1
#define NETCMD_GET_HOLIDAYCFG			0x1100f0
#define NETCMD_SET_HOLIDAYCFG			0x1100f1

#define NETCMD_GET_IPCORECFG			0x110150
#define NETCMD_SET_IPCORECFG			0x110151
#define NETCMD_GET_IPCORECFG_V31			0x110152 /*SDK V3.1新增命令字，支持使用IPC  域名接入*/
#define NETCMD_SET_IPCORECFG_V31			0x110153 /*SDK V3.1新增命令字，支持使用IPC  域名接入*/
#define NETCMD_GET_IPALARMINCFG		    0x110160
#define NETCMD_SET_IPALARMINCFG		    0x110161
#define NETCMD_GET_IPALARMOUTCFG		0x110170
#define NETCMD_SET_IPALARMOUTCFG		0x110171

#define DVR_GET_SCALECFG			0x020a04 /* 获取缩放配置*/
#define DVR_SET_SCALECFG			0x020a05  /*设置缩放配置*/
#define DVR_GET_SCALECFG_V30			0x110180 /* 获取缩放配置*/
#define DVR_SET_SCALECFG_V30			0x110181  /*设置缩放配置*/

/*ATM机端口设置*/
#define DVR_GET_ATMPORT    0x020a06  /*获取ATM PORT配置*/
#define DVR_SET_ATMPORT    0x020a07  /*设置ATM PORT配置*/
#define DVR_PTZSELZOOMIN 	0x030290	/*设置球机选定区域放大*/

#ifdef USEIMG
#define NETCMD_GET_FTPCFG				0x020002		/*获取图片上传FTP参数	*/
#define NETCMD_SET_FTPCFG				0x020003		/*设置图片上传FTP参数*/
#define NETCMD_GET_JPEGCFG			0x020004		/*获取图片参数	*/
#define NETCMD_SET_JPEGCFG			0x020005		/*设置图片参数*/
#define NETCMD_GET_JPEGPICTURE_EX				0x03000a		/*触发jpeg抓图*/
#endif

#define NETCMD_GET_DEVCFGFILE   0x020a00	/*获取当前服务器配置文件*/
#define NETCMD_PUT_DEVCFGFILE	0x020a01	/*导入配置文件到服务器*/
#ifdef NET3G_SDK
#define NETCMD_GET_COMPRESSCFG_AUD  0x110042     /* 获取对讲音频压缩参数 */
#define NETCMD_SET_COMPRESSCFG_AUD  0x110043     /* 设置对讲音频压缩参数*/
#define NETCMD_GET_COMPRESSCFG_AUD_EX   0x110044    /* 获取当前生效的对讲音频压缩参数 */
#define NETCMD_GET_CMSCFG   0x111300
#define NETCMD_SET_CMSCFG   0x111301
#define NETCMD_GET_DIALCFG  0x111302        /* 获取拨号参数 */
#define NETCMD_SET_DIALCFG  0x111303        /* 设置拨号参数 */
#define NETCMD_GET_DIALSTATUS   0x111304    /* 获取拨号状态 */
#define NETCMD_GET_SMSCFG   0x111305        /* 获取短信参数 */
#define NETCMD_SET_SMSCFG   0x111306        /* 设置短信参数 */
#define NETCMD_GET_SMSLIST  0x111307        /* 获取短信列表 */
#define NETCMD_SEND_SMS     0x111308        /* 发送短信内容 */
#define NETCMD_GET_SMSCONTENT   0x111309    /* 获取短信内容 */
#define NETCMD_GET_PINSTATUS    0x11130a    /* 获取Pin状态 */
#define DVR_SET_PINCMD          0x11130b    /* 设置PIN命令 */
#define DVR_TRA_JPEGPICCENTER   0x11130c  //触发设备抓图上传，上传到图片服务器

#define NETCMD_ALARMCHAN    0x030400        /* 建立报警上传通道(布防) */
#define NETCMD_ALARMCHAN_V30   0x111020        /* 建立报警上传通道 */
#ifdef SDK_NAT
#define NETCMD_QUERYMAPPEDADDR  0x111420   /* 查询外网地址 */
#define NETCMD_NATPREVIEWQUEST  0x111421   /* UDP预览请求 */
#endif
#endif

/*
 * ============================================================================
 *                            3. remote  operation
 * ============================================================================
 */
/* preview */
#define NETCMD_TCP_PREV			0x030000	/* TCP preview */
#define NETCMD_UDP_PREV			0x030001	/* UDP preview */
#define NETCMD_MCAST_PREV		0x030002	/* MCAST preview */
#define NETCMD_RTP_PREV			0x030003	/* RTP preview */
#define NETCMD_VIDEO_ONLY		0x030004	/* 音视频分开 */
#define NETCMD_AUDIO_ONLY		0x030005
#define NETCMD_DATAEXCHANGE		0x030006	/* data exchange */
#define NETCMD_GET_VIDEOEFFECT	0x030007
#define NETCMD_SET_VIDEOEFFECT	0x030008
#define NETCMD_GET_VIDEOEFFECT_V30	0x053943 /*暂时实现，需要和SDK定义命令*/
#define NETCMD_SET_VIDEOEFFECT_V30	0x073456

#define NETCMD_GET_VOLUME		0x030010	/*获取每个通道输入音量*/

/* playback */
#define NETCMD_FINDFILE			0x030100	/* 查找文件 */
#define NETCMD_FINDFILE_V30			0x111040	/* 查找文件 */
#define NETCMD_PLAYBYFILE		0x030101	/* 按文件回放 */
#define NETCMD_PLAYBYTIME		0x030102	/* 按时间回放 */
#define NETCMD_STARTPLAY		0x030103	/* 开始回放 */
#define NETCMD_STOPPLAY			0x030104	/* 停止回放,释放连接 */
#define NETCMD_SETPOS			0x030105	/* 按文件回放,改变播放的进度 */
#define NETCMD_BACKWARD			0x030106	/* 后跳n秒 */
#define NETCMD_PAUSE			0x030107	/* 暂停 */
#define NETCMD_RESTART			0x030108	/* 重新开始 */
#define NETCMD_EXCHANGE			0x030109	/* 回放交互命令 */
#define NETCMD_STREAMSPEED      0x03010d    /* 下载的速度 */
#define NETCMD_LOCK_FILE        0x030112
#define NETCMD_UNLOCK_FILE      0x030113
#define NETCMD_LOCK_BYTIME      0x030114
#define NETCMD_UNLOCK_BYTIME    0x030115
#ifdef USEIMG
#define NETCMD_FINDPICTURE      0x03010a	/*查找图片*/
#define NETCMD_GETPICTURE		0x03010b	/*下载图片*/
#endif
#define NETCMD_GET_JPEGPICTURE			0x030009		/*抓JPEG图像*/

#ifdef SUP_PICTURE
#define NETCMD_GET_SCHED_CAPTURE                0x111146        // 获取抓图计划
#define NETCMD_SET_SCHED_CAPTURE                0x111147        // 设置抓图计划
#define NETCMD_SEARCH_PICTURE_V30	            0x111148
#define NETCMD_GET_PICTURE_V30		            0x111149
#define NETCMD_GET_PICTURE_CAPTURE_CFG          0x111150        // 获取DVR抓图配置
#define NETCMD_SET_PICTURE_CAPTURE_CFG          0x111151        // 设置DVR抓图配置
#define NETCMD_GET_FTP_CFG				        0x020002	//获取图片上传FTP参数
#define NETCMD_SET_FTP_CFG					    0x020003	//设置图片上传FTP参数
#endif

#define NETCMD_GET_IPC_COMP_ABILITY     0x1110d0    /* 获取压缩参数能力列表*/
#define NETCMD_GET_PIC_CAPTURE_ABILITY  0x1110d1    /* 获取抓图能力列表*/


//PTZ control 
#define NETCMD_PTZ				0x030200	/* 云台控制 */
#define NETCMD_TRANSPTZ		0x030201	/* 透明云台控制 (没有使用)*/
#define NETCMD_GETPTZCONTROL	0x030202	/* 获取云台控制权 */
#define DVR_PTZWITHSPEED		0x030203    /*带速度的云台控制*/

//remote control local display 
#define NETCMD_LOCALPREV		0x030300
#define NETCMD_LOCALPLAYBYNAME	0x030301
#define NETCMD_LOCALPLAYBYTIME	0x030302
#define NETCMD_LOCALFAST		0x030303
#define NETCMD_LOCALSLOW		0x030304
#define NETCMD_LOCALSINGLEFRAME	0x030305
#define NETCMD_LOCALNORMAL		0x030306
#define NETCMD_LOCALFORWARD		0x030307
#define NETCMD_LOCALBACKWARD	0x030308
#define NETCMD_LOCALSETPOS		0x030309
#define NETCMD_LOCALGETPOS		0x03030a
#define NETCMD_LOCALSTOPPLAY	0x03030b
#define NETCMD_CLICKKEY			0x03030c
#define NETCMD_START_PANELKEY			0x111060
#define NETCMD_STOP_PANELKEY			0x111061
#define NETCMD_PREVIEWONECHAN	0x03030d
/* alarm */
#define NETCMD_ALARMCHAN		0x030400	/* 建立报警上传通道 */
#define NETCMD_ALARMCHAN_V30			0x111020	/* 建立报警上传通道 */
#define NETCMD_SETALARMOUT		0x030401	/* 控制报警输出 */
#define NETCMD_GETALARMOUT		0x030402	/* 获取报警输出 */
#define NETCMD_GETALARMOUT_V30		0x111010	/* 获取报警输出 */
/* voice talk */
#define NETCMD_STARTVOICECOM	 0x030500	/* 开始语音对讲 */
#define NETCMD_STARTVOICECOM_V30 		0x111030	/* 开始语音对讲 */
/* transparent channel */
#define NETCMD_SERIALSTART		0x030600	/* 建立透明通道 */
#define NETCMD_SERIALSEND		0x030601	/* 不建立透明通道直接发送数据 */
/* control */
#define NETCMD_RESTORE_CFG		0x030700	/* 恢复缺省参数 */
#define NETCMD_SAVE_CFG			0x030800	/* 保存参数 */
#define NETCMD_REBOOT			0x030900	/* reboot DVR */
#define NETCMD_SHUTDOWN			0x030a00	/* shutdown DVR */
#define NETCMD_UPGRADE			0x030b00	/* upgrade software */
#define NETCMD_FORMAT			0x030c00	/* format hard disk */
#define NETCMD_GET_HDMANAGE  			0x111050	/* format hard disk */
#define NETCMD_SET_HDATTRIBUTE		0x111051	/* format hard disk */
#define NETCMD_GET_HDGROUP  			0x111052	/* format hard disk */
#define NETCMD_SET_HDGROUP			0x111053	/* format hard disk */
#define NETCMD_STARTRECORD		0x030d00	/* start record */
#define NETCMD_STOPRECORD		0x030d01	/* stop record */
#define DVR_SETALARMINPUT   	0x030d02  	/*手动报警*/
#define NETCMD_GET_LOG			0x030e00	/* get log */
#define NETCMD_GET_LOG_V30			0x111000	/* get log */
#define NETCMD_GET_SMART_LOG			0x111001	/* get HD SMART log */

#define NETCMD_GET_WORKSTATUS	0x040000	/* 获取工作状态 */
#define NETCMD_GET_WORKSTATUS_V30	0x111070	/* 获取工作状态 */
#define NETCMD_GET_FRAMEFORMAT  0x040200  	/* 获取交易信息 */
#define NETCMD_SET_FRAMEFORMAT  0x040201  	/* 设置交易信息 */
#define NETCMD_GET_FRAMEFORMAT_NEW  0x110080  	/* 获取交易信息 */
#define NETCMD_SET_FRAMEFORMAT_NEW  0x110081  	/* 设置交易信息 */


#define NETCMD_SET_PIPMODE		0x040400	/* 设置画中画模式 */
#define NETCMD_GETBMPBYTIME		0x090004	/* 按时间抓BMP图 */
#define NETCMD_MAKEIFRAME		0x090100	/* 强制I帧编码 */
#define NETCMD_MAKESUBIFRAME	0x090101	/* 强制I帧编码 */

#ifdef USEIMG
#define NETCMD_GET_FTPCFG				0x020002		/*获取图片上传FTP参数	*/
#define NETCMD_SET_FTPCFG				0x020003		/*设置图片上传FTP参数*/
#define NETCMD_GET_JPEGCFG			0x020004		/*获取图片参数	*/
#define NETCMD_SET_JPEGCFG			0x020005		/*设置图片参数*/
#define NETCMD_GET_JPEGPICTURE_EX				0x03000a		/*触发jpeg抓图*/
#endif

#define NETCMD_GET_JPEGPICTURE			0x030009		/*抓JPEG图像*/

#ifdef VIDEO_SWITCH
#define NETCMD_VIDEO_SWITCH 0x090909 /* 切换5150的输入 */
#endif

#define NETCMD_FINDFILE_EVENTSEARCH	0x090413	/*事件搜索接口*/
#define NETCMD_GET_RTSPCFG      0x020c02
#define NETCMD_SET_RTSPCFG	    0x020c03
#define NETCMD_GET_RTSPPORT     0x020c04

#ifdef SUPPORT_SNMP
#define DVR_GET_SNMPCFG_V30       0x1110d7         //获取SNMPv30参数 
#define DVR_SET_SNMPCFG_V30       0x1110d8         //获取SNMPv30参数 
#define NETCMD_GET_SNMPCFG      0x1110d5 // get net app cfg, snmp
#define NETCMD_SET_SNMPCFG      0x1110d6 // set net app cfg, snmp
#endif




/* define status that return to client */
#define NETRET_QUALIFIED		1
#define NETRET_EXCHANGE			2
#define NETRET_ERRORPASSWD		3
#define NETRET_LOWPRI			4
#define NETRET_OPER_NOPERMIT	5
#define NETRET_VER_DISMATCH		6
#define NETRET_NO_CHANNEL		7
#define NETRET_NO_SERIAL		8
#define NETRET_NO_ALARMIN		9
#define NETRET_NO_ALARMOUT		10
#define NETRET_NO_DISK			11
#define NETRET_NO_HARDDISK		12
#define NETRET_NOT_SUPPORT		13
#define NETRET_ERROR_DATA		14
#define NETRET_CHAN_ERROR		15
#define NETRET_DISK_ERROR		16
#define NETRET_CMD_TIMEOUT		17
#define NETRET_MAXLINK			18
#define NETRET_NEEDRECVHEADER	19
#define NETRET_NEEDRECVDATA		20
#define NETRET_NEEDRECVDATA_V30	104
#define NETRET_IPCCFG_CHANGE	105
#define NETRET_IPCCFG_CHANGE_V31 106
#define NETRET_KEEPAUDIOTALK    NETRET_EXCHANGE
#define NETRET_RECVKEYDATA      90       /* SETPOS后接收发过来的是关键帧数据（往前找I帧）*/
#define NETRET_RECVSETPOSDATA   91       /* SETPOS后接收改变位置后实际位置的数据 */
#define NETRET_SAME_USER              49
#define NETRET_DEVICETYPE_ERROR        50 /*导入参数时设备型号不匹配*/
#define NETRET_LANGUAGE_ERROR           51 /*导入参数时语音不匹配*/
#define NETRET_PARAVERSION_ERROR      52/*导入参数时软件版本不匹配*/
#define NETRET_IPC_NOTCONNECT      	    53/*IPC不在线*/
/*去除NETRET_720P_SUB_NOTSUPPORT, 需要时返回 NETRET_NOT_SUPPORT*/
//#define NETRET_720P_SUB_NOTSUPPORT         54/*720P 子码流不支持*/
#define NETRET_IPC_COUNT_OVERFLOW      	54	/*IPC总数溢出*/
#define NETRET_EMAIL_TEST_ERROR			55	/*邮件测试失败 9000_1.1*/

#define NETRET_PLAY_END			21
#define NETRET_WRITEFLASHERROR	22
#define NETRET_UPGRADE_FAILED	23
#define NETRET_UPGRADING		24
#define NETRET_NEEDWAIT			25
#define NETRET_FILELISTOVER		26
#define NETRET_RECVFILEINFO		27
#define NETRET_FORMATING		28
#define NETRET_FORMAT_END		29
#define NETRET_NO_USERID		30
#define NETRET_EXCEED_MAX_USER	31
#define NETRET_DVR_NO_RESOURCE	32
#define NETRET_DVR_OPER_FAILED	33		/* operation failed */
#define NETRET_IP_MISMATCH		34
#define NETRET_SOCKIP_MISMATCH	35
#define NETRET_MAC_MISMATCH		36
#define NETRET_ENC_NOT_STARTED	37
#define NETRET_LANG_MISMATCH	38		/* 升级时语言不匹配 */
#define NETRET_NEED_RELOGIN		39		/* 需要进行密码/用户名二次认证 */
#define NETRET_HD_READONLY			48
#ifdef NET3G_SDK
#define NETRET_ALREADYLOGON     101    /* 设备已经注册到CMS */
#define NETRET_ADDR_ALREADYUSED 102     /* udp预览地址重叠 */
#define	NETRET_SNDALARM_GPS	140         /* GPS报警上传信息 */
#define NETRET_SNDALARM_3GPICINFO    141 /* 图片上传 */
#define NETRET_NEEDRECVPUSHALARMDATA 142    /* 推模式设备基本报警信息上传 */
#define	NETRET_NEEDRECVPUSHALARMDATA_V30   143 /* 推模式设备基本报警信息上传 */
#endif

#define NETRET_NET_OVERFLOW       800    /*网络流量超过设别能力上限*/

/*
 * ====================================================================================
 *									 net data struct
 * ====================================================================================
 */
typedef struct{
    UINT32  length;             /* total length */
    UINT8   ifVer;              /* version: 90 -- new interface/60 -- old interface */	
	UINT8   ipVer;
	UINT8	byRetVal;			/* 最高位表示命令类型，REQUEST(0)，RESPONSE(1)，其余7位保留 */
	UINT8	res1[1];			/* just used in RESPONSE */
    UINT32  checkSum;           /* checksum */
    UINT32  netCmd;             /* client request command */
    UINT32  clientIp;           /* clinet IP address */
    UINT32  userID;             /* user ID */
    UINT8   clientMac[6];
    UINT8   res[2];
    struct in6_addr clientIp6;
}NETCMD_HEADER_V6;

#ifdef SUPPORT_IPV6
typedef struct{
    UINT32  length;             /* total length */
    UINT8   ifVer;              /* version: 90 -- new interface/60 -- old interface */	
	UINT8   ipVer;
	UINT8	byRetVal;			/* 最高位表示命令类型，REQUEST(0)，RESPONSE(1)，其余7位保留 */
	UINT8	res1[1];			/* just used in RESPONSE */
    UINT32  checkSum;           /* checksum */
    UINT32  netCmd;             /* client request command */
    UINT32  clientIp;           /* clinet IP address */
    UINT32  userID;             /* user ID */
    UINT8   clientMac[6];
    UINT8   res[2];
    struct in6_addr clientIp6;
}NETCMD_HEADER;

typedef struct{
	UINT32 	length;				/* total length */
	UINT8  	ifVer;				/* version: 90 -- new interface/60 -- old interface */
	UINT8   ipVer;
	UINT8	byRetVal;			/* 最高位表示命令类型，REQUEST(0)，RESPONSE(1)，其余7位保留 */
	UINT8	res1[1];
	UINT32	checkSum;			/* checksum */
	UINT32	netCmd;				/* client request command */
	UINT32	clientIp;			/* clinet IP address */
	UINT32	userID;				/* user ID */
	UINT8	clientMac[6];
	UINT8	res[2];
}NETCMD_HEADER_V4;

#else
typedef struct{
	UINT32 	length;				/* total length */
	UINT8  	ifVer;				/* version: 90 -- new interface/60 -- old interface */
	#ifdef NET3G_SDK
	UINT8	byCmdType;			/* 最高位表示命令类型，REQUEST(0)，RESPONSE(1)，其余7位保留 */
	UINT8	byRetVal;			/* just used in RESPONSE */
	UINT8	res1[1];
	#else
	UINT8	res1[3];
	#endif
	UINT32	checkSum;			/* checksum */
	UINT32	netCmd;				/* client request command */
	UINT32	clientIp;			/* clinet IP address */
	UINT32	userID;				/* user ID */
	UINT8	clientMac[6];
	UINT8	res[2];
}NETCMD_HEADER;//32

#endif

typedef struct{
	NETCMD_HEADER header;
	UINT32 channel;
}NETCMD_CHAN_HEADER;

typedef struct{
	UINT8	startHour;
	UINT8	startMin;
	UINT8	stopHour;
	UINT8	stopMin;
}NETPARAM_TIMESEG;

//返回给客户端状态的头 
typedef struct{
	UINT32	length;
	UINT32	checkSum;
	UINT32	retVal;
	UINT8	res[4];
}NETRET_HEADER;
#ifndef SUPPORT_IPV6
//login
typedef struct{
	UINT32 	length;
	UINT8	ifVer;
	UINT8	res1[3];
	UINT32	checkSum;
	UINT32	netCmd;
	UINT32	version;
	UINT8	res2[4];
	UINT32	clientIp;
	UINT8	clientMac[6];
	UINT8	res3[2];
	UINT8	username[NAME_LEN];
	UINT8	password[PASSWD_LEN];
}NET_LOGIN_REQ;
#else
//login
typedef struct{
	UINT32 	length;
	UINT8	ifVer;
	UINT8	res1[3];
	UINT32	checkSum;
	UINT32	netCmd;
	UINT32	version;
	UINT8	res2[4];
	UINT32	clientIp;
	UINT8	clientMac[6];
	UINT8	res3[2];
}NET_LOGIN_REQ;

typedef struct{
    UINT32  length;
    UINT8   ifVer;
    UINT8   ipVer;   /*0: IPv4; 1:IPv6*/
    UINT8   res1[2];
    UINT32  checkSum;
    UINT32  netCmd;
    UINT32  version;
    UINT8   res2[4];
    UINT32  clientIp;
    UINT8   clientMac[6];
    UINT8   res3[2];
    struct in6_addr clientIp6;
}NET_LOGIN_REQ_V6;

#endif




typedef struct{
	UINT32	length;
	UINT32	checkSum;
	UINT32	retVal;
	UINT32  devSdkVer;
	UINT32	userID;
	UINT8	serialno[SERIALNO_LEN];//68
	UINT8	devType;
	UINT8	channelNums;
	UINT8	firstChanNo;
	UINT8	alarmInNums;
	UINT8	alarmOutNums;
	UINT8	hdiskNums;
	UINT8   	supportProtocols;/*加支持的预览协议类型，按位*/
	UINT8	audioChanNums;/*语音对讲通道个数*/
	UINT8      maxIpcChanNums;/*设备支持的最大IPC个数*/
//#ifdef DVS65
	UINT8	subProto;
	UINT8	zeroChanNum; 		/* 零通道编码个数 */
	UINT8   support;	/*支持能力*/
						/*support & 0x1, 表示是否支持智能搜索*/
						/*support & 0x2, 表示是否支持备份*/
						/*support & 0x4, 表示是否支持压缩参数能力获取*/
						/*support & 0x8, 表示是否支持双网卡*/
    UINT8   support1;	//support1 & 0x1，表示是否支持snmp v30
	UINT8	res[27];
//#else
//	UINT8      res[31];
//#endif
}NET_LOGIN_RET;

typedef struct {
		UINT32	length;			/* 返回数据总长度 */
		UINT32  checkSum;		/* 数据校验和 */
		UINT32  retVal;			/* 返回状态，特定的标识表示是9000设备 */
		UINT32  devSdkVer;
		UINT8	challenge[60];	/* BASE64加密之后的挑战串 */
} NET_LOGIN_CHALLENGE;


#ifdef RTSP
typedef struct 
{
	UINT32	length;
	UINT16  rtspPort;/*RTSP协议端口,默认是554*/	
	UINT8	res[54];
} NETPARAM_RTSP_CFG;
#endif

//device parameter
typedef struct{
	UINT32 	length;
	UINT8	DVRName[NAME_LEN];
	UINT32	deviceID;
	UINT32	recycleRecord;
	UINT8	serialno[SERIALNO_LEN];
	UINT32	softwareVersion;
	UINT32	softwareBuildDate;
	UINT32	dspSoftwareVersion;
	UINT32	dspSoftwareBuildDate;
	UINT32	panelVersion;
	UINT32	hardwareVersion;
	UINT8	alarmInNums;
	UINT8	alarmOutNums;
	UINT8	rs232Nums;
	UINT8	rs485Nums;
	UINT8	netIfNums;
	UINT8	hdiskCtrlNums;
	UINT8	hdiskNums;
	UINT8	devType;
	UINT8	channelNums;
	UINT8	firstChanNo;
	UINT8	decodeChans;
	UINT8	vgaNums;
	UINT8	usbNums;
	UINT8	auxOutNum;
	UINT8	audioNum;
	UINT8 	ipChanNum;
}NETPARAM_DEVICE_CFG;


typedef struct{
    UINT32  length;
    UINT8   DVRName[NAME_LEN];
    UINT32  deviceID;
    UINT32  recycleRecord;
    UINT8   serialno[SERIALNO_LEN];
    UINT32  softwareVersion;
    UINT32  softwareBuildDate;
    UINT32  dspSoftwareVersion;
    UINT32  dspSoftwareBuildDate;
    UINT32  panelVersion;
    UINT32  hardwareVersion;
    UINT8   alarmInNums;
    UINT8   alarmOutNums;
    UINT8   rs232Nums;
    UINT8   rs485Nums;
    UINT8   netIfNums;
    UINT8   hdiskCtrlNums;
    UINT8   hdiskNums;
    UINT8   devType;
    UINT8   channelNums;
    UINT8   firstChanNo;
    UINT8   decodeChans;
    UINT8   vgaNums;
    UINT8   usbNums;
    UINT8   auxOutNum;
    UINT8   audioNum;
    UINT8   ipChanNum;
    UINT8   zeroChanNum;        /* 零通道编码个数 */
    UINT8   supportAbility;     /* 能力，位与结果为0表示不支持，1表示支持，
                                 supportAbility & 0x1, 表示是否支持智能搜索
                                supportAbility & 0x2, 表示是否支持一键备份
                                supportAbility & 0x4, 表示是否支持压缩参数能力获取
                                supportAbility & 0x8, 表示是否支持双网卡 
                                supportAbility & 0x10, 表示支持远程SADP 
                                supportAbility & 0x20  表示支持Raid功能*/
    
    UINT8   bESataFun;          /* eSATA的默认用途，0-默认录像，1-默认备份 */
    UINT8   bEnableIPCPnp;      /* 0-不支持即插即用，1-支持即插即用 */
	
    UINT8 byStorageMode; //0-盘组模式,1-磁盘配额
    UINT8 bySupport1;   //能力，位与结果为0表示不支持，1表示支持
                        //bySupport1 & 0x1, 支持 SNMP v30
                        //bySupport1 & 0x2, 支持区分回放和下载
    UINT16 wDevType;//设备型号
    UINT8  byDevTypeName[24];//设备型号名称 
    UINT8  res[16]; //保留
}NETPARAM_DEVICE_CFG_V40;



/*
	IP地址：包括IPv4和IPv6格式的地址
*/
typedef struct
{		/* 24 bytes */
	struct in_addr	v4;							/* IPv4地址 */
	struct in6_addr	v6;							/* IPv6地址 */
	UINT8			res[4];
}U_IN_ADDR;


//NETPARAM_ETHER_CFG
#define MACADDR_LEN  6
typedef struct{
	U_IN_ADDR devIp;
	U_IN_ADDR devIpMask;
	UINT32	mediaType;		/* network interface type */
	UINT16	ipPortNo;		/* command port */
	UINT16  mtu;            /*MTU*/
	UINT8	macAddr[MACADDR_LEN];
	UINT8	res2[2];
}NETPARAM_ETHER_CFG_NEW;



//NETPARAM_PPPOE_CFG
typedef struct{
	UINT32 enablePPPoE;
	char PPPoEUser[NAME_LEN];
	char PPPoEPassword[PASSWD_LEN];
    char   res[4];
	U_IN_ADDR PPPoEIp;	
}NETPARAM_PPPOE_CFG;



//NETPARAM_NETWORK_CFG
typedef struct{
	UINT32	length;
	NETPARAM_ETHER_CFG_NEW etherCfg[MAX_ETHERNET];
	U_IN_ADDR manageHost1IpAddr;
	U_IN_ADDR manageHost2IpAddr;
	U_IN_ADDR alarmHostIpAddr;
	UINT16    manageHost1Port;
	UINT16    manageHost2Port;
	UINT16    alarmHostIpPort;
	UINT8	bUseDhcp;
	UINT8     res1[9];
	U_IN_ADDR dnsServer1IpAddr;
	U_IN_ADDR dnsServer2IpAddr;
	UINT8     ipResolver[MAX_DOMAIN_NAME];
	UINT16    ipResolverPort;
	UINT16    httpPortNo;
	UINT8     res2[4];
	U_IN_ADDR  multicastIpAddr;
	U_IN_ADDR  gatewayIpAddr;
	NETPARAM_PPPOE_CFG PPPoECfg;
	UINT8     res3[24];
}NETPARAM_NETWORK_CFG_V30;

typedef struct{
	UINT8	streamType;
	UINT8	resolution;
	UINT8	bitrateType;
	UINT8	quality;
	UINT32	maxBitRate;
	UINT32	videoFrameRate;
	UINT16  intervalFrameI;
	UINT8	BFrameNum;			/* B帧个数: 0:BBP, 1:BP, 2:P */
	UINT8   EFrameNum;
	UINT8   videoEncType;
	UINT8   audioEncType;
	UINT8   res[10];
}NETPARAM_COMP_PARA_V30;

typedef struct{
	UINT32	length;
	NETPARAM_COMP_PARA_V30 normHighCompPara;
	NETPARAM_COMP_PARA_V30 normLowCompPara;
	NETPARAM_COMP_PARA_V30 eventCompPara;
	NETPARAM_COMP_PARA_V30 netCompPara;
}NETPARAM_COMPRESS_CFG_V30;

//8000 network parameter 
typedef struct{
	UINT32	devIp;
	UINT32	devIpMask;
	UINT32	mediaType;		/* network interface type */
	UINT16	ipPortNo;		/* command port */
	UINT16	mtu;			/* MTU */
	UINT8	macAddr[6];
	UINT8	res2[2];
}NETPARAM_ETHER_CFG;

typedef struct{
	UINT32	length;
	NETPARAM_ETHER_CFG etherCfg[MAX_ETHERNET];
	UINT32	manageHostIp;
	UINT16	manageHostPort;
	UINT16	httpPort;
	UINT32	ipResolverIpAddr;
	UINT32	mcastAddr;
	UINT32	gatewayIp;
	UINT32	nfsIp;
	UINT8	nfsDirectory[PATHNAME_LEN];
	UINT32	bEnablePPPoE;
	UINT8	pppoeName[NAME_LEN];
	UINT8	pppoePassword[PASSWD_LEN];
	UINT8	res2[4];
	UINT32	pppoeIp;
}NETPARAM_NETWORK_CFG;

typedef struct{
	UINT32 	length;
	UINT8	ifVer;
	UINT8	res1[3];
	UINT32	checkSum;
	UINT32	netCmd;
	UINT8   rec[16];
	UINT32  cmd0;
	UINT32  cmd1;
}NET_CMD11000_REQ;


/*
 * ========================================================
 *			PIC_CFG	aparameter
 * ========================================================
 */
typedef struct{
	UINT32 		handleType;						/* 异常处理,异常处理方式的"或"结果 */
	UINT32		alarmOutTriggered;				/* 被触发的报警输出(此处限制最大报警输出数为32) */
}NETPARAM_EXCEPTION;

typedef struct{
	UINT32 		handleType;						/* 异常处理,异常处理方式的"或"结果 */
	UINT8		alarmOutTrigStatus[16];				/* 被触发的报警输出(此处限制最大报警输出数为32) */
}NETPARAM_EXCEPTION_V30;

/*
 * ========================================================
 *			 alarmIn parameter 
 * ========================================================
 */
typedef struct{
	UINT8		alarmInName[NAME_LEN];				/* 名称 */
	UINT8		sensorType;							/* 报警器类型：0为常开；1为常闭 */
	UINT8		bEnableAlarmIn;						/* 处理报警输入 */
	UINT8		res[2];
	NETPARAM_EXCEPTION alarmInAlarmHandleType;				/* 报警输入处理 */
	NETPARAM_TIMESEG armTime[MAX_DAYS][MAX_TIMESEGMENT_8000];	/* 布防时间段 */
	UINT8		recordChanTriggered[16];			/* 被触发的录像(此处限制最大通道数为128) */
	UINT8		bEnablePreset[MAX_CHANNUM_8000];			/* 是否调用预置点 */
	UINT8		presetNo[MAX_CHANNUM_8000];				/* 调用的云台预置点序号,一个报警输入可以调用
												   	   多个通道的云台预置点, 0xff表示不调用预置点。
												   	 */
	UINT8       bEnablePtzCruise[MAX_CHANNUM_8000];		/* 是否调用巡航 */
	UINT8		ptzCruise[MAX_CHANNUM_8000];				/* 巡航 */
	UINT8       bEnablePtzTrack[MAX_CHANNUM_8000];		/* 是否调用轨迹 */
	UINT8		trackNo[MAX_CHANNUM_8000];				/* 云台的轨迹序号(同预置点) */
}NETPARAM_ALARMIN;

typedef struct{
	UINT8		alarmInName[NAME_LEN];				/* 名称 */
	UINT8		sensorType;							/* 报警器类型：0为常开；1为常闭 */
	UINT8		bEnableAlarmIn;						/* 处理报警输入 */
	UINT8		res[2];
	NETPARAM_EXCEPTION_V30 alarmInAlarmHandleType;				/* 报警输入处理 */
	NETPARAM_TIMESEG armTime[MAX_DAYS][MAX_TIMESEGMENT];	/* 布防时间段 */
	UINT8		recordChanTriggered[16];			/* 被触发的录像(此处限制最大通道数为128) */
	UINT8		bEnablePreset[MAX_CHANNUM_V30];			/* 是否调用预置点 */
	UINT8		presetNo[MAX_CHANNUM_V30];				/* 调用的云台预置点序号,一个报警输入可以调用
												   	   多个通道的云台预置点, 0xff表示不调用预置点。
												   	 */
	UINT8		bEnablePresetRevert[MAX_CHANNUM_V30];	
	UINT16		presetRevertDelay[MAX_CHANNUM_V30];
	UINT8       bEnablePtzCruise[MAX_CHANNUM_V30];		/* 是否调用巡航 */
	UINT8		ptzCruise[MAX_CHANNUM_V30];				/* 巡航 */
	UINT8       bEnablePtzTrack[MAX_CHANNUM_V30];		/* 是否调用轨迹 */
	UINT8		trackNo[MAX_CHANNUM_V30];				/* 云台的轨迹序号(同预置点) */
}NETPARAM_ALARMIN_V30;

typedef struct{
	UINT32	length;
	NETPARAM_ALARMIN alarmIn;
}NETPARAM_ALARMIN_CFG;

typedef struct{
	UINT32	length;
	NETPARAM_ALARMIN_V30 alarmIn;
}NETPARAM_ALARMIN_CFG_V30;







typedef struct{
	BYTE brightness;
	BYTE contrast;
	BYTE saturation;
	BYTE tonality;
}NETPARAM_COLOR;

typedef struct
{
	NETPARAM_COLOR	  color[MAX_TIMESEGMENT];
	NETPARAM_TIMESEG  handleTime[MAX_TIMESEGMENT];
}NETPARAM_VICOLOR_V30;

typedef struct{
	UINT32 		enableSignalLostAlarm;
	NETPARAM_EXCEPTION_V30 signalLostAlarmHandleType;	/* 信号丢失处理 */
	NETPARAM_TIMESEG signalLostArmTime[MAX_DAYS][MAX_TIMESEGMENT];
}VI_SIGNAL_LOST_CFG_V30;

typedef struct{
	UINT8 	motionLine[64][12];
	UINT8	motionLevel;
	UINT8	bEnableHandleMotion;
	UINT8   precision;
	UINT8	res;
	NETPARAM_EXCEPTION_V30 motionHandleType;
	NETPARAM_TIMESEG motDetArmTime[MAX_DAYS][MAX_TIMESEGMENT];
	UINT8	motTriggerRecChans[16];
}NETPARAM_MOTDET_CFG_V30;

typedef struct{
	UINT32	bEnableMaskAlarm;
	UINT16	maskX;
	UINT16	maskY;
	UINT16	maskW;
	UINT16	maskH;
	NETPARAM_EXCEPTION_V30 maskAlarmHandleType;
	NETPARAM_TIMESEG maskAlarmArmTime[MAX_DAYS][MAX_TIMESEGMENT];
}NETPARAM_MASKALARM_CFG_V30;

#define MAX_MASK_REGION_NUM		4				/* 最大遮挡区域个数 */
/*
	坐标
*/
typedef struct
{		/* 4 bytes */
	UINT16	x;									/* 横坐标 */
	UINT16	y;									/* 纵坐标 */
} COORDINATE;

/*
	矩形区域
*/
typedef struct
{		/* 8 bytes */
	COORDINATE	upLeft;							/* 左上角坐标 */
	SIZE		size;							/* 大小(宽度和高度) */
} ZONE;

#define CHANNEL_MAIN			1				/*主口*/

//NETPARAM_PIC_CFG_V30
typedef struct{
	UINT32 	length;
	UINT8	chanName[NAME_LEN];
	UINT32	videoFormat;
	NETPARAM_VICOLOR_V30 viColor;
	UINT32	bShowChanName;
	UINT16	chanNameX;
	UINT16	chanNameY;
	VI_SIGNAL_LOST_CFG_V30		viLostCfg;
	VI_SIGNAL_LOST_CFG_V30		aiLostCfg;
	NETPARAM_MOTDET_CFG_V30 	motionCfg;
	NETPARAM_MASKALARM_CFG_V30	maskAlarmCfg;
	UINT32	bEnableHide;
	ZONE hideArea[MAX_MASK_REGION_NUM];
	UINT32	bShowOsd;
	UINT16	osdX;
	UINT16	osdY;
	UINT8	osdType;
	UINT8	bDispWeek;
	UINT8	osdAttrib;
	UINT8	hourOsdType;
	UINT8	res2[24];
}NETPARAM_PIC_CFG_V30;



//security.h
/* defines */
#define MAX_LOGIN_USERS		128		/* maximum logined user numbers */
#ifdef NET3G_SDK
#define REG_USER_MAX_CMS    	16
#define REG_USER_BASE_INDEX 	(MAX_LOGIN_USERS - REG_USER_MAX_CMS)
#endif
#define BASE_USER_ID			0x10000
#define KEEP_ALIVE_INTERVAL	(5*60)		/* logined user must send keep alive message */
#define CHECK_USER_INTERVAL	5		/* check user timeout at interval 5 seconds */
#define	NO_USER					(-1)
//#ifdef PSIA_PAD
#define PSIA_USER           	NO_USER
//#endif

#define	ACTUAL_MAX_NAME_LEN	32
#define LIMITED_NAME_LEN		LOG_NAME_LEN			/* Now we limit username length to 32 bytes */

/* user login return status */
#define INVALID_USER			0x1000
#define EXCEED_MAX_USER		0x1001
#define EMPTY_USER				0x1002
#define USER_NO_PERMISSION 	0x1003

/* typedefs */
typedef struct
{
	int 	userID;				/* user ID, DVR assign an exclusive ID when user login */
	int    	cfgUserID;			/*该userID对应于配置参数中的用户ID*/
	UINT8	userName[NAME_LEN];		/* user name */
	UINT32	permission;			/* permission */
	UINT64  localPrevPermission;	
	UINT64	netPrevPermission;			/* 远程预览通道 */
	UINT64	localPlayPermission;			/* 本地回放通道 */
	UINT64	netPlayPermission;			/* 远程回放通道 */
	UINT64	localRecordPermission;		/* 本地回放通道 */
	UINT64	netRecordPermission;		/* 远程回放通道 */
	UINT64	localPtzCtrlPermission;		/* 本地回放通道 */
	UINT64	netPtzCtrlPermission;		/* 远程回放通道 */
	UINT64	localBackupPermission;		/* 本地回放通道 */
	UINT32	priority;
	BOOL	bLocalUser;			/* local user or network user */
	time_t	loginTime;			/* timer of user login */
	time_t	expireTime;			/* client should send a 'keepalive' at intervals of 'KEEP_ALIVE_INTERVAL' seconds when idle */	
#ifndef SUPPORT_IPV6
	struct in_addr peerClientIp;		/* peer's IP address get from client program */
	struct in_addr peerSocketIp;		/* peer's Ip address get form socket accept() */
#else
	U_IN_ADDR peerClientIp; 	/* peer's IP address get from client program */
	U_IN_ADDR peerSocketIp; 	/* peer's Ip address get form socket accept() */
#endif
//	struct in_addr peerClientIp;		/* peer's IP address get from client program */
//	struct in_addr peerSocketIp;		/* peer's Ip address get form socket accept() */
	UINT16  persistOpNums;			/* persistent operation(e.g. preview, download file) numbers of this user */
	char	peerMacAddr[MACADDR_LEN];	/* peer's MAC address */
	UINT32 	sdkVersion;			/* SDK version of network user */
}USER_INFO;


#endif


