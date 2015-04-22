// zyrh2xh.cpp : 定义控制台应用程序的入口点。
//
//#include "tcpServer/DeviceCommServer.h"
#include "rtspServer/H264FramedLiveSource.hh"
#include "tcpServer/DeviceServer.h"
#include "stdafx.h"
#include <string>
#include "devsdk/DevSdk.h"
#include "global.h"
#include <vector>
#include "CrashRpt/CrashRpt.h"
#include <Winsock2.h>
#include <windows.h>
#include "stdafx.h"
#include "winbase.h"
#include <stdlib.h>
#include "tchar.h"
#include "windows.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "kernel32.lib")

char* videobuf = new char[1024*1024];

using namespace std;
std::string sSdkServerIp;
int sSdkServerPort;
std::string sUserName;
std::string sPassWord;
int nServerLine;

std::string sHttpUrl;

//xhkj
std::string spagip;
int npagPort;
//CCrashRptException g_Crash;
struct  DevInfo
{
	std::string sPuid;
	std::string sDOMAIN_ID;
	std::string sDevId;
	int nDevLine;
	int nChannel;
	CdevSdk*  pDevSdk;
	DevInfo()
	{
		pDevSdk = new CdevSdk;
		nDevLine = 0;
		nChannel = 0;
	}
	
};

