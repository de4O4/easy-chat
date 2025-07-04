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


void ChatUserWid::SetInfo(QString name, QString head, QString msg)
{
    _name = name;
    _head = head;
    _msg = msg;
    QPixmap pixmap(_head);      //设置头像
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size() , Qt::KeepAspectRatio , Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);
    ui->user_name_lb->setText(_name);
    ui->user_chat_lb->setText(_msg);
}
