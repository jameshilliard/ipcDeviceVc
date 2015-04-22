#ifndef _INCnetCommandFuncs_h
#define _INCnetCommandFuncs_h

#include "./DeviceCommProtocol.h"
#include "./netUtil.h"

using Poco::Net::StreamSocket;
using Poco::FIFOBuffer;

enum
{
	BUFFER_SIZE = 1024*128
};

STATUS netClientLogin(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientLogout(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);

STATUS netClientReLogin(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientUserExchange(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientGetNetCfgV30(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientGetRtspPort(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientGetDeviceCfgV40(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientGetDeviceCfg(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientGetCompressCfgV30(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientGetNetCfg(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientReloveCmd11000(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientSetDevTime(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientGetPicCfgV30(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientGetAlarmInCfgV30(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS netClientRestoreCfg(StreamSocket  &connfd, char *recvbuff, struct sockaddr_in *pClientSockAddr);
STATUS relovePacket(StreamSocket  &connfd,FIFOBuffer &fifoBuffer);
STATUS reloveOnePacket(StreamSocket  &connfd,char *fifoBuffer,UINT32 length);

#endif
