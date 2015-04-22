#pragma once
#include <string>
#include <boost/asio/detail/mutex.hpp>
#include "../x264/bytestream.h"
/* offsets for packed values */
#define FLV_AUDIO_SAMPLESSIZE_OFFSET 1
#define FLV_AUDIO_SAMPLERATE_OFFSET  2
#define FLV_AUDIO_CODECID_OFFSET     4

#define FLV_VIDEO_FRAMETYPE_OFFSET   4

/* bitmasks to isolate specific values */
#define FLV_AUDIO_CHANNEL_MASK    0x01
#define FLV_AUDIO_SAMPLESIZE_MASK 0x02
#define FLV_AUDIO_SAMPLERATE_MASK 0x0c
#define FLV_AUDIO_CODECID_MASK    0xf0

#define FLV_VIDEO_CODECID_MASK    0x0f
#define FLV_VIDEO_FRAMETYPE_MASK  0xf0

#define AMF_END_OF_OBJECT         0x09

enum
{
	FLV_HEADER_FLAG_HASVIDEO = 1,
	FLV_HEADER_FLAG_HASAUDIO = 4,
};

enum
{
	FLV_TAG_TYPE_AUDIO = 0x08,
	FLV_TAG_TYPE_VIDEO = 0x09,
	FLV_TAG_TYPE_META  = 0x12,
};

enum
{
	FLV_MONO   = 0,
	FLV_STEREO = 1,
};

enum
{
	FLV_SAMPLESSIZE_8BIT  = 0,
	FLV_SAMPLESSIZE_16BIT = 1 << FLV_AUDIO_SAMPLESSIZE_OFFSET,
};

enum
{
	FLV_SAMPLERATE_SPECIAL = 0, /**< signifies 5512Hz and 8000Hz in the case of NELLYMOSER */
	FLV_SAMPLERATE_11025HZ = 1 << FLV_AUDIO_SAMPLERATE_OFFSET,
	FLV_SAMPLERATE_22050HZ = 2 << FLV_AUDIO_SAMPLERATE_OFFSET,
	FLV_SAMPLERATE_44100HZ = 3 << FLV_AUDIO_SAMPLERATE_OFFSET,
};

enum
{
	FLV_CODECID_MP3 = 2 << FLV_AUDIO_CODECID_OFFSET,
	FLV_CODECID_AAC = 10<< FLV_AUDIO_CODECID_OFFSET,
};

enum
{
	FLV_CODECID_H264 = 7,
};

enum
{
	FLV_FRAME_KEY   = 1 << FLV_VIDEO_FRAMETYPE_OFFSET | 7,
	FLV_FRAME_INTER = 2 << FLV_VIDEO_FRAMETYPE_OFFSET | 7,
};



int GetSoundSampleIndex(int nSoundRate);
int GetSoundRateIndex(int nSize);

class CMyRtmp
{
public:
	CMyRtmp();
	~CMyRtmp(void);
	void handleVideo(uint8_t* vidoedata,uint32_t nsize,__int64 TimeStamp);
	void handleAudio(uint8_t *pAudio, int i_size,uint8_t audioType, uint64_t NowTic,int nChannel,int nSoundRate);
	void SetParamVideo(uint32_t nWidth,uint32_t nHeight,uint32_t nFrameRate);
	void SetParamAudio(int nSampleRate,int nNumChannels);
	bool OpenUrl(std::string url);
	void SendRtmp(buffer *pbuf,uint32_t type,__int64 nTimeStamp);
	bool InPutPsData(uint8_t* videoPsBuf,uint32_t psBufsize);
	bool Ps_AnalyzeDataGetPacketEx(char* h264OutBuf,unsigned int& nh264Size,unsigned int& TimeStamp,unsigned int& nDataType );

	bool SetUrl(std::string url);
	void StopRtmp();
private:
	
	RTMP* m_pRtmp;
	char m_pNalSPS[256];
	unsigned int m_nSpsLen;
	char m_pNalPPS[256];
	unsigned int m_nPpsLen;
	bool m_bVideobegin;//视频是否开始写了
	bool m_bSetparamVideo;//是否写入了Video param
	bool m_bSetparamAudio;//是否写入了Audio param
	bool m_bVideoHead;//是否写入了视频头了
	bool m_bAudioHead;//是否写入了音频头了
	uint8_t* m_outbuf;
	int      m_outlen;
	__int64  m_nLastTic;
	__int64  m_nLsatVideoTic;
	__int64  m_nBeginTic;
	__int64  m_nNowTic;
	//视频参数
	uint32_t m_nWidth;
	uint32_t m_nHeight;
	uint32_t m_nFrameRate;

	//音频参数
	int m_nSampleRate;//采样率
	int m_nNumChannels;//通道数

	//url 
	std::string m_strUrl;

	boost::asio::detail::mutex mutex_Lock;

	char* m_outBufPsVideo;
	uint32_t m_outPslen;
	unsigned int m_PsLastTic;
	int m_nAnalyzeHandle;
private:
	
	void ResetParam();
	__int64 CheckTimeStamp(__int64 nowTimeStamp);
	__int64 CheckTimeStampOffset(__int64 nowTimeStamp );

	//视频
	int WriteVidoeHeaders(char* pNalSPS,unsigned int nSpsLen,char* pNalPPS,unsigned int nPpsLen);
	void WriteVideoFrame(uint8_t *p_nalu, int i_size, bool key,uint64_t NowTic,__int64 offset);
    //声音
	void WriteAudioHeaders(int nSoundRate, int nChannel);
	void WriteAacFrame(uint8_t *p_aac, int i_size, uint64_t NowTic,int nChannel,int nSoundRate);
	void WriteAudioFrame(uint8_t *pAudio, int i_size,uint8_t audioType, uint64_t NowTic,int nChannel,int nSoundRate);
};
