#include "MysqlDao.h"
#include "ConfigMgr.h"
#include <iostream>
MysqlDao::MysqlDao()
{
	auto& cfg = ConfigMgr::Instance();
	const auto& host = cfg["Mysql"]["Host"];
	const auto& port = cfg["Mysql"]["Port"];
	const auto& pwd = cfg["Mysql"]["Passwd"];
	const auto& user = cfg["Mysql"]["User"];
	const auto& db = cfg["Mysql"]["Schema"];
	_pool.reset(new MysqlPool(host + ":" + port, user, pwd, db , 5));
}

MysqlDao::~MysqlDao()
{
	_pool->Close();
}

int MysqlDao::RegUser(const std::string& name, const std::string& email, const std::string& pass)
{
	auto conn = _pool->getConnection();
	try
	{
		if (conn == nullptr) {
			//_pool->ReturnConnection(std::move(conn));
			return false;
		}
		std::unique_ptr<sql::PreparedStatement> stmt(conn->prepareStatement("CALL reg_user(?, ?, ?,@result)"));		// 调用存储过程
		stmt->setString(1, name);			//设置输入参数
		stmt->setString(2, email);
		stmt->setString(3, pass);
		stmt->execute();					// 执行存储过程
		std::unique_ptr<sql::Statement> stmtResult(conn->createStatement());
		std::unique_ptr<sql::ResultSet> res(stmtResult->executeQuery("SELECT @result As result"));	// 获取输出参数
		if (res->next()) {
			int result = res->getInt("result");
			std::cout << "RegUser result: " << result << std::endl;
			_pool->ReturnConnection(std::move(conn));
			return result;
		}
		_pool->ReturnConnection(std::move(conn));
		return -1;
	}
	catch (sql::SQLException& e)
	{
		_pool->ReturnConnection(std::move(conn));
		std::cerr << "SQLException: " << e.what() << std::endl;
		std::cerr << "Error code: " << e.getErrorCode() << std::endl;
		std::cerr << "SQLState: " << e.getSQLState() << std::endl;
		return -1;
	}
}

bool MysqlDao::CheckEmail(const std::string& name, const std::string& email)
{
	auto conn = _pool->getConnection();
	try
	{
		if (conn == nullptr) {
			return false;
		}
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT email FROM user WHERE name = ?	"));
		pstmt->setString(1, name);			//填充？号位置为name
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());	//执行查询
		while (res->next()) {
			std::string emil = res->getString("email");
			if (email == email) {
				_pool->ReturnConnection(std::move(conn));
				return true;
			}
			_pool->ReturnConnection(std::move(conn));
			return false;
		}
	}
	catch (sql::SQLException& e)
	{
		_pool->ReturnConnection(std::move(conn));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
	

	return false;
}

bool MysqlDao::UpdatePass(const std::string& name, const std::string& pass)
{
	auto conn = _pool->getConnection();
	try
	{
		if (conn == nullptr) {
			return false;
		}
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("UPDATE user SET pwd = ? WHERE name = ?"));
		pstmt->setString(1, pass);			//填充？号位置为pass
		pstmt->setString(2, name);			//填充？号位置为name
		int rowsAffected = pstmt->executeUpdate();	//执行更新操作
		_pool->ReturnConnection(std::move(conn));
		return rowsAffected > 0;			//如果更新了行数大于0，则返回true
	}
	catch (sql::SQLException& e)
	{
		_pool->ReturnConnection(std::move(conn));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
	return false;
}

bool MysqlDao::CheckPass(const std::string& email, const std::string& pass, UserInfo& userinfo)
{
	auto conn = _pool->getConnection();
	try
	{
		if (conn == nullptr) {
			return false;
		}
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM user WHERE email = ?"));
		pstmt->setString(1, email);			//填充？号位置为name
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());	//执行查询
		std::string origin_pwd = "";
		std::string name = "";
		if (res->next()) {
			origin_pwd = res->getString("pwd");
			name = res->getString("name");
			std::cout << "password is " << origin_pwd <<std::endl;
		}
		else {
			std::cout << "查询不到这个用户：" << email << std::endl;
			return false;
		}
		if (origin_pwd != pass) {
			std::cout << "密码错误" << std::endl;
			return false;
		}
		userinfo.name = name;
		userinfo.email = res->getString("email");
		userinfo.uid = res->getInt("uid");
		userinfo.pwd = origin_pwd;
		return true;

	}
	catch (sql::SQLException& e)
	{
		_pool->ReturnConnection(std::move(conn));
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
	return false;
}


