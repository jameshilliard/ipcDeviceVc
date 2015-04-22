#pragma once
//线程类
#ifndef  _THREAD_H_
#define _THREAD_H_
#include <boost/shared_ptr.hpp>
#include <process.h>          // for _beginthread() 
#include <winsock2.h>
#include <windows.h>          // for HANDLE  
#include <boost/asio/detail/mutex.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
enum ThreadStatue
{	
	THREAD_RUN = 0,//运行中
	THREAD_SUSPENDED = CREATE_SUSPENDED,//挂起
	THREAD_STOP,//结束
	THREAD_INVALIAD,
}; 

class CThread
{
private:
	unsigned int  m_ThreadStatur;
	HANDLE m_ThreadHandle;
	unsigned int m_ThreadID;
	boost::asio::detail::mutex mutex_;
	static unsigned __stdcall  Run(void* param);
public:
	CThread(void);
	~CThread(void);
	void StartThread(boost::function<void()> FunThread,bool bRunNow = true);
	boost::function<void()> m_FunThread;
	void StopThread();
	virtual void DoThreadProc();
	void DoSuspendThread();
	void DoResumeThread();
};
typedef boost::shared_ptr<CThread> ThreadPtr;
typedef boost::weak_ptr<CThread>   ThreadWPtr;
#endif