#include "StatusGrpcClient.h"

StatusConPool::StatusConPool(std::size_t poolsize, std::string host, std::string port):poolsize_(poolsize) ,
host_(host),port_(port),b_stop_(false){
	for (std::size_t i = 0; i < poolsize; i++) {
		std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
		connections_.push(StatusService::NewStub(channel));
	}

}

StatusConPool::~StatusConPool()
{
	std::lock_guard<std::mutex> lock(mutex_);
	Close();
	while (!connections_.empty()) {
		connections_.pop();
	}
}

std::unique_ptr<StatusService::Stub> StatusConPool::GetConnection() {
	std::unique_lock<std::mutex> lock(mutex_);
	cond_.wait(lock, [this] {
		if (b_stop_) {
			return true;
		}
		return !connections_.empty();
		});
	if (b_stop_) {
		return nullptr;
	}
	auto ioc = std::move(connections_.front());
	connections_.pop();
	return ioc;
}

void StatusConPool::ReturnConnection(std::unique_ptr<StatusService::Stub> ioc) {
	std::lock_guard<std::mutex> lock(mutex_);
	if (b_stop_) {
		return;
	}
	connections_.push(std::move(ioc));
	cond_.notify_one();
}

void StatusConPool::Close() {
	b_stop_ = true;
	cond_.notify_all();
}



GetChatServerRsp StatusGrpcClient::GetChatServer(int uid)
{
	ClientContext context;
	GetChatServerReq req;
	GetChatServerRsp rsp;
	req.set_uid(uid);
	auto stub = _pool->GetConnection();
	Status status = stub->GetChatServer(&context, req, &rsp);
	if (status.ok()) {
		_pool->ReturnConnection(std::move(stub));
		return rsp;
	}
	else {
		_pool->ReturnConnection(std::move(stub));
		return rsp;
	}
}

StatusGrpcClient::StatusGrpcClient() {
	auto& gCfgMgr = ConfigMgr::Instance();
	std::string host = gCfgMgr["StatusServer"]["Host"];
	std::string port = gCfgMgr["StatusServer"]["Port"];
	_pool.reset(new StatusConPool(5, host, port));
}

