/*****************************************************
Copyright 2008-2011 Hikvision Digital Technology Co., Ltd.

FileName: AnalyzeInterface.h

Description: 码流分析库接口
 	 
Modification History: 2008/10/22 by 洪瑜
*****************************************************/

#ifndef _ANALYZEDATAINTERFACE_H_
#define _ANALYZEDATAINTERFACE_H_

#if defined(_WINDLL)
	#define ANALYZEDATA_API  extern "C" __declspec(dllexport) 
#else 
	#define ANALYZEDATA_API  extern "C" __declspec(dllimport) 
#endif

//数据包类型
#define FILE_HEAD			            0
#define VIDEO_I_FRAME		            1
#define VIDEO_B_FRAME		            2
#define VIDEO_P_FRAME		            3
#define AUDIO_PACKET		            10
#define PRIVT_PACKET                    11

//标记
#define HIK_H264_E_FRAME        	    (1 << 6)
	    
//错误码		    
#define ERROR_NOOBJECT                  -1
#define ERROR_NO                        0
#define ERROR_OVERBUF                   1
#define ERROR_PARAMETER                 2
#define ERROR_CALL_ORDER                3
#define ERROR_ALLOC_MEMORY              4
#define ERROR_OPEN_FILE                 5
#define ERROR_MEMORY                    11
#define ERROR_SUPPORT                   12
#define ERROR_UNKNOWN                   99
#include <windows.h>
typedef struct _PACKET_INFO
{
	int		nPacketType;
	char*	pPacketBuffer;
	DWORD	dwPacketSize;
	
	int		nYear;	
	int		nMonth;
	int		nDay;
	int		nHour;
	int		nMinute;
	int		nSecond;

	DWORD   dwTimeStamp;

} PACKET_INFO;

typedef struct _PACKET_INFO_EX
{
	int		       nPacketType;
	char*	       pPacketBuffer;
	DWORD	       dwPacketSize;
	
	int		       nYear;	
	int		       nMonth;
	int		       nDay;
	int		       nHour;
	int		       nMinute;
	int		       nSecond;

	DWORD          dwTimeStamp;

	DWORD          dwFrameNum;
	DWORD          dwFrameRate;
	unsigned short uWidth;
	unsigned short uHeight;
	DWORD		   dwTimeStampHigh;
	DWORD          dwFlag;
	DWORD		   dwFilePos;
	DWORD          Reserved[4];

} PACKET_INFO_EX;

ANALYZEDATA_API int   __stdcall AnalyzeDataGetSafeHandle();

ANALYZEDATA_API BOOL  __stdcall	AnalyzeDataOpenStream(LONG lHandle);

ANALYZEDATA_API BOOL  __stdcall	AnalyzeDataOpenStreamEx(LONG lHandle, PBYTE pHeader);

ANALYZEDATA_API BOOL  __stdcall	AnalyzeDataOpenFile(LONG lHandle, char* szFileName);

ANALYZEDATA_API void  __stdcall	AnalyzeDataClose(LONG lHandle);
	
ANALYZEDATA_API BOOL  __stdcall	AnalyzeDataInputData(LONG lHandle, PBYTE pBuffer, DWORD dwSize);
	
ANALYZEDATA_API int	  __stdcall AnalyzeDataGetPacket(LONG lHandle, PACKET_INFO* pstPacket);

ANALYZEDATA_API int	  __stdcall AnalyzeDataGetPacketEx(LONG lHandle, PACKET_INFO_EX* pstPacket);

ANALYZEDATA_API BOOL  __stdcall AnalyzeDataGetTail(LONG lHandle, BYTE** pData, DWORD* pdwSize);

ANALYZEDATA_API DWORD __stdcall AnalyzeDataGetLastError(LONG lHandle);

#endif