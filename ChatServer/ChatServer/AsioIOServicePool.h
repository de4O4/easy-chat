#pragma once
#include <boost/asio.hpp>
#include <vector>
#include "Singleton.h"
#include <memory>
#include <thread>

class AsioIOServicePool :public Singleton<AsioIOServicePool>
{
	friend class Singleton<AsioIOServicePool>;
public:
	using IOService = boost::asio::io_context;
	using Work = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;
	using WorkPtr = std::unique_ptr<Work>;
	AsioIOServicePool& operator=(const AsioIOServicePool&) = delete;
	AsioIOServicePool(const AsioIOServicePool&) = delete;
	void stop();
	boost::asio::io_context& GetIOService();
	~AsioIOServicePool();
private:
	AsioIOServicePool(std::size_t = std::thread::hardware_concurrency());
	std::vector<IOService> _ioServices;;
	std::vector<WorkPtr> _works;
	std::vector<std::thread> _threads;
	std::size_t _nextIOServiceIndex;
};

