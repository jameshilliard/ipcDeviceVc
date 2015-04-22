#ifndef _INNetUtil_h
#define _INNetUtil_h
#include "./DeviceCommProtocol.h"
#include <time.h>
#ifdef WIN32
#   include <windows.h>
#else
#   include <sys/time.h>
#endif



#ifdef WIN32
int gettimeofday(struct timeval *tp, void *tzp);
#endif
void 	bzero(char  *buffer,  /* buffer to be zeroed*/int   nbytes  /* number of bytes in buffer */ );
int 	get_peer_name(int fd, struct sockaddr_in *peer);
void 	convertNetLoginReqByteOrder(NET_LOGIN_REQ *pLoginReq);
void 	convertNetCmdHeaderByteOrder(NETCMD_HEADER *pHeader);


#endif
