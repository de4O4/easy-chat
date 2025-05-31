#pragma once
#include "const.h"
#include "Singleton.h"
#include "VarifyGrpcClient.h"


class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

class LogicSystem :public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();
	bool HandleGet(std::string, std::shared_ptr<HttpConnection>);
	bool HandlePost(std::string, std::shared_ptr<HttpConnection>);
	void RegGet(std::string, HttpHandler handler);
	void RegPost(std::string, HttpHandler handler);
private:
	LogicSystem();
	std::map<std::string, HttpHandler> _post_handler;		//post����ص�����map,keyΪ·�ɣ�valueΪ�ص�����
	std::map<std::string, HttpHandler> _get_handler;		//get����ص�����map,keyΪ·�ɣ�valueΪ�ص�����
};

