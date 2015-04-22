#include "UdpClient.h"
#include "TcpClient.h"
#pragma comment(lib,"ws2_32.lib")
unsigned int g_nSequence = 1;
CTcpClient* pTcpClient = NULL;
#include "../Logger.h"

// extern std::string sDevID;
// extern std::string sSession;
CUdpClient::CUdpClient()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(1,1),&wsa);
	ResetParam();

}
CUdpClient::~CUdpClient()
{
	WSACleanup();
}
bool CUdpClient::ConnectServer(std::string sIp,unsigned int nPort)
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	g_logInfo.Write2Caching("udp connect %s:%d \n",sIp.c_str(),nPort);
	m_sIp = sIp;
	m_nPort = nPort;
	if (m_udpSocket != INVALID_SOCKET)
	{
		closesocket(m_udpSocket);
		m_udpSocket = INVALID_SOCKET;
	}
	if (m_udpSocket == INVALID_SOCKET)
	{
		m_udpSocket = socket(AF_INET,SOCK_DGRAM,0);//UDP·½Ê½
		m_servaddr.sin_family = AF_INET;
		m_servaddr.sin_port = htons(m_nPort);
		m_servaddr.sin_addr.s_addr = inet_addr(m_sIp.c_str());
	}
	m_bSendKey = false;
	return true;
}
void CUdpClient::ResetParam()
{
	m_udpSocket = INVALID_SOCKET;
}
void CUdpClient::SendUdpData(const char* sendBuf,unsigned int nLength)
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	if (m_udpSocket != INVALID_SOCKET)
	{
		int nlen = sendto(m_udpSocket,sendBuf,nLength,0,(struct sockaddr *)&m_servaddr,sizeof(m_servaddr));  
		if (nLength != nlen)
		{
			g_logInfo.Write2Caching("SendUdpData nLength:%d != nlen:%d  %s:%d\n",nLength,nlen,m_sIp.c_str(),m_nPort);
		}
	}
	else
	{
		g_logInfo.Write2Caching("m_udpSocket != INVALID_SOCKET %d\n",nLength);
	}
}
void CUdpClient::Disconnect()
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	if (m_udpSocket != INVALID_SOCKET)
	{
		closesocket(m_udpSocket);
		m_udpSocket = INVALID_SOCKET;
	}

}
bool CUdpClient::IsConnect()
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	if (m_udpSocket != INVALID_SOCKET)
	{
		return true;
	}
	return false;


}
