#ifndef HTTPClient_H_
#define HTTPClient_H_
#include <map>
#include <string>
#include <vector>
using namespace std;

class CHTTPClient
{
public:
    CHTTPClient(void);
    ~CHTTPClient(void);
public:
	bool HttpPost(const std::string & strUrl,char* buf,int length,std::map<string,string>& _ResonseHead,std::vector<char>& vcResponse);
	bool HttpPost(const std::string & strUrl,char* buf,int length,std::string& strResult)  ;
	bool HttpGet(const std::string & strUrl,std::string& strResult)  ;
	int GetPostConnectLength(char* pBuf,unsigned int nLen);
};


#endif