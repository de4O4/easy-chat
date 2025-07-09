#include "RedisMgr.h"

RedisMgr::~RedisMgr()
{
}


bool RedisMgr::Get(const std::string& key, std::string& value)
{
	auto context = conn_pool_->GetConnection();
	if(context == nullptr) {
		std::cout << "redis连接失败" << std::endl;
		return false;		////如果连接池中没有可用的连接，则返回false
	}
	auto reply = (redisReply*)redisCommand(context, "GET %s", key.c_str());
	if(reply == nullptr) {
		std::cout << "redis命令执行失败" << std::endl;
		conn_pool_->returnConnection(context);		////将连接放回连接池
		return false;		////如果执行命令失败，则返回false
	}
	if(reply->type != REDIS_REPLY_STRING) {
		std::cout << "redis返回值类型错误" << std::endl;
		freeReplyObject(reply);		////释放redisReply所占用的内存
		conn_pool_->returnConnection(context);		////将连接放回连接池
		return false;		////如果返回值类型不是字符串，则返回false
	}
	value = reply->str;		////将返回值赋值给value
	freeReplyObject(reply);		////释放redisReply所占用的内存
	std::cout << "redis命令执行成功" << std::endl;
	conn_pool_->returnConnection(context);		////将连接放回连接池 
	return true;
}

bool RedisMgr::Set(const std::string& key, const std::string& value)
{	
	auto context = conn_pool_->GetConnection();
	if(context == nullptr) {
		std::cout << "redis连接失败" << std::endl;
		return false;		////如果连接池中没有可用的连接，则返回false
	}
	auto reply = (redisReply*)redisCommand(context, "SET %s %s", key.c_str() , value.c_str());
	if(reply == nullptr) {
		std::cout << "redis命令执行失败" << std::endl;
		conn_pool_->returnConnection(context);		////将连接放回连接池
		return false;		////如果执行命令失败，则返回false
	}
	if(!(reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "OK") == 0) || strcmp(reply->str , "ok") == 0) {
		std::cout << "redis返回值错误" << std::endl;
		freeReplyObject(reply);		////释放redisReply所占用的内存
		conn_pool_->returnConnection(context);		////将连接放回连接池
		return false;		////如果返回值不是OK，则返回false
	}
	freeReplyObject(reply);		////释放redisReply所占用的内存
	std::cout << "redis命令执行成功" << std::endl;
	conn_pool_->returnConnection(context);		////将连接放回连接池
	return true;
}



bool RedisMgr::LPush(const std::string& key, const std::string& value)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "LPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == reply)
	{
		std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		conn_pool_->returnConnection(connect);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
		std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		conn_pool_->returnConnection(connect);
		return false;
	}

	std::cout << "Execut command [ LPUSH " << key << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(reply);
	conn_pool_->returnConnection(connect);
	return true;
}

bool RedisMgr::LPop(const std::string& key, std::string& value)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "LPOP %s ", key.c_str());
	if (reply == nullptr) {
		std::cout << "Execut command [ LPOP " << key << " ] failure ! " << std::endl;
		conn_pool_->returnConnection(connect);
		return false;
	}

	if (reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ LPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		conn_pool_->returnConnection(connect);
		return false;
	}

	value = reply->str;
	std::cout << "Execut command [ LPOP " << key << " ] success ! " << std::endl;
	freeReplyObject(reply);
	conn_pool_->returnConnection(connect);
	return true; 
}

bool RedisMgr::RPush(const std::string& key, const std::string& value)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "RPUSH %s %s", key.c_str(), value.c_str());
	if (NULL == reply)
	{
		std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		conn_pool_->returnConnection(connect);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer <= 0) {
		std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		conn_pool_->returnConnection(connect);
		return false;
	}

	std::cout << "Execut command [ RPUSH " << key << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(reply);
	conn_pool_->returnConnection(connect);
	return true;
}

bool RedisMgr::RPop(const std::string& key, std::string& value)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "RPOP %s ", key.c_str());
	if (reply == nullptr) {
		std::cout << "Execut command [ RPOP " << key << " ] failure ! " << std::endl;
		conn_pool_->returnConnection(connect);
		return false;
	}

	if (reply->type == REDIS_REPLY_NIL) {
		std::cout << "Execut command [ RPOP " << key << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		conn_pool_->returnConnection(connect);
		return false;
	}
	value = reply->str;
	std::cout << "Execut command [ RPOP " << key << " ] success ! " << std::endl;
	freeReplyObject(reply);
	conn_pool_->returnConnection(connect);
	return true;
}

bool RedisMgr::HSet(const std::string& key, const std::string& hkey, const std::string& value)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "HSET %s %s %s", key.c_str(), hkey.c_str(), value.c_str());
	if (reply == nullptr) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] failure ! " << std::endl;
		conn_pool_->returnConnection(connect);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		conn_pool_->returnConnection(connect);
		return false;
	}

	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] success ! " << std::endl;
	freeReplyObject(reply);
	conn_pool_->returnConnection(connect);
	return true;
}

