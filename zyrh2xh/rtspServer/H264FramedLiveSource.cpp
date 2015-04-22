#include "H264FramedLiveSource.hh"
#include "../Logger.h"

using namespace std;

H264FramedLiveSource::H264FramedLiveSource(UsageEnvironment& env,H264FrameDeviceSource *ptH264FrameDeviceSource, unsigned preferredFrameSize, unsigned playTimePerFrame)
: FramedSource(env)
{
	//Framed_datasize = datasize;//数据区大小指针
	//Framed_databuf = databuf;//数据区指针
	//Framed_dosent = dosent;//发送标示
	m_ptH264FrameDeviceSource=ptH264FrameDeviceSource;
}

H264FramedLiveSource* H264FramedLiveSource::createNew(UsageEnvironment& env, H264FrameDeviceSource *ptH264FrameDeviceSource, unsigned preferredFrameSize, unsigned playTimePerFrame)
{
	//static H264FramedLiveSource  newSource(env, nSdkServerData, preferredFrameSize, playTimePerFrame);
	H264FramedLiveSource* newSource = new H264FramedLiveSource(env,ptH264FrameDeviceSource, preferredFrameSize, playTimePerFrame);
	newSource->setDeviceSource(ptH264FrameDeviceSource);
	return newSource;
}

H264FramedLiveSource::~H264FramedLiveSource()
{
	m_ptH264FrameDeviceSource=NULL;
}
void H264FramedLiveSource::doGetNextFrame()
{
	//printf("time:%d,start do get next frame\n",GetTickCount());
	unsigned int dataSize=0;
	unsigned int frameSize=0;
	int i=0;
	bool bRet=true;
	//while(bRet)
	{
		bRet=m_ptH264FrameDeviceSource->GetVideoData(fTo+dataSize,frameSize,fMaxSize-dataSize);
		dataSize+=frameSize;
		fFrameSize=dataSize;

	}
	if(fFrameSize==0)
		fFrameSize=fMaxSize;
	nextTask() = envir().taskScheduler().scheduleDelayedTask(0,(TaskFunc*)FramedSource::afterGetting, this);//表示延迟0秒后再执行 afterGetting 函数
	//printf("time:%d,over do get next fram\n",GetTickCount());
	return;
}



static string Encode(const unsigned char* Data,int DataByte)
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
static void CBF_OnStreamPlay(int h,int sflag,const char* data  ,unsigned int data_size,void* ctx)
{
	H264FrameDeviceSource *pDevSdk = (H264FrameDeviceSource *)ctx;
	if(pDevSdk==NULL)
		return;
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
		int i=0;
		i++;
		pDevSdk->InPutPsData((unsigned char*)data,data_size,sflag);
	}

}



int inline ProgramStreamPackHeader(char* Pack, int length, char **NextPack, int *leftlength)
{
	//printf("[%s]%x %x %x %x\n", __FUNCTION__, Pack[0], Pack[1], Pack[2], Pack[3]);
	//通过 00 00 01 ba头的第14个字节的最后3位来确定头部填充了多少字节
	program_stream_pack_header *PsHead = (program_stream_pack_header *)Pack;
	unsigned char pack_stuffing_length = PsHead->stuffinglen & '\x07';

	*leftlength = length - sizeof(program_stream_pack_header) - pack_stuffing_length;//减去头和填充的字节
	*NextPack = Pack+sizeof(program_stream_pack_header) + pack_stuffing_length;

	if(*leftlength<4) return 0;

	//printf("[%s]2 %x %x %x %x\n", __FUNCTION__, (*NextPack)[0], (*NextPack)[1], (*NextPack)[2], (*NextPack)[3]);

	return *leftlength;
}

inline int ProgramStreamMap(char* Pack, int length, char **NextPack, int *leftlength, char **PayloadData, int *PayloadDataLen)
{
	//printf("[%s]%x %x %x %x\n", __FUNCTION__, Pack[0], Pack[1], Pack[2], Pack[3]);
	
	program_stream_map* PSMPack = (program_stream_map*)Pack;

	//no payload
	*PayloadData = 0;
	*PayloadDataLen = 0;
	
	if(length < sizeof(program_stream_map)) return 0;

	littel_endian_size psm_length;
	psm_length.byte[0] = PSMPack->PackLength.byte[1];
	psm_length.byte[1] = PSMPack->PackLength.byte[0];

	*leftlength = length - psm_length.length - sizeof(program_stream_map);

	//printf("[%s]leftlength %d\n", __FUNCTION__, *leftlength);
	
	if(*leftlength<=0) return 0;

	*NextPack = Pack + psm_length.length + sizeof(program_stream_map);

	return *leftlength;
}

