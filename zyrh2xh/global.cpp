#include "global.h"
void strseparate(char* src,std::string& sfrist,std::string& ssecond,const char* chSeparate)
{
	char* sret = strtok(src,chSeparate);
	if (sret)
	{
		sfrist = sret;
		ssecond = (src + strlen(sret) + strlen(chSeparate));
	}
}
string&   replace_all(string&   str,const   string&   old_value,const   string&   new_value)     
{     
	while(true)   {     
		string::size_type   pos(0);     
		if(   (pos=str.find(old_value))!=string::npos   )     
			str.replace(pos,old_value.length(),new_value);     
		else   break;     
	}     
	return   str;     
}     
string&   replace_all_distinct(string&   str,const   string&   old_value,const   string&   new_value)     
{     
	for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   {     
		if(   (pos=str.find(old_value,pos))!=string::npos   )     
			str.replace(pos,old_value.length(),new_value);     
		else   break;     
	}     
	return   str;     
}    