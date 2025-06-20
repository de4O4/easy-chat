#include "StatusServiceImpl.h"
#include "ConfigMgr.h"
#include "const.h"
#include "RedisMgr.h"

std::string generate_unique_string() {
    // 创建UUID对象
    boost::uuids::uuid uuid = boost::uuids::random_generator()();

    // 将UUID转换为字符串
    std::string unique_string = to_string(uuid);

    return unique_string;
}

Status StatusServiceImpl::GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* reply)
{
    std::string prefix("easy-chat status server has received :  ");
    const auto& server = getChatServer();
    reply->set_host(server.host);           //给客户端返回聊天服务器的地址
    reply->set_port(server.port);  
    std::cout << server.host << "   " << server.port << std::endl;
    reply->set_error(ErrorCodes::Success);
    reply->set_token(generate_unique_string());
    insertToken(request->uid(), reply->token());
    return Status::OK;
}

Status StatusServiceImpl::Login(ServerContext* context, const LoginReq* request, LoginRsp* reply) {
    auto uid = request->uid();
    auto token = request->token();
    std::lock_guard<std::mutex> lock(_token_mtx);
    auto it = _tokens.find(uid);
    if (it == _tokens.end()) {
        reply->set_error(ErrorCodes::UidInvalid);
        return Status::OK;
    }
    if (it->second != token) {
        reply->set_error(ErrorCodes::TokenInvalid);
        return Status::OK;
    }

    reply->set_error(ErrorCodes::Success);
    reply->set_uid(uid);
    reply->set_token(token);
    return Status::OK;
}

void StatusServiceImpl::insertToken(int uid, std::string token)
{
   // std::string uid_str = std::to_string(uid);
    //std::string token_key = USERTOKENPREFIX + uid_str;
    //RedisMgr::GetInstance()->Set(token_key, token);
    std::lock_guard<std::mutex> lock(_token_mtx);
    _tokens[uid] = token;
}

ChatServer StatusServiceImpl::getChatServer()
{
    std::lock_guard<std::mutex> lock(_server_mtx);
    auto minserver = _servers.begin()->second;
    return minserver;
}

StatusServiceImpl::StatusServiceImpl()
{
    auto& cfg = ConfigMgr::Instance();
    auto server_list = cfg["chatservers"]["Name"];

    std::vector<std::string> words;

    std::stringstream ss(server_list);
    std::string word;

    while (std::getline(ss, word, ',')) {
        words.push_back(word);
    }

    for (auto& word : words) {
        if (cfg[word]["Name"].empty()) {
            continue;
        }

        ChatServer server;
        server.port = cfg[word]["Port"];
        server.host = cfg[word]["Host"];
        server.name = cfg[word]["Name"];
        _servers[server.name] = server;
    }
}
