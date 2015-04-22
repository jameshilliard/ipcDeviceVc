// HaiKangTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <string>



char* videobuf = new char[1024*1024];


std::string sServerIp;
std::string sDevID;
std::string sSession;
std::string sLocalIp;
unsigned int nServerPort;
int _tmain()
{

	char buf[1000];
	int i=1000; 

	GetCurrentDirectory(1000,buf);   //得到当前工作路径 
    std::string path = buf;
	path += "/config.ini";


	GetPrivateProfileString("DevInfo","ServerIp","",buf,256,path.c_str());
	sServerIp = buf;

	GetPrivateProfileString("DevInfo","DevID","",buf,256,path.c_str());
	sDevID = buf;

	GetPrivateProfileString("DevInfo","LocalIP","",buf,256,path.c_str());
	sLocalIp = buf;


	GetPrivateProfileString("DevInfo","Session","",buf,256,path.c_str());
	sSession = buf;

	nServerPort = GetPrivateProfileInt("DevInfo","ServerPort",0,path.c_str());
// 	pTcpClient = new CTcpClient;
// 	pUdpClient = new CUdpClient;
// 	pUdpClient->ConnectServer(sServerIp.c_str(),nServerPort);
// 	cmd_register sRegister("PU",sDevID.c_str(),"123456","1.0.0.1",
// 		sLocalIp.c_str(), "7660", "255.255.255.0", "1","1");
// 	pUdpClient->SendXml(&sRegister);
	 


	while(1)
	{
		Sleep(10);
	}

	return 0;
}

