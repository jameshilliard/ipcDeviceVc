#ifndef _H264_LIVE_VIDEO_SERVER_MEDIA_SUBSESSION_HH
#define _H264_LIVE_VIDEO_SERVER_MEDIA_SUBSESSION_HH

#include "H264VideoFileServerMediaSubsession.hh"
#include "H264FramedLiveSource.hh"
#include "H264VideoStreamFramer.hh"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"lib\\libBasicUsageEnvironment.lib")
#pragma comment(lib,"lib\\libgroupsock.lib")
#pragma comment(lib,"lib\\libliveMedia.lib")
#pragma comment(lib,"lib\\libUsageEnvironment.lib")


class H264LiveVideoServerMediaSubssion : public H264VideoFileServerMediaSubsession {

public:
	static H264LiveVideoServerMediaSubssion* createNew(UsageEnvironment& env, Boolean reuseFirstSource,H264FrameDeviceSource *ptH264FrameDeviceSource);

protected: // we're a virtual base class
	H264LiveVideoServerMediaSubssion(UsageEnvironment& env, Boolean reuseFirstSource,H264FrameDeviceSource *ptH264FrameDeviceSource);
	~H264LiveVideoServerMediaSubssion();

protected: // redefined virtual functions
	FramedSource* createNewStreamSource(unsigned clientSessionId,unsigned& estBitrate);
public:
	H264FrameDeviceSource *m_ptH264FrameDeviceSource;
	char fFileName[100];
	//int Server_datasize;//数据区大小指针
	//unsigned char  *Server_databuf;//数据区指针
	//bool Server_dosent;//发送标示
};


#endif
