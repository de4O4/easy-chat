#include "VarifyGrpcClient.h"

RPConnPool::RPConnPool(std::size_t poolsize, std::string host, std::string port):poolsize_(poolsize),host_(host),port_(port),
b_stop_(false)
{
	for (std::size_t i = 0; i < poolsize; i++) {
		std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, grpc::InsecureChannelCredentials());
		connections_.push(VarifyService::NewStub(channel));
	}
}

RPConnPool::~RPConnPool()
{
	std::lock_guard<std::mutex> lock(mutex_);
	Close();
	while (!connections_.empty()) {
		connections_.pop();
	}
}

std::unique_ptr<VarifyService::Stub> RPConnPool::GetConnection()
{
	std::unique_lock<std::mutex> lock(mutex_);
	cond_.wait(lock, [this]() {
		if (b_stop_) {
			return true;
		}
		return !connections_.empty();
		});
	if (b_stop_) {
		return nullptr;
	}
	auto context = std::move(connections_.front());
	connections_.pop();
	return context;
}

void RPConnPool::returnConnection(std::unique_ptr<VarifyService::Stub> ioc)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (b_stop_) {
		return;
	}
	connections_.push(std::move(ioc));
	cond_.notify_one();
}

void RPConnPool::Close() {
	b_stop_ = true;
	cond_.notify_all();
}

VarifyGrpcClient::VarifyGrpcClient()
{
	auto& cfg = ConfigMgr::Instance();
	std::string host = cfg["VarifyServer"]["Host"];
	std::string port = cfg["VarifyServer"]["Port"];
	pool_.reset(new RPConnPool(5, host, port));
}
