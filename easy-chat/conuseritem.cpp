#include "conuseritem.h"
#include "ui_conuseritem.h"

ConUserItem::ConUserItem(QWidget *parent)
    : ListItemBase(parent)
    , ui(new Ui::ConUserItem)
{
    ui->setupUi(this);
    SetItemType(ListItemType::ContactUserItem);
    ui->red_lb->raise();
    ShowRedPoint(false);
}

ConUserItem::~ConUserItem()
{
    delete ui;
}

QSize ConUserItem::sizeHint() const
{
    return QSize(250,70);
}

void ConUserItem::SetInfo(std::shared_ptr<AuthInfo> auth_info)
{
    _info = std::make_shared<UserInfo>(auth_info);       //转换为userinfo类型
    QPixmap pixmap(_info->_icon);
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size() , Qt::KeepAspectRatio , Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);
    ui->user_name_lb->setText(_info->_name);
}

void ConUserItem::SetInfo(std::shared_ptr<AuthRsp> auth_rsp)
{
    _info = std::make_shared<UserInfo>(auth_rsp);       //转换为userinfo类型
    QPixmap pixmap(_info->_icon);
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size() , Qt::KeepAspectRatio , Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);
    ui->user_name_lb->setText(_info->_name);
}

void ConUserItem::SetInfo(int uid, QString name, QString icon)
{
    _info = std::make_shared<UserInfo>(uid , name , icon);       //转换为userinfo类型
    QPixmap pixmap(_info->_icon);
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size() , Qt::KeepAspectRatio , Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);
    ui->user_name_lb->setText(_info->_name);
}

void ConUserItem::ShowRedPoint(bool show)
{
    if(show){
        ui->red_lb->show();
    }else{
        ui->red_lb->hide();
    }
}

std::shared_ptr<UserInfo> ConUserItem::GetInfo()
{
    return _info;
}
