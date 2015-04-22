
#include "../stdafx.h"
#include "../tinyxml/xmlCmd.h"
#include "TcpClient.h"
#include "Sendbuffer.hpp"
#include "../global.h"
#include "../devsdk/DevSdk.h"
#include "../Logger.h"


CTcpClient::CTcpClient() {
	bConnect = false;
	m_hSocket = NULL;
	WSADATA wsaData;
	WSAStartup(0x202, &wsaData);
	m_bStop = false;
// 	m_hRecvThread.reset(new boost::thread(
// 		boost::bind(&CTcpClient::ReceiveHandle, this)));
	m_hHeartThread.reset(new boost::thread(
		boost::bind(&CTcpClient::HeartHandle, this)));
	m_pDevSdk = NULL;
	
}


CTcpClient::~CTcpClient() {
	WSACleanup();
}

bool CTcpClient::ConnectServer(const char *ip,int port)
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	m_sIp = ip;
	m_nPort = port;
	int ret;
	LPHOSTENT lpHost;	
	struct sockaddr_in server;	
	if (m_hSocket != NULL) {
		shutdown(m_hSocket,SD_BOTH);
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	lpHost = gethostbyname(ip);
	if(lpHost == NULL) return FALSE;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = *((u_long FAR *)(lpHost->h_addr));
	server.sin_port=htons(port);

	ret = connect(m_hSocket, (LPSOCKADDR)&server, sizeof(SOCKADDR));
	g_logInfo.Write2Caching("ConnectServer 设备ID:%s %s:%d ret:%d",m_sDevID.c_str(),ip,port,ret);

	if (ret < 0) {
		return false;
	}
	if(!bConnect){
		bConnect = true;
	
	}
	m_bStop = false;
	m_hRecvThread.reset(new boost::thread(
		boost::bind(&CTcpClient::ReceiveHandle, this)));
	return true;
}
bool CTcpClient::ReConnectServer()
{
	if (m_sIp == "")
	{
		return false;
	}
	int ret;
	LPHOSTENT lpHost;	
	struct sockaddr_in server;	
	if (m_hSocket != NULL) {
		closesocket(m_hSocket);
		m_hSocket = NULL;
	}
	m_hSocket = socket(AF_INET, SOCK_STREAM, 0);
	lpHost = gethostbyname(m_sIp.c_str());
	if(lpHost == NULL) return FALSE;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = *((u_long FAR *)(lpHost->h_addr));
	server.sin_port=htons(m_nPort);

	ret = connect(m_hSocket, (LPSOCKADDR)&server, sizeof(SOCKADDR));

	g_logInfo.Write2Caching("ReConnectServer 设备ID:%s ,%s:%d ret:%d",m_sDevID.c_str(),m_sIp.c_str(),m_nPort,ret);
	if (ret < 0) {
		return false;
	}
	if(!bConnect){
		bConnect = true;
	}
	m_bStop = false;
	m_hRecvThread.reset(new boost::thread(
		boost::bind(&CTcpClient::ReceiveHandle, this)));
	return true;
}
void CTcpClient::DisConnect()
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	if(bConnect == 0 || m_hSocket == NULL)
	{
		return ;
	}
	shutdown(m_hSocket,SD_BOTH);
	closesocket(m_hSocket);
	m_hSocket = NULL;
	bConnect = false;
	g_logInfo.Write2Caching("DisConnect %s",m_sDevID.c_str());
	
}

void CTcpClient::StopDev()
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	g_logInfo.Write2Caching("StopDev %s",m_sDevID.c_str());
	m_bStop = true;
	DisConnect();
	if (m_hRecvThread)
	{
		m_hRecvThread->join();
		m_hRecvThread.reset();
	}
	

}
int CTcpClient::SendData(char*buf,int len)
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	if (m_bStop)
	{
		return 0;
	}
	if(!bConnect)
	{
		g_logInfo.Write2Caching("bConnect is false %s",m_sDevID.c_str());
	}
	int nSend;
	{
		int sendLen =  send(m_hSocket,buf,len,0);
		nSend = sendLen;
	}
	return nSend;
}
bool CTcpClient::getBConnect()
{
	return bConnect;
};


void CTcpClient::ReceiveHandle()
{
	char* buf = new char[100*1024];
	bool berr = false;
	while(1)
	{
		if (m_bStop)
		{
			return;
		}
		if (bConnect)
		{
			
			int nlen = recv(m_hSocket, buf, 5, 0);
			if (nlen == 5)
			{
				if (buf[0] == 0x00)
				{
					int packagelen = *(int *)(buf+1);
					if (packagelen<100*1024)
					{
						nlen = recv(m_hSocket, buf, packagelen+1, 0);
						if (nlen == (packagelen + 1))
						{
							HandleCmd(buf+1,packagelen);
							berr = false;
							continue;

						}

					}

				}
			}
			berr = true;
		}
		else
		{
			Sleep(10);
		}
		
	}

}
void CTcpClient::HeartHandle()
{
	char* buf = new char[100*1024];
	bool berr = false;
	while(1)
	{
		Sleep(30*1000);
		if (m_pDevSdk)
		{
			m_pDevSdk->SendPuHeart();
		}
	}
}
void CTcpClient::HandleCmd(char* buf,unsigned int nCmdLen)
{
	m_pDevSdk->HandleCmd(buf,nCmdLen+1);
}
void CTcpClient::BuildAndSendCmd(char* buf,int nLen)
{
	CSendbuffer sBuffer;
	sBuffer.BuiladPakage(buf,nLen);
	SendData(sBuffer.Data(),sBuffer.length());
}