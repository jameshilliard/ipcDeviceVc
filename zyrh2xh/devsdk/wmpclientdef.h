#pragma once

#ifdef __cplusplus
extern "C"
{
#endif



typedef int WMP_HANDLE;				//注册句柄

#define WMP_TRANS_TCP	1
#define WMP_TRANS_UDP	2

#define WMP_STREAM_MAIN		1	//主码流
#define WMP_STREAM_SUB		2	//子码流

#define WMP_VIDEO_HEADER	1	//视频头
#define WMP_VIDEO_DATA		2	//视频数据


//录像类型
#define WMP_RECORD_ALL		0xff	//所有录像
#define WMP_RECORD_TIMING	0		//定时录像
#define WMP_RECORD_MONTION	1		//移动侦测录像
#define WMP_RECORD_ALARM	2			//报警录像
#define WMP_RECORD_MONTION_AND_ALARM	3	//移动侦测且报警
#define WMP_RECORD_MONTION_OR_ALARM		4	//移动侦测或报警
#define WMP_RECORD_COMMAND	5		//命令触发录像
#define WMP_RECORD_MANUAL	6		//手动录像


//云台控制
#define WMP_PTZ_UP		1			//上
#define WMP_PTZ_DOWN	2			//下
#define WMP_PTZ_LEFT	3			//左
#define WMP_PTZ_RIGHT	4			//右
#define WMP_PTZ_UP_RIGHT	5		//右上
#define WMP_PTZ_RIGHT_DOWN	6		//右下
#define WMP_PTZ_DOWN_LEFT	7		//左下
#define WMP_PTZ_LEFT_UP		8			//左上
#define WMP_PTZ_AUTO		9				//自动
#define WMP_PTZ_ZOOMIN		10			//放大
#define WMP_PTZ_ZOOMOUT		11			//缩小
#define WMP_PTZ_FOCUS_NEAR	12		//聚焦
#define WMP_PTZ_FOCUS_FAR	13		//散焦
#define WMP_PTZ_DIAPHRAGM_ENLARGE	14	//光圈放大(变亮)
#define WMP_PTZ_DIAPHRAGM_SHRINK	15	//光圈缩小(变暗)
#define WMP_PTZ_WIPER	16			//雨刷
#define WMP_PTZ_LIGHT	17			//灯光
#define WMP_PTZ_HEAT	18			//加热

#define WMP_PTZ_ACTION_START	1
#define WMP_PTZ_ACTION_STOP		0

#define LENS_UP  0x01    //向上转
#define LENS_LEFT  0x02   // 向左转
#define LENS_ROTATE  0x03   // 旋转
#define LENS_RIGHT  0x04   // 向右转
#define LENS_DOWN  0x05   // 向下转
#define LENS_FAR  0x06    //镜头远
#define LENS_FOCUSNEAR  0x07    //聚焦
#define LENS_AUTO  0x08    //自动
#define LENS_FOCUSFAR  0x09   // 散焦
#define LENS_NEAR  0x0A    //镜头近
#define LENS_DIAPHRAGM_LARGE    0x0B    //光圈增大（变亮）
#define LENS_DIAPHRAGM_SMALL    0x0C   // 光圈减小（变暗）
#define LENS_STOP  0x0D    //停止动作
#define LENS_SPEAKER_ON  0x0E    //打开喇叭
#define LENS_LIGHT_ON  0x0F    //打开灯光
#define LENS_HOTDOG  0x10    //热狗扫描
#define LENS_SPEAKER_OFF  0x11    //关闭喇叭
#define LENS_LIGHT_OFF  0x12    //关闭灯光
#define LENS_PRESET_GOTO  0x13    //切换到预置点
#define LENS_PRESET_SET  0x14   // 设置预置点
#define LENS_PRESET_DEL  0x15    //删除预置点
#define LENS_PRESET_CLEAR  0x1E    //清除所有预置点
#define LENS_CAMERA_RESET  0x16    //摄像机复位
#define LENS_AUTOCRUISE  0x1D    //自动巡航
#define LENS_STARTTRACKING  0x1F   // 启动跟踪
#define LENS_STOPTRACKING  0x20    //停止跟踪
#define LENS_CAMERAACTIVE  0x28    //摄像机激活
#define LENS_SETPANSPEED  0x29    //设置左右转动速度
#define LENS_SETTILTSPEED  0x30    //设置上下转动速度
#define LENS_SETZOOMSPEED  0x31    //设置光圈速度
#define LENS_SETFOCUSSPEED  0x32    //设置聚焦/散焦速度 
#define LENS_SPEEDSETTINGGET    0x33    //获取摄像机速度设置
#define LENS_MATRIXSWITCH  0x40    //矩阵切换
//预置点
#define WMP_PRESET_SET	1
#define WMP_PRESET_DEL	2
#define WMP_PRESET_GOTO	3




//GPS数据
typedef struct _WMP_GPSINFO
{

}WMP_GPSINFO;

//报警数据
typedef struct _WMP_ALARMINFO
{

}WMP_ALARMINFO;

//设备状态数据
typedef struct _WMP_STATEINFO
{

}WMP_STATEINFO;


//录像文件
typedef struct _WMP_RECORDFILEINFO
{
	unsigned int file_id;		//文件编号
	int channel;				//通道号
	int rec_type;				//录像类型
	unsigned long long file_size;	//文件大小
	char begin_time[32];	//开始时间
	char end_time[32];		//结束时间
	char file_name[64];		//文件名
	char full_name[256];
}WMP_RECORDFILEINFO;


typedef struct _WMP_IMAGEINFO
{
	unsigned char hue;		//色调 0~255
	unsigned char contrast;	//对比度 0~255
	unsigned char bright;		//亮度 0~255
	unsigned char saturation;	//饱和度 0~255
}WMP_IMAGEINFO;




//硬盘状态
typedef struct _WMP_DISK_STATUS
{
	int disk_no;				//硬盘编号
	int status;					//硬盘状态:0-正常;1-休眠;2-异常
	unsigned long long total_size;//硬盘总容量,单位:字节
	unsigned long long free_size;//硬盘可用容量,单位:字节
}WMP_DISK_STATUS;

//通道视频状态
typedef struct _WMP_VIDEO_STATUS
{
	int channel;				//通道号
	int rec_status;				//录像状态:1-录像;0-未录像
	int video_status;			//视频状态:0-正常;1-异常
	int dsp_status;				//编码状态:0-正常;1-异常
	unsigned int bit_rate;		//当前码率
	unsigned int client_number;	//客户端连接数
}WMP_VIDEO_STATUS;


//报警通道状态
typedef struct _WMP_ALARM_CHANNEL_STATUS
{
	int alarm_channel;	//报警通道
	int status;			//通道状态:1-报警,0-未报警
}WMP_ALARM_CHANNEL_STATUS;

//设备工作状态
typedef struct _WMP_DEVICE_WORK_STATUS
{
	int cpu;		//CPU使用百分比
	int memory;		//内存使用百分比

	WMP_DISK_STATUS* disks;
	unsigned int disk_count;

	WMP_VIDEO_STATUS* videos;
	unsigned int video_count;

	WMP_ALARM_CHANNEL_STATUS* alarm_in;
	unsigned int alarm_in_count;

	WMP_ALARM_CHANNEL_STATUS* alarm_out;
	unsigned int alarm_out_count;

}WMP_DEVICE_WORK_STATUS;




//设备升级信息
typedef struct _WMP_DEVICE_UPDATE
{
	const char* ftp_ip;
	const char* ftp_account;
	const char* ftp_pwd;
	const char* file;
	int ftp_port;
}WMP_DEVICE_UPDATE;

//连接断开回调
typedef void (*CBF_OnClosed)(char* ip,unsigned int len,unsigned short* port,void* ctx);
//GPS消息回调
typedef void (*CBF_OnGps)(WMP_HANDLE h,const WMP_GPSINFO* gps,void* ctx);
//报警消息回调
typedef void (*CBF_OnAlarm)(WMP_HANDLE h,const WMP_ALARMINFO* alarm,void* ctx);
//G状态消息回调
typedef void (*CBF_OnState)(WMP_HANDLE h,const WMP_STATEINFO* state,void* ctx);
//视频数据回调
typedef void (*CBF_OnStream)(int h,int sflag,const char* pdata,unsigned int data_size,void* ctx);
//音频数据回调
typedef void (*CBF_OnAudioStream)(int h,const char* pdata,unsigned int data_size,void* ctx);
//设备录像数据回调
typedef void (*CBF_OnDevRecord)(int h,int sflag,const char* pdata,unsigned int data_size,void* ctx);




#ifdef __cplusplus
}
#endif