bool RedisMgr::HSet(const char* key, const char* hkey, const char* hvalue, std::size_t hvaluelen)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return false;
	}
	const char* argv[4];
	size_t argvlen[4];
	argv[0] = "HSET";
	argvlen[0] = 4;
	argv[1] = key;
	argvlen[1] = strlen(key);
	argv[2] = hkey;
	argvlen[2] = strlen(hkey);
	argv[3] = hvalue;
	argvlen[3] = hvaluelen;

	auto reply = (redisReply*)redisCommandArgv(connect, 4, argv, argvlen);
	if (reply == nullptr) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] failure ! " << std::endl;
		conn_pool_->returnConnection(connect);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		conn_pool_->returnConnection(connect);
		return false;
	}
	std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << hvalue << " ] success ! " << std::endl;
	freeReplyObject(reply);
	conn_pool_->returnConnection(connect);
	return true;
}

std::string RedisMgr::HGet(const std::string& key, const std::string& hkey)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return "";
	}
	const char* argv[3];
	size_t argvlen[3];
	argv[0] = "HGET";
	argvlen[0] = 4;
	argv[1] = key.c_str();
	argvlen[1] = key.length();
	argv[2] = hkey.c_str();
	argvlen[2] = hkey.length();

	auto reply = (redisReply*)redisCommandArgv(connect, 3, argv, argvlen);
	if (reply == nullptr) {
		std::cout << "Execut command [ HGet " << key << " " << hkey << "  ] failure ! " << std::endl;
		conn_pool_->returnConnection(connect);
		return "";
	}

	if (reply->type == REDIS_REPLY_NIL) {
		freeReplyObject(reply);
		std::cout << "Execut command [ HGet " << key << " " << hkey << "  ] failure ! " << std::endl;
		conn_pool_->returnConnection(connect);
		return "";
	}

	std::string value = reply->str;
	freeReplyObject(reply);
	conn_pool_->returnConnection(connect);
	std::cout << "Execut command [ HGet " << key << " " << hkey << " ] success ! " << std::endl;
	return value;
}

bool RedisMgr::HDel(const std::string& key, const std::string& field)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return false;
	}

	redisReply* reply = (redisReply*)redisCommand(connect, "HDEL %s %s", key.c_str(), field.c_str());
	if (reply == nullptr) {
		std::cerr << "HDEL command failed" << std::endl;
		return false;
	}

	bool success = false;
	if (reply->type == REDIS_REPLY_INTEGER) {
		success = reply->integer > 0;
	}

	freeReplyObject(reply);
	return success;
}

bool RedisMgr::Del(const std::string& key)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return false;
	}
	auto reply = (redisReply*)redisCommand(connect, "DEL %s", key.c_str());
	if (reply == nullptr) {
		std::cout << "Execut command [ Del " << key << " ] failure ! " << std::endl;
		conn_pool_->returnConnection(connect);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER) {
		std::cout << "Execut command [ Del " << key << " ] failure ! " << std::endl;
		freeReplyObject(reply);
		conn_pool_->returnConnection(connect);
		return false;
	}

	std::cout << "Execut command [ Del " << key << " ] success ! " << std::endl;
	freeReplyObject(reply);
	conn_pool_->returnConnection(connect);
	return true;
}

bool RedisMgr::Exists(const std::string& key)
{
	auto connect = conn_pool_->GetConnection();
	if (connect == nullptr) {
		return false;
	}

	auto reply = (redisReply*)redisCommand(connect, "exists %s", key.c_str());
	if (reply == nullptr) {
		std::cout << "Not Found [ Key " << key << " ]  ! " << std::endl;
		conn_pool_->returnConnection(connect);
		return false;
	}

	if (reply->type != REDIS_REPLY_INTEGER || reply->integer == 0) {
		std::cout << "Not Found [ Key " << key << " ]  ! " << std::endl;
		conn_pool_->returnConnection(connect);
		freeReplyObject(reply);
		return false;
	}
	std::cout << " Found [ Key " << key << " ] exists ! " << std::endl;
	freeReplyObject(reply);
	conn_pool_->returnConnection(connect);
	return true; 
}

void RedisMgr::Close() {
	conn_pool_->Close();		////关闭连接池，释放连接池中的连接

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

RedisConnPool::~RedisConnPool()
{
	std::lock_guard<std::mutex> lock(mutex_);
	while (!connections_.empty()) {
		connections_.pop();		////释放连接池中的连接
	}
}

redisContext* RedisConnPool::GetConnection() {
	std::unique_lock < std::mutex > lock(mutex_);
	cond_.wait(lock, [this]() {
		if (b_stop_) {
			return true;			////如果连接池已经停止，则直接返回
		}
		return !connections_.empty();
		});
	if (b_stop_) {
		return nullptr;			////如果连接池已经停止，则返回空指针
	}
	auto context = connections_.front();
	connections_.pop();		////从连接池中取出一个连接
	return context;		////返回连接
}

void RedisConnPool::returnConnection(redisContext* conn) {
	std::lock_guard<std::mutex> lock(mutex_);
	if (b_stop_) {
		redisFree(conn);
		return;
	}
	connections_.push(conn);		////将连接放回连接池中
	cond_.notify_one();		////通知等待的线程有连接可用
}

void RedisConnPool::Close() {
	b_stop_ = true;		////设置连接池停止标志
	cond_.notify_all();		////通知所有等待的线程
}

RedisMgr::RedisMgr()
{
	auto& config = ConfigMgr::Instance();
	auto host = config["Redis"]["Host"];
	auto port = config["Redis"]["Port"];
	auto pwd = config["Redis"]["Passwd"];
	conn_pool_.reset(new RedisConnPool(5, host.c_str(), atoi(port.c_str()), pwd.c_str()));		////创建一个RedisConnPool对象，连接池大小为5，host、port和pwd从配置文件中读取
}
