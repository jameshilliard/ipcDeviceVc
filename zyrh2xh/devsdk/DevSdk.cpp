#include "DevSdk.h"
#include <iostream>
#include <stdlib.h>
#include <map>
#include "../x264/bytestream.h"
#include "../global.h"
#include "../Logger.h"
#include "../httpClient/httpClient.h"
#include <boost/format.hpp>
#define  UDP_MAX_SIZE 1400

void CBF_OnClosed_(char* ip,unsigned int len,unsigned short* port,void* ctx)
{

}
string Encode(const unsigned char* Data,int DataByte)
{
	//编码表
	const char EncodeTable[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//返回值
	string strEncode;
	unsigned char Tmp[4]={0};
	int LineLength=0;
	for(int i=0;i<(int)(DataByte / 3);i++)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		Tmp[3] = *Data++;
		strEncode+= EncodeTable[Tmp[1] >> 2];
		strEncode+= EncodeTable[((Tmp[1] << 4) | (Tmp[2] >> 4)) & 0x3F];
		strEncode+= EncodeTable[((Tmp[2] << 2) | (Tmp[3] >> 6)) & 0x3F];
		strEncode+= EncodeTable[Tmp[3] & 0x3F];
		if(LineLength+=4,LineLength==76) {strEncode+="\r\n";LineLength=0;}
	}
	//对剩余数据进行编码
	int Mod=DataByte % 3;
	if(Mod==1)
	{
		Tmp[1] = *Data++;
		strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4)];
		strEncode+= "==";
	}
	else if(Mod==2)
	{
		Tmp[1] = *Data++;
		Tmp[2] = *Data++;
		strEncode+= EncodeTable[(Tmp[1] & 0xFC) >> 2];
		strEncode+= EncodeTable[((Tmp[1] & 0x03) << 4) | ((Tmp[2] & 0xF0) >> 4)];
		strEncode+= EncodeTable[((Tmp[2] & 0x0F) << 2)];
		strEncode+= "=";
	}

	return strEncode;
}
void ChangeXhkjParam2Zyrh(int nParamIn, int& nParamOut,int& nAction)
{
	int nRet = 0;
	nAction = WMP_PTZ_ACTION_START;
	switch(nParamIn)
	{
	case LENS_UP:
		nRet = WMP_PTZ_UP;
		break;
	case LENS_LEFT:
		nRet = WMP_PTZ_LEFT;
		break;
	case LENS_RIGHT:
		nRet = WMP_PTZ_RIGHT;
		break;
	case LENS_DOWN:
		nRet = WMP_PTZ_DOWN;
		break;
	case LENS_FOCUSNEAR:
		nRet = WMP_PTZ_FOCUS_NEAR;
		break;
	case LENS_FOCUSFAR:
		nRet = WMP_PTZ_FOCUS_FAR;
		break;
	case LENS_DIAPHRAGM_LARGE:
		nRet = WMP_PTZ_WIPER;
		break;
	case LENS_DIAPHRAGM_SMALL:
		nRet = WMP_PTZ_DIAPHRAGM_SHRINK;
		break;
	case LENS_AUTO:
		nRet = WMP_PTZ_AUTO;
		break;
	case LENS_NEAR:
		nRet = WMP_PTZ_ZOOMIN;
		break;
	case LENS_FAR:
		nRet = WMP_PTZ_ZOOMOUT;
		break;
	case LENS_STOP:
		{
			nRet = WMP_PTZ_UP;
			nAction = WMP_PTZ_ACTION_STOP;
			break;
		}
		
	}
	nParamOut = nRet;

}
void CBF_OnStreamPlay(int h,int sflag,const char* data  ,unsigned int data_size,void* ctx)
{
	CdevSdk *pDevSdk = (CdevSdk *)ctx;
	unsigned int nLength = 0;
	unsigned int nType;
	unsigned int nTimeStamp = 0;
	if (sflag == 2)
	{
		//printf("%d %d\n",data_size,GetTickCount());
		pDevSdk->InPutPsData((unsigned char*)data,data_size,sflag);
		while(pDevSdk->zyrh_AnalyzeDataGetPacketEx(pDevSdk->m_buf,nLength,nTimeStamp,nType))
		{

		}

	}
	else
	{
		pDevSdk->InPutPsData((unsigned char*)data,data_size,sflag);
	}
}
CdevSdk::CdevSdk()
{
	static bool binit = false;
	if (!binit)
	{

		binit = true;
	}
	char buf[20];
	sprintf(buf,"%u%u",GetTickCount(),rand());
	m_sCallID = buf;
	m_buf = new char[512*1024];
	m_nSeq = 1;
	m_seq_num = 1;
	m_nAnalyzeHandle = -1;
	m_sDevTimeStamp = time(NULL);
	m_bDevOnline = false;
	m_sPuTimeStamp = time(NULL);
	m_bNeedVidoe = false;

}
CdevSdk::~CdevSdk()
{
	delete[] m_buf;

}
bool CdevSdk::StartDev(char* sSdkServerIp,unsigned int nSdkServerPort,char* user,char* password,int nServerLine,char* sdevId,unsigned int nDevLine,unsigned int nchannel)
{
	m_sSdkServerIp = sSdkServerIp;
	m_nSdkServerPort= nSdkServerPort;
	m_spassword = password;
	m_sUserName = user;
	m_nServerLine = nServerLine;

	m_nDevLine = nDevLine;;
	m_nnchannel = nchannel;
	m_sDevId = sdevId;
	if (m_wmp_handle != -1)
	{
		StopDev();
	}
	m_wmp_handle = WMP_Create();
	if (m_wmp_handle == -1)
	{
		return false;
	}
	int ret =  WMP_Login(m_wmp_handle,sSdkServerIp,nSdkServerPort, user,password,nServerLine);
	if (ret == -1)
	{
		return false;
	}
	//WMP_SetClosedCallback(m_wmp_handle,CBF_OnClosed_,this);
	ret = WMP_Play(m_wmp_handle,
		sdevId,//devid:设备ID
		nchannel,//channel:设备通道号
		WMP_STREAM_MAIN, //stream_type:WMP_STREAM_MAIN 1-主码流   WMP_STREAM_SUB 2-子码流 
		WMP_TRANS_TCP,//trans_mode:WMP_TRANS_TCP/WMP_TRANS_UDP  #define WMP_TRANS_TCP	1#define WMP_TRANS_UDP	2
		nDevLine,//dev_line:设备线路号
		CBF_OnStreamPlay, (void*)this,(int*)&m_stream_handle);
	g_logInfo.Write2Caching("开启设备，设备ID:%s,服务器线路号:%d,设备通道号:%d,设备线路号:%d m_wmp_handle:%d返回ret:%d",
		sdevId,nServerLine,nchannel,nDevLine,m_wmp_handle,ret);
	PuLogOutXml();
	char buf[20];
	sprintf(buf,"%u%u",GetTickCount(),rand());
	m_sCallID = buf;
	if (ret != 0)
	{
		m_bDevOnline = false;
		return false;
	}
	else
	{
		m_bDevOnline = true;
		m_TcpClient.m_sDevID = sdevId;
		m_TcpClient.ConnectServer(m_sPagIp.c_str(),m_nPagPort);
		PuLogin();
	}
	return true;
}
bool CdevSdk::SetDevInof(char* sSdkServerIp,unsigned int nSdkServerPort,char* user,char* password,int nServerLine,char* sdevId,unsigned int nDevLine,unsigned int nchannel)
{
	m_sSdkServerIp = sSdkServerIp;
	m_nSdkServerPort= nSdkServerPort;
	m_spassword = password;
	m_sUserName = user;
	m_nServerLine = nServerLine;

	m_nDevLine = nDevLine;;
	m_nnchannel = nchannel;
	m_sDevId = sdevId;
	return true;
}
bool CdevSdk::ReStartDev()
{
	StopDev();
	m_wmp_handle = WMP_Create();
	if (m_wmp_handle == -1)
	{
		return false;
	}
	int ret =  WMP_Login(m_wmp_handle,m_sSdkServerIp.c_str(),m_nSdkServerPort, m_sUserName.c_str(),m_spassword.c_str(),m_nServerLine);
	if (ret == -1)
	{
		StopDev();
		g_logError.Write2Caching("WMP_Login ret = -1 设备ID:%s,服务器线路号:%d,设备通道号:%d,设备线路号:%d m_wmp_handle:%d",
			m_sDevId.c_str(),m_nServerLine,m_nnchannel,m_nDevLine,m_wmp_handle);
		return false;
	}
	ret = WMP_Play(m_wmp_handle,
		m_sDevId.c_str(),//devid:设备ID
		m_nnchannel,//channel:设备通道号
		WMP_STREAM_MAIN, //stream_type:WMP_STREAM_MAIN 1-主码流   WMP_STREAM_SUB 2-子码流 
		WMP_TRANS_UDP,//trans_mode:WMP_TRANS_TCP/WMP_TRANS_UDP  #define WMP_TRANS_TCP	1#define WMP_TRANS_UDP	2
		m_nDevLine,//dev_line:设备线路号
		CBF_OnStreamPlay, (void*)this,(int*)&m_stream_handle);
	g_logInfo.Write2Caching("重练设备，设备ID:%s,服务器线路号:%d,设备通道号:%d,设备线路号:%d m_wmp_handle:%d,返回ret:%d",
		m_sDevId.c_str(),m_nServerLine,m_nnchannel,m_nDevLine,m_wmp_handle,ret);
	if (ret != 0)
	{
		return false;
	}
	return true;
}
bool CdevSdk::StartDev()
{
	StopDev();
	m_wmp_handle = WMP_Create();
	if (m_wmp_handle == -1)
	{
		return false;
	}
	int ret =  WMP_Login(m_wmp_handle,m_sSdkServerIp.c_str(),m_nSdkServerPort, m_sUserName.c_str(),m_spassword.c_str(),m_nServerLine);
	if (ret == -1)
	{
		StopDev();
		g_logError.Write2Caching("WMP_Login ret = -1 设备ID:%s,服务器线路号:%d,设备通道号:%d,设备线路号:%d m_wmp_handle:%d",
			m_sDevId.c_str(),m_nServerLine,m_nnchannel,m_nDevLine,m_wmp_handle);
		return false;
	}
	ret = WMP_Play(m_wmp_handle,
		m_sDevId.c_str(),//devid:设备ID
		m_nnchannel,//channel:设备通道号
		WMP_STREAM_MAIN, //stream_type:WMP_STREAM_MAIN 1-主码流   WMP_STREAM_SUB 2-子码流 
		WMP_TRANS_UDP,//trans_mode:WMP_TRANS_TCP/WMP_TRANS_UDP  #define WMP_TRANS_TCP	1#define WMP_TRANS_UDP	2
		m_nDevLine,//dev_line:设备线路号
		CBF_OnStreamPlay, (void*)this,(int*)&m_stream_handle);
	g_logInfo.Write2Caching("重练设备，设备ID:%s,服务器线路号:%d,设备通道号:%d,设备线路号:%d m_wmp_handle:%d,返回ret:%d",
		m_sDevId.c_str(),m_nServerLine,m_nnchannel,m_nDevLine,m_wmp_handle,ret);
	if (ret != 0)
	{
		return false;
	}
	return true;
}
void CdevSdk::ResetParam()
{
	m_nSeq = 1;
	m_seq_num = 1;
	char buf[20];
	sprintf(buf,"%u%u",GetTickCount(),rand());
	m_sCallID = buf;
	m_bNeedVidoe = false;

}
void CdevSdk::StopDev()
{
	if (m_wmp_handle != -1)
	{
		WMP_Stop(m_wmp_handle,m_stream_handle);
		WMP_Close(m_wmp_handle);
		g_logInfo.Write2Caching("停止设备取流 m_wmp_handle %d 设备ID:%s,puid:%s",m_wmp_handle,m_sDevId.c_str(),m_sPuID.c_str());
		m_wmp_handle = -1;
	}
	if (m_nAnalyzeHandle != -1)
	{
		AnalyzeDataClose(m_nAnalyzeHandle);
		g_logInfo.Write2Caching("停止解包 m_nAnalyzeHandle %d 设备ID:%s,puid:%s",m_nAnalyzeHandle,m_sDevId.c_str(),m_sPuID.c_str());
		m_nAnalyzeHandle = -1;
	}

}
bool CdevSdk::InPutPsData(unsigned char* videoPsBuf,unsigned int  psBufsize,int nType )
{
	if(nType == 1)
	{
		if (m_nAnalyzeHandle == -1)
		{
			m_nAnalyzeHandle = AnalyzeDataGetSafeHandle();
			g_logInfo.Write2Caching("初始化解包模块 m_nAnalyzeHandle:%d，设备ID:%s,puid:%s",m_nAnalyzeHandle,m_sDevId.c_str(),m_sPuID.c_str());
		}
		m_strHead = Encode(videoPsBuf,psBufsize);
		AnalyzeDataOpenStreamEx(m_nAnalyzeHandle, (PBYTE)videoPsBuf);
		
	}
	else
	{
		AnalyzeDataInputData(m_nAnalyzeHandle, videoPsBuf, psBufsize);
	}
	return true;
}
bool CdevSdk::zyrh_AnalyzeDataGetPacketEx(char* h264OutBuf,unsigned int& nh264Size,unsigned int& TimeStamp,unsigned int& nDataType)
{
	if (m_nAnalyzeHandle == -1)
	{
		return false;
	}
	PACKET_INFO_EX stPacket;
	/*
	=0x36,标识视频I帧；
	=0x37,标识视频P帧；
	=0x38,表示视频B帧；
	=0x39,标识音频帧
	*/
	while (AnalyzeDataGetPacketEx(m_nAnalyzeHandle, &stPacket) == 0)
	{
		if (stPacket.nPacketType == VIDEO_I_FRAME ||stPacket.nPacketType == VIDEO_P_FRAME||stPacket.nPacketType == VIDEO_B_FRAME)
		{
			ConvertPsToRtp(&stPacket);
		}
		else if (stPacket.nPacketType == AUDIO_PACKET)
		{

		}
		return true;
	}
	return false;
}
bool CdevSdk::SetXhkeInfo(char* pagIp,unsigned int pagPort,char* puId,int nPuPort,char* puIP,char* DOMAIN_ID,char* sPuName)
{
	m_sPagIp = pagIp;
	m_nPagPort = pagPort;
	m_sPuID = puId;
	m_sPuIp = puIP;
	m_sPuPort = nPuPort;
	m_sDOMAIN_ID = DOMAIN_ID;
	m_sPuName = sPuName;
	m_TcpClient.m_pDevSdk = this;
	
	return true;
}
bool CdevSdk::PuLogin()
{
	MSG_PU_LOGIN_REQ sMSG_PU_LOGIN_REQ(m_sDOMAIN_ID,m_sPuIp,m_sPuID,m_sCallID,m_sPuName);
	std::string strCmd = sMSG_PU_LOGIN_REQ.GetCmdStr(m_nSeq++);
	m_TcpClient.BuildAndSendCmd((char*)strCmd.c_str(),strCmd.length());
	g_logInfo.Write2Caching("Pu登录，域ID:%s, puid:%s,callid:%s,puNmae:%s",
		m_sDOMAIN_ID.c_str(),m_sPuID.c_str(),m_sCallID.c_str(),m_sPuName.c_str());
	return true;
}
bool CdevSdk::PuLoginXml()
{
	MSG_PU_LOGIN_REQ sMSG_PU_LOGIN_REQ(m_sDOMAIN_ID,m_sPuIp,m_sPuID,m_sCallID,m_sPuName);
	std::string strCmd = sMSG_PU_LOGIN_REQ.GetCmdStrXml(m_nSeq++);
	m_TcpClient.BuildAndSendCmd((char*)strCmd.c_str(),strCmd.length());
	g_logInfo.Write2Caching("Pu登录带xml，域ID:%s, puid:%s,callid:%s,puNmae:%s",
		m_sDOMAIN_ID.c_str(),m_sPuID.c_str(),m_sCallID.c_str(),m_sPuName.c_str());
	return true;
}
bool CdevSdk::PuLogOutXml()
{
	MSG_PU_LOGOUT_REQ sMSG_PU_LOGOUT_REQ(m_sDOMAIN_ID,m_sPuIp,m_sPuID,m_sCallID,m_sPuName);
	std::string strCmd = sMSG_PU_LOGOUT_REQ.GetCmdStrXml(m_nSeq++);
	m_TcpClient.BuildAndSendCmd((char*)strCmd.c_str(),strCmd.length());
	g_logInfo.Write2Caching("Pu登出，域ID:%s, puid:%s,callid:%s,puNmae:%s",
		m_sDOMAIN_ID.c_str(),m_sPuID.c_str(),m_sCallID.c_str(),m_sPuName.c_str());
	return true;
}
void CdevSdk::HandleCmd(char* buf,unsigned int nCmdLen)
{
	xml_data sXmlD_Data;
	char* pstart,*nowBuf;
	pstart = nowBuf = buf;
	int nCmdType = *(int*)buf;
	int nHeadLen = 0;
	if (nCmdType == 0x2f504953)
	{
		nowBuf += strlen("SIP/2.0") +1;
		std::map<std::string,std::string> mapParam;
		char* op;
		op  = strtok(nowBuf,"\r\n");
		std::string skey,svalue;
		strseparate(op,skey,svalue," ");
		mapParam["result"] = skey;
		if (skey != "200")
		{
			PuLoginXml();	 
		}
		else
		{
			for (int i = 0;i< nCmdLen;i++)
			{
				int nValue = *(int*)(pstart+i);
				if (nValue == 0x0A0D0A0D&&nCmdLen - i >4)
				{
					*(pstart + nCmdLen - 1) = '\0';
					nHeadLen = i;
					xmlparser::DecodeXml(pstart+i+4,&sXmlD_Data);
				}
			}
		}
	}
	else if (nCmdType ==  0x49564e49||((nCmdType<<8)>>8) == 0x4B4341||((nCmdType<<8)>>8) == 0x455942 ||nCmdType == 0x4f464e49)
	{
		for (int i = 0;i< nCmdLen;i++)
		{
			int nValue = *(int*)(pstart+i);
			if (nValue == 0x0A0D0A0D&&nCmdLen - i >4)
			{
				*(pstart + nCmdLen - 1) = '\0';
				nHeadLen = i;
				xmlparser::DecodeXml(pstart+i+4,&sXmlD_Data);
			}
		}
	}
	if (sXmlD_Data.MessageType != "")
	{
		g_logInfo.Write2Caching("handle %s \n",sXmlD_Data.MessageType.c_str());
		HandleCmd(&sXmlD_Data,buf,nHeadLen);	  
	}



}
void CdevSdk::SendPuHeart()
{
	unsigned int nTimeCur = time(NULL);
	if ((nTimeCur > m_sPuTimeStamp&&nTimeCur - m_sPuTimeStamp > 70))
	{
		m_sPuTimeStamp = nTimeCur;
		CheckOnlineDev();
	}
	if(m_bNeedVidoe&&nTimeCur - m_sDevTimeStamp > 30)
	{
		ReStartDev();
	}
	MSG_PU_HEART sMSG_PU_HEART(m_sDOMAIN_ID,m_sPuIp,m_sPuID,m_sCallID,m_sPuName);
	std::string strCmd = sMSG_PU_HEART.GetCmdStr(m_nSeq++);
	m_TcpClient.BuildAndSendCmd((char*)strCmd.c_str(),strCmd.length());
}
void CdevSdk::HandleCmd(xml_data* sXmlD_Data,char* pCmdBuf,unsigned int nHeadLen)
{
	//处理观看视频
	if (sXmlD_Data->MessageType == MSG_START_VIDEO_REQ)
	{
		HandleStartVideo(sXmlD_Data,pCmdBuf,nHeadLen);
	}
	else if(sXmlD_Data->MessageType == MSG_STOP_VIDEO_REQ)
	{
		HandleStopVideo(sXmlD_Data,pCmdBuf,nHeadLen);
	}
	else if(sXmlD_Data->MessageType == MSG_STOP_VIDEO_REQ)
	{
		HandleStartVideoAck(sXmlD_Data,pCmdBuf,nHeadLen);
	}
	else if(sXmlD_Data->MessageType == MSG_PTZ_REQ)
	{
		HandlePTZREQ(sXmlD_Data,pCmdBuf,nHeadLen);
	}
	else if(sXmlD_Data->MessageType == MSG_PU_HEART_RESP)
	{
		HandlePuHeart(sXmlD_Data,pCmdBuf,nHeadLen);
	}


}
void CdevSdk::HandleStopVideo(xml_data* sXmlD_Data,char* pCmdBuft,unsigned int nHeadLen)
{
	m_bNeedVidoe = false;
	StopDev();
	g_logInfo.Write2Caching("停止发送流 设备ID:%s,PUID:%s ",m_sDevId.c_str(),m_sPuID.c_str());
	m_UdpClient.Disconnect();
}
void CdevSdk::HandlePuHeart(xml_data* sXmlD_Data,char* pCmdBuft,unsigned int nHeadLen)
{
	g_logInfo.Write2Caching("处理心跳 设备ID:%s,PUID:%s ",m_sDevId.c_str(),m_sPuID.c_str());
	m_sPuTimeStamp = time(NULL);

}
void CdevSdk::HandlePTZREQ(xml_data* sXmlD_Data,char* pCmdBuft,unsigned int nHeadLen)
{
	int ChannelType = atoi(sXmlD_Data->param1["ChannelType"].c_str());
	int ChannelID = atoi(sXmlD_Data->param1["ChannelID"].c_str());
	int xhkjAction = atoi(sXmlD_Data->param1["Action"].c_str());
	int param = atoi(sXmlD_Data->param1["Para1"].c_str());


	g_logInfo.Write2Caching("ChannelID %d Action %d Para1 %d\n",ChannelID,xhkjAction,param);
	if (param == 0)
	{
		param = 1;
	}

	
	int zyrh_aciton,zyrh_start;
	if (m_wmp_handle != -1)
	{
		ChangeXhkjParam2Zyrh(xhkjAction,zyrh_aciton,zyrh_start);
		int ret = WMP_PtzControl(m_wmp_handle,m_sDevId.c_str(),ChannelID,zyrh_aciton,zyrh_start,param);
	}
	std::string str1,str2,str3;
	str1 = pCmdBuft;
	strseparate((char*)str1.c_str(),str2,str3,"\r\n");
	std::string strret = "SIP/2.0 200 OK\r\n";
	std::string strackret;
	str1 = str3;
	while(str1 != "")
	{
		std::string str2,str3;
		strseparate((char*)str1.c_str(),str2,str3,"\r\n");
		if (str2.find("Via:") != std::string::npos ||
			str2.find("From:") != std::string::npos ||
			str2.find("To:") != std::string::npos ||
			str2.find("Call-ID:") != std::string::npos ||
			str2.find("Contact:") != std::string::npos ||
			str2.find("CSeq:") != std::string::npos
			)
		{
			strackret += str2;
			strackret += "\r\n";
		}
		if ( str2.find("Content-Length:") != std::string::npos)
		{
			break;
		}
		str1 = str3;
	}
	char buf[2048];
	sprintf(buf,"SIP/2.0 200 OK\r\n");
	strret = buf;
	strret += strackret;
	strret += "Content-Type: text/xml\r\n";
	strret += "Max-forwards: 70\r\n";


	std::string xmlstr;

	MapValue IE_RESULT;
	IE_RESULT["ErrorCode"] = "0";

	xml_data sxml_data1;
	sxml_data1.MessageType = MSG_PTZ_RESP;
	sxml_data1.param["IE_RESULT"] = IE_RESULT;
	xmlparser::EncodeXml(&sxml_data1,xmlstr);
	sprintf(buf,"Content-Length: %d\r\n\r\n",xmlstr.length());
	strret += buf;
	strret += xmlstr;

	m_TcpClient.BuildAndSendCmd((char*)strret.c_str(),strret.length());


}
void CdevSdk::HandleStartVideoAck(xml_data* sXmlD_Data,char* pCmdBuft,unsigned int nHeadLen)
{
	// 	 std::string str1,str2,str3;
	// 	 str1 = pCmdBuft;
	// 	 strseparate((char*)str1.c_str(),str2,str3,"\r\n");
	// 	 std::string strret = "SIP/2.0 200 OK\r\n";
	// 	 std::string strackret;
	// 	 str1 = str3;
	// 	 while(str1 != "")
	// 	 {
	// 		 std::string str2,str3;
	// 		 strseparate((char*)str1.c_str(),str2,str3,"\r\n");
	// 		 if (str2.find("Via:") != std::string::npos ||
	// 			 str2.find("From:") != std::string::npos ||
	// 			 str2.find("To:") != std::string::npos ||
	// 			 str2.find("Call-ID:") != std::string::npos ||
	// 			 str2.find("Contact:") != std::string::npos ||
	// 			 str2.find("CSeq:") != std::string::npos
	// 			 )
	// 		 {
	// 			 strackret += str2;
	// 			 strackret += "\r\n";
	// 		 }
	// 		 if ( str2.find("Content-Length:") != std::string::npos)
	// 		 {
	// 			 break;
	// 		 }
	// 		 str1 = str3;
	// 	 }
	// 	 char buf[2048];
	// 	 sprintf(buf,"ACK sip:%s@%s;MSG_TYPE=MSG_START_VIDEO_ACK SIP/2.0\r\n",m_sPuID.c_str(),m_sDOMAIN_ID.c_str());
	// 	 strret = buf;
	// 	 strret += strackret;
	// 	 strret += "Content-Type: txt/xml\r\n";
	// 	 strret += "Max-forwards: 70\r\n";
	// 
	// 
	// 	 std::string xmlstr;
	// 
	// 	 MapValue IE_RESULT;
	// 	 IE_RESULT["ErrorCode"] = "0";
	// 
	// 	 xml_data sxml_data1;
	// 	 sxml_data1.param["IE_RESULT"] = IE_RESULT;
	// 	 xmlparser::EncodeXml(&sxml_data1,xmlstr);
	// 	 sprintf(buf,"Content-Length: %d\r\n\r\n",xmlstr.length());
	// 	 strret += buf;
	// 	 strret += xmlstr;

	// m_TcpClient.BuildAndSendCmd((char*)strret.c_str(),strret.length());


	// m_UdpClient.ConnectServer(strip.c_str(),nPort);


}

