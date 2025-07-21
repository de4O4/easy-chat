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

bool MysqlMgr::AddFriendApply(const int& from, const int& to)
{
	return _dao.AddFriendApply(from, to);
}

std::shared_ptr<UserInfo> MysqlMgr::GetUser(int uid) {
	return _dao.GetUser(uid);
}

std::shared_ptr<UserInfo> MysqlMgr::GetUser(const std::string& name)
{
	return _dao.GetUser(name);
}

bool MysqlMgr::GetFriendApplyInfo(int to_uid, std::vector<std::shared_ptr<ApplyInfo>>& list, int offset, int limit) {
	return _dao.GetFriendApplyInfo(to_uid, list, offset, limit);
}

bool MysqlMgr::AuthFriendApply(const int& from, const int& to) {
	return _dao.AuthFriendApply(from, to);
}

bool MysqlMgr::AddFriend(const int& from, const int& to, std::string back_name) {
	return _dao.AddFriend(from, to, back_name);
}