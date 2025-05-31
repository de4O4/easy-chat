#include "LogicSystem.h"
#include "HttpConnection.h"

LogicSystem::~LogicSystem()
{
}

bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> con)
{
	if (_get_handler.find(path) == _get_handler.end()) {
		return false;
	}
	_get_handler[path](con);		//path存在于_get_handlers中，取出对应的处理函数并调用，传入HTTP连接对象con
	return true;	

}

bool LogicSystem::HandlePost(std::string path, std::shared_ptr<HttpConnection> con)
{
	if (_post_handler.find(path) == _post_handler.end()) {
		return false;
	}

	_post_handler[path](con);
	return true;
}

void LogicSystem::RegGet(std::string url, HttpHandler handler)
{
	_get_handler.insert(make_pair(url, handler));
}

void LogicSystem::RegPost(std::string url, HttpHandler handler)
{
	_post_handler.insert(make_pair(url, handler));
}

LogicSystem::LogicSystem()
{
	RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {
		beast::ostream(connection->_response.body()) << "receive get_test req" << std::endl;
		int i = 0;
		i++;
		for (auto& elem : connection->_get_params) {
			beast::ostream(connection->_response.body()) << "param is " << i << " key is " << elem.first;
			beast::ostream(connection->_response.body()) << " , " << i << " value is " << elem.second << std::endl;
		}
	});

	RegPost("/get_varifycode", [](std::shared_ptr<HttpConnection> connection) {
		auto body_str = beast::buffers_to_string(connection->_request.body().data());		//将请求的url转为string类型处理
		std::cout << "receive body is " << body_str << std::endl;
		connection->_response.set(http::field::content_type, "text/json");
		Json::Value root;
		Json::Reader reader;
		Json::Value src_root;
		bool parse_success = reader.parse(body_str, src_root);
		if (!parse_success) {
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}
		if (!src_root.isMember("email")) {
			std::cout << "Failed to parse JSON data!" << std::endl;
			root["error"] = ErrorCodes::Error_Json;
			std::string jsonstr = root.toStyledString();
			beast::ostream(connection->_response.body()) << jsonstr;
			return true;
		}

		auto email = src_root["email"].asString();
		GetVarifyRsp rsp = VarifyGrpcClient::GetInstance()->GetVarifyCode(email);
		std::cout << "email is " << email << std::endl;
		root["error"] = rsp.error();
		root["email"] = src_root["email"];
		std::string jsonstr = root.toStyledString();
		beast::ostream(connection->_response.body()) << jsonstr;
		return true;
		});
}

