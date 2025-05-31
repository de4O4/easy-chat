#pragma once
#include "const.h"
#include "Singleton.h"

class RedisConnPool {
public:
	RedisConnPool(std::size_t poolsize , const char* host , int potr ,const char* pwd);
private:
	std::atomic<bool> b_stop_;
	std::mutex mutex_;
	std::condition_variable cond_;
	std::queue<redisContext*> connections_;
	const char* host_;
	const char* pwd_;
	std::size_t poolsize_;
	int port_;
};




class RedisMgr :public Singleton<RedisMgr>,public std::enable_shared_from_this<RedisMgr>
{
	friend class Singleton<RedisMgr>;
public:
	~RedisMgr();
	bool Get(const std::string & key , std::string& value);
	bool Set(const std::string& key , const std::string& value);
	bool Auth(const std::string& passwd);
	bool LPush(const std::string& key , const std::string& value);
	bool LPop(const std::string& key, std::string& value);
	bool RPush(const std::string& key, const std::string& value);
	bool RPop(const std::string& key, std::string& value);
	bool HSet(const std::string& key, const std::string& hkey, const std::string& value);
	bool HSet(const char* key, const char* hkey, const char* hvalue, std::size_t hvaluelen);
	std::string HGet(const std::string& key, const std::string& hkey);
	bool Del(const std::string& key);
	bool Exists(const std::string& key);
	void Close();
private:
	RedisMgr();
	redisContext* _connect;
	redisReply* _reply;
};

