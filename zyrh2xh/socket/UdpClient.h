#pragma  once
#include <string>
#include "../tinyxml/xmlCmd.h"
#include <boost/asio/detail/mutex.hpp>
using namespace std;
class CUdpClient
{
public:
	CUdpClient();
	~CUdpClient();
	bool ConnectServer(std::string sIp,unsigned int nPort);
	void ResetParam();
	void SendUdpData(const char* sendBuf,unsigned int nLength);
	void Disconnect();
	bool IsConnect();
	
private:
	unsigned int m_nPort;
	std::string m_sIp;
	boost::asio::detail::mutex mutex_;
public:
	SOCKET m_udpSocket;;//套接字

	SOCKADDR_IN m_servaddr;//服务器地址信息
	bool m_bSendKey;





	std::string m_sVideoIp;

	unsigned int m_nVideoPort;

};