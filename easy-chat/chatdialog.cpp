#include "chatdialog.h"
#include "ui_chatdialog.h"
#include "clickedbtn.h"
#include <QAction>
#include "customizeedit.h"
#include <QRandomGenerator>
#include "chatuserwid.h"
#include "loadingdlg.h"
#include <QListWidget>
#include <QTimer>
#include <QMouseEvent>
#include "tcpmgr.h"
#include "usermgr.h"
#include "friendinfopage.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog),_mode(ChatUIMode::ChatMode),_state(ChatUIMode::ChatMode),_b_loading(false),_cur_chat_uid(0),_last_widget(nullptr)
{
    ui->setupUi(this);
    ui->add_btn->SetState("normal","hover","press");
    QAction* searchaction = new QAction(ui->search_edit);
    searchaction->setIcon(QIcon(":/res/search.png"));                //设置搜索图标
    ui->search_edit->addAction(searchaction , QLineEdit::LeadingPosition);      //将图标至于开头
    ui->search_edit->setPlaceholderText(QStringLiteral("搜索"));
    ui->search_edit->SetMaxLength(15);
    QAction* clearaction = new QAction(ui->search_edit);
    clearaction->setIcon(QIcon(":/res/close_transparent.png"));
    ui->search_edit->addAction(clearaction , QLineEdit::TrailingPosition);      //将清楚图标放在尾部
    connect(ui->search_edit , &QLineEdit::textChanged , [clearaction](const QString& text){             // 当需要显示清除图标时，更改为实际的清除图标
        if(!text.isEmpty()){        //搜索栏非空
            clearaction->setIcon(QIcon(":/res/close_search.png"));
        }else{              //搜索栏为空
            clearaction->setIcon(QIcon(":/res/close_transparent.png"));
        }
    });
    connect(clearaction , &QAction::triggered , [this , clearaction](){     // 连接清除动作的触发信号到槽函数，用于清除文本
        ui->search_edit->clear();
        clearaction->setIcon(QIcon(":/res/close_transparent.png"));
        ui->search_edit->clearFocus();
    });
    ShowSearch(false);
    addChatUserList();
    connect(ui->chatuser_list , &ChatUserList::sig_loading_chat_user , this , &ChatDialog::slot_loading_chat_user);

    QString head_icon = UserMgr::getintance()->GetIcon();
    QPixmap pixmap(head_icon);
    ui->side_head_lb->setPixmap(head_icon);
    QPixmap scalpixmap = pixmap.scaled(ui->side_head_lb->size() , Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->side_head_lb->setPixmap(scalpixmap);
    ui->side_head_lb->setScaledContents(true);      //自适应缩放

    ui->side_chat_lb->setProperty("state","normal");
    ui->side_chat_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");

    ui->side_contact_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");


    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    connect(ui->side_chat_lb , &StateWidget::clicked , this , &ChatDialog::slot_side_chat);
    connect(ui->side_contact_lb , &StateWidget::clicked , this , &ChatDialog::slot_side_contact);
    connect(ui->search_edit , &QLineEdit::textChanged , this , &ChatDialog::slot_text_change);

    AddLBGroup(ui->side_chat_lb);
    AddLBGroup(ui->side_contact_lb);
    this->installEventFilter(this);

    SetSelectChatItem();
    //更新聊天界面信息
    SetSelectChatPage();

    ui->side_chat_lb->SetSelected(true);
    ui->search_list->SetSearchEdit(ui->search_edit);
    connect(TcpMgr::getintance().get() , &TcpMgr::sig_friend_apply , this , &ChatDialog::slot_friend_apply);
    connect(TcpMgr::getintance().get() , &TcpMgr::sig_auth_rsp , this , &ChatDialog::slot_auth_rsp);
    connect(TcpMgr::getintance().get() , &TcpMgr::sig_add_auth_friend , this , &ChatDialog::slot_add_auth_friend);
    connect(ui->search_list , &SearchList::sig_jump_chat_item , this , &ChatDialog::slot_jump_chat_item);
    connect(ui->con_user_list , &ContactUserList::sig_loading_contact_user , this , &ChatDialog::slot_loading_contact_user);
    connect(ui->con_user_list , &ContactUserList::sig_switch_friend_info_page , this ,&ChatDialog::slot_friend_info_page);
    connect(ui->con_user_list , &ContactUserList::sig_switch_apply_friend_page , this , &ChatDialog::slot_switch_apply_friend_page);
    connect(ui->friend_info_page , &FriendInfoPage::sig_jump_chat_item , this , &ChatDialog::slot_jump_chat_item_from_infopage);
    connect(ui->chat_page , &ChatPage::sig_append_send_chat_msg , this , &ChatDialog::slot_append_send_chat_msg);
    connect(ui->chatuser_list, &QListWidget::itemClicked, this, &ChatDialog::slot_item_clicked);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::ShowSearch(bool bsearch)
{
    if(bsearch){
        ui->chatuser_list->hide();
        ui->con_user_list->hide();
        ui->search_list->show();
        _mode = ChatUIMode::SearchMode;
    }else if(_state == ChatUIMode::ChatMode){
        ui->chatuser_list->show();
        ui->con_user_list->hide();
        ui->search_list->hide();
        _mode = ChatUIMode::ChatMode;
    }else if(_state == ChatUIMode::ContactMode){
        ui->chatuser_list->hide();
        ui->search_list->hide();
        ui->con_user_list->show();
        _mode = ChatUIMode::ContactMode;
    }

}



void ChatDialog::addChatUserList()
{
    auto friend_list = UserMgr::getintance()->GetChatListPerPage();
    if(!friend_list.empty()){
        for(auto& friend_it : friend_list){
            auto it = _chat_items_added.find(friend_it->_uid);
            if(it != _chat_items_added.end()){          //聊天列表已存在该聊天消息
                continue;
            }
            auto* chat_user_wid = new ChatUserWid();
            auto user_info = std::make_shared<UserInfo>(friend_it);
            chat_user_wid->SetInfo(user_info);
            QListWidgetItem* item = new QListWidgetItem();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->chatuser_list->addItem(item);
            ui->chatuser_list->setItemWidget(item , chat_user_wid);
            _chat_items_added.insert(friend_it->_uid , item);
        }
        UserMgr::getintance()->UpdateChatLoadedCount();
    }

    // 创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();
        auto *chat_user_wid = new ChatUserWid();
        auto user_info = std::make_shared<UserInfo>(0,names[name_i],
                                                    names[name_i],heads[head_i],0,strs[str_i]);
        chat_user_wid->SetInfo(user_info);
        QListWidgetItem *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(chat_user_wid->sizeHint());
        ui->chatuser_list->addItem(item);
        ui->chatuser_list->setItemWidget(item, chat_user_wid);
    }
}

void ChatDialog::ClearLabelState(StateWidget *lb)
{
    for(auto& ele : _lb_list){          //只将被点击的标签置为选中状态，将其他标签置为正常
        if(ele == lb){
            continue;
        }
        ele->ClearState();
    }
}

void ChatDialog::AddLBGroup(StateWidget *lb)
{
    _lb_list.push_back(lb);
}

void ChatDialog::handleGlobalMousePress(QMouseEvent *event)
{
    if(_mode != ChatUIMode::SearchMode){
        return;
    }
    QPoint posInSearchList = (ui->search_list->mapFromGlobal(event->globalPosition())).toPoint();       // 将鼠标点击位置转换为搜索列表坐标系中的位置
    if(!ui->search_list->rect().contains(posInSearchList)){     //点击坐标不在搜索列表中
        ui->search_edit->clear();
        ShowSearch(false);
    }
}

void ChatDialog::SetSelectChatItem(int uid)
{
    if(ui->chatuser_list->count() < 0){
        return;
    }
    if(uid == 0){           //当传入的 uid 为 0 时，逻辑是“默认选中列表中的第一个用户。
        ui->chatuser_list->setCurrentRow(0);
        QListWidgetItem* firstitem = ui->chatuser_list->item(0);
        if(!firstitem){
            return;
        }
        QWidget* widget = ui->chatuser_list->itemWidget(firstitem);
        if(!widget){
            return;
        }
        auto con_item = qobject_cast<ChatUserWid*>(widget);
        if(!con_item){
            return;
        }
        _cur_chat_uid = con_item->GetUserInfo()->_uid;
        return;
    }
    auto find_it = _chat_items_added.find(uid);
    if(find_it == _chat_items_added.end()){
        qDebug()<<"uid "<<uid<<" not found set current row 0 ";
        ui->chatuser_list->setCurrentRow(0);
        return;
    }
    ui->chatuser_list->setCurrentItem(find_it.value());
    _cur_chat_uid = uid;
}

void ChatDialog::SetSelectChatPage(int uid)
{
    if( ui->chatuser_list->count() <= 0){
        return;
    }

    if (uid == 0) {
        auto item = ui->chatuser_list->item(0);
        //转为widget
        QWidget* widget = ui->chatuser_list->itemWidget(item);
        if (!widget) {
            return;
        }

        auto con_item = qobject_cast<ChatUserWid*>(widget);
        if (!con_item) {
            return;
        }

        //设置信息
        auto user_info = con_item->GetUserInfo();
        ui->chat_page->SetUserInfo(user_info);
        return;
    }

    auto find_iter = _chat_items_added.find(uid);
    if(find_iter == _chat_items_added.end()){
        return;
    }

    //转为widget
    QWidget *widget = ui->chatuser_list->itemWidget(find_iter.value());
    if(!widget){
        return;
    }

    //判断转化为自定义的widget
    // 对自定义widget进行操作， 将item 转化为基类ListItemBase
    ListItemBase *customItem = qobject_cast<ListItemBase*>(widget);
    if(!customItem){
        qDebug()<< "qobject_cast<ListItemBase*>(widget) is nullptr";
        return;
    }

    auto itemType = customItem->GetItemType();
    if(itemType == ChatUserItem){
        auto con_item = qobject_cast<ChatUserWid*>(customItem);
        if(!con_item){
            return;
        }

        //设置信息
        auto user_info = con_item->GetUserInfo();
        ui->chat_page->SetUserInfo(user_info);

        return;
    }

}

void ChatDialog::loadMoreChatUser()
{
    auto friend_list = UserMgr::getintance()->GetChatListPerPage();
    if(!friend_list.empty()){
        for(auto& friend_it : friend_list){
            auto find_it = _chat_items_added.find(friend_it->_uid);
            if(find_it != _chat_items_added.end()){         //好友已添加到聊天条目中
                continue;
            }
            auto* chat_user_wid = new ChatUserWid();
            auto user_info = std::make_shared<UserInfo>(friend_it);
            chat_user_wid->SetInfo(user_info);
            QListWidgetItem* item = new QListWidgetItem();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->chatuser_list->addItem(item);
            ui->chatuser_list->setItemWidget(item , chat_user_wid);
            _chat_items_added.insert(friend_it->_uid , item);
        }
        UserMgr::getintance()->UpdateChatLoadedCount();
    }
}

void ChatDialog::loadMoreConUser()
{
    auto friend_list = UserMgr::getintance()->GetConListPerPage();
    if (friend_list.empty() == false) {
        for(auto & friend_ele : friend_list){
            auto *chat_user_wid = new ConUserItem();
            chat_user_wid->SetInfo(friend_ele->_uid,friend_ele->_name,
                                   friend_ele->_icon);
            QListWidgetItem *item = new QListWidgetItem;
            //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->con_user_list->addItem(item);
            ui->con_user_list->setItemWidget(item, chat_user_wid);
        }

        //更新已加载条目
        UserMgr::getintance()->UpdateContactLoadedCount();
    }
}

bool ChatDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress){      //chat界面出现点击事件
        QMouseEvent* mouseevent = static_cast<QMouseEvent*>(event);
        handleGlobalMousePress(mouseevent);
    }
    return QDialog::eventFilter(watched , event);
}

