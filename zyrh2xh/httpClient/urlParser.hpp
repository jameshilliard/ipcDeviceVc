const int NOPOS = -1;

class urlparser
{
	typedef std::string Stringt;
public:
	urlparser(const Stringt &url)
		: url_(url),
		protpos_(NOPOS),
		dnpos_(NOPOS),
		userpos_(NOPOS),
		pwendpos_(NOPOS),
		portpos_(NOPOS),
		pathpos_(NOPOS),
		filepos_(NOPOS),
		parampos_(NOPOS)
	{
		parseurl();
	}

	urlparser(const char *url)
		: url_(url),
		protpos_(NOPOS),
		dnpos_(NOPOS),
		userpos_(NOPOS),
		pwendpos_(NOPOS),
		portpos_(NOPOS),
		pathpos_(NOPOS),
		filepos_(NOPOS),
		parampos_(NOPOS)
	{
		parseurl();
	}

	Stringt geturl()
	{
		return url_;
	}

	Stringt getprotocol()
	{
		if(protpos_ != NOPOS)
			return url_.substr(0, protpos_);
		else
			return "";
	}

	Stringt getdomain()
	{
		if(dnpos_ != NOPOS && portpos_ != NOPOS)
			return url_.substr(dnpos_, portpos_ - 1 - dnpos_);
		else if(dnpos_ != NOPOS && pathpos_ != NOPOS)
			return url_.substr(dnpos_, pathpos_ - dnpos_);
		else
			return "";
	}

	Stringt getport()
	{
		if(portpos_ != NOPOS && pathpos_ != NOPOS)
			return url_.substr(portpos_, pathpos_ - portpos_);
		else
			return "";
	}

	Stringt getpath()
	{
		if(pathpos_ != NOPOS && filepos_ != NOPOS)
			return url_.substr(pathpos_, filepos_ - pathpos_);
		else if(pathpos_ != NOPOS && parampos_ != NOPOS)
			return url_.substr(pathpos_, parampos_ - 1 - pathpos_);
		else if(pathpos_ != NOPOS)
			return url_.substr(pathpos_, url_.length() - 1);
		else
			return "";
	}

	Stringt getfile()
	{
		if(filepos_ != NOPOS && parampos_ != NOPOS)
			return url_.substr(filepos_, parampos_ - 1 - filepos_);
		else if(filepos_ != NOPOS)
			return url_.substr(filepos_, url_.length() - 1);
		else
			return "";
	}

	Stringt getparameter()
	{
		if(parampos_ != NOPOS && anchorpos_ != NOPOS)
			return url_.substr(parampos_, anchorpos_ - 1 - parampos_);
		else if(parampos_ != NOPOS)
			return url_.substr(parampos_, url_.length() - 1);
		else
			return "";
	}

	Stringt getanchor()
	{
		if(anchorpos_ != NOPOS)
			return url_.substr(anchorpos_, url_.length() - 1);
		else
			return "";
	}

	Stringt gethost()
	{
		return url_.substr(dnpos_, pathpos_ - dnpos_);
	}

	Stringt getreferer()
	{
		return url_.substr(0, pathpos_);
	}
	Stringt getPathUrl()
	{
		return url_.substr(pathpos_, url_.length() - pathpos_);
	}

private:
	void parseurl()
	{
		Stringt::size_type beginpos = 0, endpos = 0;

		beginpos = url_.find(':' , 0);
		endpos = url_.find('/', 0);
		if(beginpos != Stringt::npos && beginpos < endpos && beginpos < url_.find('.', 0))
		{
			protpos_ = beginpos;
			beginpos = url_.find('/', endpos + 1) + 1;
			dnpos_ = beginpos;
		}
		else
		{
			dnpos_ = 0;
			beginpos = dnpos_;
		}

		endpos = url_.find(':', beginpos);
		if(endpos != Stringt::npos)
		{
			portpos_ = endpos + 1;
			beginpos = endpos;
		}

		endpos = url_.find('/', beginpos);
		if(endpos != Stringt::npos)
		{
			pathpos_ = endpos;
		}
		else
		{
			url_ = url_ + '/';
			endpos = url_.find('/', beginpos);
			pathpos_ = endpos;
		}

		beginpos = endpos;
		endpos = url_.find('.', beginpos);
		if(endpos != Stringt::npos)
		{
			beginpos = url_.rfind('/', endpos) + 1;
			filepos_ = beginpos;
		}

		beginpos = url_.find('?', beginpos);
		if(beginpos != Stringt::npos)
		{
			parampos_ = beginpos + 1;
		}

		beginpos = url_.rfind('#', url_.length() - 1);
		if(beginpos != Stringt::npos)
		{
			anchorpos_ = beginpos + 1;
		}
	}

private:
	Stringt url_;
	size_t protpos_;
	size_t dnpos_;
	size_t userpos_;
	size_t pwendpos_;
	size_t portpos_;
	size_t pathpos_;
	size_t filepos_;
	size_t parampos_;
	size_t anchorpos_;
};