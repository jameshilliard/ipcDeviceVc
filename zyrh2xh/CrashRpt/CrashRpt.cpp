#include "CrashRpt.h"
#include <iostream>
BOOL WINAPI CrashCallback(LPVOID /*lpvState*/)  
{    
	// 返回TRUE, 由crashrpt生成错误报告  
	return TRUE;  
}  
bool initCrash()
{
	CR_INSTALL_INFO info;    
	memset(&info, 0, sizeof(CR_INSTALL_INFO));    
	info.cb = sizeof(CR_INSTALL_INFO);      
	info.pszAppName = ("MyApp");    
	info.pszAppVersion = ("1.0.0");    
	info.pszEmailSubject = ("MyApp 1.0.0 Error Report");    
	info.pszEmailTo = ("myapp_support@hotmail.com");      
	info.pszUrl = ("http://myapp.com/tools/crashrpt.php"); 
	info.pszErrorReportSaveDir = TEXT("./crashrpt");  
	info.pfnCrashCallback = CrashCallback;     
	info.uPriorities[CR_HTTP] = 3;  // 首先使用HTTP的方式发送错误报告  
	info.uPriorities[CR_SMTP] = 2;  // 然后使用SMTP的方式发送错误报告    
	info.uPriorities[CR_SMAPI] = 1; //最后尝试使用SMAPI的方式发送错误报告      
	// 捕获所有能够捕获的异常, 使用HTTP二进制编码的方式传输  
	info.dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS;  
	info.dwFlags |= CR_INST_HTTP_BINARY_ENCODING;   
	//info.dwFlags |= CR_INST_APP_RESTART;   
	info.dwFlags |= CR_INST_DONT_SEND_REPORT;     
	// 隐私策略URL  
	info.pszPrivacyPolicyURL = ("http://myapp.com/privacypolicy.html");   

	int nResult = crInstall(&info);      
	if(nResult!=0)    
	{      
		TCHAR szErrorMsg[512] = ("");          
		crGetLastErrorMsg(szErrorMsg, 512);      
		printf(("%s\n"), szErrorMsg);      
		return false;  
	}   
	// 添加任意的信息到错误报告中，这里以显卡信息作为示例  
	crAddProperty(("VideoCard"), ("nVidia GeForce 8600 GTS"));
	return true;

}