void ChatDialog::slot_loading_chat_user()
{
    if(_b_loading){
        return;
    }

    _b_loading = true;
    LoadingDlg *loadingDialog = new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    qDebug() << "add new data to list.....";
    loadMoreChatUser();
    // 加载完成后关闭对话框
    loadingDialog->deleteLater();

    _b_loading = false;
}

void ChatDialog::slot_side_chat()
{
    qDebug()<<"recvive Clicked";
    ClearLabelState(ui->side_chat_lb);
    ui->stackedWidget->setCurrentWidget(ui->chat_page);
    _state = ChatUIMode::ChatMode;
    ShowSearch(false);
}

void ChatDialog::slot_side_contact()
{
    qDebug()<<"change contact";
    ClearLabelState(ui->side_contact_lb);
    ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
    _state = ChatUIMode::ContactMode;
    ShowSearch(false);
}

void ChatDialog::slot_text_change(const QString &str)
{
    if(!str.isEmpty()){
        ShowSearch(true);
    }
}

void ChatDialog::slot_friend_apply(std::shared_ptr<AddFriendApply> apply)
{
    qDebug() << "receive apply friend slot, applyuid is " << apply->_from_uid << " name is "
             << apply->_name << " desc is " << apply->_desc;
    bool b_already = UserMgr::getintance()->AlreadyApply(apply->_from_uid);     //查找该id的好友申请是否已在申请列表中
    if(b_already){
        return;
    }
    UserMgr::getintance()->AddApplyList(std::make_shared<ApplyInfo>(apply));         //不在申请列表则加入申请列表中
    ui->side_contact_lb->ShowRedPoint(true);
    ui->con_user_list->ShowRedPoint(true);
    ui->friend_apply_page->AddNewApply(apply);

}

