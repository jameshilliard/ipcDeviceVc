#pragma once
#include <string>
#include <map>
#include "tinyxml.h"
typedef std::map<std::string,std::string> MapValue;
struct xml_data
{
	std::string Command;
	std::string MessageType;
	std::map<std::string,MapValue> param;
	std::map<std::string,std::string> param1;

	
	//用于接收
	std::string Statue;
	std::string Description;
	xml_data()
	{

	}


	xml_data(const xml_data& _xml_data)
	{
		Command = _xml_data.Command;
		param = _xml_data.param;
	}
};

class xmlparser
{
public:
	xmlparser(void);
	~xmlparser(void);
	static void	EncodeXml(xml_data *_xml_data,std::string &strxml);
	static bool DecodeXml(const char *strxml,xml_data *_xml_data);
};