void CdevSdk::HandleStartVideo(xml_data* sXmlD_Data,char* pCmdBuft,unsigned int nHeadLen)
{
	char* bufCur = NULL;

	g_logInfo.Write2Caching("HandleStartVideo PuID:%s,设备ID:%s",m_sPuID.c_str(),m_sDevId.c_str());

	std::string str1,str2,str3;
	str1 = pCmdBuft;
	strseparate((char*)str1.c_str(),str2,str3,"\r\n");
	std::string strret = "SIP/2.0 200 OK\r\n";
	std::string strackret;
	str1 = str3;
	while(str1 != "")
	{
		std::string str2,str3;
		strseparate((char*)str1.c_str(),str2,str3,"\r\n");

		if (str2.find("Via:") != std::string::npos ||
			str2.find("From:") != std::string::npos ||
			str2.find("To:") != std::string::npos ||
			str2.find("Call-ID:") != std::string::npos ||
			str2.find("CSeq:") != std::string::npos ||
			str2.find("Contact:") != std::string::npos 
			)
		{
			strret += str2;
			strret += "\r\n";
		}
		if ( str2.find("Content-Length:") != std::string::npos)
		{
			break;
		}
		str1 = str3;
	}
	strret += "User-Agent: hik pu\r\n";
	strret += "Content-Type: text/xml\r\n";
	xml_data sxml_data;
	sxml_data.MessageType = MSG_START_VIDEO_RESP;

	MapValue IE_RESULT;
	IE_RESULT["ErrorCode"] = "0";
	sxml_data.param["IE_RESULT"] = IE_RESULT;


	MapValue IE_OPEN_VIDEO_ACK;
	IE_OPEN_VIDEO_ACK["MediaType"] = "1";
	IE_OPEN_VIDEO_ACK["VidEncode"] = "3";
	IE_OPEN_VIDEO_ACK["VidFormat"] = "1";
// 	IE_OPEN_VIDEO_ACK["AudEncode"] = "G711";
// 	IE_OPEN_VIDEO_ACK["AudSamping"] = "16000";
// 	IE_OPEN_VIDEO_ACK["AudBitRate"] = "16000";
// 	IE_OPEN_VIDEO_ACK["AudTrack"] = "1";
	IE_OPEN_VIDEO_ACK["Reserved"] = m_strHead;
	sxml_data.param["IE_OPEN_VIDEO_ACK"] = IE_OPEN_VIDEO_ACK;

	std::string xmlstr;
	xmlparser::EncodeXml(&sxml_data,xmlstr);


	char buf[1024];
	sprintf(buf,"Content-Length: %d\r\n\r\n",xmlstr.length());
	strret += buf;
	strret += xmlstr;


	m_TcpClient.BuildAndSendCmd((char*)strret.c_str(),strret.length());


	std::string strip = sXmlD_Data->param1["Address"];
	unsigned int nPort = atoi((sXmlD_Data->param1["Port"]).c_str());
	m_seq_num = 1;
	m_bNeedVidoe = true;
	StartDev();
	m_UdpClient.ConnectServer(strip.c_str(),nPort);
}
void CdevSdk::ConvertPsToRtp(PACKET_INFO_EX* stPacket )
{
	unsigned int nTimeCur = time(NULL);
	m_sDevTimeStamp = nTimeCur;


	if (!m_UdpClient.IsConnect())
	{
		return;
	}
	char* pPsBuf = stPacket->pPacketBuffer;
	unsigned int  nPsBufLength = stPacket->dwPacketSize;
	unsigned int nTimeStamp = stPacket->dwTimeStamp;
	char buf[2048];
	char* nextBufStart = buf;
	unsigned char nFrameType ;

	if (stPacket->nPacketType == VIDEO_I_FRAME)
	{
		nFrameType = 0x36;
	}
	else if(stPacket->nPacketType == VIDEO_P_FRAME)
	{
		nFrameType = 0x37;
	}
	else if (stPacket->nPacketType == VIDEO_B_FRAME)
	{
		nFrameType = 0x38;
	}
	while(nPsBufLength > UDP_MAX_SIZE)
	{  
		nextBufStart = buf;
		char* tmpStart = nextBufStart;
		bool bend = false;
		nextBufStart = CreatePsRtpPackage(nextBufStart,bend,nTimeStamp,m_sPuID,nFrameType);
		nextBufStart = append_data(nextBufStart,pPsBuf,UDP_MAX_SIZE);
		nPsBufLength -= UDP_MAX_SIZE;
		pPsBuf += UDP_MAX_SIZE;
		m_UdpClient.SendUdpData(buf,nextBufStart - buf );
	}
	if (nPsBufLength>0)
	{
		nextBufStart = buf;
		char* tmpStart = nextBufStart;
		nextBufStart = CreatePsRtpPackage(nextBufStart,true,nTimeStamp,m_sPuID,nFrameType);	
		nextBufStart = append_data(nextBufStart,pPsBuf,nPsBufLength);
		m_UdpClient.SendUdpData(buf,nextBufStart - buf);
		nPsBufLength = 0;
	}

}
char* CdevSdk::CreatePsRtpPackage(char* rtpPackage,bool bend,unsigned int nTimeStamp,std::string PuID,unsigned char nFrameType)
{
	char* pCurPackage = rtpPackage;
	unsigned char version = 2;  /* V  expect 2 */ 
	unsigned char padding = 0;  /* P  expect 0 */ 
	unsigned char extension = 0;/* X  expect 1, see RTP_OP below */  
	unsigned char csrc_len = 0; /* CC expect 0 */ 

	pCurPackage = put_byte(pCurPackage,0x91);
	if (bend)
	{
		pCurPackage = put_byte(pCurPackage,0x75);	
	}
	else
	{
		pCurPackage = put_byte(pCurPackage,0xF5);
	}

	/* byte 2,3 */  
	unsigned short seq_no = m_seq_num++;   /*sequence number*/  
	pCurPackage = put_be16(pCurPackage,(seq_no));
	/* byte 4-7 */  
	unsigned  int timestamp = nTimeStamp; 
	pCurPackage = put_be32(pCurPackage,(timestamp));
	/* byte 8-11 */  

	unsigned int ssrc = 0x0; 
	pCurPackage = put_be32(pCurPackage,ssrc);

	unsigned int csrc = 0x01; 
	pCurPackage = put_be32(pCurPackage,csrc);

	unsigned short manufacurecode = 0x0B00;
	pCurPackage = put_be16(pCurPackage,manufacurecode);

	unsigned short length = 0x0003;
	pCurPackage = put_be16(pCurPackage,length);

	unsigned __int64 nPuid ;
	sscanf(PuID.c_str(),"%I64u",&nPuid );
	pCurPackage = append_data(pCurPackage,(char*)&nPuid,8 );


	pCurPackage = put_byte(pCurPackage,nFrameType);
	if (bend)
	{
		pCurPackage = put_byte(pCurPackage,0x31);
	}
	else
	{
		pCurPackage = put_byte(pCurPackage,0x30);
	}

	pCurPackage = put_byte(pCurPackage,0x30);
	pCurPackage = put_byte(pCurPackage,0x01);

	return pCurPackage;
}
bool CdevSdk::IsOnline()
{	
	CHTTPClient shttpClient;
	std::string str = (boost::format("%1%?strDevCodeList=%2%&getOnlineDevice=true")%sHttpUrl.c_str()%m_sDevId.c_str()).str();
	std::string sResult;
	xml_data sxml_data;
	shttpClient.HttpGet(str,sResult);
	xmlparser::DecodeXml(sResult.c_str(),&sxml_data);
	if (sxml_data.param1["Status"] == "1")
	{
		return true;
	}
	return false;
}
bool CdevSdk::CheckOnlineDev()
{
	if (!IsOnline())
	{
		PuLogOutXml();
		m_UdpClient.Disconnect();
		m_TcpClient.StopDev();
		ResetParam();
		m_bDevOnline = false;
		return false;
	}
	else
	{
		m_bDevOnline = true;
		m_TcpClient.m_sDevID = m_sDevId;
		m_TcpClient.ConnectServer(m_sPagIp.c_str(),m_nPagPort);
		PuLogin();
	}
	return true;
}