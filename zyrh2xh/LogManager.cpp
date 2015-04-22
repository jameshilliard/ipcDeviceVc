#include "LogManager.h"
#include <boost/bind.hpp>
#include "devsdk/wmpclient.h"
CLogManager* CLogManager::m_gLogManager = NULL;

CLogManager::CLogManager()
{

}
CLogManager::~CLogManager()
{

}

void CLogManager::AddLog(Logger* pLogger)
{
	m_loggerList.pushBack(pLogger);
}

CLogManager* CLogManager::GetInstance()
{
	if (m_gLogManager == NULL)
	{
		m_gLogManager = new CLogManager();
		WMP_Init();
		m_gLogManager->StartWriteLogThread();
	}
	return m_gLogManager;
}
void CLogManager::StartWriteLogThread()
{
	m_Thead.StartThread(boost::bind(&CLogManager::DoWriteLog,this));
}
void CLogManager::DoWriteLog()
{
	Sleep(10);
	std::vector<Logger*> vcLogList;
	m_loggerList.GetDataList(vcLogList);
	for (int i = 0;i<vcLogList.size();i++)
	{
		if (vcLogList[i])
		{
			vcLogList[i]->DoWriteLog();
		}
	}
}