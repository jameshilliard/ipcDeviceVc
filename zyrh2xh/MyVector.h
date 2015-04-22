#pragma once
#include <boost/asio/detail/mutex.hpp>
#include <vector>
template<class T>
class CMyVector
{
public:
private:
	std::vector<T> dDataBuf;
	boost::asio::detail::mutex mutex_;
public:
    void pushBack(const T& datBuf)
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_);
		dDataBuf.push_back(datBuf);
	}
	
	T& GetData()
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_);
		return dDataBuf.front();
	}
	void clear()
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_);
		dDataBuf.clear();
	}
	bool IsHasData()
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_);
		if(dDataBuf.size()>0) 
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	int GetSize()
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_);
		return dDataBuf.size(); 
	}
	void GetDataListAndClear(std::vector<T>& _tmpVal)
	{
		{
			boost::asio::detail::mutex::scoped_lock lock(mutex_);
			_tmpVal = dDataBuf;
			dDataBuf.clear();
		}
	}
	void GetDataList(std::vector<T>& _tmpVal)
	{	
		boost::asio::detail::mutex::scoped_lock lock(mutex_);
		_tmpVal = dDataBuf;
	}
};
