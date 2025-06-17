#include "CServer.h"
#include "AsioIOServicePool.h"


CServer::CServer(boost::asio::io_context& ioc, short port):_ioc(ioc) ,_acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _port(port)
{
	std::cout << "Server start success, listen on port : " << _port << std::endl;
	StartAccept();
}

CServer::~CServer()
{
	std::cout << "Server destruct listen on port : " << _port << std::endl;
}

void CServer::ClearSession(std::string id)
{
	std::lock_guard<std::mutex> lock(_mutex);
	if(_sessions.find(id) != _sessions.end())
	{
		auto uid = _sessions[id]->GetUserid();			//将session关联的用户ID取出
	}
	_sessions.erase(id);
}

std::shared_ptr<CSession> CServer::GetSession(std::string id)
{
	auto it = _sessions.find(id);
	if (it != _sessions.end()) {
		return it->second;
	}
	return nullptr;
}

bool CServer::CheckValid(std::string uuid)
{
	std::lock_guard<std::mutex> lock(_mutex);
	auto it = _sessions.find(uuid);
	if (it != _sessions.end()) {
		return true;
	}
	return false;
}

void CServer::HandlerAccept(std::shared_ptr<CSession> session, const boost::system::error_code& ec)
{
	if (ec) {
		std::cout << "accept failed code is :" << ec.message() << std::endl;
	
	}
	else {
		session->Start();	//开始会话处理		
		std::lock_guard<std::mutex> lock(_mutex);
		_sessions.insert(std::make_pair(session->GetSessionid(), session));	//将会话对象存入会话列表中
	}
	StartAccept();	//继续接受新的连接请求
}

void CServer::StartAccept()
{
	auto& ioc = AsioIOServicePool::GetInstance()->GetIOService();		//从IOService池中获取一个IOService对象
	std::shared_ptr<CSession> session = std::make_shared<CSession>(ioc, this);	//创建一个新的会话对象
	_acceptor.async_accept(session->GetSocket(), std::bind(&CServer::HandlerAccept , this , session , std::placeholders::_1));
}



