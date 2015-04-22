//
// io_buffer.hpp
// ~~~~~~~~~~~~~
//
// The class based on boost::asio::detail::buffered_stream_storage.
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Copyright (c) 2009 Xu Ye Jun (moore.xu@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BAS_SEND_BUFFER_HPP
#define BAS_SEND_BUFFER_HPP

#include <boost/assert.hpp>
#include <boost/asio/detail/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include <vector>
using namespace std;


class CSendbuffer 
{
public:
	CSendbuffer()
	{

	}
	~CSendbuffer()
	{

	}
	CSendbuffer(char* sendBuf,unsigned int buflen)
	{
		buffer_.assign(sendBuf,sendBuf + buflen);
	}
	void InsertData(char* sendBuf,unsigned int buflen)
	{
		buffer_.insert(buffer_.end(),sendBuf,sendBuf + buflen);
	}
	void push_back(char chValue)
	{
		buffer_.push_back(chValue);
	}
	char* Data()
	{
		if (buffer_.size() > 0)
		{
			return &buffer_[0];
		}
		return NULL;
	}
	unsigned int length()
	{
		return buffer_.size();
	}
	void clear()
	{
		buffer_.clear();
	}
	void BuiladPakage(char* buf,unsigned int nLength)
	{
		push_back(0x00);
		unsigned int nlen = nLength + 1;
		InsertData((char*)&nlen,sizeof(nLength));
		push_back(0x00);
		InsertData(buf,nLength);
		push_back('#');
	}

private:
  std::vector<char> buffer_;
};

#endif 
