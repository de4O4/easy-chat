#pragma once
#include "MysqlDao.h"
#include "Singleton.h"

class MysqlMgr : public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
public:
	~MysqlMgr();
	int RegUser(const std::string& name, const std::string& email, const std::string& pass);
	bool CheckEmail(const std::string& name, const std::string& email);
	bool UpdatePass(const std::string& name, const std::string& pass);
	bool CheckPass(const std::string& email, const std::string& pass, UserInfo& userinfo);
	bool AddFriendApply(const int& from, const int& to);
	bool GetFriendApplyInfo(int to_uid, std::vector<std::shared_ptr<ApplyInfo>>& list, int offset, int limit);
	bool AuthFriendApply(const int& from, const int& to);
	bool AddFriend(const int& from, const int& to, std::string back_name);
	bool GetFriendList(int self_id, std::vector<std::shared_ptr<UserInfo> >& user_info_list);
	std::shared_ptr<UserInfo> GetUser(int uid);
	std::shared_ptr<UserInfo> GetUser(const std::string& name);
private:
	MysqlMgr();
	MysqlDao _dao;

};

