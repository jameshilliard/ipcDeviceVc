#include "stdafx.h"
#include "Thread.h"

CThread::CThread(void)
{
	m_ThreadHandle = INVALID_HANDLE_VALUE;
	m_ThreadID = 0;
	m_ThreadStatur = THREAD_INVALIAD;
	m_FunThread = 0;
}

CThread::~CThread(void)
{
	StopThread();
}
void CThread::StartThread(boost::function<void()> FunThread,bool bRunNow)
{
	if (m_ThreadStatur != THREAD_INVALIAD)
	{
		return;
	}
	if (bRunNow)
	{
		m_ThreadStatur = THREAD_RUN;
	}
	else
	{
		m_ThreadStatur = THREAD_SUSPENDED;
	}
	m_FunThread = FunThread;
	m_ThreadHandle = (HANDLE)_beginthreadex( NULL,         
		0,           
		CThread::Run,  
		this,           
		m_ThreadStatur,  // 0 立即运行 CREATE_SUSPENDED 挂起
		&m_ThreadID ); 
}
void CThread::StopThread()
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	m_ThreadStatur = THREAD_STOP;
	if (m_ThreadHandle != INVALID_HANDLE_VALUE)
	{
		WaitForSingleObject( m_ThreadHandle, INFINITE ); 
		CloseHandle(m_ThreadHandle);
		m_ThreadHandle = INVALID_HANDLE_VALUE;
	}
}
void CThread::DoThreadProc()
{
	if (m_FunThread)
	{
		m_FunThread();
	}

}
void CThread::DoSuspendThread()
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	if (m_ThreadHandle != INVALID_HANDLE_VALUE)
	{
		SuspendThread(m_ThreadHandle);
		m_ThreadStatur = THREAD_SUSPENDED;
	}
}
void CThread::DoResumeThread()
{
	boost::asio::detail::mutex::scoped_lock lock(mutex_);
	if (m_ThreadHandle != INVALID_HANDLE_VALUE)
	{
		ResumeThread(m_ThreadHandle);
		m_ThreadStatur = THREAD_RUN;
	}
}
 unsigned __stdcall  CThread::Run(void* param)
{
	CThread* pThread = (CThread*)param;
	while(pThread->m_ThreadStatur != THREAD_STOP)
	{
		pThread->DoThreadProc();
		Sleep(1);
	}
	return 1;	
}