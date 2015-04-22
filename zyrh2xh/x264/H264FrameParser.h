#ifndef _H264_FRAME_PARSER_H_
#define _H264_FRAME_PARSER_H_
#include "stdint.h"

enum nal_unit_type_e
{
	NAL_UNKNOWN     = 0,
	NAL_SLICE       = 1,
	NAL_SLICE_DPA   = 2,
	NAL_SLICE_DPB   = 3,
	NAL_SLICE_DPC   = 4,
	NAL_SLICE_IDR   = 5,    /* ref_idc != 0 */
	NAL_SEI         = 6,    /* ref_idc == 0 */
	NAL_SPS         = 7,
	NAL_PPS         = 8,
	NAL_AUD         = 9,
	NAL_FILLER      = 12,
	/* ref_idc == 0 for 6,9,10,11,12 */
};
const char* AVCFindStartCodeInternal(const char *p, const char *end);

const char* AVCFindStartCode(const char *p, const char *end);

void AVCParseNalUnits(const char *bufIn, int inSize, char* bufOut, int* outSize);


void CheckH264key(const char* nalsbuf, int size,  bool& isKeyframe);
static int convert_sps_pps( const uint8_t *p_buf,
						   uint32_t i_buf_size, uint8_t *p_out_buf,
						   uint32_t i_out_buf_size, uint32_t *p_sps_pps_size,
						   uint32_t *p_nal_size);

void ParseH264NalSpsPps(const char* nalsbuf, int size,char* spsBuf,unsigned int &spsSize, char* ppsBuf,unsigned int &ppsSize);
#endif // _H264_FRAME_PARSER_H_
