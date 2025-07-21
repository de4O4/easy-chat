#include "usermgr.h"
#include <QJsonValue>


UserMgr::~UserMgr()
{

}



void UserMgr::SetToken(QString token)
{
    _token = token;
}

QString UserMgr::GetName()
{
    return _user_info->_name;
}

int UserMgr::GetUid()
{
    return _user_info->_uid;
}

bool UserMgr::AlreadyApply(int uid)             //检查该uid所对应的用户是否已经在申请好友列表内
{
    for(auto& apply : _apply_list){
        if(apply->_uid == uid){
            return true;
        }
    }
    return false;
}

std::vector<std::shared_ptr<ApplyInfo> > UserMgr::GetApplyList()
{
    return _apply_list;
}

void UserMgr::AppendApplyList(QJsonArray array)
{
    for(const QJsonValue &value : array){
        auto name = value["name"].toString();
        auto desc = value["desc"].toString();
        auto icon = value["icon"].toString();
        auto nick = value["nick"].toString();
        auto sex = value["sex"].toInt();
        auto uid = value["uid"].toInt();
        auto status = value["status"].toInt();
        auto info = std::make_shared<ApplyInfo>(uid, name , desc , icon , nick , sex , status);
        _apply_list.push_back(info);
    }
}

void UserMgr::AddApplyList(std::shared_ptr<ApplyInfo> app)
{
    _apply_list.push_back(app);
}

void UserMgr::SetUserInfo(std::shared_ptr<UserInfo> user_info)
{
    _user_info = user_info;
}

bool UserMgr::CheckFriendById(int uid)
{
    auto it = _friend_map.find(uid);
    if(it == _friend_map.end()){
        return false;
    }
    return true;
}

void UserMgr::AddFriend(std::shared_ptr<AuthRsp> auth_rsp)
{
    auto friend_info = std::make_shared<FriendInfo>(auth_rsp);
    _friend_map[friend_info->_uid] = friend_info;
}

void UserMgr::AddFriend(std::shared_ptr<AuthInfo> auth_info)
{
    auto friend_info = std::make_shared<FriendInfo>(auth_info);
    _friend_map[friend_info->_uid] = friend_info;
}

UserMgr::UserMgr():_user_info(nullptr)
{

}
