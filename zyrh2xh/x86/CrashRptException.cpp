#include "CrashRptException.h"
#include <string>

CCrashRptException::CCrashRptException(void)
{
}

CCrashRptException::~CCrashRptException(void)
{
}


BOOL WINAPI CrashCallback(LPVOID lpvState)
{
	// Add two files to the error report:    
	// log file and application configuration file
	//CString sLogFile = GetAppDir() + _T("\\LOG\\socketCom.log");

	return TRUE; 
}

bool CCrashRptException::InstallCrashRpt()
{
	// Install crash reporting

	CR_INSTALL_INFO info;     
	memset(&info, 0, sizeof(CR_INSTALL_INFO));     
	info.cb = sizeof(CR_INSTALL_INFO);       
	info.pszAppName = ("zyrh"); // Define application name.
	info.pszAppVersion = ("1.0.0");     // Define application version.
	info.pszEmailSubject = ("zyrh"); // Define subject for email. 
	info.pfnCrashCallback = CrashCallback;      
	info.uPriorities[CR_HTTP] = 3;  // First try send report over HTTP    
	info.uPriorities[CR_SMTP] = 2;  // Second try send report over SMTP     
	info.uPriorities[CR_SMAPI] = 1; // Third try send report over Simple MAPI       
	// Install all available exception handlers, use HTTP binary transfer encoding (recommended).   
	info.dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS;   
	info.dwFlags |= CR_INST_HTTP_BINARY_ENCODING;    
	info.dwFlags |= CR_INST_APP_RESTART; //
	info.dwFlags |= CR_INST_DONT_SEND_REPORT;    
	info.dwFlags |= CR_INST_NO_GUI;                 // Don't display GUI.
	info.pszRestartCmdLine = ("/restart");   
	// Define the Privacy Policy URL    
	info.pszPrivacyPolicyURL = "";    
	info.pszErrorReportSaveDir = TEXT("./Crash");

	// Install exception handlers   
	int nResult = crInstall(&info);       
	if(nResult!=0)     
	{       
		// Something goes wrong. Get error message.   
		char szErrorMsg[512];       
		szErrorMsg[0]=0;       
		crGetLastErrorMsg(szErrorMsg, 512);       
		printf("%s\n", szErrorMsg);       
		return false;   
	}

	return true;
}

void CCrashRptException::UnstallCrashRpt()   
{   
	crUninstall();   
}   