void StartDeviceServer()
{
	if(!initCrash())
	{
		printf("initCrash flase 程序将关闭");
		Sleep(10000);
		exit(0);
		return ;
	}
	char buf[2048];
	int i=1000; 

	char FilePath[MAX_PATH+1]= {0};
	char *p = NULL;
	
	GetModuleFileNameA(NULL, FilePath, sizeof(FilePath)); //获取程序当前执行文件名
	p=strrchr(FilePath, '\\');                       
	*p='\0';
	GetCurrentDirectoryA(1000,buf);   //得到当前工作路径 
	std::string path = FilePath;
	path += "/config.ini";

	GetPrivateProfileString("ZyrhOpenService","httpurl","",buf,2048,path.c_str());
	sHttpUrl = buf;

	GetPrivateProfileString("client","Sdkclient","",buf,2048,path.c_str());
	std::string str,str1,str2;
	str = buf;

	SDKServerData sSDKserverData;
	for (int i = 1;i<=5;i++)
	{
		strseparate((char*)str.c_str(),str1,str2,"_");
		switch(i)
		{
		case 1:
			sSDKserverData.m_sSdkServerIp = str1;
			break;
		case 2:
			sSDKserverData.m_nSdkServerPort = atoi(str1.c_str());
			break;
		case 3:
			sSDKserverData.m_nServerLine = atoi(str1.c_str());
			break;
		case 4:
			sSDKserverData.m_sUserName = str1;
			break;
		case 5:
			sSDKserverData.m_spassword = str1;
			break;
		}
		str = str2;
	}

	GetPrivateProfileString("Gateway","Setpag","",buf,2048,path.c_str());
	str = buf;
	
	strseparate((char*)str.c_str(),str1,str2,"_");
	spagip = str1;
	npagPort = atoi(str2.c_str());
	
	unsigned int DevCount = GetPrivateProfileInt("Dev","Devcount",0,path.c_str());
	vector<DeviceServer *> 	vcDeviceServer;
	int 					commServerPort;
	int 					rtspServerPort;
	std::string 			deviceUserName;
	std::string 			deviceSecret;
	for (int i = 0;i<DevCount;i++)
	{
		//#设备ID=原设备ID_原设备取流线路_原设备通道数_新设备ID_域
		char sBufDevId[1024];
		sprintf(sBufDevId,"DevId_%d",i+1);
		GetPrivateProfileString("Dev",sBufDevId,"",buf,2048,path.c_str());
		str = buf;

		for (int j = 1;j<=7;j++)
		{
			strseparate((char*)str.c_str(),str1,str2,"_");
			switch(j)
			{
			case 1:
				sSDKserverData.m_sDevId = str1;
				break;
			case 2:
				sSDKserverData.m_nDevLine = atoi(str1.c_str());
				break;
			case 3:
				sSDKserverData.m_nnchannel = atoi(str1.c_str());
				break;
			case 4:
				commServerPort = atoi(str1.c_str());
				break;
			case 5:
				rtspServerPort = atoi(str1.c_str());
				break;
			case 6:
				deviceUserName = str1;
				break;
			case 7:
				deviceSecret = str1;
				break;
			default:
				break;
			}
			str = str2;

		}
		DeviceServer *stDeviceServer = new DeviceServer(commServerPort,rtspServerPort,deviceUserName,deviceSecret);
		stDeviceServer->setSdkServerData(sSDKserverData);
		stDeviceServer->start();
		vcDeviceServer.push_back(stDeviceServer); 		
	}

}
void StartServer()
{
	if(!initCrash())
	{
		printf("initCrash flase 程序将关闭");
		Sleep(10000);
		exit(0);
		return ;
	}
	char buf[2048];
	int i=1000; 

	char FilePath[MAX_PATH+1]= {0};
	char *p = NULL;
	GetModuleFileNameA(NULL, FilePath, sizeof(FilePath)); //获取程序当前执行文件名
	p=strrchr(FilePath, '\\');                       
	*p='\0';
	GetCurrentDirectoryA(1000,buf);   //得到当前工作路径 
	std::string path = FilePath;
	path += "/config.ini";

	GetPrivateProfileString("ZyrhOpenService","httpurl","",buf,2048,path.c_str());
	sHttpUrl = buf;

	GetPrivateProfileString("client","Sdkclient","",buf,2048,path.c_str());
	std::string str,str1,str2;
	str = buf;

	for (int i = 1;i<=5;i++)
	{
		strseparate((char*)str.c_str(),str1,str2,"_");
		switch(i)
		{
		case 1:
			sSdkServerIp = str1;
			break;
		case 2:
			sSdkServerPort = atoi(str1.c_str());
			break;
		case 3:
			nServerLine = atoi(str1.c_str());
			break;
		case 4:
			sUserName = str1;
			break;
		case 5:
			sPassWord = str1;
			break;

		}
		str = str2;
	}

	GetPrivateProfileString("Gateway","Setpag","",buf,2048,path.c_str());
	str = buf;

	strseparate((char*)str.c_str(),str1,str2,"_");
	spagip = str1;
	npagPort = atoi(str2.c_str());


	unsigned int DevCount = GetPrivateProfileInt("Dev","Devcount",0,path.c_str());
	vector<DevInfo> vcDevInfos;
	for (int i = 0;i<DevCount;i++)
	{
		//#设备ID=原设备ID_原设备取流线路_原设备通道数_新设备ID_域
		char sBufDevId[1024];
		sprintf(sBufDevId,"DevId_%d",i+1);
		GetPrivateProfileString("Dev",sBufDevId,"",buf,2048,path.c_str());
		str = buf;
		DevInfo sDevInfo;
		for (int j = 1;j<=5;j++)
		{
			strseparate((char*)str.c_str(),str1,str2,"_");
			switch(j)
			{
			case 1:
				sDevInfo.sDevId = str1;
				break;
			case 2:
				sDevInfo.nDevLine = atoi(str1.c_str());
				break;
			case 3:
				sDevInfo.nChannel = atoi(str1.c_str());
				break;
			case 4:
				sDevInfo.sPuid = str1;
				break;
			case 5:
				sDevInfo.sDOMAIN_ID = str1;
				break;

			}
			str = str2;

		}
		vcDevInfos.push_back(sDevInfo); 
		sDevInfo.pDevSdk->SetXhkeInfo((char*)spagip.c_str(),npagPort,(char*)sDevInfo.sPuid.c_str(),0,"127.0.0.1",(char*)sDevInfo.sDOMAIN_ID.c_str(),(char*)sDevInfo.sPuid.c_str());
		sDevInfo.pDevSdk->SetDevInof((char*)sSdkServerIp.c_str(),sSdkServerPort,(char*)sUserName.c_str(),(char*)sPassWord.c_str(),nServerLine,(char*)sDevInfo.sDevId.c_str(),sDevInfo.nDevLine,sDevInfo.nChannel);
		sDevInfo.pDevSdk->CheckOnlineDev();

	}

}
//定义全局函数变量
void Init();//初始化
BOOL IsInstalled();//判断服务是否已经被安装
BOOL Install();//安装服务函数
BOOL Uninstall();//删除服务函数
void LogEvent(LPCTSTR pszFormat, ...);//记录服务事件
void WINAPI ServiceMain();
void WINAPI ServiceStrl(DWORD dwOpcode);

