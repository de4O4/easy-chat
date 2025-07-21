#include "chatuserwid.h"
#include "ui_chatuserwid.h"
#include <QPixmap>

ChatUserWid::ChatUserWid(QWidget *parent)
    : ListItemBase(parent), ui(new Ui::ChatUserWid)
{
    ui->setupUi(this);
    SetItemType(ListItemType::ChatUserItem);
}

ChatUserWid::~ChatUserWid()
{
    delete ui;
}

void ChatUserWid::SetInfo(std::shared_ptr<UserInfo> user_info)
{
    _user_info = user_info;
    QPixmap pixmap(_user_info->_icon);
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size() , Qt::KeepAspectRatio , Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);
    ui->user_name_lb->setText(_user_info->_name);
    ui->user_chat_lb->setText(_user_info->_last_msg);
}

void ChatUserWid::SetInfo(std::shared_ptr<FriendInfo> friend_info)
{
    _user_info = std::make_shared<UserInfo>(friend_info);
    QPixmap pixmap(_user_info->_icon);
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size() , Qt::KeepAspectRatio , Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);
    ui->user_name_lb->setText(_user_info->_name);
    ui->user_chat_lb->setText(_user_info->_last_msg);
}

std::shared_ptr<UserInfo> ChatUserWid::GetUserInfo()
{
    return _user_info;
}

void ChatUserWid::SetInfo(QString name, QString head, QString msg)
{
    _name = name;
    _head = head;
    _msg = msg;
    // 加载图片
    QPixmap pixmap(_head);

    // 设置图片自动缩放
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);

    ui->user_name_lb->setText(_name);
    ui->user_chat_lb->setText(_msg);

}



