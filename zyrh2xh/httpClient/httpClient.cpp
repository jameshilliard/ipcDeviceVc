#include "httpclient.h"  
#include "urlParser.hpp"
#include <WinSock2.h>
#include <vector>

using namespace std;
#pragma comment(lib,"ws2_32.lib") 
#include <stdio.h>
#define  HTTPVESION "HTTP/1.1"
#define  POST       "POST"
#define  GET        "GET"
#define  PUT        "PUT"
#define  DELETE        "DELETE"
#define  SENDLEN     1460
#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))
CHTTPClient::CHTTPClient(void)  
{  

}  

CHTTPClient::~CHTTPClient(void)  
{  

}  
void OnRead(char* buf,int nlength,int socket);
bool CHTTPClient::HttpPost(const std::string & strUrl,char* buf,int length,std::map<string,string>& _ResonseHead,std::vector<char>& vcResponse)  
{    
	urlparser surlparser(strUrl);
	std::string sIp = surlparser.getdomain();
	unsigned int nPort = atoi(surlparser.getport().c_str());
	std::string spath = surlparser.getPathUrl();
	WSADATA	WsaData;
	WSAStartup (0x0101, &WsaData);
	sockaddr_in       sin;
	int sock = socket (AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		return false;
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons( (unsigned short)nPort);

	struct hostent * host_addr = gethostbyname(sIp.c_str());
	if(host_addr==NULL) {
		return false;
	}
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list) ;

	if( connect (sock,(const struct sockaddr *)&sin, sizeof(sockaddr_in) ) == -1 ) {
		return false;
	}

	char sendbuf[2048];
	char buftmp[1024];
	ZeroMemory(sendbuf,2048);
	sprintf(sendbuf,"%s %s %s\r\n",POST,spath.c_str(),HTTPVESION);


	sprintf(buftmp,"%s %d\r\n","Content-Length:",length);
	strcat(sendbuf,buftmp);

	sprintf(buftmp,"%s %s:%d\r\n","Host:",sIp.c_str(),nPort);
	strcat(sendbuf,buftmp);

	sprintf(buftmp,"%s %s\r\n","User-Agent:","dwk");
	strcat(sendbuf,buftmp);

	sprintf(buftmp,"%s %s\r\n","Accept:","*/*");
	strcat(sendbuf,buftmp);

	strcat(sendbuf,"\r\n");
	//发送http 的头
	int sendret = send(sock,sendbuf,strlen(sendbuf),0);
	if (sendbuf <= 0)
	{
		return false;
	}
	int poslen = 0;
	sendret = send(sock,buf,length,0);
	char c1[1];
	int l,line_length;
	bool loop = true;
	bool bHeader = false;
	std::string message;
	while(loop) {
		l = recv(sock, c1, 1, 0);
		if(l<0) loop = false;
		if(c1[0]=='\n') {
			if(line_length == 0) 
			{
				loop = false;
				break;
			}
			line_length = 0;
			if(message.find(HTTPVESION) != string::npos)
			{
				std::string svalue = (char*)memchr(message.c_str(),' ',message.length());
				svalue = svalue.substr(1,3);
				_ResonseHead[HTTPVESION] =  svalue;
			}
			else
			{
				std::string svalue = (char*)memchr(message.c_str(),' ',message.length());
				svalue = svalue.substr(1,svalue.length() -1);
				std::string skey = strtok ((char*)message.c_str(),":");
				_ResonseHead[skey] =  svalue;
			}
			message.clear();
		}
		else if(c1[0]!='\r')
		{
			line_length++;	
			message += c1[0];
		}
	}
	length = atoi(_ResonseHead["Content-Length"].c_str());
	vcResponse.clear();	
	if (length > 0)
	{
		vcResponse.assign(length+1,'\0');
		l = recv(sock, (char*)&vcResponse[0], length, 0);
		if (l != length)
		{
			return false;
		}
		return true;
	}
	return true;
}  
bool CHTTPClient::HttpPost(const std::string & strUrl,char* buf,int length,std::string& strResult)  
{    
	std::vector<char> vcResponse;
	std::map<string,string> _ResonseHead;
	urlparser surlparser(strUrl);
	std::string sIp = surlparser.getdomain();
	unsigned int nPort = atoi(surlparser.getport().c_str());
	std::string spath = surlparser.getPathUrl();
	WSADATA	WsaData;
	WSAStartup (0x0101, &WsaData);
	sockaddr_in       sin;
	int sock = socket (AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		return false;
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons( (unsigned short)nPort);

	struct hostent * host_addr = gethostbyname(sIp.c_str());
	if(host_addr==NULL) {
		return false;
	}
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list) ;

	if( connect (sock,(const struct sockaddr *)&sin, sizeof(sockaddr_in) ) == -1 ) {
		return false;
	}

	char sendbuf[2048];
	char buftmp[1024];
	ZeroMemory(sendbuf,2048);
	sprintf(sendbuf,"%s %s %s\r\n",POST,spath.c_str(),HTTPVESION);


	sprintf(buftmp,"%s %d\r\n","Content-Length:",length);
	strcat(sendbuf,buftmp);

	sprintf(buftmp,"%s %s:%d\r\n","Host:",sIp.c_str(),nPort);
	strcat(sendbuf,buftmp);

	sprintf(buftmp,"%s %s\r\n","User-Agent:","dwk");
	strcat(sendbuf,buftmp);

	sprintf(buftmp,"%s %s\r\n","Accept:","*/*");
	strcat(sendbuf,buftmp);

	strcat(sendbuf,"\r\n");
	//发送http 的头
	int sendret = send(sock,sendbuf,strlen(sendbuf),0);
	if (sendbuf <= 0)
	{
		return false;
	}
	int poslen = 0;
	if (length > 0)
	{
		sendret = send(sock,buf,length,0);
	}
	char c1[1];
	int l,line_length;
	bool loop = true;
	bool bHeader = false;
	std::string message;
	while(loop) {
		l = recv(sock, c1, 1, 0);
		if(l<0) loop = false;
		if(c1[0]=='\n') {
			if(line_length == 0) 
			{
				loop = false;
				break;
			}
			line_length = 0;
			if(message.find(HTTPVESION) != string::npos)
			{
				std::string svalue = (char*)memchr(message.c_str(),' ',message.length());
				svalue = svalue.substr(1,3);
				_ResonseHead[HTTPVESION] =  svalue;
			}
			else
			{
				std::string svalue = (char*)memchr(message.c_str(),' ',message.length());
				svalue = svalue.substr(1,svalue.length() -1);
				std::string skey = strtok ((char*)message.c_str(),":");
				_ResonseHead[skey] =  svalue;
			}
			message.clear();
		}
		else if(c1[0]!='\r')
		{
			line_length++;	
			message += c1[0];
		}
	}
	length = atoi(_ResonseHead["Content-Length"].c_str());
	vcResponse.clear();	
	if (length > 0)
	{
		vcResponse.assign(length+1,'\0');
		l = recv(sock, (char*)&vcResponse[0], length, 0);
		if (l != length)
		{
			return false;
		}
		strResult = (char*)&vcResponse[0];
		return true;
	}
	return true;
}
bool CHTTPClient::HttpGet(const std::string & strUrl,std::string& strResult)  
{    
	std::map<string,string> _ResonseHead;
	std::vector<char> vcResponse;
	urlparser surlparser(strUrl);
	std::string sIp = surlparser.getdomain();
	UINT nPort = atoi(surlparser.getport().c_str());
	std::string spath = surlparser.getPathUrl();
	WSADATA	WsaData;
	WSAStartup (0x0101, &WsaData);
	sockaddr_in       sin;
	int sock = socket (AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		return false;
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons( (unsigned short)nPort);

	struct hostent * host_addr = gethostbyname(sIp.c_str());
	if(host_addr==NULL) {
		return false;
	}
	sin.sin_addr.s_addr = *((int*)*host_addr->h_addr_list) ;

	if( connect (sock,(const struct sockaddr *)&sin, sizeof(sockaddr_in) ) == -1 ) {
		return false;
	}

	char sendbuf[2048];
	char buftmp[1024];
	ZeroMemory(sendbuf,2048);
	sprintf(sendbuf,"%s %s %s\r\n",GET,spath.c_str(),HTTPVESION);




	sprintf(buftmp,"%s %s:%d\r\n","Host:",sIp.c_str(),nPort);
	strcat(sendbuf,buftmp);

	sprintf(buftmp,"%s %s\r\n","User-Agent:","dwk");
	strcat(sendbuf,buftmp);

	sprintf(buftmp,"%s %s\r\n","Accept:","*/*");
	strcat(sendbuf,buftmp);

	//strcat(sendbuf,m_sHead.c_str());
	strcat(sendbuf,"\r\n");
	//发送http 的头
	int sendret = send(sock,sendbuf,strlen(sendbuf),0);
	if (sendbuf <= 0)
	{
		return false;
	}
	char c1[1];
	int l,line_length;
	bool loop = true;
	bool bHeader = false;
	std::string message;
	while(loop) {
		l = recv(sock, c1, 1, 0);
		if(l<0) loop = false;
		if(c1[0]=='\n') {
			if(line_length == 0) 
			{
				loop = false;
				break;
			}
			line_length = 0;
			if(message.find(HTTPVESION) != string::npos)
			{
				std::string svalue = (char*)memchr(message.c_str(),' ',message.length());
				svalue = svalue.substr(1,3);
				_ResonseHead[HTTPVESION] =  svalue;
			}
			else
			{
				std::string svalue = (char*)memchr(message.c_str(),' ',message.length());
				svalue = svalue.substr(1,svalue.length() -1);
				std::string skey = strtok ((char*)message.c_str(),":");
				_ResonseHead[skey] =  svalue;
			}
			message.clear();
		}
		else if(c1[0]!='\r')
		{
			line_length++;	
			message += c1[0];
		}

	}
	std::string strkeylen = "Content-Length";
	map<std::string,std::string>::iterator it = _ResonseHead.find(strkeylen.c_str());
	std::string strlen = _ResonseHead[strkeylen];
	int length = atoi(strlen.c_str());
	vcResponse.clear();	
	if (length > 0)
	{
		vcResponse.assign(length+1,'\0');
		l = recv(sock, (char*)&vcResponse[0], length, 0);
		if (l != length)
		{
			return false;
		}
	}
	strkeylen = "Transfer-Encoding";
	it = _ResonseHead.find(strkeylen.c_str());
	if (it != _ResonseHead.end())		
	{
		loop = true;
		while(loop) {
			l = recv(sock, c1, 1, 0);
			if(l<0) loop = false;

			if(c1[0]=='\n') {
				int len = 0;
				sscanf(message.c_str(),"%x",&len);
				if (len > 0 )
				{
					vcResponse.assign(len+1,'\0');
					l = recv(sock, (char*)&vcResponse[0], len, 0);
				}
				loop = false;
			}
			else if(c1[0]!='\r')
			{
				line_length++;	
				message += c1[0];
			}
		}

	}
	vcResponse.push_back('\0');
	if (vcResponse.size() > 0 )
	{
		strResult = &vcResponse[0];
	}
	return true;
}  
void OnRead(char* buf,int nlength,int socket)
{

}
int CHTTPClient::GetPostConnectLength(char* pBuf,unsigned int nLen)
{
	if (pBuf != NULL)
	{
		char* pConnectLenth = strstr(pBuf,"Content-Length: ");
		if (pConnectLenth != NULL)
		{
			pConnectLenth =  strtok(pConnectLenth,"\r\n");
			if (pConnectLenth != NULL)
			{
				int nCntentlen = strlen("Content-Length: ");
				if (strlen(pConnectLenth) > nCntentlen)
				{
					return atoi(pConnectLenth + nCntentlen);
				}	
			}
		}
	}
	return 0;
}
