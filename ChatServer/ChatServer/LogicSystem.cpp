#include "LogicSystem.h"
#include "StatusGrpcClient.h"
#include "UserMgr.h"
#include "RedisMgr.h"
#include "MysqlMgr.h"
#include "ChatGrpcClient.h"

LogicSystem::~LogicSystem()
{
	_b_stop = true;
	_consume.notify_one();
	_worker_thread.join();
}

LogicSystem::LogicSystem():_b_stop(false) {
	RegisterCallbacks();
	_worker_thread = std::thread(&LogicSystem::DealMsg, this);
}


void LogicSystem::PostMsgToQue(std::shared_ptr<LogicNode> msg)
{
	std::unique_lock<std::mutex> lock(_mutex);
	_msg_que.push(msg);
	if (_msg_que.size() == 1) {			// If this is the first message in the queue, notify the worker thread
		lock.unlock();
		_consume.notify_one();
	}
}

void LogicSystem::DealMsg()
{
	for (;;) {
		std::unique_lock<std::mutex> lock(_mutex);
		while( !_b_stop && _msg_que.empty()) {	// Wait until there is a message to process or stop signal
			_consume.wait(lock);
		}
		if (_b_stop) {
			while (!_msg_que.empty()) {			//停止并且消息队列不为空，则清空消息队列
				auto msg_node = _msg_que.front();
				std::cout << "收到的消息id为：" << msg_node->_recvnode->_msg_id << std::endl;
				auto callback_it = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
				if (callback_it == _fun_callbacks.end()) {			//未找到对应的回调函数
					_msg_que.pop();
					continue;
				}
				callback_it->second(msg_node->_session, msg_node->_recvnode->_msg_id, std::string(msg_node->_recvnode->_data , msg_node->_recvnode->_cur_len));		//执行对应的回调函数
				_msg_que.pop();
			}
			break;
		}
		auto msg_node = _msg_que.front();
		std::cout << "recv_msg id  is " << msg_node->_recvnode->_msg_id << std::endl;
		auto call_back_iter = _fun_callbacks.find(msg_node->_recvnode->_msg_id);
		if (call_back_iter == _fun_callbacks.end()) {
			_msg_que.pop();
			std::cout << "msg id [" << msg_node->_recvnode->_msg_id << "] handler not found" << std::endl;
			continue;
		}
		call_back_iter->second(msg_node->_session, msg_node->_recvnode->_msg_id,
			std::string(msg_node->_recvnode->_data, msg_node->_recvnode->_cur_len));
		_msg_que.pop();
	}
}

void LogicSystem::RegisterCallbacks()
{
	_fun_callbacks[MSG_CHAT_LOGIN] = std::bind(&LogicSystem::LoginHandler, this, std::placeholders::_1, std::placeholders::_2,
		std::placeholders::_3);
	_fun_callbacks[ID_SEARCH_USER_REQ] = std::bind(&LogicSystem::SearchInfo, this, std::placeholders::_1, std::placeholders::_2 
	, std::placeholders::_3);
	_fun_callbacks[ID_ADD_FRIEND_REQ] = std::bind(&LogicSystem::AddFriendApply, this, std::placeholders::_1, std::placeholders::_2,
		std::placeholders::_3);
}

bool LogicSystem::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo) {
	//优先查redis中查询用户信息
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		userinfo->uid = root["uid"].asInt();
		userinfo->name = root["name"].asString();
		userinfo->pwd = root["pwd"].asString();
		userinfo->email = root["email"].asString();
		userinfo->nick = root["nick"].asString();
		userinfo->desc = root["desc"].asString();
		userinfo->sex = root["sex"].asInt();
		userinfo->icon = root["icon"].asString();
		std::cout << "user login uid is  " << userinfo->uid << " name  is "
			<< userinfo->name << " pwd is " << userinfo->pwd << " email is " << userinfo->email << std::endl;
	}
	else {
		//redis中没有则查询mysql
		//查询数据库
		std::shared_ptr<UserInfo> user_info = nullptr;
		user_info = MysqlMgr::GetInstance()->GetUser(uid);
		if (user_info == nullptr) {
			return false;
		}

		userinfo = user_info;

		//将数据库内容写入redis缓存
		Json::Value redis_root;
		redis_root["uid"] = uid;
		redis_root["pwd"] = userinfo->pwd;
		redis_root["name"] = userinfo->name;
		redis_root["email"] = userinfo->email;
		redis_root["nick"] = userinfo->nick;
		redis_root["desc"] = userinfo->desc;
		redis_root["sex"] = userinfo->sex;
		redis_root["icon"] = userinfo->icon;
		RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
	}

	return true;
}

