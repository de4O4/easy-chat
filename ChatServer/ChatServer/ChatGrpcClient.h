#pragma once
#include "const.h"
#include "message.grpc.pb.h"
#include "message.pb.h"
#include <grpcpp/grpcpp.h>
#include "Singleton.h"
#include "ConfigMgr.h"
#include "data.h"
#include <condition_variable>
#include <unordered_map>

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::AddFriendReq;
using message::AddFriendRsp;

using message::AuthFriendReq;
using message::AuthFriendRsp;

using message::GetChatServerRsp;
using message::LoginRsp;
using message::LoginReq;
using message::ChatService;

using message::TextChatMsgReq;
using message::TextChatMsgRsp;
using message::TextChatData;

class ChatConnPool {
public:
	ChatConnPool(std::size_t poolsize, std::string host, std::string port) :_poolsize(poolsize), _host(host), _port(port), _b_stop(false) {
		for (std::size_t i = 0; i < _poolsize; ++i) {
			std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + _port, grpc::InsecureChannelCredentials());			//创建通信通道
			_connections.push(ChatService::NewStub(channel));		//根据每个通道建立客户端与服务器通信的存根stub
		}
	}

	~ChatConnPool() {
		std::lock_guard<std::mutex> lock(_mutex);
		Close();
		while (!_connections.empty()) {
			_connections.pop();
		}
	}

	std::unique_ptr < ChatService::Stub> GetConnection() {
		std::unique_lock<std::mutex> lock(_mutex);
		_cond.wait(lock, [this] {
			if(_b_stop) {
				return true;
			}
			return !_connections.empty();
			});
		if (_b_stop) {
			return nullptr;
		}
		auto context = std::move(_connections.front());
		_connections.pop();
		return context;
	}

	void ReturnConnection(std::unique_ptr < ChatService::Stub > context) {
		std::lock_guard<std::mutex> lock(_mutex);
		if (_b_stop) {
			return;
		}
		_connections.push(std::move(context));
		_cond.notify_one();
	}

	void Close() {
		_b_stop = true;
		_cond.notify_all();
	}

private:
	std::atomic<bool> _b_stop;
	std::size_t _poolsize;
	std::string _host;
	std::string _port;
	std::mutex _mutex;
	std::condition_variable _cond;
	std::queue<std::unique_ptr<ChatService::Stub>> _connections;
};

class ChatGrpcClient:public Singleton<ChatGrpcClient>
{
	friend class Singleton<ChatGrpcClient>;
public:
	~ChatGrpcClient() {

	}
	AddFriendRsp NotifyAddFriend(std::string server_ip, const AddFriendReq& req);
	AuthFriendRsp NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req);
	bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo);
	TextChatMsgRsp NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtvalue);
private:
	ChatGrpcClient();
	std::unordered_map<std::string, std::unique_ptr<ChatConnPool>> _pools;
};

