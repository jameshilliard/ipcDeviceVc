#pragma once
#include "Logger.h"
#include "Thread.h"
#include "MyVector.h"
class CLogManager
{
private:
	CLogManager();
	~CLogManager();
	static CLogManager* m_gLogManager;
	
	CMyVector<Logger*> m_loggerList;
	CThread m_Thead;
public:
	static CLogManager* GetInstance();
    void AddLog(Logger* pLogger);
	void DoWriteLog();
	void StartWriteLogThread();

};