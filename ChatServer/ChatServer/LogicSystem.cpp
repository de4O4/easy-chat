#include "LogicSystem.h"
#include "StatusGrpcClient.h"
#include "UserMgr.h"

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

void LogicSystem::LoginHandler(std::shared_ptr<CSession> session, const short& msg_id, const std::string& msg_data)
{
	Json::Reader reader;
	Json::Value root;
	reader.parse(msg_data, root);
	std::cout << "user login id is :" << root["uid"].asInt() << "user token is :" << root["token"].asString() << std::endl;
	auto uid = root["uid"].asInt();
	auto rsp = StatusGrpcClient::GetInstance()->Login(uid, root["token"].asString());		//向状态服务器验证用户所提交的id和token是否正确
	Json::Value rvalue;
	Defer defer([this, &rvalue, session]() {
		std::string return_str = rvalue.toStyledString();
		session->Send(return_str, MSG_CHAT_LOGIN_RSP);
		});
	rvalue["error"] = rsp.error();
	if (rsp.error() != ErrorCodes::Success) {
		return;
	}
	rvalue["uid"] = uid;
	rvalue["token"] = rsp.token();
	//rvalue["name"] = user_info->name;
}
