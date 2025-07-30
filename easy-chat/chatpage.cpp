#include "chatpage.h"
#include "ui_chatpage.h"
#include <QStyleOption>
#include <QPainter>
#include "bubbleframe.h"
#include "chatitembase.h"
#include "textbubble.h"
#include "picturebubble.h"
#include "usermgr.h"
#include "tcpmgr.h"

ChatPage::ChatPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatPage)
{
    ui->setupUi(this);
    ui->recv_btn->SetState("normal","hover","press");
    ui->send_btn->SetState("normal","hover","press");
    //设置图标样式
    ui->emo_lab->SetState("normal","hover","press","normal","hover","press");
    ui->file_lab->SetState("normal","hover","press","normal","hover","press");
    connect(ui->chat_edit , &MessageTextEdit::send , this , &ChatPage::on_send_btn_clicked);
}

ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::SetUserInfo(std::shared_ptr<UserInfo> user_info)
{
    _user_info = user_info;
    ui->title_lab->setText(_user_info->_name);
    ui->chat_data_list->removeAllItem();
    for(auto& msg : user_info->_chat_msgs){
        AppendChatMsg(msg);
    }
}

void ChatPage::AppendChatMsg(std::shared_ptr<TextChatData> msg)
{
    auto self_info = UserMgr::getintance()->GetUserInfo();
    ChatRole role;
    if(msg->_from_uid == self_info->_uid){      //自己发送的信息
        role = ChatRole::Self;
        ChatItemBase* pchatitem = new ChatItemBase(role);
        pchatitem->setUserName(self_info->_name);
        pchatitem->setUserIcon(QPixmap(self_info->_icon));
        QWidget* pbubble = nullptr;
        pbubble = new TextBubble(role , msg->_msg_content);
        pchatitem->setWidget(pbubble);
        ui->chat_data_list->appendChatItem(pchatitem);
    }else{
        role = ChatRole::Other;
        ChatItemBase* pchatitem = new ChatItemBase(role);
        auto friend_info = UserMgr::getintance()->GetFriendById(msg->_from_uid);
        if(friend_info == nullptr){
            return;
        }
        pchatitem->setUserName(friend_info->_name);
        pchatitem->setUserIcon(QPixmap(friend_info->_icon));
        QWidget* pbubble = nullptr;
        pbubble = new TextBubble(role , msg->_msg_content);
        pchatitem->setWidget(pbubble);
        ui->chat_data_list->appendChatItem(pchatitem);
    }
}

void ChatPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ChatPage::on_send_btn_clicked()
{
    if(_user_info == nullptr){          //检查目标用户信息（_user_info）是否为空，避免后续操作崩溃
        qDebug()<<"friend_info is empty!";
        return;
    }
    auto user_info = UserMgr::getintance()->GetUserInfo();
    auto ptextedit = ui->chat_edit;
    ChatRole role = ChatRole::Self;
    QString username = user_info->_name;
    QString usericon = user_info->_icon;
    const QVector<MsgInfo>& msglist = ptextedit->getMsgList();
    QJsonObject textobj;
    QJsonArray textarray;
    int txt_size = 0;

    for(int i =0; i < msglist.size() ; ++i){
        if(msglist[i].content.length() > 1024){         //消息长度大于1024 则不处理
            continue;
        }
        QString type = msglist[i].msgFlag;
        ChatItemBase* pchatitem = new ChatItemBase(role);
        pchatitem->setUserName(username);
        pchatitem->setUserIcon(usericon);
        QWidget* pbubble = nullptr;
        if(type == "text"){
            QUuid uuid = QUuid::createUuid();           //确保每条消息有唯一标识，用于后续消息状态跟踪（如“已送达”“已读”）
            QString uuidstring = uuid.toString();
            pbubble = new TextBubble(role , msglist[i].content);
            if(txt_size + msglist[i].content.length() > 1024){         // 检查累计文本长度是否超过1024，超过则分开发送
                textobj["fromuid"] = user_info->_uid;
                textobj["touid"] = _user_info->_uid;
                textobj["text_array"] = textarray;
                QJsonDocument doc(textobj);
                QByteArray jsondata = doc.toJson(QJsonDocument::Compact);
                txt_size = 0;       //// 重置累计变量，准备下一批消息
                textarray = QJsonArray();
                textobj = QJsonObject();
                emit TcpMgr::getintance()->sig_send_data(ReqType::ID_TEXT_CHAT_MSG_REQ , jsondata);
            }
            txt_size += msglist[i].content.length();
            QJsonObject obj;
            QByteArray utf8message = msglist[i].content.toUtf8();
            obj["content"] = QString::fromUtf8(utf8message);
            obj["msgid"] = uuidstring;
            textarray.append(obj);
            auto text_msg = std::make_shared<TextChatData>(uuidstring , obj["content"].toString() , user_info->_uid , _user_info->_uid);
            emit sig_append_send_chat_msg(text_msg);        // 通知界面添加发送的消息（本地显示）
        }else if(type == "image"){
            pbubble = new PictureBubble(QPixmap(msglist[i].content) , role);
        }else if(type == "file"){

        }
        if(pbubble != nullptr){
            pchatitem->setWidget(pbubble);
            ui->chat_data_list->appendChatItem(pchatitem);
        }
    }
    qDebug()<<" textarray is "<<textarray;
    textobj["text_array"] = textarray;
    textobj["fromuid"] = user_info->_uid;
    textobj["touid"] = _user_info->_uid;
    QJsonDocument doc(textobj);
    QByteArray jsondata = doc.toJson(QJsonDocument::Compact);
    txt_size = 0;
    textarray = QJsonArray();
    textobj = QJsonObject();
    emit TcpMgr::getintance()->sig_send_data(ReqType::ID_TEXT_CHAT_MSG_REQ , jsondata);
}