void ChatDialog::slot_add_auth_friend(std::shared_ptr<AuthInfo> auth_info)      //服务器给另一个客户端的添加好友处理
{
    qDebug() << "receive slot_add_auth_rsp uid is " << auth_info->_uid
             << " name is " << auth_info->_name << " nick is " << auth_info->_nick;
    auto bfriend = UserMgr::getintance()->CheckFriendById(auth_info->_uid);      //检查同意申请的好友 是否已经是好友了
    if(bfriend){
        return;
    }
    UserMgr::getintance()->AddFriend(auth_info);         //不是好友则添加好友
    int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
    int str_i = randomValue % strs.size();
    int head_i = randomValue % heads.size();
    int name_i = randomValue % names.size();

    auto* chat_user_wid = new ChatUserWid();            //新建一个聊天条目
    auto user_info = std::make_shared<UserInfo>(auth_info);
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatuser_list->insertItem(0 , item);            //再聊天列表最上面插入
    ui->chatuser_list->setItemWidget(item , chat_user_wid);
    _chat_items_added.insert(auth_info->_uid , item);
}

void ChatDialog::slot_auth_rsp(std::shared_ptr<AuthRsp> auth_rsp)               //服务器给本客户端的添加好友处理
{
    qDebug() << "receive slot_auth_rsp uid is " << auth_rsp->_uid
             << " name is " << auth_rsp->_name << " nick is " << auth_rsp->_nick;
    auto bfriend = UserMgr::getintance()->CheckFriendById(auth_rsp->_uid);      //检查同意申请的好友 是否已经是好友了
    if(bfriend){
        return;
    }
    UserMgr::getintance()->AddFriend(auth_rsp);         //不是好友则添加好友
    int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
    int str_i = randomValue % strs.size();
    int head_i = randomValue % heads.size();
    int name_i = randomValue % names.size();

    auto* chat_user_wid = new ChatUserWid();            //新建一个聊天条目
    auto user_info = std::make_shared<UserInfo>(auth_rsp);
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatuser_list->insertItem(0 , item);            //再聊天列表最上面插入
    ui->chatuser_list->setItemWidget(item , chat_user_wid);
    _chat_items_added.insert(auth_rsp->_uid , item);
}