TCHAR szServiceName[] = _T("Zyrh2Xh");
BOOL bInstall;

SERVICE_STATUS_HANDLE hServiceStatus;
SERVICE_STATUS status;

DWORD dwThreadID;


int _tmain(int argc, _TCHAR* argv[])
{
	StartDeviceServer();
	while(1)
	{
		Sleep(10000);
		//printf("deviceServer is run \n");
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR     lpCmdLine,int       nCmdShow)
{
	Init();

	dwThreadID = ::GetCurrentThreadId();

    SERVICE_TABLE_ENTRY st[] =
    {
        { szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
        { NULL, NULL }
    };

	if (stricmp(lpCmdLine, "-i") == 0)
	{
		Install();
	}
	else if (stricmp(lpCmdLine, "-u") == 0)
	{
		Uninstall();
	}
	else
	{
		if (!::StartServiceCtrlDispatcher(st))
		{
			LogEvent(_T("Register Service Main Function Error!"));
		}
	}

	return 0;
}
//*********************************************************
//Functiopn:			Init
//Description:			初始化
//Calls:				main
//Called By:				
//Table Accessed:				
//Table Updated:				
//Input:				
//Output:				
//Return:				
//Others:				
//History:				
//			<author>niying <time>2006-8-10		<version>		<desc>
//*********************************************************
void Init()
{
    hServiceStatus = NULL;
    status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    status.dwCurrentState = SERVICE_STOPPED;
    //status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE;
    status.dwWin32ExitCode = 0;
    status.dwServiceSpecificExitCode = 0;
    status.dwCheckPoint = 0;
    status.dwWaitHint = 0;
}

//*********************************************************
//Functiopn:			ServiceMain
//Description:			服务主函数，这在里进行控制对服务控制的注册
//Calls:
//Called By:
//Table Accessed:
//Table Updated:
//Input:
//Output:
//Return:
//Others:
//History:
//			<author>niying <time>2006-8-10		<version>		<desc>
//*********************************************************
void WINAPI ServiceMain()
{
    // Register the control request handler
	printf("start----server\n");
    status.dwCurrentState = SERVICE_START_PENDING;
	status.dwControlsAccepted = SERVICE_ACCEPT_STOP;

	//注册服务控制
    hServiceStatus = RegisterServiceCtrlHandler(szServiceName, ServiceStrl);
    if (hServiceStatus == NULL)
    {
        LogEvent(_T("Handler not installed"));
        return;
    }
    SetServiceStatus(hServiceStatus, &status);

    status.dwWin32ExitCode = S_OK;
    status.dwCheckPoint = 0;
    status.dwWaitHint = 0;
	status.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(hServiceStatus, &status);
	
	StartServer();
	printf("start-2---\n");
    while(status.dwCurrentState==SERVICE_RUNNING)
    {
		Sleep(1000);
	}
    status.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(hServiceStatus, &status);
	
	printf("start----over\n");
    LogEvent(_T("Service stopped"));
}

//*********************************************************
//Functiopn:			ServiceStrl
//Description:			服务控制主函数，这里实现对服务的控制，
//						当在服务管理器上停止或其它操作时，将会运行此处代码
//Calls:
//Called By:
//Table Accessed:
//Table Updated:
//Input:				dwOpcode：控制服务的状态
//Output:
//Return:
//Others:
//History:
//			<author>niying <time>2006-8-10		<version>		<desc>
//*********************************************************
void WINAPI ServiceStrl(DWORD dwOpcode)
{
    switch (dwOpcode)
    {
    case SERVICE_CONTROL_STOP:
		status.dwCurrentState = SERVICE_STOP_PENDING;
        SetServiceStatus(hServiceStatus, &status);
        PostThreadMessage(dwThreadID, WM_CLOSE, 0, 0);
		LogEvent(_T("SERVICE_CONTROL_STOP"));
        break;
    case SERVICE_CONTROL_PAUSE:
        break;
    case SERVICE_CONTROL_CONTINUE:
        break;
    case SERVICE_CONTROL_INTERROGATE:
        break;
    case SERVICE_CONTROL_SHUTDOWN:		
		status.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(hServiceStatus, &status);
		LogEvent(_T("SERVICE_CONTROL_SHUTDOWN"));
        break;
    default:
        LogEvent(_T("Bad service request"));
    }
}
//*********************************************************
//Functiopn:			IsInstalled
//Description:			判断服务是否已经被安装
//Calls:
//Called By:
//Table Accessed:
//Table Updated:
//Input:
//Output:
//Return:
//Others:
//History:
//			<author>niying <time>2006-8-10		<version>		<desc>
//*********************************************************
BOOL IsInstalled()
{
    BOOL bResult = FALSE;

	//打开服务控制管理器
    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM != NULL)
    {
		//打开服务
        SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_QUERY_CONFIG);
        if (hService != NULL)
        {
            bResult = TRUE;
            ::CloseServiceHandle(hService);
        }
        ::CloseServiceHandle(hSCM);
    }
    return bResult;
}

