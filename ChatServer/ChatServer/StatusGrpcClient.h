#pragma once
#include "const.h"
#include "ConfigMgr.h"
#include "Singleton.h"
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "message.pb.h"


using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetChatServerReq;
using message::GetChatServerRsp;
using message::LoginRsp;
using message::LoginReq;
using message::StatusService;

class StatusConPool
{
public:
	StatusConPool(std::size_t poolsize, std::string host, std::string port);
	~StatusConPool();
	std::unique_ptr<StatusService::Stub> GetConnection();
	void ReturnConnection(std::unique_ptr<StatusService::Stub> ioc);
	void Close();
private:
	std::atomic<bool> b_stop_;
	std::size_t poolsize_;
	std::string host_;
	std::string port_;
	std::queue<std::unique_ptr<StatusService::Stub>> connections_;
	std::mutex mutex_;
	std::condition_variable cond_;
};


class StatusGrpcClient : public Singleton<StatusGrpcClient>
{
	friend class Singleton<StatusGrpcClient>;
public:
	~StatusGrpcClient() {

	}
	GetChatServerRsp GetChatServer(int uid);
	LoginRsp Login(int uid, std::string token);
private:
	StatusGrpcClient();
	std::unique_ptr<StatusConPool> _pool;
};