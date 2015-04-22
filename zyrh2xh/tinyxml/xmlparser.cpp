#include "xmlparser.h"
#include "xmlCmd.h"
xmlparser::xmlparser(void)
{
}

xmlparser::~xmlparser(void)
{
}


void xmlparser::EncodeXml(xml_data *_xml_data,std::string &strxml)
{

	TiXmlDocument pTiXmlDocument; 
	TiXmlDeclaration *pTiXmlDeclaration = new TiXmlDeclaration("1.0","UTF-8", ""); 
	pTiXmlDocument.LinkEndChild( pTiXmlDeclaration );

	TiXmlElement *pElementroot= new TiXmlElement("Message"); 
	pElementroot->SetAttribute("Version","1.0.1");
	pTiXmlDocument.LinkEndChild(pElementroot);

	TiXmlElement *pElementIE_HEADER = new TiXmlElement("IE_HEADER");
	pElementroot->LinkEndChild(pElementIE_HEADER);

	TiXmlElement *pMessageType = new TiXmlElement("MessageType");
	pElementIE_HEADER->LinkEndChild(pMessageType);
	TiXmlText *pTextMessageType = new TiXmlText(_xml_data->MessageType.c_str());
	pMessageType->LinkEndChild(pTextMessageType);

	TiXmlElement *pReserved = new TiXmlElement("Reserved");
	pElementIE_HEADER->LinkEndChild(pReserved);
// 	TiXmlText *pTextReserved = new TiXmlText(_xml_data->MessageType.c_str());
// 	pReserved->LinkEndChild(pTextReserved);



	std::map<std::string,MapValue>::iterator it = _xml_data->param.begin();
	while(it != _xml_data->param.end())
	{
		if (it->first != "IE_HEADER")
		{

			TiXmlElement *pElementParent = new TiXmlElement(it->first.c_str());
			pElementroot->LinkEndChild(pElementParent);

			for (MapValue::iterator itParam = it->second.begin();itParam != it->second.end();itParam++ )
			{
				TiXmlElement *pMessageKey = new TiXmlElement(itParam->first.c_str());
				pElementParent->LinkEndChild(pMessageKey);

				if (itParam->second != "")
				{
					TiXmlText *pMessageValue = new TiXmlText(itParam->second.c_str());
					pMessageKey->LinkEndChild(pMessageValue);
				}
			}
		}
		it++;
	}
	TiXmlPrinter printer;
	pTiXmlDocument.Accept(&printer);

	strxml.assign(printer.CStr());
	strxml += "\n";
}

bool xmlparser::DecodeXml(const char *strxml,xml_data *_xml_data)
{
	TiXmlDocument tiXmlDocument;
	tiXmlDocument.Parse(strxml);
	if ( tiXmlDocument.Error() )
	{
		tiXmlDocument.SaveFile("C:\\error1.xml");
		return false;
	}
	TiXmlElement *lmtRoot = tiXmlDocument.RootElement();
	if(!lmtRoot)
		return false;
	TiXmlElement *pElement= lmtRoot->FirstChildElement();
	while (pElement)
	{
		std::string str = pElement->Value();
		MapValue sMapValue;
		{

			TiXmlElement *pElementKey = pElement->FirstChildElement();
			while (pElementKey)
			{
				{
					std::string strkey;
					if(pElementKey->Value())
					{
						strkey = pElementKey->Value();
					}
					std::string strValue;
					if(pElementKey->GetText())
					{
						strValue = pElementKey->GetText();
					}
					if(strkey == "MessageType")
					{
						_xml_data->MessageType = strValue;

					}
					sMapValue[strkey] = strValue;
					_xml_data->param1[strkey] = strValue;

				}
				pElementKey = pElementKey->NextSiblingElement();
			}

		}
		_xml_data->param[str] = sMapValue;
		sMapValue.clear();	
		pElement = pElement->NextSiblingElement();
	}
	return true;
}