#pragma once

#include "wmpclientdef.h"

#ifdef __cplusplus
extern "C"
{
#endif

//初始化wmp库
//return:错误代码
int WMP_Init();

//注销wmp库
void WMP_Cleanup();

//创建wmp句柄
//return:句柄,-1失败
WMP_HANDLE WMP_Create();

//关闭wmp句柄
//h:句柄
//return:错误代码
int WMP_Close(WMP_HANDLE h);

//设置GPS回调函数
//h:句柄
//cbf:回调函数
//ctx:回调函数上下文
//return:错误代码
int WMP_SetGpsCallback(WMP_HANDLE h,CBF_OnGps cbf,void* ctx);

//设置报警回调函数
//h:句柄
//cbf:回调函数
//ctx:回调函数上下文
//return:错误代码
int WMP_SetAlarmCallback(WMP_HANDLE h,CBF_OnAlarm cbf,void* ctx);

//设置设备状态回调函数
//h:句柄
//cbf:回调函数
//ctx:回调函数上下文
//return:错误代码
int WMP_SetStateCallback(WMP_HANDLE h,CBF_OnState cbf,void* ctx);

//设置断线回调函数
//h:句柄
//cbf:回调函数
//ctx:回调函数上下文
//return:错误代码
int WMP_SetClosedCallback(WMP_HANDLE h,CBF_OnClosed cbf,void* ctx);

//登录
//h:句柄
//host:CAG地址
//port:CAG端口
//user:登录用户名
//pwd:登录密码
//line:线路号
//return:错误代码
int WMP_Login(WMP_HANDLE h,const char* host,unsigned short port,const char* user,const char* pwd,int line);




//开始预览
//h:句柄
//devid:设备ID
//channel:设备通道号
//stream_type:WMP_STREAM_MAIN-主码流   WMP_STREAM_SUB-子码流
//trans_mode:WMP_TRANS_TCP/WMP_TRANS_UDP
//dev_line:设备线路号
//on_stream:流数据回调
//ctx:回调函数上下文
//stream_handle:取流句柄
//return:错误代码
int WMP_Play(WMP_HANDLE h,const char* devid,int channel,int stream_type,int trans_mode,int dev_line,
			 CBF_OnStream on_stream,void* ctx,int* stream_handle);

//关闭实时预览
int WMP_Stop(WMP_HANDLE h,int stream_handle);

//开启语音对讲
int WMP_AudioPlay(WMP_HANDLE h,const char* devid,int audio_channel,CBF_OnAudioStream cbf,void* ctx,int* audio_handle);

//关闭语音对讲
int WMP_AudioStop(WMP_HANDLE h,int audio_handle);

//输入语音数据
int WMP_AudioInput(WMP_HANDLE h,int audio_handle,const char* pdata,unsigned int data_size);

//搜索设备录像
int WMP_SearchDeviceRecord(WMP_HANDLE h,
						   const char* devid,int channel,
						   const char* begintime,const char* endtime,
						   unsigned int rec_type,
						   unsigned int offset,unsigned int limit,
						   WMP_RECORDFILEINFO** files,unsigned int* count);

//搜索中心录像
int WMP_SearchCentralRecord(WMP_HANDLE h,
						   const char* devid,int channel,
						   const char* begintime,const char* endtime,
						   unsigned int rec_type,
						   unsigned int offset,unsigned int limit,
						   WMP_RECORDFILEINFO** files,unsigned int* count);

//释放WMP_SearchDeviceRecord申请的内存
void WMP_FreeRecordFileInfo(WMP_RECORDFILEINFO* files);

//播放设备录像
int WMP_PlayDeviceRecord(
	WMP_HANDLE h,
	const char* devid,
	int channel,
	const char* filename,
	unsigned long long seek,
	unsigned long long read_size,		//预留,暂时不起作用
	int dev_line,
	int central_record,		//0-不进行重新存储,1-使用录像时间存储,2-使用本地时间存储
	int* rec_handle,
	CBF_OnDevRecord cbf,
	void* ctx);

//停止播放录像
int WMP_StopDeviceRecord(WMP_HANDLE h,int rec_handle);

//播放中心录像
int WMP_PlayCentralRecord(
						 WMP_HANDLE h,
						 const char* devid,
						 int channel,
						 const char* begintime,
						 const char* endtime,
						 int rec_flag,
						 int stream_control,
						 int* rec_handle,
						 CBF_OnDevRecord cbf,
						 void* ctx);

//停止播放中心录像
int WMP_StopCentralRecord(WMP_HANDLE h,int rec_handle);

//查询设备状态
int WMP_QueryDeviceStatus(WMP_HANDLE h,const char* devid,int* status);

//升级设备
int WMP_UpdateDevice(WMP_HANDLE h,const char* devid,const WMP_DEVICE_UPDATE* du);

//格式化磁盘
//disk_id_list:硬盘号,用逗号隔开
int WMP_FormatDisk(WMP_HANDLE h,const char* devid,int disk_id);

//云台控制
int WMP_PtzControl(WMP_HANDLE h,const char* devid,int channel,int ptz_cmd,int action,int param);

//3D云台控制
int WMP_Ptz3DControl(WMP_HANDLE h,const char* devid,int channel,int x,int y,int cx,int cy);

//预置点操作
int WMP_SetPreset(WMP_HANDLE h,const char* devid,int channel,int action,int preset_id,const char* preset_name);

//设置图像参数
int WMP_SetImageParam(WMP_HANDLE h,const char* devid,int channel,const WMP_IMAGEINFO* image);
//获取图像参数
int WMP_GetImageParam(WMP_HANDLE h,const char* devid,int channel,WMP_IMAGEINFO* image);

//重启设备
int WMP_Reboot(WMP_HANDLE h,const char* devid);



#ifdef __cplusplus
}
#endif

