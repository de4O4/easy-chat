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

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog),_mode(ChatUIMode::ChatMode),_state(ChatUIMode::ChatMode),_b_loading(false)
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

    QPixmap pixmap(":/res/head_4.jpg");
    ui->side_head_lb->setPixmap(pixmap);
    QPixmap scalpixmap = pixmap.scaled(ui->side_head_lb->size() , Qt::KeepAspectRatio);
    ui->side_head_lb->setPixmap(scalpixmap);
    ui->side_head_lb->setScaledContents(true);      //自适应缩放

    ui->side_chat_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");

    ui->side_contact_lb->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
    ui->side_chat_lb->setProperty("state","normal");

    connect(ui->side_chat_lb , &StateWidget::clicked , this , &ChatDialog::slot_side_chat);
    connect(ui->side_contact_lb , &StateWidget::clicked , this , &ChatDialog::slot_side_contact);
    connect(ui->search_edit , &QLineEdit::textChanged , this , &ChatDialog::slot_text_change);

    AddLBGroup(ui->side_chat_lb);
    AddLBGroup(ui->side_contact_lb);
   // ui->widget.set
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

std::vector<QString>  strs ={"hello world !",
                             "nice to meet u",
                             "New year，new life",
                             "You have to love yourself",
                             "My love is written in the wind ever since the whole world is you"};
std::vector<QString> heads = {
    ":/res/head_1.jpg",
    ":/res/head_2.jpg",
    ":/res/head_3.jpg",
    ":/res/head_4.jpg",
    ":/res/head_5.jpg"
};
std::vector<QString> names = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};

void ChatDialog::addChatUserList()
{
    // 创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();
        auto *chat_user_wid = new ChatUserWid();
        chat_user_wid->SetInfo(names[name_i], heads[head_i], strs[str_i]);
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

void ChatDialog::slot_loading_chat_user()
{
    if(_b_loading){
        return;
    }
    _b_loading = true;
    LoadingDlg* load = new LoadingDlg(this);
    _loadingitem = new QListWidgetItem();
    _loadingitem->setSizeHint(load->sizeHint());     //获取loaddlg高度
    ui->chatuser_list->addItem(_loadingitem);
    ui->chatuser_list->setItemWidget(_loadingitem , load);
    qDebug()<<"loading user ...";

    QTimer::singleShot(100 , this , [=](){
        addChatUserList();
        if(_loadingitem){       //删除动画
            delete ui->chatuser_list->takeItem(ui->chatuser_list->row(_loadingitem));
            _loadingitem = nullptr;
        }
        ui->chatuser_list->scrollToBottom();
        _b_loading = false;
    });
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

