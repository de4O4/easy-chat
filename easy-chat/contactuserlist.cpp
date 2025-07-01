#include "contactuserlist.h"
#include <QEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QRandomGenerator>
#include "grouptipitem.h"


ContactUserList::ContactUserList(QWidget *parent)
{
    Q_UNUSED(parent);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewport()->installEventFilter(this);
    addContactUserList();
    connect(this , &QListWidget::itemClicked , this , &ContactUserList::slot_item_clicked);     //当组件被点击触发


}

void ContactUserList::ShowRedPoint(bool bshow)
{
    _add_friend_item->ShowRedPoint(bshow);
}

bool ContactUserList::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->viewport()){
        if(event->type() == QEvent::Enter){
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        }else if(event->type() == QEvent::Leave){
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }

    if(watched == this->viewport() && event->type() == QEvent::Wheel){
        QWheelEvent *wheelevent = static_cast<QWheelEvent*>(event);
        int numdegrees = wheelevent->angleDelta().y() / 8;
        int numsteps = numdegrees / 15;
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numsteps);
        QScrollBar * scrollbar = this->verticalScrollBar();
        int maxscrollvalue = scrollbar->maximum();
        int currentvalue = scrollbar->value();
        if(maxscrollvalue  - currentvalue <= 0){
            qDebug()<<"load more contact user";
            emit sig_loading_contact_user();
        }
        return true;
    }
    return QListWidget::eventFilter(watched , event);
}




void ContactUserList::addContactUserList()
{
    auto * groupTip = new GroupTipItem();
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(groupTip->sizeHint());
    this->addItem(item);
    this->setItemWidget(item, groupTip);
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    _add_friend_item = new ConUserItem();
    _add_friend_item->setObjectName("new_friend_item");
    _add_friend_item->SetInfo(0,tr("新的朋友"),":/res/add_friend.png");
    _add_friend_item->SetItemType(ListItemType::APPLY_FRIEND_ITEM);
    QListWidgetItem *add_item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    add_item->setSizeHint(_add_friend_item->sizeHint());
    this->addItem(add_item);
    this->setItemWidget(add_item, _add_friend_item);
    //默认设置新的朋友申请条目被选中
    this->setCurrentItem(add_item);
    auto * groupCon = new GroupTipItem();
    groupCon->SetGroupTip(tr("联系人"));
    _groupitem = new QListWidgetItem;
    _groupitem->setSizeHint(groupCon->sizeHint());
    this->addItem(_groupitem);
    this->setItemWidget(_groupitem, groupCon);
    _groupitem->setFlags(_groupitem->flags() & ~Qt::ItemIsSelectable);
    // 创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();
        auto *con_user_wid = new ConUserItem();
        con_user_wid->SetInfo(0,names[name_i], heads[head_i]);
        QListWidgetItem *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(con_user_wid->sizeHint());
        this->addItem(item);
        this->setItemWidget(item, con_user_wid);
    }
}

void ContactUserList::slot_item_clicked(QListWidgetItem *item)          //根据item的种类不同响应不同的界面
{
    QWidget* widget = this->itemWidget(item);       //获取自定义widget对象的
    if(!widget){
        qDebug()<<"slot item clicked widget is nullptr";
        return;
    }
    ListItemBase* customitem = qobject_cast<ListItemBase*>(widget);     //将自定义的widget转为基类 listitem
    if(!customitem){
        qDebug()<<"slot item clicked widget is null";
        return;
    }
    auto itemtype = customitem->GetItemType();
    if(itemtype == ListItemType::InvalidItem || itemtype == ListItemType::GROUP_TIP_ITEM){
        qDebug()<<"slot invaild item clicked";
        return;
    }
    if(itemtype == ListItemType::APPLY_FRIEND_ITEM){
        qDebug()<<"apply friend item clicked";
        emit sig_switch_apply_friend_page();
        return;
    }
    if(itemtype == ListItemType::ContactUserItem){
        qDebug()<<"concact user item clicked";
        emit sig_switch_friend_info_page();
        return;
    }
}
