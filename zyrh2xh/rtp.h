#ifndef _RTP_H
#define _RTP_H
typedef struct   
{  
    /* byte 0 */  
    unsigned char csrc_len:4; /* CC expect 0 */  
    unsigned char extension:1;/* X  expect 1, see RTP_OP below */  
    unsigned char padding:1;  /* P  expect 0 */  
    unsigned char version:2;  /* V  expect 2 */  
    /* byte 1 */  
    unsigned char payload:7; /* PT  RTP_PAYLOAD_RTSP */  
    unsigned char marker:1;  /* M   expect 1 */  
    /* byte 2,3 */  
    unsigned short seq_no;   /*sequence number*/  
    /* byte 4-7 */  
    unsigned  long timestamp;  
    /* byte 8-11 */  
    unsigned long ssrc; /* stream number is used here. */  
} RTP_FIXED_HEADER;/*12 bytes*/ 
/****************************************************************** 
NALU_HEADER 
+---------------+ 
|0|1|2|3|4|5|6|7| 
+-+-+-+-+-+-+-+-+ 
|F|NRI|  Type   | 
+---------------+ 
******************************************************************/  
typedef struct {  
	//byte 0   
	unsigned char TYPE:5;  
	unsigned char NRI:2;  
	unsigned char F:1;  
} NALU_HEADER; /* 1 byte */  


/****************************************************************** 
FU_INDICATOR 
+---------------+ 
|0|1|2|3|4|5|6|7| 
+-+-+-+-+-+-+-+-+ 
|F|NRI|  Type   | 
+---------------+ 
******************************************************************/  
typedef struct {  
	//byte 0   
	unsigned char TYPE:5;  
	unsigned char NRI:2;   
	unsigned char F:1;           
} FU_INDICATOR; /*1 byte */  


/****************************************************************** 
FU_HEADER 
+---------------+ 
|0|1|2|3|4|5|6|7| 
+-+-+-+-+-+-+-+-+ 
|S|E|R|  Type   | 
+---------------+ 
******************************************************************/  
typedef struct {  
	//byte 0   
	unsigned char TYPE:5;  
	unsigned char R:1;  
	unsigned char E:1;  
	unsigned char S:1;      
} FU_HEADER; /* 1 byte */  

#define  UDP_MAX_SIZE 1434   
#define  H264         96 
#define  AAC          94 
#endif