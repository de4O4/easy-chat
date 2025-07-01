#include "grouptipitem.h"
#include "ui_grouptipitem.h"
#include "global.h"

GroupTipItem::GroupTipItem(QWidget *parent)
    : ListItemBase(parent),_tip("")
    , ui(new Ui::GroupTipItem)
{
    ui->setupUi(this);
    SetItemType(ListItemType::GROUP_TIP_ITEM);
}

GroupTipItem::~GroupTipItem()
{
    delete ui;
}

QSize GroupTipItem::sizeHint() const
{
    return QSize(250,30);
}

void GroupTipItem::SetGroupTip(QString str)
{
    ui->label->setText(str);
}