bool LogicSystem::isPureDigit(const std::string& str)
{
	for (char c : str) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}

void LogicSystem::GetUserByUid(std::string uid_str, Json::Value& rtvalue)
{
	rtvalue["error"] = ErrorCodes::Success;
	std::string base_key = USER_BASE_INFO + uid_str;
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);		//先从redis中根据uid查找是否存在该用户
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		auto uid = root["uid"].asInt();
		auto name = root["name"].asString();
		auto pwd = root["pwd"].asString();
		auto email = root["email"].asString();
		auto nick = root["nick"].asString();
		auto desc = root["desc"].asString();
		auto sex = root["sex"].asInt();
		auto icon = root["icon"].asString();
		std::cout << "user  uid is  " << uid << " name  is "
			<< name << " pwd is " << pwd << " email is " << email << " icon is " << icon << std::endl;

		rtvalue["uid"] = root["uid"].asInt();
		rtvalue["name"] = root["name"].asString();
		rtvalue["pwd"] = root["pwd"].asString();
		rtvalue["email"] = root["email"].asString();
		rtvalue["nick"] = root["nick"].asString();
		rtvalue["desc"] = root["desc"].asString();		
		rtvalue["sex"] = root["sex"].asInt();
		rtvalue["icon"] = root["icon"].asString();
		return;
	}
	auto uid = std::stoi(uid_str);			//redis中不存在，从MySQL中查询
	std::shared_ptr<UserInfo> user_info = nullptr;
	user_info = MysqlMgr::GetInstance()->GetUser(uid);
	if (user_info == nullptr) {			//MySQL中也不存在该用户
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}
	Json::Value redis_root;			//mysql中存在，则将该用户信息写入redis缓存
	redis_root["uid"] = user_info->uid;
	redis_root["pwd"] = user_info->pwd;
	redis_root["name"] = user_info->name;
	redis_root["email"] = user_info->email;
	redis_root["nick"] = user_info->nick;
	redis_root["desc"] = user_info->desc;
	redis_root["sex"] = user_info->sex;
	redis_root["icon"] = user_info->icon;

	RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
	rtvalue["uid"] = user_info->uid;
	rtvalue["pwd"] = user_info->pwd;
	rtvalue["name"] = user_info->name;
	rtvalue["email"] = user_info->email;
	rtvalue["nick"] = user_info->nick;
	rtvalue["desc"] = user_info->desc;
	rtvalue["sex"] = user_info->sex;
	rtvalue["icon"] = user_info->icon;
}

