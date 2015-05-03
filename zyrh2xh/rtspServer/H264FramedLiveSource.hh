#ifndef _H264FRAMEDLIVESOURCE_HH
#define _H264FRAMEDLIVESOURCE_HH

#include <FramedSource.hh>
#include <iostream>
#include <vector>
#include "../x264/bytestream.h"
#include "../devsdk/wmpclient.h"
#include "../devsdk/AnalyzeDataInterface.h"
#include <boost/asio/detail/mutex.hpp>
#include "../Thread.h"


struct Ps_packae_header
{
	unsigned int   unpack_start_code:32;//  32 bslbf 
	unsigned int  nVlaude01:2;//'01'  2 bslbf 
	unsigned int  system_clock_reference_base32_30:3;//  3 bslbf 
	unsigned int  marker_bit0:1;// 1 bslbf 
	unsigned int system_clock_reference_base29_15:15;//  15 bslbf  包含五个和六个字节
	unsigned int  marker_bit1:1;// 1 bslbf 
	unsigned int  system_clock_reference_base14_0:15;//15 bslbf 
	unsigned int  marker_bit2:1;//  1  bslbf 
	unsigned int  system_clock_reference_extension:9;//  9  uimsbf 
	unsigned int  marker_bit3:1;//  1 bslbf 
	unsigned int  program_mux_rate:22;//22  uimsbf 
	unsigned int  marker_bit4:1;//1 bslbf 
	unsigned int  marker_bit5:1;//1 bslbf 

	unsigned int  reserved:5;//  5  bslbf 
	unsigned int  pack_stuffing_length:3;// 3 uimsbf

	char stuffing_byte[7]; 

	__int64  nTimeStamp;


	Ps_packae_header()
	{
		//ZeroMemory(this,sizeof(Ps_packae_header));
	}

	char* SetValue( char* svalue)
	{
		char* pstart = svalue;
		unsigned short nTmp = 0;
		unpack_start_code = get_byte32(svalue);
		svalue += 4;
		//第五个字节
		unsigned char nbyte = *svalue++;
		nVlaude01 = (nbyte&0xC0)>>6;
		system_clock_reference_base32_30 = (nbyte&0x38)>>3;
		marker_bit0 = (nbyte&04)>>2;
		system_clock_reference_base29_15 = (nbyte&0x03)<<13; //占用2个字节

		//第六个字节
		nbyte = *svalue++;
		system_clock_reference_base29_15 = system_clock_reference_base29_15|(nbyte<<5);

		//第七个字节
		nbyte = *svalue++;
		system_clock_reference_base29_15 = system_clock_reference_base29_15|(nbyte&0xF8)>>3;//占用五个字节
		marker_bit1 = (nbyte&0x04)>>2;
		system_clock_reference_base14_0 = (nbyte&0x03)<<13; //占用两个字节

		//第八个字节
		nbyte = *svalue++;
		system_clock_reference_base14_0 = system_clock_reference_base14_0|(nbyte)<<5;

		//第九个字节
		nbyte = *svalue++;
		system_clock_reference_base14_0 = system_clock_reference_base14_0|(nbyte&0xF8)>>3; //占用五个字节
		marker_bit2 = (nbyte&0x04)>>2;
		system_clock_reference_extension = (nbyte&0x10)<<7; //占用两个字节


		//第十个字节
		nbyte = *svalue++;
		system_clock_reference_extension = system_clock_reference_extension|(nbyte&0xFE)>>1; //占用七个字节
		marker_bit3 = (nbyte&0x01);

		//第十一个字节
		nbyte = *svalue++;
		program_mux_rate = nbyte<<14; //共22位


		//第十二个字节
		nbyte = *svalue++;
		program_mux_rate = program_mux_rate|nbyte<<6; 

		//第十三个字节
		nbyte = *svalue++;
		program_mux_rate = program_mux_rate|(nbyte&0xFC)>>2;  ////占用六个字节
		marker_bit4 = (nbyte&0x02)>>1;
		marker_bit5 = (nbyte&0x01);

		//第十四个字节
		nbyte = *svalue++;
		reserved = (nbyte&0xF8)>>3;
		pack_stuffing_length = (nbyte&0x07);

		// 		if (pack_stuffing_length>0)
		// 		{
		// 			memcpy(stuffing_byte,svalue,pack_stuffing_length);
		// 		}

		svalue += pack_stuffing_length;
		__int64 system_clock_reference_base29_15_tmp  = system_clock_reference_base29_15;
		__int64 system_clock_reference_base32_30_tmp = system_clock_reference_base32_30;
		nTimeStamp = (system_clock_reference_base29_15_tmp<<15)|system_clock_reference_base14_0|(system_clock_reference_base32_30_tmp<<30);

		return svalue;
	}

};
struct pes_packae_header
{
	unsigned int  unpack_start_code:32;//  32 bslbf 
	unsigned int  PES_packet_length:16;// 包长 

