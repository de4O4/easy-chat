#include "searchlist.h"
#include "tcpmgr.h"
#include "adduseritem.h"
#include <QWheelEvent>
#include <QEvent>
#include <QScrollBar>
#include "findsuccessdlg.h"



SearchList::SearchList(QWidget *parent):QListWidget(parent),_find_dlg(nullptr),_search_edit(nullptr),_send_pending(false)
{
    Q_UNUSED(parent);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewport()->installEventFilter(this);     // 安装事件过滤器
    connect(this , &QListWidget::itemClicked , this , &SearchList::slot_item_clicked);      //连接点击的信号和槽
    addTipItem();
    connect(TcpMgr::getintance().get() , &TcpMgr::sig_user_search , this , &SearchList::slot_user_search);
}

void SearchList::CloseFindDlg()
{
    if(_find_dlg){
        _find_dlg->hide();
        _find_dlg = nullptr;
    }
}

void SearchList::SetSearchEdit(QWidget *edit)
{

}

bool SearchList::eventFilter(QObject *watched, QEvent *event)
{
    // 检查事件是否是鼠标悬浮进入或离开
    if (watched == this->viewport()) {
        if (event->type() == QEvent::Enter) {
            // 鼠标悬浮，显示滚动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        } else if (event->type() == QEvent::Leave) {
            // 鼠标离开，隐藏滚动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }

    // 检查事件是否是鼠标滚轮事件
    if (watched == this->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        int numDegrees = wheelEvent->angleDelta().y() / 8;
        int numSteps = numDegrees / 15; // 计算滚动步数

        // 设置滚动幅度
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numSteps);

        return true; // 停止事件传递
    }

    return QListWidget::eventFilter(watched, event);
}

void SearchList::waitPending(bool pending)
{

}

void SearchList::addTipItem()           //添加小组件
{
    auto *invalid_item = new QWidget();
    QListWidgetItem *item_tmp = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item_tmp->setSizeHint(QSize(250,10));
    this->addItem(item_tmp);
    invalid_item->setObjectName("invalid_item");
    this->setItemWidget(item_tmp, invalid_item);
    item_tmp->setFlags(item_tmp->flags() & ~Qt::ItemIsSelectable);


    auto *add_user_item = new AddUserItem();
    QListWidgetItem *item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(add_user_item->sizeHint());
    this->addItem(item);
    this->setItemWidget(item, add_user_item);
}

void SearchList::slot_item_clicked(QListWidgetItem *item)
{
    QWidget* widget = this->itemWidget(item);       //获取部件的widget对象
    if(!widget){
        qDebug()<<"slot item clicked is nullptr";
        return;
    }
    ListItemBase* customitem = qobject_cast<ListItemBase *>(widget);
    if(!customitem){
        qDebug()<< "slot item clicked widget is nullptr";
        return;
    }
    auto itemtype = customitem->GetItemType();
    if(itemtype == ListItemType::AddUserTipItem){
        _find_dlg = std::make_shared<FindSuccessDlg>(this);
        auto si = std::make_shared<SearchInfo>(0 , "duya" , "duya" , "hello" , 0);
        (std::dynamic_pointer_cast<FindSuccessDlg>(_find_dlg))->SetSearchInfo(si);
        _find_dlg->show();
        return;
    }
    if(itemtype == ListItemType::InvalidItem){
        qDebug()<< "slot invalid item clicked ";
        return;
    }
    CloseFindDlg();
}

void SearchList::slot_user_search(std::shared_ptr<SearchInfo> si)
{

}