void LogicSystem::GetUserByName(std::string name, Json::Value& rtvalue)
{
	rtvalue["error"] = ErrorCodes::Success;
	std::string base_key = NAME_INFO + name;
	std::string info_str = "";
	bool b_base = RedisMgr::GetInstance()->Get(base_key, info_str);		//先从redis中根据uid查找是否存在该用户
	if (b_base) {
		Json::Reader reader;
		Json::Value root;
		reader.parse(info_str, root);
		auto uid = root["uid"].asInt();
		auto name = root["name"].asString();
		auto pwd = root["pwd"].asString();
		auto email = root["email"].asString();
		auto nick = root["nick"].asString();
		auto desc = root["desc"].asString();
		auto sex = root["sex"].asInt();
		auto icon = root["icon"].asString();
		std::cout << "user  uid is  " << uid << " name  is "
			<< name << " pwd is " << pwd << " email is " << email << " icon is " << icon << std::endl;

		rtvalue["uid"] = root["uid"].asInt();
		rtvalue["name"] = root["name"].asString();
		rtvalue["pwd"] = root["pwd"].asString();
		rtvalue["email"] = root["email"].asString();
		rtvalue["nick"] = root["nick"].asString();
		rtvalue["desc"] = root["desc"].asString();
		rtvalue["sex"] = root["sex"].asInt();
		rtvalue["icon"] = root["icon"].asString();
		return;
	}		
	std::shared_ptr<UserInfo> user_info = nullptr;		//redis中不存在，从MySQL中查询
	user_info = MysqlMgr::GetInstance()->GetUser(name);
	if (user_info == nullptr) {			//MySQL中也不存在该用户
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}
	Json::Value redis_root;			//mysql中存在，则将该用户信息写入redis缓存
	redis_root["uid"] = user_info->uid;
	redis_root["pwd"] = user_info->pwd;
	redis_root["name"] = user_info->name;
	redis_root["email"] = user_info->email;
	redis_root["nick"] = user_info->nick;
	redis_root["desc"] = user_info->desc;
	redis_root["sex"] = user_info->sex;
	redis_root["icon"] = user_info->icon;

	RedisMgr::GetInstance()->Set(base_key, redis_root.toStyledString());
	rtvalue["uid"] = user_info->uid;
	rtvalue["pwd"] = user_info->pwd;
	rtvalue["name"] = user_info->name;
	rtvalue["email"] = user_info->email;
	rtvalue["nick"] = user_info->nick;
	rtvalue["desc"] = user_info->desc;
	rtvalue["sex"] = user_info->sex;
	rtvalue["icon"] = user_info->icon; 
	
}

bool LogicSystem::GetFriendApplyInfo(int to_uid, std::vector<std::shared_ptr<ApplyInfo>>& list)
{
	return MysqlMgr::GetInstance()->GetFriendApplyInfo(to_uid, list, 0, 10);
}

void LogicSystem::LoginHandler(std::shared_ptr<CSession> session, const short& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	std::cout << "user login id is :" << root["uid"].asInt() << "user token is :" << root["token"].asString() << std::endl;
	auto uid = root["uid"].asInt();
	auto token = root["token"].asString();
	//auto rsp = StatusGrpcClient::GetInstance()->Login(uid, root["token"].asString());		//向状态服务器验证用户所提交的id和token是否正确
	Json::Value rvalue;
	Defer defer([this, &rvalue, session]() {
		std::string return_str = rvalue.toStyledString();
		session->Send(return_str, MSG_CHAT_LOGIN_RSP);
		});
	
	std::string uid_str = std::to_string(uid);
	std::string token_key = USERTOKENPREFIX + uid_str;
	std::string token_value = "";
	bool success = RedisMgr::GetInstance()->Get(token_key, token_value);		//检查redis中是否有用户的token
	if (!success) {
		rvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}

	if (token_value != token) {
		rvalue["error"] = ErrorCodes::TokenInvalid;
		return;
	}

	rvalue["error"] = ErrorCodes::Success;

	std::string base_key = USER_BASE_INFO + uid_str;
	auto user_info = std::make_shared<UserInfo>();
	bool b_base = GetBaseInfo(base_key, uid, user_info);
	if (!b_base) {
		rvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}
	rvalue["uid"] = uid;
	rvalue["pwd"] = user_info->pwd;
	rvalue["name"] = user_info->name;
	rvalue["email"] = user_info->email;
	rvalue["nick"] = user_info->nick;
	rvalue["desc"] = user_info->desc;
	rvalue["sex"] = user_info->sex;
	rvalue["icon"] = user_info->icon;

	//从数据库中获取待处理的好友申请
	std::vector<std::shared_ptr<ApplyInfo>> apply_list;
	auto b_apply = GetFriendApplyInfo(uid, apply_list);		//获取待处理的好友申请
	if (b_apply) {
		for (auto& apply : apply_list) {
			Json::Value value;
			value["name"] = apply->_name;
			value["uid"] = apply->_uid;
			value["icon"] = apply->_icon;
			value["nick"] = apply->_nick;
			value["sex"] = apply->_sex;
			value["desc"] = apply->_desc;
			value["status"] = apply->_status;
			rvalue["apply_list"].append(value);		//将待处理的好友申请添加到返回值中
		}
	}

	auto server_name = ConfigMgr::Instance().GetValue("SelfServer", "Name");		
	auto rd_res = RedisMgr::GetInstance()->HGet(LOGIN_COUNT, server_name);
	int count = 0;
	if (!rd_res.empty()) {
		count = std::stoi(rd_res);
	}
	count++;

	auto count_str = std::to_string(count);
	RedisMgr::GetInstance()->HSet(LOGIN_COUNT, server_name, count_str);			//增加登录数量
	session->SetUserid(uid);
	std::string ipkey = USERIPPREFIX + uid_str;
	RedisMgr::GetInstance()->Set(ipkey, server_name);
	UserMgr::GetInstance()->SetUserSession(uid, session);
	return;
}

