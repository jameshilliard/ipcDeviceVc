#ifndef LOGGER_H_
#define LOGGER_H_
#include <stdio.h>
#include "Thread.h"
#include "MyVector.h"
//日志级别的提示信息
static const char * INFOPREFIX      = " Info: ";

static const int MAX_STR_LEN = 2048;
//日志级别枚举
typedef enum EnumLogLevel
{
	LogLevelAll = 0,    //所有信息都写日志
	LogLevelMid = 1,        //写错误、警告信息
	LogLevelNormal = 2,     //只写错误信息
	LogLevelStop = 3       //不写日志
};

class Logger
{
public:
	//构造函数
	Logger(const char * strLogPath = "log",const char* pStrFileName = "File");
	//析构函数
	virtual ~Logger();
public:	
	//写一般信息
	void  Write2Caching(const char * strInfo, ...);


	//写文件操作
	void DoWriteLog();
private:

	
	//获取当前系统时间
	char * GetCurrentTime();
	//创建日志文件名称
	void GenerateLogName();
	//创建日志路径
	void CreateLogPath();
private:
	//写日志文件流
	FILE * m_pFileStream;
	//日志的路径
	std::string m_strLogPath;
	//日志的名称
	std::string m_strCurLogName;

	//日志文件的索引数
	std::size_t   m_nFileIndex;
	//日志的行数
	std::size_t   m_nlogCount;

	CMyVector<std::string> m_vcStrList;

};
extern Logger g_logInfo;
extern Logger g_logError;
#endif