inline int Pes(char* Pack, int length, char **NextPack, int *leftlength, char **PayloadData, int *PayloadDataLen)
{
	//printf("[%s]%x %x %x %x\n", __FUNCTION__, Pack[0], Pack[1], Pack[2], Pack[3]);
	program_stream_e* PSEPack = (program_stream_e*)Pack;

	*PayloadData = 0;
	*PayloadDataLen = 0;

	if(length < sizeof(program_stream_e)) return 0;
	
	littel_endian_size pse_length;
	pse_length.byte[0] = PSEPack->PackLength.byte[1];
	pse_length.byte[1] = PSEPack->PackLength.byte[0];

	*PayloadDataLen = pse_length.length - 2 - 1 - PSEPack->stuffing_length;
	if(*PayloadDataLen>0) 
		*PayloadData = Pack + sizeof(program_stream_e) + PSEPack->stuffing_length;
		
	*leftlength = length - pse_length.length - sizeof(pack_start_code) - sizeof(littel_endian_size);

	//printf("[%s]leftlength %d\n", __FUNCTION__, *leftlength);

	if(*leftlength<=0) return 0;

	*NextPack = Pack + sizeof(pack_start_code) + sizeof(littel_endian_size) + pse_length.length;

	return *leftlength;
}

int GetH246FromPs(char* buffer,int length, char **h264Buffer, int *h264length)
{
	int leftlength = 0;
	char *NextPack = 0;

	*h264Buffer = buffer;
	*h264length = 0;

	if(ProgramStreamPackHeader(buffer, length, &NextPack, &leftlength)==0)
		return 0;

	char *PayloadData=NULL; 
	int PayloadDataLen=0;

	while(leftlength >= sizeof(pack_start_code))
	{
		PayloadData=NULL;
		PayloadDataLen=0;
		
		if(NextPack 
		&& NextPack[0]=='\x00' 
		&& NextPack[1]=='\x00' 
		&& NextPack[2]=='\x01' 
		&& NextPack[3]=='\xE0')
		{
			//接着就是流包，说明是非i帧
			if(Pes(NextPack, leftlength, &NextPack, &leftlength, &PayloadData, &PayloadDataLen))
			{
				if(PayloadDataLen)
				{
					memcpy(buffer, PayloadData, PayloadDataLen);
					buffer += PayloadDataLen;
					*h264length += PayloadDataLen;
				}
			}
			else 
			{
				if(PayloadDataLen)
				{
					memcpy(buffer, PayloadData, PayloadDataLen);
					buffer += PayloadDataLen;
					*h264length += PayloadDataLen;
				}

				break;
			}
		}
		else if(NextPack 
			&& NextPack[0]=='\x00' 
			&& NextPack[1]=='\x00'
			&& NextPack[2]=='\x01'
			&& NextPack[3]=='\xBC')
		{
			if(ProgramStreamMap(NextPack, leftlength, &NextPack, &leftlength, &PayloadData, &PayloadDataLen)==0)
				break;
		}
		else
		{
			//printf("[%s]no konw %x %x %x %x\n", __FUNCTION__, NextPack[0], NextPack[1], NextPack[2], NextPack[3]);
			break;
		}
	}

	
	return *h264length;
}

