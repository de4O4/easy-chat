#pragma once
#include "const.h"

class HttpConnection:public std::enable_shared_from_this<HttpConnection>
{
	friend class LogicSystem;
public:
	HttpConnection(boost::asio::io_context& ioc);
	void Start();
	tcp::socket& GetSocket();
private:
	void CheckDeadline();
	void WriteResponse();
	void HandleReq();
	void PreParseGetParam();
	tcp::socket _socket;
	beast::flat_buffer _buffer{ 8192 };			//用来接受数据
	http::request<http::dynamic_body> _request;			//用来解析请求
	http::response<http::dynamic_body> _response;		//用来回应客户端
	net::steady_timer deadline{ _socket.get_executor() , std::chrono::seconds(60) };		//用来做定时器判断请求是否超时
	std::string _get_url;
	std::unordered_map<std::string, std::string> _get_params;

};

