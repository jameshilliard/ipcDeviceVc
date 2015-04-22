#pragma once
#include <boost/asio/detail/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <map>
using namespace std;

 template <class K,class V>
 class CMapBase
 {
 public:
 	CMapBase(void)
	{
	}
 	~CMapBase(void)
	{
	}

 	void AddData(K tKey,V sValue)
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		m_DataMap[tKey] = sValue;
	}

 	bool GetData(K tKey,V &sValue)
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		map<K,V>::iterator it = m_DataMap.find(tKey);
		if (it != m_DataMap.end())
		{
			sValue = it->second;
			return true;
		}
		else
			return false;
	}

	bool GetBeginData(V &sValue)
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		map<K,V>::iterator it = m_DataMap.begin();
		if (it != m_DataMap.end())
		{
			sValue = it->second;
			return true;
		}
		else
			return false;
	}

	bool RemoveHead(V &sValue)
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		map<K,V>::iterator it = m_DataMap.begin();
		if (it != m_DataMap.end())
		{
			sValue = it->second;
			m_DataMap.erase(it);
			return true;
		}
		else
			return false;
	}

 	void DelData(K tKey)
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		map<K,V>::iterator it = m_DataMap.find(tKey);
		if (it != m_DataMap.end())
			m_DataMap.erase(it);
	}
	bool DelDataAndGetValue(K tKey,V &sValue)
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		map<K,V>::iterator it = m_DataMap.find(tKey);
		if (it != m_DataMap.end())
		{
			sValue = it->second;
			m_DataMap.erase(it);
			return true;
		}
		else
		{
			return false;
		}
	}

 	void DelAllData()
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		m_DataMap.clear();
	}

 	map<K,V> GetDataList()
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		return m_DataMap;
	}

	void SetDataList(map<K,V> mDataList)
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		m_DataMap = mDataList;
	}

	int GetListSize()
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		return m_DataMap.size();
	}
	bool HasData(K tKey)
	{
		boost::asio::detail::mutex::scoped_lock lock(mutex_Map);
		map<K,V>::iterator it = m_DataMap.find(tKey);
		if (it != m_DataMap.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
 private:
 	boost::asio::detail::mutex mutex_Map;
 	map<K,V> m_DataMap;
 };