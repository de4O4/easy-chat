#pragma once
#include "const.h"
#include <thread>

class SqlConnection {
public:
	SqlConnection(sql::Connection* conn, int64_t lasttime): _conn(conn), _last_oper_time(lasttime) {}
	std::unique_ptr<sql::Connection> _conn;
	int64_t _last_oper_time;
};

class MysqlPool{
public:
	MysqlPool(const std::string& url, const std::string& user, const std::string& pass, const std::string& schema, int poolsize)
		: _url(url), _user(user), _pass(pass), _schema(schema), _poolsize(poolsize), _b_stop(false) {
		try
		{
			for (int i = 0; i < poolsize; i++) {
				sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
				std::unique_ptr<sql::Connection> conn(driver->connect(_url, _user, _pass));
				conn->setSchema(_schema);
				_pool.push(std::move(conn));
			}

		}
		catch (sql::SQLException& e)
		{
			std::cout << "MysqlPool init failed: " << e.what() << std::endl;
		}
	}

	std::unique_ptr<sql::Connection> getConnection() {
		std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock, [this] {
			if (_b_stop) {
				return true;
			}
			return !_pool.empty();
			});
		if (_b_stop) {
			return nullptr;
		}
		auto conn = std::move(_pool.front());
		_pool.pop();
		return conn;
	}

	void ReturnConnection(std::unique_ptr<sql::Connection> conn) {
		std::unique_lock<std::mutex> lock(_mutex);
		if(_b_stop) {
			return;
		}
		_pool.push(std::move(conn));
		_cond.notify_one();
	}

	void Close(){
		_b_stop = true;
		_cond.notify_all();
	}

	~MysqlPool() {
		std::unique_lock<std::mutex> lock(_mutex);
		while(!_pool.empty()){
			_pool.pop();
		}
	}

private:
	std::string _url;
	std::string _user;
	std::string _pass;
	std::string _schema;
	int _poolsize;
	std::queue<std::unique_ptr<sql::Connection>> _pool;
	std::mutex _mutex;
	std::condition_variable _cond;
	std::atomic<bool> _b_stop;
};


struct UserInfo {
	std::string name;
	std::string pwd;
	int uid;
	std::string email;
};





class MysqlDao
{
public:
	MysqlDao();
	~MysqlDao();
	int RegUser(const std::string& name, const std::string& email, const std::string& pass);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool UpdatePass(const std::string& name, const std::string& pass);
	bool CheckPass(const std::string& email, const std::string& pass , UserInfo& userinfo);
private:
	std::unique_ptr<MysqlPool> _pool;
};

