#ifndef CHATUSERWID_H
#define CHATUSERWID_H

#include <QWidget>
#include "global.h"
#include "listitembase.h"
#include "userdata.h"

/******************************************************************************
 *
 * @file       chatuserwid.h
 * @brief      在聊天列表中的每一个小条目的widget
 *
 * @author     duya
 * @date       2025/07/31
 * @history
 *****************************************************************************/



namespace Ui {
class ChatUserWid;
}

class ChatUserWid : public ListItemBase
{
    Q_OBJECT

public:
    explicit ChatUserWid(QWidget *parent = nullptr);
    ~ChatUserWid();
    QSize sizeHint() const override {
        return QSize(250, 70); // 返回自定义的尺寸
    }
    void SetInfo(std::shared_ptr<UserInfo> user_info);
    void SetInfo(std::shared_ptr<FriendInfo> friend_info);
    std::shared_ptr<UserInfo> GetUserInfo();
    void SetInfo(QString name, QString head, QString msg);
    void updateLastMsg(std::vector<std::shared_ptr<TextChatData>> msgs);
private:
    Ui::ChatUserWid *ui;
    QString _name;
    QString _head;
    QString _msg;
    std::shared_ptr<UserInfo> _user_info;
};

#endif // CHATUSERWID_H