void LogicSystem::SearchInfo(std::shared_ptr<CSession> session, const short& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid_str = root["uid"].asString();
	std::cout << "需查找的用户id为：" << uid_str << std::endl;

	Json::Value rtvalue;

	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_SEARCH_USER_RSP);
		});
	bool b_digtal = isPureDigit(uid_str);
	if (b_digtal) {
		GetUserByUid(uid_str, rtvalue);
	}
	else {
		GetUserByName(uid_str, rtvalue);
	}
}

void LogicSystem::AddFriendApply(std::shared_ptr<CSession> session, const short& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	auto uid = root["uid"].asInt();			//主动申请添加好友的用户id
	auto applyname = root["applyname"].asString();
	auto backname = root["backname"].asString();		//给申请好友用户的备注名
	auto touid = root["touid"].asInt();		//被申请添加好友的用户id
	std::cout << "user login uid is  " << uid << " applyname  is "
		<< applyname << " bakname is " << backname << " touid is " << touid << std::endl;

	Json::Value rtvalue;
	rtvalue["error"] = ErrorCodes::Success;
	Defer defer([this, &rtvalue, session]() {
		std::string return_str = rtvalue.toStyledString();
		session->Send(return_str, ID_ADD_FRIEND_RSP);
		});

	bool suc = MysqlMgr::GetInstance()->AddFriendApply(uid, touid);
	if (!suc) {
		return;
	}
	auto to_str = std::to_string(touid);
	auto to_ip_key = USERIPPREFIX + to_str;
	std::string to_ip_value = "";
	RedisMgr::GetInstance()->Get(to_ip_key, to_ip_value);		//获取被申请添加好友的用户所在的服务器ip
	auto& cfg = ConfigMgr::Instance();
	auto self_name = cfg["SelfServer"]["Mame"];
	if (to_ip_value == self_name) {		//需要添加的好友与自己在同一服务器，直接发送
		auto session = UserMgr::GetInstance()->GetSession(touid);		//获取被申请添加好友的用户的session
		if (session) {
			Json::Value notify;
			notify["error"] = ErrorCodes::Success;
			notify["applyuid"] = uid;
			notify["name"] = applyname;		//申请添加好友的用户的名称
			notify["desc"] = "";
			std::string return_str = notify.toStyledString(); 
			session->Send(return_str, ID_NOTIFY_ADD_FRIEND_REQ);
		}
		return;
	}
	std::string base_key = USER_BASE_INFO + std::to_string(uid);		//获取主动申请添加好友的用户的基本信息
	auto apply_info = std::make_shared<UserInfo>();
	bool b_base = GetBaseInfo(base_key, uid, apply_info);

	AddFriendReq add_req;		//构造添加好友请求消息
	add_req.set_applyuid(uid);
	add_req.set_touid(touid);
	add_req.set_name(applyname);
	add_req.set_desc("");
	if (!b_base) {
		rtvalue["error"] = ErrorCodes::UidInvalid;
		return;
	}
	if (b_base) {
		add_req.set_icon(apply_info->icon);
		add_req.set_nick(apply_info->nick);
		add_req.set_sex(apply_info->sex);
	}
	ChatGrpcClient::GetInstance()->NotifyAddFriend(to_ip_value, add_req);		//向被申请添加好友的用户所在的服务器发送添加好友请求消息

}
