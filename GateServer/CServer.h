#pragma once
#include "const.h"


class CServer:public std::enable_shared_from_this<CServer>
{
public:
	CServer(net::io_context& ioc, unsigned short& port);
	void Start();
private:
	tcp::acceptor _acceptor;
	net::ip::tcp::socket _socket;
	net::io_context& _ioc;

};

