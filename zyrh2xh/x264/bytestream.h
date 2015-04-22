/*****************************************************************************
 * bytestream.h: flv muxer utilities
 *****************************************************************************
 * Copyright (C) 2009-2013 x264 project
 *
 * Authors: Kieran Kunhya <kieran@kunhya.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 *
 * This program is also available under a commercial proprietary license.
 * For more information, contact us at licensing@x264.com.
 *****************************************************************************/

#ifndef X264_BYTESTREAM_H
#define X264_BYTESTREAM_H
#include "stdint.h"

#include <stdio.h>
#include <stdlib.h>
#include  <memory.h>
#include <string.h>
struct buffer
{
	uint8_t *data;
	uint32_t d_cur;
	uint32_t d_max;
	uint64_t d_CurRead;
	__int64  TimeStamp;
	buffer(uint32_t size = 188)
	{
		data = new uint8_t[size];
		d_max = size;
		d_cur = 0;
	}
	~buffer()
	{
		delete[] data;
	}
	void Clear()
	{
		d_cur = 0;
	}
};
typedef signed char int8_t;
typedef unsigned char   uint8_t;
typedef short  int16_t;
typedef unsigned short  uint16_t;
typedef int  int32_t;
typedef unsigned int  uint32_t;
typedef __int64  int64_t;
typedef unsigned __int64 uint64_t;
typedef enum
{
	AMF_DATA_TYPE_NUMBER      = 0x00,
	AMF_DATA_TYPE_BOOL        = 0x01,
	AMF_DATA_TYPE_STRING      = 0x02,
	AMF_DATA_TYPE_OBJECT      = 0x03,
	AMF_DATA_TYPE_NULL        = 0x05,
	AMF_DATA_TYPE_UNDEFINED   = 0x06,
	AMF_DATA_TYPE_REFERENCE   = 0x07,
	AMF_DATA_TYPE_MIXEDARRAY  = 0x08,
	AMF_DATA_TYPE_OBJECT_END  = 0x09,
	AMF_DATA_TYPE_ARRAY       = 0x0a,
	AMF_DATA_TYPE_DATE        = 0x0b,
	AMF_DATA_TYPE_LONG_STRING = 0x0c,
	AMF_DATA_TYPE_UNSUPPORTED = 0x0d,
} FLVAMFDataType;


int append_data( buffer *c, uint8_t *data, uint32_t size );

uint64_t dbl2int( double svalue );
void put_byte( buffer *c, uint8_t b );
void put_be32( buffer *c, uint32_t val );
void put_be64( buffer *c, uint64_t val );
void put_be16( buffer *c, uint16_t val );
void put_be24( buffer *c, uint32_t val );
void put_tag( buffer *c, const char *tag );
unsigned int CRC32(const uint8_t *data, int len);
unsigned int bytesToUI32(const char* buf);
void rewrite_amf_be24( buffer *c, uint32_t length, uint32_t start );
void rewrite_amf_be16( buffer *c, uint16_t length, uint32_t start );
void put_amf_string( buffer *c, const char *str );
void put_amf_double( buffer *c, double d );
uint64_t dbl2int( double svalue );
double int2dbl(  uint64_t svalue );

char* put_byte( char *c, uint8_t b );

char* put_be32( char* c, uint32_t val );

char* put_be64( char *c, uint64_t val );

char* put_be16( char *c, uint16_t val );

char* put_be24( char *c, uint32_t val );

char* append_data( char *c, char *data, uint32_t  size );
// 
uint16_t get_byte16(char* val);
uint32_t get_byte24(char* val);
uint32_t get_byte32(char* val);
uint64_t get_byte64(char* val);
uint16_t get_amf_string( const char* c,char* dest);

#endif
