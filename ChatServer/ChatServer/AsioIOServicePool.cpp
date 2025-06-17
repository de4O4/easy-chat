#include "AsioIOServicePool.h"

boost::asio::io_context& AsioIOServicePool::GetIOService()
{
	auto &server = _ioServices[_nextIOServiceIndex];
	_nextIOServiceIndex++;
	if( _nextIOServiceIndex >= _ioServices.size() ) {
		_nextIOServiceIndex = 0; //ѭ��ʹ��io_service
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
		_works[i] = std::unique_ptr<Work>(new Work(_ioServices[i].get_executor()));  //����size��work���󣬷�ֹio_service��û������ʱ�˳�
	}


	for (std::size_t i = 0; i < size; i++) {
		_threads.emplace_back([this, i] {			//����size���̣߳���ִ�лص�����
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
			thread.join();  //�ȴ������߳̽���
		}
	}

}