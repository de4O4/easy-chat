#include "RedisMgr.h"

RedisMgr::~RedisMgr()
{
}


bool RedisMgr::Get(const std::string& key, std::string& value)
{

	return false;
}

bool RedisMgr::Set(const std::string& key, const std::string& value)
{
	return false;
}

bool RedisMgr::Auth(const std::string& passwd)
{
	return false;
}

RedisConnPool::RedisConnPool(std::size_t poolsize, const char* host,int port, const char* pwd):poolsize_(poolsize) , host_(host), pwd_(pwd),
b_stop_(false),port_(port)
{
	for (std::size_t i = 0; i < poolsize; i++) {
		auto* context = redisConnect(host, port);
		if(context == nullptr || context->err) {
			if (context) {
				redisFree(context);
			}
			throw std::runtime_error("Failed to connect to Redis server");
			continue;
		}
		auto reply = (redisReply *)redisCommand(context, "AUTH %s", pwd);
		if (reply->type == REDIS_REPLY_ERROR) {
			std::cout << "redis 认证失败" << std::endl;
			freeReplyObject(reply);		////执行失败 释放redisCommand执行后返回的redisReply所占用的内存
			continue;
		}
		freeReplyObject(reply);		////执行成功 释放redisCommand执行后返回的redisReply所占用的内存
		std::cout << "redis 认证成功" << std::endl;
		connections_.push(context);
	}
}