void ChatDialog::slot_jump_chat_item(std::shared_ptr<SearchInfo> si)
{
    qDebug()<<"slot jump chat item";
    auto find_it = _chat_items_added.find(si->_uid);            //查找已添加的聊天条目是否有匹配的
    if(find_it != _chat_items_added.end()){
        qDebug()<<"jump to chat item id is "<<si->_uid;
        ui->chatuser_list->scrollToItem(find_it.value());
        ui->side_chat_lb->SetSelected(true);
        SetSelectChatItem(si->_uid);
        SetSelectChatPage(si->_uid);
        slot_side_chat();
        return;
    }
    auto* chat_user_wid = new ChatUserWid();
    auto user_info = std::make_shared<UserInfo>(si);
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem;
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatuser_list->insertItem(0 , item);
    ui->chatuser_list->setItemWidget(item , chat_user_wid);
    _chat_items_added.insert(si->_uid , item);
    ui->side_chat_lb->SetSelected(true);
    SetSelectChatItem(si->_uid);
    SetSelectChatPage(si->_uid);
    slot_side_chat();

}

void ChatDialog::slot_loading_contact_user()
{
    qDebug() << "slot loading contact user";
    if(_b_loading){
        return;
    }

    _b_loading = true;
    LoadingDlg *loadingDialog = new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    qDebug() << "add new data to list.....";
    loadMoreConUser();
    // 加载完成后关闭对话框
    loadingDialog->deleteLater();

    _b_loading = false;
}

