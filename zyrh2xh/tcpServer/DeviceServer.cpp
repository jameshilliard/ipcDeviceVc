//
// DeviceServer.cpp
//
// $Id: //poco/1.4/Net/samples/DeviceServer/src/DeviceServer.cpp#1 $
//
// This sample demonstrates the TCPServer and ServerSocket classes.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//
#include "DeviceServer.h"
#include "./DeviceCommFuncs.h"
#include "../rtspServer/H264LiveVideoServerMediaSubssion.hh"
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"

#define BUFSIZE 1024*1024*1

Poco::Mutex _mutex;

void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,char const* streamName)//显示RTSP连接信息
{
	char* url = rtspServer->rtspURL(sms);
	UsageEnvironment& env = rtspServer->envir();
	env <<streamName<< "\n";
	env << "Play this stream using the URL \"" << url << "\"\n";
	delete[] url;
}

DeviceServerConnection::DeviceServerConnection(const StreamSocket& s): 
	TCPServerConnection(s)
{

}
void DeviceServerConnection::run()
{
	int  cmdLength=0;
	char buffer[BUFFER_SIZE];
	int iRet =socket().receiveBytes(&cmdLength, sizeof(cmdLength));
	cmdLength=ntohl(cmdLength);
	NET_INFO(("receive size is %d cmdLength is %d\n",iRet,cmdLength));
	if(iRet==sizeof(cmdLength))
	{
		iRet = socket().receiveBytes(buffer+sizeof(cmdLength),cmdLength-4);
		memcpy(buffer,&cmdLength,sizeof(cmdLength));
		iRet = reloveOnePacket(socket(),buffer,cmdLength);
		NET_INFO(("reloveOnePacket is %d\n",iRet));
	}
	socket().shutdownSend();
}
	
DeviceServerConnectionFactory::DeviceServerConnectionFactory()
{

}

TCPServerConnection* DeviceServerConnectionFactory::createConnection(const StreamSocket& socket)
{
	return new DeviceServerConnection(socket);
}

DeviceServer::DeviceServer(int port,int rtspPort,std::string userName,std::string secret):_commServerActivity(this, &DeviceServer::runCommServerActivity),_rtspServerActivity(this, &DeviceServer::runRtspServerActivity)
{
	commServerPort=port;
	rtspServerPort=rtspPort;
	m_userName=userName;
	m_secret=secret;
}

DeviceServer::~DeviceServer()
{

}

void DeviceServer::setSdkServerData(SDKServerData sSDKserverData)
{
	m_sdkServerData=sSDKserverData;
}


void DeviceServer::start()
{
	_commServerActivity.start();
	_rtspServerActivity.start();
}

void DeviceServer::stop()
{
	_commServerActivity.stop();
	_commServerActivity.wait();
	_rtspServerActivity.stop();
	_rtspServerActivity.wait();
}

void DeviceServer::runCommServerActivity()
{
	std::cout << "commServer start." << std::endl;
	TCPServer srv(new DeviceServerConnectionFactory(),commServerPort);
	// start the TCPServer
	srv.start();
	while (!_commServerActivity.isStopped())
	{
		std::cout << "commServer running." << std::endl;
		//this->run();
		Thread::sleep(5000);
	}
	//srv.stop();
	std::cout << "commServer stopped." << std::endl;
}


int DeviceServer::startRtspServer(int rtspServerPort) 
{
	if(rtspServerPort<0)
		return -1;
	//设置环境
	UsageEnvironment* env;
	OutPacketBuffer::maxSize = 1000000; // allow for some possibly large H.264 frames
	Boolean reuseFirstSource = False;//如果为“true”则其他接入的客户端跟第一个客户端看到一样的视频流，否则其他客户端接入的时候将重新播放
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	env = BasicUsageEnvironment::createNew(*scheduler);

	//创建RTSP服务器
	UserAuthenticationDatabase* authDB = NULL;
	RTSPServer* rtspServer = RTSPServer::createNew(*env, rtspServerPort, authDB);
	if (rtspServer == NULL) {
		*env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
		exit(1);
	}
	char const* descriptionString= "Session streamed by \"testOnDemandRTSPServer\"";

#if 0
	//模拟实时流发送相关变量
	int datasize;//数据区长度
	unsigned char*  databuf;//数据区指针
	databuf = (unsigned char*)malloc(BUFSIZE);
	bool dosent;//rtsp发送标志位，为true则发送，否则退出
	Mutex::ScopedLock lock(_mutex);
	//从文件中拷贝1M数据到内存中作为实时网络传输内存模拟，如果实时网络传输应该是双线程结构，记得在这里加上线程锁
	//此外实时传输的数据拷贝应该是发生在H264FramedLiveSource文件中，所以这里只是自上往下的传指针过去给它
	FILE *pf;
	fopen_s(&pf, "./test.264", "rb");
	fread(databuf, 1, BUFSIZE, pf);
	datasize = BUFSIZE;
	dosent = true;
	fclose(pf);
	_mutex.unlock();
#endif

 	H264FrameDeviceSource * nH264FrameDeviceSource = new H264FrameDeviceSource(m_sdkServerData);

	//上面的部分除了模拟网络传输的部分外其他的基本跟live555提供的demo一样，而下面则修改为网络传输的形式，为此重写addSubsession的第一个参数相关文件
	char const* streamName = "ch1/main/av_stream";
	ServerMediaSession* sms = ServerMediaSession::createNew(*env, streamName, streamName,descriptionString);
	sms->addSubsession(H264LiveVideoServerMediaSubssion::createNew(*env, reuseFirstSource,nH264FrameDeviceSource));//修改为自己实现的H264LiveVideoServerMediaSubssion
	rtspServer->addServerMediaSession(sms);
	announceStream(rtspServer, sms, streamName);//提示用户输入连接信息
	while(1)
	{
		try
		{		
			env->taskScheduler().doEventLoop(); //循环等待连接
		}
		catch(...)
		{
			printf("CException--\n");
		}
		Sleep(1000);
	}
	//free(databuf);//释放掉内存
	return 0;
}

void DeviceServer::runRtspServerActivity()
{
	std::cout << "rtspServer start."<<rtspServerPort<< std::endl;
	while (!_rtspServerActivity.isStopped())
	{
		std::cout << "rtspServer running." << std::endl;
		startRtspServer(rtspServerPort);
		Thread::sleep(5000);
	}
	
	std::cout << "rtspServer stopped."<<rtspServerPort << std::endl;
}


#if 0
void DeviceServer::initialize(Application& self)
{
	loadConfiguration();
	ServerApplication::initialize(self);
}
	
void DeviceServer::uninitialize()
{
	ServerApplication::uninitialize();
}

int DeviceServer::main(const std::vector<std::string>& args)
{
	ServerSocket svs(commServerPort);
	TCPServer srv(new DeviceServerConnectionFactory(), svs);
	// start the TCPServer
	srv.start();
	// wait for CTRL-C or kill
	waitForTerminationRequest();
	// Stop the TCPServer
	srv.stop();
	return Application::EXIT_OK;
}
#endif


