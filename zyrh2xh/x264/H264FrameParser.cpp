
#include "H264FrameParser.h"
#include <memory.h>

 char h264startcodebuf[]  = {0x00, 0x00, 0x00, 0x01};
 unsigned int BytesToUI32(const char* buf)
 {
	 return ( (((unsigned int)buf[0]) << 24)	& 0xff000000 )
		 | ( (((unsigned int)buf[1]) << 16)	& 0xff0000 )
		 | ( (((unsigned int)buf[2]) << 8)	& 0xff00 )
		 | ( (((unsigned int)buf[3]))		& 0xff );
 }

 inline char* UI32ToBytes(char* buf, unsigned int val)
 {
	 buf[0] = (char)(val >> 24) & 0xff;
	 buf[1] = (char)(val >> 16) & 0xff;
	 buf[2] = (char)(val >> 8) & 0xff;
	 buf[3] = (char)(val) & 0xff;
	 return buf + 4;
 }
const char* AVCFindStartCodeInternal(const char *p, const char *end)
{
    const char *a = p + 4 - ((intptr_t)p & 3);

    for (end -= 3; p < a && p < end; p++) { // 000001 NAL头部
        if (p[0] == 0 && p[1] == 0 && p[2] == 1)
            return p;
    }

    for (end -= 3; p < end; p += 4) {
        unsigned int x = *(const unsigned int*)p;
        //      if ((x - 0x01000100) & (~x) & 0x80008000) // little endian
        //      if ((x - 0x00010001) & (~x) & 0x00800080) // big endian
        if ((x - 0x01010101) & (~x) & 0x80808080) { // generic
            if (p[1] == 0) {
                if (p[0] == 0 && p[2] == 1)
                    return p;
                if (p[2] == 0 && p[3] == 1)
                    return p+1;
            }
            if (p[3] == 0) {
                if (p[2] == 0 && p[4] == 1)
                    return p+2;
                if (p[4] == 0 && p[5] == 1)
                    return p+3;
            }
        }
    }

    for (end += 3; p < end; p++) {
        if (p[0] == 0 && p[1] == 0 && p[2] == 1)
            return p;
    }

    return end + 3;
}

const char* AVCFindStartCode(const char *p, const char *end)
{
    const char *out= AVCFindStartCodeInternal(p, end);
    if(p<out && out<end && !out[-1]) out--;
    return out;
}

void AVCParseNalUnits(const char *bufIn, int inSize, char* bufOut, int* outSize)
{
    const char *p = bufIn;
    const char *end = p + inSize;
    const char *nal_start, *nal_end;

    char* pbuf = bufOut;

    *outSize = 0;
	// 查找NAL起始字节
    nal_start = AVCFindStartCode(p, end);
    while (nal_start < end)
    {
        while(!*(nal_start++));

        nal_end = AVCFindStartCode(nal_start, end);

        unsigned int nal_size = nal_end - nal_start;
		// 把4字节的NAL头部写成长度
        pbuf = UI32ToBytes(pbuf, nal_size);
        memcpy(pbuf, nal_start, nal_size);
        pbuf += nal_size;

        nal_start = nal_end;
    }

    *outSize = (pbuf - bufOut);
}


void CheckH264key(const char* nalsbuf, int size,  bool& isKeyframe)
{

	char* outBuf = new char[size + 100];
	int outLen;
	isKeyframe = false;
	AVCParseNalUnits(nalsbuf, size, (char*)outBuf, &outLen);

	char* start = outBuf;
	char* end = outBuf + outLen;

	/* look for sps and pps */
	while (start < end) 
	{
		unsigned int size = BytesToUI32(start);
		unsigned char nal_type = start[4] & 0x1f;
	    if (nal_type == NAL_SLICE_IDR)
		{
			isKeyframe = true;
			break;
		}
		start += size + 4;
	}
	delete[] outBuf;
}
static int convert_sps_pps( const uint8_t *p_buf,
						   uint32_t i_buf_size, uint8_t *p_out_buf,
						   uint32_t i_out_buf_size, uint32_t *p_sps_pps_size,
						   uint32_t *p_nal_size)
{
	int i_profile;
	uint32_t i_data_size = i_buf_size, i_nal_size, i_sps_pps_size = 0;
	unsigned int i_loop_end;

	/* */
	if( i_data_size < 7 )
	{
		return -1;
	}

	/* Read infos in first 6 bytes */
	i_profile    = (p_buf[1] << 16) | (p_buf[2] << 8) | p_buf[3];
	if (p_nal_size)
		*p_nal_size  = (p_buf[4] & 0x03) + 1;
	p_buf       += 5;
	i_data_size -= 5;

	for ( unsigned int j = 0; j < 2; j++ )
	{
		/* First time is SPS, Second is PPS */
		if( i_data_size < 1 )
		{

			return -1;
		}
		i_loop_end = p_buf[0] & (j == 0 ? 0x1f : 0xff);
		p_buf++; i_data_size--;

		for ( unsigned int i = 0; i < i_loop_end; i++)
		{
			if( i_data_size < 2 )
			{

				return -1;
			}

			i_nal_size = (p_buf[0] << 8) | p_buf[1];
			p_buf += 2;
			i_data_size -= 2;

			if( i_data_size < i_nal_size )
			{
				return -1;
 
			}
			if( i_sps_pps_size + 4 + i_nal_size > i_out_buf_size )
			{
				return -1;
			}

			p_out_buf[i_sps_pps_size++] = 0;
			p_out_buf[i_sps_pps_size++] = 0;
			p_out_buf[i_sps_pps_size++] = 0;
			p_out_buf[i_sps_pps_size++] = 1;

			memcpy( p_out_buf + i_sps_pps_size, p_buf, i_nal_size );
			i_sps_pps_size += i_nal_size;

			p_buf += i_nal_size;
			i_data_size -= i_nal_size;
		}
	}

	*p_sps_pps_size = i_sps_pps_size;

	return 1;
}
void ParseH264NalSpsPps(const char* nalsbuf, int size,char* spsBuf,unsigned int &spsSize, char* ppsBuf,unsigned int &ppsSize)
{
	char* outBuf = new char[size + 100];
	int outLen;
	AVCParseNalUnits(nalsbuf, size, (char*)outBuf, &outLen);

	char* start = outBuf;
	char* end = outBuf + outLen;

	/* look for sps and pps */
	while (start < end) 
	{
		unsigned int size = BytesToUI32(start);
		unsigned char nal_type = start[4] & 0x1f;

		if (nal_type == NAL_SPS && spsBuf)        /* SPS */
		{
			memcpy(spsBuf , start + 4  , size);
			spsSize = size;

		}
		else if (nal_type == NAL_PPS && ppsBuf)   /* PPS */
		{
			memcpy(ppsBuf , start + 4  , size);
			ppsSize = size;
		}
		start += size + 4;
	}
	delete[] outBuf;

}