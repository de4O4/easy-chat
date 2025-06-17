#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOServerPool.h"

CServer::CServer(net::io_context& ioc, unsigned short& port):_ioc(ioc) ,
_acceptor(ioc , {tcp::v4() , port}),_socket(ioc)
{

}

void CServer::Start()
{
	auto self = shared_from_this();
	auto& ioc = AsioIOServerPool::GetInstance()->GetIOServer();
	std::shared_ptr<HttpConnection> conn = std::make_shared<HttpConnection>(ioc);
	_acceptor.async_accept(conn->GetSocket(), [self , conn](beast::error_code ec) {
		try
		{
			if (ec) {
				self->Start();
				return;
			}
			conn->Start();		//接受连接后，开始监听读写事件
			self->Start();
		}
		catch (const std::exception& e)
		{
			std::cout << "exception is :" << e.what() << std::endl;
			self->Start();
		}
		});
}
