#include "MysqlMgr.h"

MysqlMgr::MysqlMgr() {

}

MysqlMgr::~MysqlMgr() {

}

int MysqlMgr::RegUser(const std::string& name, const std::string& email, const std::string& pass) {
	return _dao.RegUser(name, email, pass);
}

bool MysqlMgr::CheckEmail(const std::string& name, const std::string& email)
{
	return _dao.CheckEmail(name, email);
}

bool MysqlMgr::UpdatePass(const std::string& name, const std::string& pass) {
	return _dao.UpdatePass(name, pass);
}

bool MysqlMgr::CheckPass(const std::string& email, const std::string& pass, UserInfo& userinfo) {
	return _dao.CheckPass(email, pass, userinfo);
}

std::shared_ptr<UserInfo> MysqlMgr::GetUser(int uid) {
	return _dao.GetUser(uid);
}