	unsigned int  nVlaude01:2;//  2 bslbf 
	unsigned int  PES_scrambling_control :2;// 1 bslbf 
	unsigned int  PES_priority :1;//  1 bslbf  
	unsigned int  data_alignment_indicator :1;// 1 bslbf   
	unsigned int  copyright:1;//1 bslbf 
	unsigned int  original_or_copy:1;//1 bslbf 

	unsigned int  PTS_DTS_flags:2;//  2  bslbf 
	unsigned int  ESCR_flag:1;//  1  bslbf 
	unsigned int  ES_rate_flag:1;//  1 bslbf 
	unsigned int  DSM_trick_mode_flag:1;//1  bslbf 
	unsigned int  additional_copy_info_flag:1;//1 bslbf 
	unsigned int  PES_CRC_flag:1;//1 bslbf 
	unsigned int  PES_extension_flag:1;//1 bslbf

	unsigned int  PES_header_data_length:8;// 16 bslbf

	//假设PTS_DTS_flags == 0x02 
	unsigned int  nValue0010:4;//4 bslbf 
	unsigned int  nPTS32_30:3; //3  bslbf 
	unsigned int  marker_bit0:1;//1  bslbf 
	unsigned int  PTS29_15:15;//15 bslbf 
	unsigned int  marker_bit1:1;// 1  bslbf 
	unsigned int  PTS14_0:15;//15  bslbf 
	unsigned int  marker_bit2:1;// 1 bslbf
	__int64  nTimeStamp;

	char stuffing_byte[0xf];

	char *packagedata;
	unsigned int packagedatalen;



	pes_packae_header()
	{
		//ZeroMemory(this,sizeof(Ps_packae_header));
		nTimeStamp = 0;
		packagedata = NULL;
	}
	~pes_packae_header()
	{
		if(packagedata)
		{
			delete[] packagedata;
			packagedata = NULL;
		}
	}

