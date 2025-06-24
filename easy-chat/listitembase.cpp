#include "listitembase.h"
#include <QStyleOption>
#include <QPainter>

ListItemBase::ListItemBase(QWidget *parent):QWidget(parent)
{

}

void ListItemBase::SetItemType(ListItemType itemtype)
{
    _itemtype = itemtype;
}

ListItemType ListItemBase::GetItemType()
{
    return _itemtype;
}

void ListItemBase::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
