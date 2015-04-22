#include "MyRtmp.h"
#include "../x264/H264FrameParser.h"
#include "../x264/sps.h"
#include "AnalyzeDataInterface.h"
//长度为14个字节

#pragma pop()//恢复对齐状态
CMyRtmp::CMyRtmp(void)
{
	m_pRtmp = RTMP_Alloc();
	RTMP_Init(m_pRtmp);
	m_outbuf = new uint8_t[1000*500];
	ResetParam();
	WSADATA WSAData;
	WSAStartup( MAKEWORD( 1, 1 ), &WSAData );//初始化
	m_outBufPsVideo = new char[1024*512];
	m_nAnalyzeHandle = -1;


}

CMyRtmp::~CMyRtmp(void)
{
	if (m_nAnalyzeHandle != -1)
	{
		AnalyzeDataClose(m_nAnalyzeHandle);
	}
	if (m_pRtmp != NULL)
	{
		
		RTMP_Free(m_pRtmp);
		m_pRtmp = NULL;
	}
	
	WSACleanup();
	
	delete[] m_outbuf;
	delete[] m_outBufPsVideo;
}
void CMyRtmp::StopRtmp()
{
	if (m_nAnalyzeHandle != -1)
	{
		AnalyzeDataClose(m_nAnalyzeHandle);
	}
	if (m_pRtmp != NULL)
	{
		RTMP_Close(m_pRtmp);
	}

}
void CMyRtmp::SetParamVideo(uint32_t nWidth,uint32_t nHeight,uint32_t nFrameRate)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nFrameRate = nFrameRate;
	m_bSetparamVideo = true;

}
void CMyRtmp::SetParamAudio(int nSampleRate,int nNumChannels)
{
	m_nSampleRate = nSampleRate;
	m_nNumChannels = nNumChannels;
	m_bSetparamAudio = true;

}
void CMyRtmp::ResetParam()
{
	m_bVideobegin = false;
	m_bSetparamVideo = false;
	m_bSetparamAudio = false;
	m_bVideoHead = false;
	m_bAudioHead = false;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nFrameRate = 0;
    m_nPpsLen = 0;
	m_nSpsLen = 0;
	m_outlen = 0;
	m_nBeginTic = 1000;
	m_nLastTic = 0;
	m_nSampleRate = 0;
	m_nNumChannels = 0;
	m_outPslen = 0;
	
}