	char* SetValue( char* svalue)
	{
		char* pstart = svalue;

		unpack_start_code = get_byte32(svalue);
		svalue += 4;
		//第五、六字节
		PES_packet_length = get_byte16(svalue);
		svalue += 2;
		//第七个字节
		unsigned char nbyte = *svalue++;
		nVlaude01 = (nbyte&0xC0)>>6;
		PES_scrambling_control = (nbyte&0x30)>>4;
		PES_priority = (nbyte&0x08)>>3;
		data_alignment_indicator = (nbyte&0x04)>>2; 
		copyright = (nbyte&0x02)>>1;
		original_or_copy = (nbyte&0x01);

		//第八个字节
		nbyte = *svalue++;
		PTS_DTS_flags = (nbyte&0xC0)>>6; ;//  2  bslbf 
		ESCR_flag = (nbyte&0x20)>>5;//  1  bslbf 
		ES_rate_flag = (nbyte&0x10)>>4;;//  1 bslbf 
		DSM_trick_mode_flag = (nbyte&0x08)>>3;//1  bslbf 
		additional_copy_info_flag = (nbyte&0x40)>>2;//1 bslbf 
		PES_CRC_flag = (nbyte&0x20)>>1;//1 bslbf 
		PES_extension_flag = (nbyte&0x01);//1 bslbf

		//第九个字节
		nbyte = *svalue++;
		PES_header_data_length = nbyte;
		unsigned int header_data_length = PES_header_data_length;

		if (PTS_DTS_flags == 0x02)
		{
			unsigned short n16Tmp;
			//第十个字节
			nbyte = *svalue++;
			nValue0010 = (nbyte&0xF0)>>4;//4 bslbf 
			nPTS32_30 = (nbyte&0x0E)>>1; //3  bslbf 
			marker_bit0 = (nbyte&0x01);//1  bslbf 

			//第十一个字节
			nbyte = *svalue++;
			n16Tmp  = nbyte<<7;

			//第十二个字节
			nbyte = *svalue++;
			PTS29_15 = n16Tmp|(nbyte&0xFE)>>1;
			marker_bit1 = (nbyte&0x01);

			//第十三个字节
			nbyte = *svalue++;
			n16Tmp = nbyte<<7;

			//第十四个字节
			nbyte = *svalue++;
			PTS14_0 = n16Tmp|(nbyte&0xFE)>>1;
			marker_bit2 = (nbyte&0x01);

			__int64 nPTS32_30_tmp = nPTS32_30;
			__int64 PTS29_15_tmp = PTS29_15;
			nTimeStamp = (nPTS32_30_tmp<<30)|(PTS29_15_tmp<<15)|PTS14_0;
			header_data_length -= 5;
		}
		else if (PTS_DTS_flags == 0x03)
		{
		}
		else if (PTS_DTS_flags == 0x00)
		{
		}
		memcpy(stuffing_byte,svalue,header_data_length);
		svalue += header_data_length; 
		if (svalue - pstart <  PES_packet_length + 6 )
		{
			if (packagedata != NULL)
			{
				delete[] packagedata;
				packagedata = NULL;

			}
			packagedatalen = PES_packet_length + 6 - (svalue - pstart) ;
			packagedata = new char[packagedatalen];
			memcpy(packagedata,svalue,packagedatalen);
			svalue += packagedatalen; 
		}
		return svalue;
	}

};

class SDKServerData
{
public:

	SDKServerData()
	{
		m_sSdkServerIp="";
		m_nSdkServerPort=0;
		m_spassword="";
		m_sUserName="";
		m_nServerLine=0;

		m_nDevLine=0;
		m_nnchannel=0;
		m_sDevId="";
	}

	SDKServerData(std::string sSdkServerIp,unsigned int nSdkServerPort,std::string sPassword,
						std::string sUserName,unsigned int nServerLine,unsigned int nDevLine,
						unsigned int nChannel,std::string sDevId)
	{
		m_sSdkServerIp=sSdkServerIp;
		m_nSdkServerPort=nSdkServerPort;
		m_spassword=sPassword;
		m_sUserName=sUserName;
		m_nServerLine=nServerLine;

		m_nDevLine=nDevLine;
		m_nnchannel=nChannel;
		m_sDevId=sDevId;
	};
public:	
	//sdk 信息
	std::string 	m_sSdkServerIp;
	unsigned int 	m_nSdkServerPort;
	std::string	 	m_spassword;
	std::string 	m_sUserName;
	unsigned int 	m_nServerLine;

	unsigned int 	m_nDevLine;
	unsigned int 	m_nnchannel;
	std::string 	m_sDevId;
	
};

#pragma pack(1)
	
union littel_endian_size
{
	unsigned short int	length;
	unsigned char		byte[2];
};

struct pack_start_code
{
	unsigned char start_code[3];
	unsigned char stream_id[1];
};

struct program_stream_pack_header
{
	pack_start_code PackStart;// 4
	unsigned char Buf[9];
	unsigned char stuffinglen;
};

struct program_stream_map
{
	pack_start_code PackStart;
	littel_endian_size PackLength;//we mast do exchange
	//program_stream_info_length
	//info
	//elementary_stream_map_length
	//elem
};

