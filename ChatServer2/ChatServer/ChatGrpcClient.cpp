#include "ChatGrpcClient.h"
#include "ChatServiceImpl.h"

AddFriendRsp ChatGrpcClient::NotifyAddFriend(std::string server_ip, const AddFriendReq& req)
{
    AddFriendRsp rsp;
    Defer defer([&rsp, &req]() {
        rsp.set_error(ErrorCodes::Success);
		rsp.set_touid(req.touid());
		rsp.set_applyuid(req.applyuid());
        });
    std::cout << server_ip << std::endl;
    auto find_it = _pools.find(server_ip);
    if (find_it == _pools.end()) {          //ip不在池子内
        return rsp;
    }
    auto& pool = find_it->second;
    ClientContext context;
    auto stub = pool->GetConnection();
    Status status = stub->NotifyAddFriend(&context, req, &rsp);
    Defer defercon([&stub, this, &pool]() {
        pool->ReturnConnection(std::move(stub));
        });
    if (!status.ok()) {
        rsp.set_error(ErrorCodes::RPCFailed);
        return rsp;
    }
    return rsp;
}

AuthFriendRsp ChatGrpcClient::NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req)
{
    AuthFriendRsp rsp;
    rsp.set_error(ErrorCodes::Success);
    Defer defer([&rsp, &req]() {
        rsp.set_fromuid(req.fromuid());
		rsp.set_touid(req.touid());
        });
    auto find_it = _pools.find(server_ip);
    if (find_it == _pools.end()) {
        return rsp;
    }
    auto& pool = find_it->second;
    ClientContext context;
    auto stub = pool->GetConnection();
    Status status = stub->NotifyAuthFriend(&context, req, &rsp);
    Defer defercon([&stub, this, &pool]() {
        pool->ReturnConnection(std::move(stub));
        });
    if (!status.ok()) {
        rsp.set_error(ErrorCodes::RPCFailed);
        return rsp;
    }
    return rsp;
}



bool ChatGrpcClient::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo)
{
    return true;
}

TextChatMsgRsp ChatGrpcClient::NotifyTextChatMsg(std::string server_ip, const TextChatMsgReq& req, const Json::Value& rtvalue)
{
    TextChatMsgRsp rsp;
    return rsp;
}

ChatGrpcClient::ChatGrpcClient()
{   
    auto& cfg = ConfigMgr::Instance();
    auto server_list = cfg["peerServer"]["Servers"];
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
        _pools[cfg[word]["Name"]] = std::make_unique<ChatConnPool>(5, cfg[word]["Host"], cfg[word]["Port"]);
    }
}