//*********************************************************
//Functiopn:			Install
//Description:			安装服务函数
//Calls:
//Called By:
//Table Accessed:
//Table Updated:
//Input:
//Output:
//Return:
//Others:
//History:
//			<author>niying <time>2006-8-10		<version>		<desc>
//*********************************************************
BOOL Install()
{
    if (IsInstalled())
        return TRUE;

	//打开服务控制管理器
    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hSCM == NULL)
    {
        MessageBox(NULL, _T("Couldn't open service manager"), szServiceName, MB_OK);
        return FALSE;
    }

    // Get the executable file path
    TCHAR szFilePath[MAX_PATH];
//    ::GetModuleFileName(NULL, szFilePath, MAX_PATH);

	//创建服务
    SC_HANDLE hService = ::CreateService(
        hSCM, szServiceName, szServiceName,
        SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
        SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
        szFilePath, NULL, NULL, _T(""), NULL, NULL);

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, _T("Couldn't create service"), szServiceName, MB_OK);
        return FALSE;
    }

    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);
    return TRUE;
}

//*********************************************************
//Functiopn:			Uninstall
//Description:			删除服务函数
//Calls:
//Called By:
//Table Accessed:
//Table Updated:
//Input:
//Output:
//Return:
//Others:
//History:
//			<author>niying <time>2006-8-10		<version>		<desc>
//*********************************************************
BOOL Uninstall()
{
    if (!IsInstalled())
        return TRUE;

    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

    if (hSCM == NULL)
    {
        MessageBox(NULL, _T("Couldn't open service manager"), szServiceName, MB_OK);
        return FALSE;
    }

    SC_HANDLE hService = ::OpenService(hSCM, szServiceName, SERVICE_STOP | DELETE);

    if (hService == NULL)
    {
        ::CloseServiceHandle(hSCM);
        MessageBox(NULL, _T("Couldn't open service"), szServiceName, MB_OK);
        return FALSE;
    }
    SERVICE_STATUS status;
    ::ControlService(hService, SERVICE_CONTROL_STOP, &status);

	//删除服务
    BOOL bDelete = ::DeleteService(hService);
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);

    if (bDelete)
        return TRUE;

    LogEvent(_T("Service could not be deleted"));
    return FALSE;
}

//*********************************************************
//Functiopn:			LogEvent
//Description:			记录服务事件
//Calls:
//Called By:
//Table Accessed:
//Table Updated:
//Input:
//Output:
//Return:
//Others:
//History:
//			<author>niying <time>2006-8-10		<version>		<desc>
//*********************************************************
void LogEvent(LPCTSTR pFormat, ...)
{
    TCHAR    chMsg[256];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[1];
    va_list pArg;

    va_start(pArg, pFormat);
    _vstprintf(chMsg, pFormat, pArg);
    va_end(pArg);

    lpszStrings[0] = chMsg;
	
	hEventSource = RegisterEventSource(NULL, szServiceName);
	if (hEventSource != NULL)
	{
		ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*) &lpszStrings[0], NULL);
		DeregisterEventSource(hEventSource);
	}
}