struct program_stream_e
{
	pack_start_code		PackStart;
	littel_endian_size	PackLength;//we mast do exchange
	char				PackInfo1[2];
	unsigned char		stuffing_length;
};

#pragma pack()

class H264FrameDeviceSource
{

public:

	H264FrameDeviceSource(SDKServerData nSdkServerData);
	bool GetVideoData(std::vector<std::string > *vDeviceSource,unsigned char *ptData,unsigned int &frameSize,unsigned int dataMaxSize,unsigned int &curVideoIndex);
	~H264FrameDeviceSource();
	
	//***********************zyrh begin******************************
	bool StartDev(char* sSdkServerIp,unsigned int nSdkServerPort,char* user,char* password,int nServerLine,char* sdevId,unsigned int nDevLine,unsigned int nchannel);
	bool StartDev();
	void StopDev();
	bool ReStartDev();
	void ControlDevice();
	bool InPutPsData(unsigned char* videoPsBuf,unsigned int  psBufsize,int nType );
	bool zyrh_AnalyzeDataGetPacketEx(char* h264OutBuf,unsigned int& nh264Size,unsigned int& TimeStamp,unsigned int& nDataType);
	bool Ps_AnalyzeDataGetPacketEx();
	//***********************zyrh end******************************	
	bool addDeviceSource(std::vector<std::string > *vDeviceSource)
	{
		boost::asio::detail::mutex::scoped_lock lock(m_mutex);
		if(m_deviceSource.size()>10)
			return false;
		m_deviceSource.push_back(vDeviceSource);
		return true;
	}
	bool removeDeviceSource(std::vector<std::string > *vDeviceSource)
	{
		unsigned int i=0;
		boost::asio::detail::mutex::scoped_lock lock(m_mutex);
		for (i=0; i<m_deviceSource.size(); i++)
		{
			if(m_deviceSource[i]==vDeviceSource)
			{
				m_deviceSource.erase(m_deviceSource.begin()+i);
				//printf("remove is ---\n");
				return true;
			}
	
		}
		return false;
	}
	
public:
	int         m_stream_handle;
	//设备的解包的句柄
	int	 		m_nAnalyzeHandle;
	std::string m_strHead;
	char* 		m_h264Buf;
	int			m_cmdType;
	boost::asio::detail::mutex m_mutex;
	std::vector<std::vector<std::string > *> m_deviceSource;
		
	CThread m_DevcieThead;

private:
	WMP_HANDLE m_wmp_handle;
	SDKServerData m_SdkServerData;

};

class H264FramedLiveSource : public FramedSource
{
public:
	static H264FramedLiveSource* createNew(UsageEnvironment& env,H264FrameDeviceSource *ptH264FrameDeviceSource, unsigned preferredFrameSize = 0, unsigned playTimePerFrame = 0);
	void setDeviceSource(H264FrameDeviceSource *deviceSource)
	{
		m_ptH264FrameDeviceSource = deviceSource;
		m_ptH264FrameDeviceSource->addDeviceSource(&m_h264Data);
		m_ptH264FrameDeviceSource->StartDev();
	}

protected:
	H264FramedLiveSource(UsageEnvironment& env,H264FrameDeviceSource *ptH264FrameDeviceSource, unsigned preferredFrameSize, unsigned playTimePerFrame);
	~H264FramedLiveSource();
	

private:
	virtual void doGetNextFrame();
	
	int TransportData(unsigned char* to, unsigned maxSize);
	
	
protected:
	//int Framed_datasize;//数据区大小指针
	//unsigned char *Framed_databuf;//数据区指针
	//bool Framed_dosent;//发送标示

	//int readbufsize;//记录已读取数据区大小
	//int bufsizel;//记录数据区大小
	unsigned int m_curVideoIndex;
	std::vector<std::string > m_h264Data;
	
public:
	H264FrameDeviceSource *m_ptH264FrameDeviceSource;

};

#endif
