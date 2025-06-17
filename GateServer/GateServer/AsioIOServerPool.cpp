#include "AsioIOServerPool.h"

AsioIOServerPool::~AsioIOServerPool()
{
	std::cout << "AsIOServerPool Destruct!" << std::endl;
}

boost::asio::io_context& AsioIOServerPool::GetIOServer()
{
	auto& server = _ioServices[_nextIOService];
	if (_nextIOService == _ioServices.size()) {
		_nextIOService = 0;
	}
	return server;
}

void AsioIOServerPool::Stop()
{
	for (auto& i : _works) {
		i.reset();
	}
	for (auto& t : _threads) {
		t.join();
	}
}

AsioIOServerPool::AsioIOServerPool(std::size_t size):_ioServices(size),_works(size),_nextIOService(0)
{
	for (std::size_t i = 0; i < size; i++) {
		_works[i] = std::unique_ptr<Work>(new Work(_ioServices[i].get_executor()));
	}
	for (std::size_t i = 0; i < size; i++) {
		_threads.emplace_back([this, i]() {
			_ioServices[i].run();
			});
	}
}
