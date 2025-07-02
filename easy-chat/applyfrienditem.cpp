#include "applyfrienditem.h"
#include "ui_applyfrienditem.h"

ApplyFriendItem::ApplyFriendItem(QWidget *parent) :
    ListItemBase(parent), _added(false),
    ui(new Ui::ApplyFriendItem)
{
    ui->setupUi(this);
    SetItemType(ListItemType::APPLY_FRIEND_ITEM);
    ui->add_btn->SetState("normal","hover", "press");
    ui->add_btn->hide();
    connect(ui->add_btn, &ClickedBtn::clicked,  [this](){
        emit this->sig_auth_friend(_apply_info);
    });
}

ApplyFriendItem::~ApplyFriendItem()
{
    delete ui;
}

void ApplyFriendItem::SetInfo(std::shared_ptr<ApplyInfo> apply_info)
{
    _apply_info = apply_info;
    QPixmap pixmap(_apply_info->_icon);
    ui->icon_lb->setPixmap(pixmap.scaled(ui->icon_lb->size() , Qt::KeepAspectRatio , Qt::SmoothTransformation));
    ui->icon_lb->setScaledContents(true);
    ui->user_chat_lb->setText(_apply_info->_desc);
    ui->user_name_lb->setText(_apply_info->_name);
}

void ApplyFriendItem::ShowAddBtn(bool bshow)
{
    if(bshow){
        ui->add_btn->show();
        ui->already_add_lb->hide();
        _added = false;
    }else{
        ui->add_btn->hide();
        ui->already_add_lb->show();
        _added = false;
    }
}

int ApplyFriendItem::GetUid()
{
    return _apply_info->_uid;
}
