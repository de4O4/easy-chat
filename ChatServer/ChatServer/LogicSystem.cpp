#include "LogicSystem.h"
#include "StatusGrpcClient.h"
#include "UserMgr.h"
#include "RedisMgr.h"
#include "MysqlMgr.h"

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
