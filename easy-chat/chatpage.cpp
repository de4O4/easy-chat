#include "chatpage.h"
#include "ui_chatpage.h"
#include <QStyleOption>
#include <QPainter>
#include "bubbleframe.h"
#include "chatitembase.h"
#include "textbubble.h"
#include "picturebubble.h"

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

void ChatPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ChatPage::on_send_btn_clicked()
{
    auto pTextEdit = ui->chat_edit;
    ChatRole role = ChatRole::Self;
    QString userName = QStringLiteral("渡鸦");
    QString userIcon = ":/res/head_1.jpg";

    const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();
    for(int i=0; i<msgList.size(); ++i)
    {
        QString type = msgList[i].msgFlag;
        ChatItemBase *pChatItem = new ChatItemBase(role);
        pChatItem->setUserName(userName);
        pChatItem->setUserIcon(QPixmap(userIcon));
        QWidget *pBubble = nullptr;
        if(type == "text")
        {
            pBubble = new TextBubble(role, msgList[i].content);
        }
        else if(type == "image")
        {
            pBubble = new PictureBubble(QPixmap(msgList[i].content) , role);
        }
        else if(type == "file")
        {

        }
        if(pBubble != nullptr)
        {
            pChatItem->setWidget(pBubble);
            ui->chat_data_list->appendChatItem(pChatItem);
        }
    }
}

