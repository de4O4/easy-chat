#ifndef USERMGR_H
#define USERMGR_H
#include <QObject>
#include <memory>
#include <singleton.h>
#include "userdata.h"

class UserMgr:public QObject,public SingteTon<UserMgr>,
                public std::enable_shared_from_this<UserMgr>
{
    Q_OBJECT
public:
    friend class SingteTon<UserMgr>;
    ~ UserMgr();
    void SetToken(QString token);
    QString GetName();
    int GetUid();
    bool AlreadyApply(int uid);
    std::vector<std::shared_ptr<ApplyInfo>> GetApplyList();
    void AppendApplyList(QJsonArray array);
    void AddApplyList(std::shared_ptr<ApplyInfo> app);
    void SetUserInfo(std::shared_ptr<UserInfo> user_info);
    bool CheckFriendById(int uid);
    void AddFriend(std::shared_ptr<AuthRsp> auth_rsp);
    void AddFriend(std::shared_ptr<AuthInfo> auth_info);

private:
    UserMgr();
    QString _name;
    QString _token;
    int _uid;
    std::shared_ptr<UserInfo> _user_info;
    std::vector<std::shared_ptr<ApplyInfo>> _apply_list;
    std::vector<std::shared_ptr<FriendInfo>> _friend_list;
    QMap<int, std::shared_ptr<FriendInfo>> _friend_map;
};

#endif // USERMGR_H