H264FrameDeviceSource::H264FrameDeviceSource(SDKServerData nSdkServerData)
{
	m_SdkServerData=nSdkServerData;
	m_nAnalyzeHandle = -1;
	m_stream_handle=-1;
	m_wmp_handle=-1;
	m_buf = new char[512*1024];
}
H264FrameDeviceSource::~H264FrameDeviceSource()
{
	delete[] m_buf;
}
bool H264FrameDeviceSource::InPutPsData(unsigned char* videoPsBuf,unsigned int  psBufsize,int nType )
{
	if(nType == 1)
	{
		if (m_nAnalyzeHandle == -1)
		{
			m_nAnalyzeHandle = AnalyzeDataGetSafeHandle();
			g_logInfo.Write2Caching("初始化解包模块 m_nAnalyzeHandle:%d，设备ID:%s",m_nAnalyzeHandle, m_SdkServerData.m_sDevId.c_str());
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
bool H264FrameDeviceSource::zyrh_AnalyzeDataGetPacketEx(char* h264OutBuf,unsigned int& nh264Size,unsigned int& TimeStamp,unsigned int& nDataType)
{
	if (m_nAnalyzeHandle == -1)
	{
		return false;
	}
	PACKET_INFO_EX stPacket;
	char *ptrBuffer=NULL;
	int length=0;
	int *ptrLength=&length;
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

			GetH246FromPs(stPacket.pPacketBuffer,stPacket.dwPacketSize,&ptrBuffer,ptrLength);
			if(length!=0)
			{			
				std::string temp(ptrBuffer,length);
				{

					//FILE *pf;	fopen_s(&pf, "./test_w.264", "a+");	
					//fwrite(ptrBuffer, 1, length, pf);
					//fclose(pf);		
					boost::asio::detail::mutex::scoped_lock lock(m_mutex);
					m_h264Data.push(temp);
					printf("this 0x%x,insert data size is %d   stask %d\n",this,temp.length(),m_h264Data.size());
				}

			}

			//Sleep(30);
			//ConvertPsToRtp(&stPacket);
		}
		else if (stPacket.nPacketType == AUDIO_PACKET)
		{

		}
		return true;
	}
	return false;
}

bool H264FrameDeviceSource::GetVideoData(unsigned char *ptData,unsigned int &frameSize,unsigned int dataMaxSize)
{
	unsigned int timeOut=0;
	while(m_h264Data.empty())
	{
		Sleep(10);
		timeOut++;
		if(timeOut>100)
			break;
		
	}
	if(!m_h264Data.empty())
	{
		boost::asio::detail::mutex::scoped_lock lock(m_mutex);
		frameSize=m_h264Data.top().length();
		memcpy(ptData,m_h264Data.top().c_str(),frameSize);
		m_h264Data.pop();
		printf("this time:%d,this 0x%x,fFrameSize 1 is %d--%d--\n",GetTickCount(),this,frameSize,m_h264Data.size());	
		return true;
	}
	else
	{
		frameSize=0;
		return false;
	}
}
bool H264FrameDeviceSource::StartDev()
{
	StopDev();
	m_wmp_handle = WMP_Create();
	if (m_wmp_handle == -1)
	{
		return false;
	}
	int ret =  WMP_Login(m_wmp_handle,m_SdkServerData.m_sSdkServerIp.c_str(),m_SdkServerData.m_nSdkServerPort, 
			   m_SdkServerData.m_sUserName.c_str(),m_SdkServerData.m_spassword.c_str(),m_SdkServerData.m_nServerLine);
	if (ret == -1)
	{
		StopDev();
		g_logError.Write2Caching("this 0x%d,WMP_Login ret = -1 设备ID:%s,服务器线路号:%d,设备通道号:%d,设备线路号:%d m_wmp_handle:%d",this,
			m_SdkServerData.m_sDevId.c_str(),m_SdkServerData.m_nServerLine,m_SdkServerData.m_nnchannel,m_SdkServerData.m_nDevLine,m_wmp_handle);
		return false;
	}
	ret = WMP_Play(m_wmp_handle,
		m_SdkServerData.m_sDevId.c_str(),//devid:设备ID
		m_SdkServerData.m_nnchannel,//channel:设备通道号
		WMP_STREAM_MAIN, //stream_type:WMP_STREAM_MAIN 1-主码流   WMP_STREAM_SUB 2-子码流 
		WMP_TRANS_UDP,//trans_mode:WMP_TRANS_TCP/WMP_TRANS_UDP  #define WMP_TRANS_TCP	1#define WMP_TRANS_UDP	2
		m_SdkServerData.m_nDevLine,//dev_line:设备线路号
		CBF_OnStreamPlay, (void*)this,(int*)&m_stream_handle);
	g_logInfo.Write2Caching("this 0x%d,重练设备，设备ID:%s,服务器线路号:%d,设备通道号:%d,设备线路号:%d m_wmp_handle:%d,返回ret:%d",this,
		m_SdkServerData.m_sDevId.c_str(),m_SdkServerData.m_nServerLine,m_SdkServerData.m_nnchannel,m_SdkServerData.m_nDevLine,m_wmp_handle,ret);
	if (ret != 0)
	{
		return false;
	}
	return true;
}

void H264FrameDeviceSource::StopDev()
{
	if (m_wmp_handle != -1)
	{
		WMP_Stop(m_wmp_handle,m_stream_handle);
		WMP_Close(m_wmp_handle);
		g_logInfo.Write2Caching("this 0x%d,停止设备取流 m_wmp_handle %d 设备ID:%s",this,m_wmp_handle,m_SdkServerData.m_sDevId.c_str());
		m_wmp_handle = -1;
	}
	if (m_nAnalyzeHandle != -1)
	{
		AnalyzeDataClose(m_nAnalyzeHandle);
		g_logInfo.Write2Caching("this 0x%d,停止解包 m_nAnalyzeHandle %d 设备ID:%s",this,m_nAnalyzeHandle,m_SdkServerData.m_sDevId.c_str());
		m_nAnalyzeHandle = -1;
	}
	while(!m_h264Data.empty())
		m_h264Data.pop();
}
