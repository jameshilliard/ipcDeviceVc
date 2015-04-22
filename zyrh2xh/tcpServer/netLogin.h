#ifndef _INCnetCommandNetLogin_h
#define _INCnetCommandNetLogin_h

#include "./DeviceCommProtocol.h"
#include "./netUtil.h"



#define 	SerialNo			"ZY20141120CCCH490402389"
#define 	DevType				0	
#define 	DevName				"IPCAMERA"
#define 	ChannelNums		1
#define  	FirstChanNo		1
#define 	AlarmInNums		1
#define 	AlarmOutNums   	1
#define 	HdiskNums			0
#define 	SupportProtocols  0xF0
#define 	AudioChanNums		1
#define 	MaxIpcChanNums		0
#define 	SubProto			0
#define 	ZeroChanNum		0
#define 	Support0			0x80
#define		Support1			0x0

UINT32 checkByteSum(char *pBuf, int len);
STATUS challenge_login(StreamSocket  &connfd, NET_LOGIN_REQ *reqdata, int *userid,struct sockaddr_in *pClientSockAddr);

#endif


