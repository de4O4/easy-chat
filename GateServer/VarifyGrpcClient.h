#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
#include "ConfigMgr.h"
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::VarifyService;
using message::GetVarifyReq;
using message::GetVarifyRsp;

class VarifyGrpcClient;

class RPConnPool {
public:
	RPConnPool(std::size_t poolsize, std::string host, std::string port);
	~RPConnPool();
	std::unique_ptr<VarifyService::Stub> GetConnection();
	void returnConnection(std::unique_ptr<VarifyService::Stub> ioc);
	void Close();
private:
	std::atomic<bool> b_stop_;
	std::size_t poolsize_;
	std::string host_;
	std::string port_;
	std::queue<std::unique_ptr<VarifyService::Stub>> connections_;
	std::mutex mutex_;
	std::condition_variable cond_;

};


class VarifyGrpcClient:public Singleton<VarifyGrpcClient>
{
	friend class Singleton<VarifyGrpcClient>;
public:
	GetVarifyRsp GetVarifyCode(std::string email) {
		ClientContext context;
		GetVarifyRsp reply;
		GetVarifyReq requset;
		requset.set_email(email);
		auto stub = pool_->GetConnection();
		Status status = stub->GetVarifyCode(&context, requset, &reply);
		if (status.ok()) {
			pool_->returnConnection(std::move(stub));
			return reply;
		}
		else {
			pool_->returnConnection(std::move(stub));
			reply.set_error(ErrorCodes::RPCFailed);
			return reply;
		}
	}
private:
	VarifyGrpcClient();
	std::unique_ptr<RPConnPool> pool_;
};

