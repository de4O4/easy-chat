#pragma once
#include "const.h"
#include "Singleton.h"

class AsioIOServerPool:public Singleton<AsioIOServerPool>
{
	friend class Singleton<AsioIOServerPool>;
public:
	using IOService = boost::asio::io_context;
	using Work = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;
	using WorkPtr = std::unique_ptr<Work>;
	~AsioIOServerPool();
	AsioIOServerPool(const AsioIOServerPool&) = delete;
	AsioIOServerPool& operator=(const AsioIOServerPool) = delete;
	boost::asio::io_context& GetIOServer();
	void Stop();
private:
	AsioIOServerPool(std::size_t size= 2);
	std::vector<IOService> _ioServices;
	std::vector<WorkPtr> _works;
	std::vector<std::thread> _threads;
	std::size_t _nextIOService;

};