void ChatDialog::slot_switch_apply_friend_page()
{
    qDebug()<<"receive switch apply friend page sig";
    _last_widget = ui->friend_apply_page;
    ui->stackedWidget->setCurrentWidget(ui->friend_apply_page);
}


void ChatDialog::slot_friend_info_page(std::shared_ptr<UserInfo> user_info)
{
    qDebug()<<"receive switch friend info page sig";
    _last_widget = ui->friend_info_page;
    ui->stackedWidget->setCurrentWidget(ui->friend_info_page);
    ui->friend_info_page->SetInfo(user_info);
}

void ChatDialog::slot_jump_chat_item_from_infopage(std::shared_ptr<UserInfo> user_info)
{
    qDebug()<<"receive swtich jump chat item from friendinfo page!";
    //_last_widget = ui->friend_info_page;
    auto find_it = _chat_items_added.find(user_info->_uid);
    ui->side_chat_lb->SetSelected(true);
    if(find_it != _chat_items_added.end()){
        qDebug()<<"jump to chat item , uid is "<<user_info->_uid;
        ui->chatuser_list->scrollToItem(find_it.value());           //跳转到该用户的聊天框
        SetSelectChatItem(user_info->_uid);
        SetSelectChatPage(user_info->_uid);
        slot_side_chat();
        return;
    }
    auto* chat_user_wid = new ChatUserWid();
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatuser_list->insertItem(0 , item);
    ui->chatuser_list->setItemWidget(item , chat_user_wid);
    _chat_items_added.insert(user_info->_uid , item);
    SetSelectChatItem(user_info->_uid);
    SetSelectChatPage(user_info->_uid);
    slot_side_chat();
}

void ChatDialog::slot_append_send_chat_msg(std::shared_ptr<TextChatData> msgdata)
{
    if(_cur_chat_uid == 0){
        return;
    }
    auto find_it = _chat_items_added.find(_cur_chat_uid);
    if(find_it == _chat_items_added.end()){
        return;
    }

    QWidget* widget = ui->chatuser_list->itemWidget(find_it.value());
    if(!widget){
        return;
    }

    ListItemBase* customitem = qobject_cast<ListItemBase*>(widget);
    if(!customitem){
        qDebug()<<"qobject_cast<ListItemBase*>(widget) is nullptr";
        return;
    }
    auto itemtype = customitem->GetItemType();
    if(itemtype == ChatUserItem){
        auto con_item = qobject_cast<ChatUserWid*>(customitem);         //将基类的item转为自定义的item
        if(!con_item){
            return;
        }
        auto user_info = con_item->GetUserInfo();
        user_info->_chat_msgs.push_back(msgdata);
        std::vector<std::shared_ptr<TextChatData>> msg_vec;
        msg_vec.push_back(msgdata);
        UserMgr::getintance()->AppendFriendChatMsg(user_info->_uid , msg_vec);
        return;
    }
}

void ChatDialog::slot_item_clicked(QListWidgetItem *item)
{
    QWidget *widget = ui->chatuser_list->itemWidget(item); // 获取自定义widget对象
    if(!widget){
        qDebug()<< "slot item clicked widget is nullptr";
        return;
    }

    // 对自定义widget进行操作， 将item 转化为基类ListItemBase
    ListItemBase *customItem = qobject_cast<ListItemBase*>(widget);
    if(!customItem){
        qDebug()<< "slot item clicked widget is nullptr";
        return;
    }

    auto itemType = customItem->GetItemType();
    if(itemType == ListItemType::InvalidItem
        || itemType == ListItemType::GROUP_TIP_ITEM){
        qDebug()<< "slot invalid item clicked ";
        return;
    }


    if(itemType == ListItemType::ChatUserItem){
        // 创建对话框，提示用户
        qDebug()<< "chat user item clicked ";

        auto chat_wid = qobject_cast<ChatUserWid*>(customItem);
        auto user_info = chat_wid->GetUserInfo();
        //跳转到聊天界面
        ui->chat_page->SetUserInfo(user_info);
        _cur_chat_uid = user_info->_uid;
        return;
    }
}
