#pragma once 
#include "../tinyxml/xmlCmd.h"
#include "wmpclient.h"
#include "AnalyzeDataInterface.h"
#include "../socket/TcpClient.h"
#include "../socket/UdpClient.h"
#include <string>
extern std::string sHttpUrl;
class  CdevSdk
{
public:
	CdevSdk();
	~CdevSdk();

	//***********************zyrh begin******************************
	bool StartDev(char* sSdkServerIp,unsigned int nSdkServerPort,char* user,char* password,int nServerLine,char* sdevId,unsigned int nDevLine,unsigned int nchannel);
	bool StartDev();
	bool SetDevInof(char* sSdkServerIp,unsigned int nSdkServerPort,char* user,char* password,int nServerLine,char* sdevId,unsigned int nDevLine,unsigned int nchannel);
	void StopDev();
	bool ReStartDev();
	bool InPutPsData(unsigned char* videoPsBuf,unsigned int  psBufsize,int nType );
	bool zyrh_AnalyzeDataGetPacketEx(char* h264OutBuf,unsigned int& nh264Size,unsigned int& TimeStamp,unsigned int& nDataType);

	//***********************zyrh end******************************


	//***********************xhke begin******************************
	//puid 设备ID
	bool SetXhkeInfo(char* pagIp,unsigned int pagPort,char* puId,int nPuPort,char* puIP,char* DOMAIN_ID,char* sPuName);
    bool PuLogin();
	bool PuLoginXml();
	bool PuLogOutXml();
	void HandleCmd(char* buf,unsigned int nCmdLen);
	void SendPuHeart();
	void HandleCmd(xml_data* sXmlD_Data,char* pCmdBuf,unsigned int nCmdLen);
	void HandleStartVideo(xml_data* sXmlD_Data,char* pCmdBuf,unsigned int nHeadLen);
	void HandleStopVideo(xml_data* sXmlD_Data,char* pCmdBuf,unsigned int nHeadLen);
	void HandleStartVideoAck(xml_data* sXmlD_Data,char* pCmdBuft,unsigned int nHeadLen);
	void HandlePTZREQ(xml_data* sXmlD_Data,char* pCmdBuft,unsigned int nHeadLen);
	void HandlePuHeart(xml_data* sXmlD_Data,char* pCmdBuft,unsigned int nHeadLen);
  
	//rtp
	 void ConvertPsToRtp(PACKET_INFO_EX* stPacket);
	 char* CreatePsRtpPackage(char* rtpPackage,bool bend,unsigned int nTimeStamp,std::string PuID,unsigned char nFrameType);
	//***********************xhke end******************************
	 bool IsOnline();
	 bool CheckOnlineDev();
private:
	void ResetParam();
	
	WMP_HANDLE m_wmp_handle;
public:
	long m_gVideoPort;
	char* m_buf;
	unsigned int m_nLength;


	//sdk 信息
	std::string m_sSdkServerIp;
	unsigned int m_nSdkServerPort;
	std::string m_spassword;
	std::string m_sUserName;
	unsigned int m_nServerLine;


	unsigned int m_nDevLine;
	unsigned int m_nnchannel;
	std::string m_sDevId;
	int         m_stream_handle;

	CTcpClient m_TcpClient;
	CUdpClient m_UdpClient;

	//设备的解包的句柄
	int m_nAnalyzeHandle;

	//新华科技设备信息
	std::string m_sCallID;
	int m_nSeq;//发送序列号
	std::string m_sPagIp;//服务器IP
	unsigned int m_nPagPort;//服务器端口
	std::string m_sPuID;//设备ID
	std::string m_sPuPort;//设备端口
	std::string m_sPuIp;//设备Ip
	std::string m_sDOMAIN_ID;//域ID
	std::string m_sPuName;//设备名称

	//rtp包头信息
	unsigned short m_seq_num;
	//
	std::string m_strHead;
	unsigned int m_sDevTimeStamp;
	unsigned int m_sPuTimeStamp;
	bool m_bDevOnline;//设备是否在线
	bool m_bNeedVidoe;//是否需要视频数据
};