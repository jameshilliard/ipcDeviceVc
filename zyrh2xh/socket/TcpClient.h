#ifndef _TCPCLIENT_H_
#define _TCPCLIENT_H_
#include <boost/asio/detail/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#pragma comment(lib,"ws2_32.lib")
#include <string>
class CdevSdk;

class CTcpClient {
public:
	CTcpClient();
	virtual ~CTcpClient();

	bool ConnectServer(const char *ip,int port);
	

	void BuildAndSendCmd(char* buf,int nLen);
	
	

	bool getBConnect();

	bool ReConnectServer();

	void StopDev();

	void ReceiveHandle();

	void HandleCmd(char* buf,unsigned int nCmdLen);
	void HeartHandle();
	

private:
	void DisConnect();
	bool bConnect;
	int m_hSocket;
	std::string m_sIp;
	unsigned int m_nPort;
	bool m_bStop;
	int SendData(char*buf,int len);

public:
	std::string m_Session;
	std::string m_sDevID;
	boost::asio::detail::mutex mutex_;
	boost::shared_ptr<boost::thread>	m_hRecvThread;
	boost::shared_ptr<boost::thread>	m_hHeartThread;
	CdevSdk* m_pDevSdk;
};

#endif /* TCPCLIENT_H_ */
