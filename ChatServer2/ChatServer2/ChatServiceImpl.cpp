#include "ChatServiceImpl.h"
#include "UserMgr.h"
#include "const.h"
#include "CSession.h"

ChatServiceImpl::ChatServiceImpl()
{
}

Status ChatServiceImpl::NotifyAddFriend(ServerContext* context, const AddFriendReq* request,            //服务端收到添加好友请求后调用
    AddFriendRsp* reply) {
	auto to_uid = request->touid();
    auto session = UserMgr::GetInstance()->GetSession(to_uid);      //获取自己的会话
    Defer defer([request, reply]() {
        reply->set_error(ErrorCodes::Success);
        reply->set_touid(request->touid());
        reply->set_applyuid(request->applyuid());
        });
    if (session == nullptr) {
        return Status::OK;
    }

	Json::Value rtvalue;            //session存在
    rtvalue["error"] = ErrorCodes::Success;
    rtvalue["applyuid"] = request->applyuid();
    rtvalue["name"] = request->name();
    rtvalue["desc"] = request->desc();
    rtvalue["sex"] = request->sex();
	rtvalue["nick"] = request->nick();
	rtvalue["icon"] = request->icon();
    std::string rt_str = rtvalue.toStyledString();
	session->Send(rt_str, ID_NOTIFY_ADD_FRIEND_REQ);  //发送添加好友请求给对方的客户端
    return Status::OK;
}

Status ChatServiceImpl::NotifyAuthFriend(ServerContext* context,
    const AuthFriendReq* request, AuthFriendRsp* response) {
    return Status::OK;
}

Status ChatServiceImpl::NotifyTextChatMsg(::grpc::ServerContext* context,
    const TextChatMsgReq* request, TextChatMsgRsp* response) {
    return Status::OK;
}

bool ChatServiceImpl::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo) {
    return true;
}