

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


 __int64   InitEncoder();
//
/*
【in】 h264VidoeBuf:完整的一帧h264视频数据
【in】 nH264BufLength 视频数据长度
【in】 nTimeStamp：时间戳 
【out】OutHKBuf 返回的海康流的缓冲区，缓冲区应足够大，一般考虑关键帧的话512kb
【out】nOutHKLen 返回的海康流的长度
【return】 bool true 成功 false 返回失败
*/
 bool  __stdcall ConvertH264ToHKPs(long nPort,char* h264VidoeBuf,unsigned int nH264BufLength,__int64 nTimeStamp,char* OutHKBuf,unsigned int& nOutHKLen );

 /*
 【in】 audioBuf: 音频数据
 【in】 nAudioBufLength 音频数据长度
 【out】outBufAudio返回的完整的h264视频数据长度，缓冲区应足够大，一般考虑关键帧的话512kb
 【out】nOutHKLen  返回的完整的h264视频数据的长度
 【return】 bool true 成功 false 返回失败
 */
bool  __stdcall ConvertAudioToHk(long nPort,char* audioBuf,unsigned int nAudioBufLength,__int64 nTimeStamp,char* outBufAudio,unsigned int& nOutHKLen );


 /*
 【in】 h264VidoeBuf:完整的一帧h264视频数据
 【in】 nH264BufLength 视频数据长度
 【in】 nTimeStamp：时间戳 
 【in】  char* sDevID:设备ID
 【out】OutHKBuf 返回的海康流Rtp流的缓冲区，缓冲区应足够大，一般考虑关键帧的话512kb
 【out】nOutHKLen 返回的海康流的长度
 【return】 bool true 成功 false 返回失败
 */
bool  __stdcall ConvertH264ToHKRtp(long nPort,char* h264VidoeBuf,unsigned int nH264BufLength,__int64 nTimeStamp,char* sDevID,char* OutHKBuf,unsigned int& nOutHKLen );
/*
【in】 h264Buf: 不完整的h264数据
【in】 nH264BufLength 视频数据长度
【out】outBufH264 返回的完整的h264视频数据长度，缓冲区应足够大，一般考虑关键帧的话512kb
【out】nOutHKLen  返回的完整的h264视频数据的长度
【return】 bool true 成功 false 返回失败
*/
 bool __stdcall H264_InputData(long nPort,char* h264Buf,unsigned int nH264BufLen,char* outBufH264,unsigned int& outLen);




  /*
  设置rtmp的地址
 【in】 strRtmpUrl: rtmp的地址
 【in】 nPort       rmtp的通道
 【return】 bool true 成功 false 返回失败
 */
int    openRtmpUrl(__int64 nPort,char* sdevId,char* password,__int64 nDevLine,__int64 nchannel, char* strRtmpUrl);

 bool  Ps_InputData(long nPort,char* psVideoData,unsigned int nPsDatalen);


 bool  Ps_AnalyzeDataGetPacketEx(long nPort,char* pH264VideoData,unsigned int& nH264Datalen,unsigned int& nTimeStamp,unsigned int& nType);


bool  SendRtmpVideoData(long nPort,char* videoData,unsigned int nvideolen,unsigned int nTimeStamp);


bool  SendRtmpAduioData(long nPort,char *pAudio, int i_size,unsigned char audioType, unsigned int NowTic,int nChannel,int nSoundRate);
bool  UnInitEncoder(__int64 nPort);
int  opentestchar(__int64 nPort, char* sdevIp);
#ifdef __cplusplus
}
#endif
//调用流程
/*h264 转HKPs流
1.long nPort = InitEncoder();
如果取到的视频时完整的一帧，直接调用
ConvertH264ToHK();
如果取到的视频时不是完整的一帧，直接调用
if（H264_InputData）
{
   ConvertH264ToHK();
}
结束转换
UnInitEncoder(nPort);
*/


/*h264 转HK Rtp流
1.long nPort = InitEncoder();
如果取到的视频时完整的一帧，直接调用
ConvertH264ToHKRtp();
如果取到的视频时不是完整的一帧，直接调用
if（H264_InputData）
{
ConvertH264ToHKRtp();
}
结束转换
UnInitEncoder(nPort);
*/


/*海康Ps流转成 转Rtmp流
1.long nPort = InitEncoder();
//连接到rtmp
openRtmpUrl（nPort,Rtmp完整的地址）
UnInitEncoder(nPort);
*/
