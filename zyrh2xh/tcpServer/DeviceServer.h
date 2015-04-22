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
#include "../rtspServer/H264FramedLiveSource.hh"
#include <iostream>

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Activity.h"
#include "Poco/Thread.h"
#include "Poco/Mutex.h"

using Poco::Activity;
using Poco::Thread;
using Poco::Net::ServerSocket;
using Poco::Net::StreamSocket;
using Poco::Net::TCPServerConnection;
using Poco::Net::TCPServerConnectionFactory;
using Poco::Net::TCPServer;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Mutex;



/*net client debug define*/
#define NET_INFO(x)  printf x
#define NET_ERR(x)   printf x
#define NET_FATAL(x) printf x


class DeviceServerConnection: public TCPServerConnection
{
public:
	DeviceServerConnection(const StreamSocket& s);
	void run();
	
};

class DeviceServerConnectionFactory: public TCPServerConnectionFactory
{
public:
	DeviceServerConnectionFactory();
	TCPServerConnection* createConnection(const StreamSocket& socket);
};

class DeviceServer//: public Poco::Util::ServerApplication
{
public:;
	DeviceServer();
	DeviceServer(int port,int rtspPort,std::string userName,std::string secret);
	~DeviceServer();
	void setSdkServerData(SDKServerData sSDKserverData);
	void start();
	void stop();
	
public:
	void runCommServerActivity();
	void runRtspServerActivity();
	#if 0
	void initialize(Application& self);
	void uninitialize();
	int  main(const std::vector<std::string>& args);
	#endif

public:
	int startRtspServer(int rtpServerPort);
	Activity<DeviceServer> _commServerActivity;
	Activity<DeviceServer> _rtspServerActivity;
	

	SDKServerData 			m_sdkServerData;
	int 					commServerPort;
	int 					rtspServerPort;
	std::string 			m_userName;
	std::string 			m_secret;
};