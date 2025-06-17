#include "AsioIOServicePool.h"

boost::asio::io_context& AsioIOServicePool::GetIOService()
{
	auto &server = _ioServices[_nextIOServiceIndex];
	_nextIOServiceIndex++;
	if( _nextIOServiceIndex >= _ioServices.size() ) {
		_nextIOServiceIndex = 0; //循环使用io_service
	}
	return  server;
}

AsioIOServicePool::~AsioIOServicePool()
{
	std::cout << "AsioIOServicePool destructor called" << std::endl;
}

AsioIOServicePool::AsioIOServicePool(std::size_t size):_nextIOServiceIndex(0) ,
_ioServices(size),_works(size)
{
	for(std::size_t i = 0 ; i< size; i++) {
		_works[i] = std::unique_ptr<Work>(new Work(_ioServices[i].get_executor()));  //创建size个work对象，防止io_service在没有任务时退出
	}


	for (std::size_t i = 0; i < size; i++) {
		_threads.emplace_back([this, i] {			//创建size个线程，并执行回调函数
			_ioServices[i].run();
			});
	}
}

void AsioIOServicePool::stop() {
	for (auto& i : _works) {
		i.reset();
	}

	for(auto& thread : _threads) {
		if(thread.joinable()) {
			thread.join();  //等待所有线程结束
		}
	}

}