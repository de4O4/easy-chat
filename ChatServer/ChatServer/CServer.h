#pragma once
#include "CSession.h"
#include <boost/asio.hpp>
#include <memory>
#include <vector>
#include <mutex>
#include <map>
using boost::asio::ip::tcp;

class CServer :public std::enable_shared_from_this<CServer>
{
public:
	CServer(boost::asio::io_context& ioc , short port);
	~CServer();
	void ClearSession(std::string id);
	std::shared_ptr<CSession> GetSession(std::string id);
	bool CheckValid(std::string uuid);
private:
	void HandlerAccept(std::shared_ptr<CSession> session, const boost::system::error_code& ec);
	void StartAccept();
	boost::asio::io_context& _ioc;
	tcp::acceptor _acceptor;
	short _port;
	std::map<std::string, std::shared_ptr<CSession>> _sessions;
	std::mutex _mutex;
};

