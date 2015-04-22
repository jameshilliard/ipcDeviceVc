#ifndef _SPS_H_
#define _SPS_H_
#include "bytestream.h"
typedef unsigned char byte;
void parse_sps(byte * sps, size_t sps_size, uint32_t * width, uint32_t * height) ;
#endif