void CMyRtmp::SendRtmp(buffer *pbuf,uint32_t type,__int64 nTimeStamp)
{
	RTMPPacket rtmpPacket;
	RTMPPacket_Reset(&rtmpPacket);
	RTMPPacket_Alloc(&rtmpPacket,pbuf->d_cur);

	rtmpPacket.m_packetType = type;
	rtmpPacket.m_nBodySize = pbuf->d_cur;
	rtmpPacket.m_nTimeStamp = nTimeStamp;
    rtmpPacket.m_nChannel = 4;
	rtmpPacket.m_headerType = RTMP_PACKET_SIZE_LARGE;
	rtmpPacket.m_packetType = type;
	rtmpPacket.m_nInfoField2 = m_pRtmp->m_stream_id;

	memcpy(rtmpPacket.m_body,pbuf->data,pbuf->d_cur);

	
	int ret1 = RTMP_IsConnected(m_pRtmp);
	//int ret2 = RTMP_IsTimedout(m_pRtmp);
	if (  ret1 <= 0 )
	{
		ResetParam();
		RTMP_Close(m_pRtmp);
		RTMP_Init(m_pRtmp);
		OpenUrl(m_strUrl);	
		RTMPPacket_Free(&rtmpPacket);
		return;
	}
	int ret = RTMP_SendPacket(m_pRtmp,&rtmpPacket,0);
	RTMPPacket_Free(&rtmpPacket);

}
bool CMyRtmp::OpenUrl(std::string url)
{
	bool bret = false;
	m_strUrl = url;
	int err= RTMP_SetupURL(m_pRtmp,(char*)url.c_str());
	if (err <= 0)
	{
		return bret;
	}
	RTMP_EnableWrite(m_pRtmp);
	err = RTMP_Connect(m_pRtmp,NULL);
	if (err <= 0)
	{
		return bret;
	}
	err = RTMP_ConnectStream(m_pRtmp,0);
	if (err <= 0)
	{
		return bret;
	}
	bret = true;
	m_strUrl = url;
	return bret;
}
bool CMyRtmp::SetUrl(std::string url)
{
	m_strUrl = url;
	return true;
}
void CMyRtmp::WriteVideoFrame(uint8_t *p_nalu, int i_size, bool key,uint64_t NowTic,__int64 offset)
{
	buffer *c = new buffer(1024);

	// A new frame - write packet header
	//put_byte( c, FLV_TAG_TYPE_VIDEO );

	put_byte( c, key ? FLV_FRAME_KEY : FLV_FRAME_INTER );
	put_byte( c, 1 ); // AVC NALU
	put_be24( c, offset );


	append_data( c, p_nalu, i_size );

	SendRtmp(c,FLV_TAG_TYPE_VIDEO,NowTic);
	delete c;
}
__int64 CMyRtmp::CheckTimeStamp(__int64 nowTimeStamp)
{

	boost::asio::detail::mutex::scoped_lock lock(mutex_Lock);

	if (m_nLastTic == 0)
	{
		m_nLastTic = nowTimeStamp;
		m_nBeginTic = 0;
		m_nNowTic = m_nBeginTic;

	}
	else
	{
		if (m_nLastTic >= nowTimeStamp)
		{
			m_nNowTic += 10;
		}
		else
		{
			m_nNowTic += (nowTimeStamp - m_nLastTic);
		}
		m_nLastTic = nowTimeStamp;
	}
	return m_nNowTic;
}
__int64 CMyRtmp::CheckTimeStampOffset(__int64 nowTimeStamp )
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_Lock);
	__int64 retTs;
	if (m_nLsatVideoTic == 0)
	{
		m_nLsatVideoTic = nowTimeStamp;
		retTs = m_nLsatVideoTic;
	}
	else
	{
		retTs = nowTimeStamp - m_nLsatVideoTic;
		m_nLsatVideoTic = nowTimeStamp;
	}
	return retTs;
}
void CMyRtmp::WriteAudioHeaders(int nSoundRate, int nChannel)
{
	buffer *c = new buffer(1024);

	uint8_t nSoundRateIndex = GetSoundRateIndex(nSoundRate);

	//put AUDIODATA 
	uint8_t flag = 10<<4 | //10 = AAC 
		nSoundRateIndex<<2  //0 = 5.5-kHz  1 = 11-kHz 2 = 22-kHz 3 = 44-kHz 
		| 1<<1 //Size of each sample   For AAC: always 1 
		| 1;  //Mono or stereo sound  For AAC: always 1 
	put_byte( c, flag );

	put_byte( c, 0);//0: AAC sequence header
	//put AudioSpecificConfig
	int nSampleIndex = GetSoundSampleIndex(nSoundRate); 
	uint16_t AudioSpecificConfig = 2<<11 |nSampleIndex<<7|2<<3;
	put_be16( c, AudioSpecificConfig );

	SendRtmp(c,FLV_TAG_TYPE_AUDIO,0);
	delete c;
}
void CMyRtmp::WriteAacFrame(uint8_t *p_aac, int i_size, uint64_t NowTic,int nChannel,int nSoundRate)
{
	// A new frame - write packet header
	buffer *c = new buffer(1024);

	uint8_t nSoundRateIndex = GetSoundRateIndex(nSoundRate);

	//put AUDIODATA 
	uint8_t flag = 10<<4 | //10 = AAC 
		nSoundRateIndex<<2  //0 = 5.5-kHz  1 = 11-kHz 2 = 22-kHz 3 = 44-kHz 
		| 1<<1 //Size of each sample   For AAC: always 1 
		| 1;  //Mono or stereo sound  For AAC: always 1 
	put_byte( c, flag );

	put_byte( c, 1);//1: AAC raw 
	append_data( c, p_aac, i_size );// Raw AAC frame data 
	SendRtmp(c,FLV_TAG_TYPE_AUDIO,NowTic);
	delete c;
}
int GetSoundSampleIndex(int nSoundRate)
{
	int nSampleIndex = 0x07;
	switch (nSoundRate)
	{
	case 96000:
		nSampleIndex = 0x00;	
		break;
	case 88200:
		nSampleIndex = 0x01;	
		break;
	case 64000:
		nSampleIndex = 0x02;	
		break;
	case 48000:
		nSampleIndex = 0x03;	
		break;
	case 44100:
		nSampleIndex = 0x04;	
		break;
	case 32000:
		nSampleIndex = 0x05;	
		break;
	case 24000:
		nSampleIndex = 0x06;	
		break;
	case 22050:
		nSampleIndex = 0x07;	
		break;
	case 16000:
		nSampleIndex = 0x08;	
		break;
	case 12000:
		nSampleIndex = 0x09;	
		break;
	case 11025:
		nSampleIndex = 0x0A;	
		break;
	case 8000:
		nSampleIndex = 0x0B;	
		break;
	case 7350:
		nSampleIndex = 0x0C;	
		break;
	}
	return nSampleIndex;
}
int GetSoundRateIndex(int nSize)
{
	if (nSize <= 8000)
		return 0;
	if (nSize > 8000 && nSize <= 16000)
		return 1;
	if (nSize > 16000 && nSize <= 32000)
		return 2;
	else
		return 3;
}
typedef struct _HIK_MEDIAINFO_				// modified by gb 080425
{
	unsigned int    media_fourcc;			// "HKMI": 0x484B4D49 Hikvision Media Information
	unsigned short  media_version;			// 版本号：指本信息结构版本号，目前为0x0101,即1.01版本，01：主版本号；01：子版本号。
	unsigned short  device_id;				// 设备ID，便于跟踪/分析			

	unsigned short  system_format;          // 系统封装层
	unsigned short  video_format;           // 视频编码类型

	unsigned short  audio_format;           // 音频编码类型
	unsigned char   audio_channels;         // 通道数  
	unsigned char   audio_bits_per_sample;  // 样位率
	unsigned int    audio_samplesrate;      // 采样率 
	unsigned int    audio_bitrate;          // 压缩音频码率,单位：bit

	unsigned int    reserved[4];            // 保留
}HIK_MEDIAINFO;
//stPacket.nPacketType 
bool CMyRtmp::InPutPsData(uint8_t* videoPsBuf,uint32_t psBufsize )
{
	if(m_nAnalyzeHandle == -1)
	{
// 		_HIK_MEDIAINFO_ sHead;
// 		ZeroMemory((char*)&sHead,sizeof(_HIK_MEDIAINFO_));
// 		sHead.media_fourcc = 'HKMI';
// 		sHead.media_version = 0x0101;
// 		sHead.device_id = 1;
// 		sHead.system_format = 0x02;
// 		sHead.video_format = 0x01;
// 		sHead.audio_format = 0x7110;
// 		sHead.audio_channels = 0x01;
// 		sHead.audio_bits_per_sample = 0x10;
// 		sHead.audio_samplesrate = 0x1F40;
// 		sHead.audio_bitrate = 0xFA00;
 		m_nAnalyzeHandle = AnalyzeDataGetSafeHandle();
		AnalyzeDataOpenStreamEx(m_nAnalyzeHandle, (PBYTE)videoPsBuf);
		OpenUrl(m_strUrl);
		//AnalyzeDataInputData(m_nAnalyzeHandle, videoPsBuf, psBufsize);
	}
	else
	{
		AnalyzeDataInputData(m_nAnalyzeHandle, videoPsBuf, psBufsize);
	}
	return true;
}
bool CMyRtmp::Ps_AnalyzeDataGetPacketEx(char* h264OutBuf,unsigned int& nh264Size,unsigned int& TimeStamp,unsigned int& nDataType)
{
	if (m_nAnalyzeHandle == -1)
	{
		return false;
	}
	PACKET_INFO_EX stPacket;
    while (AnalyzeDataGetPacketEx(m_nAnalyzeHandle, &stPacket) == 0)
	{
		if (stPacket.nPacketType == VIDEO_I_FRAME ||stPacket.nPacketType == VIDEO_P_FRAME||stPacket.nPacketType == VIDEO_B_FRAME)
		{
			Ps_packae_header Ps_packae_header_;
			pes_packae_header pes_packae_header_;
			char* pStart = stPacket.pPacketBuffer;
			char* pEnd = stPacket.pPacketBuffer + stPacket.dwPacketSize;
			TimeStamp = stPacket.dwTimeStamp;
			nh264Size = 0;
			while (pStart < pEnd)
			{
				unsigned char nType = (unsigned char)*(pStart + 3) ;	
				unsigned short ndatelen = 0;
				
				if (nType == 0xba)
				{
				    pStart = Ps_packae_header_.SetValue(pStart);
				}
				else if(nType == 0xE0)
				{
					pStart = pes_packae_header_.SetValue(pStart);
					memcpy(h264OutBuf+nh264Size,pes_packae_header_.packagedata,pes_packae_header_.packagedatalen);
					nh264Size += pes_packae_header_.packagedatalen;
				}
				else
				{
					unsigned short ndatelen = get_byte16(pStart + 4);
					pStart += ndatelen + 6; 
				}
			}
			if (nh264Size>0)
			{
				nDataType = 1;
				return true;
			}
			
		}
		else if (stPacket.nPacketType == AUDIO_PACKET)
		{
			pes_packae_header pes_packae_header_;
			char* pStart = stPacket.pPacketBuffer;
			char* pEnd = stPacket.pPacketBuffer + stPacket.dwPacketSize;
			unsigned char nType = (unsigned char)*(pStart + 3) ;
			while (pStart < pEnd)
			{
				unsigned char nType = (unsigned char)*(pStart + 3) ;	
				unsigned short ndatelen = 0;

				if(nType == 0xC0)
				{
					pStart = pes_packae_header_.SetValue(pStart);
					memcpy(h264OutBuf+nh264Size,pes_packae_header_.packagedata,pes_packae_header_.packagedatalen);
					nh264Size += pes_packae_header_.packagedatalen;
				}
				else
				{
					unsigned short ndatelen = get_byte16(pStart + 4);
					pStart += ndatelen + 6; 
				}
			}
			TimeStamp = stPacket.dwTimeStamp;
			nDataType = 2;
			if (nh264Size>0)
			{
				return true;
			}
		}
	}
	return false;
}
