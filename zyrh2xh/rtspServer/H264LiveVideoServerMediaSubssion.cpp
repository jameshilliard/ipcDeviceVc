#include "H264LiveVideoServerMediaSubssion.hh"


H264LiveVideoServerMediaSubssion* H264LiveVideoServerMediaSubssion::createNew(UsageEnvironment& env, Boolean reuseFirstSource, H264FrameDeviceSource *ptH264FrameDeviceSource)
{
	return new H264LiveVideoServerMediaSubssion(env, reuseFirstSource,ptH264FrameDeviceSource);
}

H264LiveVideoServerMediaSubssion::H264LiveVideoServerMediaSubssion(UsageEnvironment& env, Boolean reuseFirstSource,H264FrameDeviceSource *ptH264FrameDeviceSource)
: H264VideoFileServerMediaSubsession(env, fFileName, reuseFirstSource)//H264VideoFileServerMediaSubsession不是我们需要修改的文件，
																	  //但是我们又要用它来初始化我们的函数，
																	  //所以给个空数组进去即可
{
	//Server_datasize = datasize;//数据区大小指针
	//Server_databuf = databuf;//数据区指针
	//Server_dosent = dosent;//发送标示
	m_ptH264FrameDeviceSource=ptH264FrameDeviceSource;
}


H264LiveVideoServerMediaSubssion::~H264LiveVideoServerMediaSubssion()
{
	m_ptH264FrameDeviceSource=NULL;
}

FramedSource* H264LiveVideoServerMediaSubssion::createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate)
{
	/* Remain to do : assign estBitrate */
	estBitrate = 1000; // kbps, estimate
	
	//创建视频源
	H264FramedLiveSource* liveSource = H264FramedLiveSource::createNew(envir(),m_ptH264FrameDeviceSource);
	if (liveSource == NULL)
	{
		return NULL;
	}

	// Create a framer for the Video Elementary Stream:
	return H264VideoStreamFramer::createNew(envir(), liveSource);
}