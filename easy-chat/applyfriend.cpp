#include "applyfriend.h"
#include "ui_applyfriend.h"
#include <QScrollArea>
#include <QScrollBar>
#include "global.h"
#include "usermgr.h"

ApplyFriend::ApplyFriend(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ApplyFriend),_label_point(2,6)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->setObjectName("ApplyFrined");
    this->setModal(true);
    qDebug()<<"apply friend success!";
    ui->name_ed->setPlaceholderText(tr("渡鸦"));
    ui->lb_ed->setPlaceholderText("搜索，添加标签 ");
    ui->back_ed->setPlaceholderText("燃烧的胸毛");

    ui->lb_ed->setMaxLength(21);
    ui->lb_ed->move(2 ,2);
    ui->lb_ed->setFixedHeight(35);
    ui->lb_ed->setMaxLength(10);
    ui->input_wid->hide();

    _tip_cur_point = QPoint(5, 5);

    _tip_data = { "同学","家人","菜鸟教程","C++ Primer","Rust 程序设计",
                 "父与子学Python","nodejs开发指南","go 语言开发指南",
                 "游戏伙伴","金融投资","微信读书","拼多多拼友" };            //标签文本
    connect(ui->more_lb , &ClickedOnceLabel::clicked , this , &ApplyFriend::ShowMoreLabel);
    InitTipLbs();
    connect(ui->lb_ed , &CustomizeEdit::returnPressed , this , &ApplyFriend::SlotLabelEnter);
    connect(ui->lb_ed , &CustomizeEdit::textChanged , this , &ApplyFriend::SlotLabelTextChange);
    connect(ui->lb_ed , &CustomizeEdit::editingFinished , this , &ApplyFriend::SlotLabelEditFinished);
    connect(ui->tip_lb , &ClickedOnceLabel::clicked , this , &ApplyFriend::SlotAddFriendLabelByClickTip);

    ui->scrollArea->horizontalScrollBar()->setHidden(true);
    ui->scrollArea->verticalScrollBar()->setHidden(true);
    ui->scrollArea->installEventFilter(this);
    ui->sure_btn->SetState("normal" , "hover" , "press");
    ui->cancel_btn->SetState("normal" , "hover" , "press");

    connect(ui->cancel_btn , &QPushButton::clicked , this , &ApplyFriend::SlotApplyCancel);
    connect(ui->sure_btn , &QPushButton::clicked , this , &ApplyFriend::SlotApplySure);
}

ApplyFriend::~ApplyFriend()
{
    qDebug()<< "ApplyFriend destruct";
    delete ui;
}

void ApplyFriend::InitTipLbs()
{
    int lines = 1;
    for(int i=0 ; i < _tip_data.size() ; i++){
        auto* lb = new ClickedLabel(ui->lb_list);       //创建新可点击的标签
        lb->SetState("normal" , "hover" , "pressed" , "selected_normal" , "selected_hover" , "selected_pressed");
        lb->setObjectName("tipslb");
        lb->setText(_tip_data[i]);
        connect(lb , &ClickedLabel::clicked , this , &ApplyFriend::SlotChangeFriendLabelByTip);     //为每个标签连接信号与槽

        QFontMetrics fontmetrics(lb->font());
        int textwidth = fontmetrics.horizontalAdvance(lb->text());      //获取标签内文本高度
        int textheight = fontmetrics.height();
        if(_tip_cur_point.x() + textwidth + tip_offset > ui->lb_list->width()){
            lines++;
            if(lines > 2){
                delete lb;
                return;
            }
            _tip_cur_point.setX(tip_offset);
            _tip_cur_point.setY(_tip_cur_point.y() + textheight + 15);
        }
        auto next_point = _tip_cur_point;

        AddTipLbs(lb, _tip_cur_point,next_point, textwidth, textheight);

        _tip_cur_point = next_point;

    }
}

void ApplyFriend::AddTipLbs(ClickedLabel *lb, QPoint cur_point, QPoint &next_point, int text_width, int text_height)
{
    lb->move(cur_point);
    lb->show();
    _add_labels.insert(lb->text() , lb);
    _add_label_keys.push_back(lb->text());
    next_point.setX(lb->pos().x() + text_width + 15);       //下一个标签位置的坐标
    next_point.setY(lb->pos().y());
}

bool ApplyFriend::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->scrollArea && event->type() == QEvent::Enter){            //回车事件发生在scrollarea
        ui->scrollArea->verticalScrollBar()->setHidden(false);
    }else if(obj == ui->scrollArea && event->type() == QEvent::Leave){
        ui->scrollArea->verticalScrollBar()->setHidden(true);
    }
    return QObject::eventFilter(obj , event);
}

void ApplyFriend::SetSearchInfo(std::shared_ptr<SearchInfo> si)
{
    _si = si;
    auto applyname = UserMgr::getintance()->GetName();
    auto backname = si->_name;
    ui->name_ed->setText(applyname);
    ui->back_ed->setText(backname);
}

void ApplyFriend::resetLabels()     //重排好友标签编辑栏的标签
{
    auto max_width = ui->gridWidget->width();
    auto label_height = 0;
    for(auto it = _friend_labels.begin();it != _friend_labels.end() ;it++){
        if(_label_point.x() + it.value()->width() > max_width){
            _label_point.setY(_label_point.y() + it.value()->height() + 6);
            _label_point.setX(2);
        }
        it.value()->move(_label_point);
        it.value()->show();
        _label_point.setX(_label_point.x() + it.value()->width() + 2);
        _label_point.setY(_label_point.y());
        label_height = it.value()->Height();
    }
    if(_friend_labels.isEmpty()){
        ui->lb_ed->move(_label_point);
        return;
    }
    if(_label_point.x() + MIN_APPLY_LABEL_ED_LEN >ui->gridWidget->width()){     //若输入的标签超过输入框的宽度
        ui->lb_ed->move(2 , _label_point.y() + label_height + 6);
    }else{
        ui->lb_ed->move(_label_point);
    }
}

void ApplyFriend::addLabel(QString name)            //添加自定义的好友标签在输入框中
{
    if(_friend_labels.find(name) != _friend_labels.end()){      //已存在这个标签
        return;
    }
    auto temlabel = new FriendLabel(ui->gridWidget);
    temlabel->SetText(name);
    temlabel->setObjectName("FriendLabel");
    auto max_width = ui->gridWidget->width();
    if(_label_point.x() + temlabel->Width() > max_width){
        _label_point.setY(_label_point.y() + temlabel->Height() + 6);
        _label_point.setX(2);
    }else{

    }
    temlabel->move(_label_point);
    temlabel->show();
    temlabel->setFixedHeight(33);
    _friend_labels[temlabel->Text()] = temlabel;     //将自定义标签存储
    _friend_label_keys.push_back(temlabel->Text());
    connect(temlabel , &FriendLabel::sig_close , this , &ApplyFriend::SLotRemoveFriendLabel);
    _label_point.setX(_label_point.x() + temlabel->width() + 2);
    if(_label_point.x() + MIN_APPLY_LABEL_ED_LEN > ui->gridWidget->width()){        //标签和输入框超出容器宽度
        ui->lb_ed->move(2 , _label_point.y() + temlabel->height() + 2);
    }else{
        ui->lb_ed->move(_label_point);
    }
    ui->lb_ed->clear();
    if(ui->gridWidget->height() < _label_point.y() + temlabel->height() + 2){
        ui->gridWidget->setFixedHeight(_label_point.y() + temlabel->height() + 15);        //重新调整容器的高度
    }
}

void ApplyFriend::ShowMoreLabel()
{
    qDebug()<<"reveice more label clicked";
    ui->more_lb_wid->hide();
    ui->lb_list->setFixedWidth(330);
    _tip_cur_point = QPoint(5,5);
    auto next_point = _tip_cur_point;
    int textwidth;
    int textheight;
    for(auto& added_key:_add_label_keys){           //获取已经存在的标签
        auto added_lb = _add_labels[added_key];
        QFontMetrics fontmetrics(added_lb->font());
        textwidth = fontmetrics.horizontalAdvance(added_lb->text());        //获取文本宽度
        textheight = fontmetrics.height();
        if(_tip_cur_point.x() + textwidth + tip_offset > ui->lb_list->width()){         //当前行标签长度超出标签框的长度
            _tip_cur_point.setX(tip_offset);
            _tip_cur_point.setY(_tip_cur_point.y() + textheight + 15);
        }
        added_lb->move(_tip_cur_point);         //标签换到下一行
        next_point.setX(added_lb->pos().x() + textwidth + 15);          //下一个标签的位置
        next_point.setY(_tip_cur_point.y());
        _tip_cur_point = next_point;            //将下个标签的位置赋给当前位置
    }
    for(int i=0;i<_tip_data.size();i++){
        auto it = _add_labels.find(_tip_data[i]);
        if(it != _add_labels.end()){            //若发现标签之前已经添加过则跳过
            continue;
        }
        auto* lb = new ClickedLabel(ui->lb_list);
        lb->SetState("normal" , "hover" , "pressed" , "selected_normal" , "selected_hover" , "selected_pressed");
        lb->setObjectName("tipslb");
        lb->setText(_tip_data[i]);
        connect(lb , &ClickedLabel::clicked , this , &ApplyFriend::SlotChangeFriendLabelByTip);     //为每个标签连接信号与槽

        QFontMetrics fontmetrics(lb->font());
        int textwidth = fontmetrics.horizontalAdvance(lb->text());      //获取标签内文本高度
        int textheight = fontmetrics.height();
        if(_tip_cur_point.x() + textwidth + tip_offset > ui->lb_list->width()){
            _tip_cur_point.setX(tip_offset);
            _tip_cur_point.setY(_tip_cur_point.y() + textheight + 15);
        }
        next_point = _tip_cur_point;
        AddTipLbs(lb , _tip_cur_point , next_point , textwidth , textheight);
        _tip_cur_point = next_point;
    }
    int diff_height = next_point.y() + textheight + tip_offset - ui->lb_list->height();
    ui->lb_list->setFixedHeight(next_point.y() + textheight + tip_offset);      //重新调整标签栏的高度
    ui->scrollAreaWidgetContents->setFixedHeight(ui->scrollAreaWidgetContents->height() + diff_height);
}

void ApplyFriend::SlotLabelEnter()
{
    if(ui->lb_ed->text().isEmpty()){
        return;
    }
    auto text = ui->lb_ed->text();
    addLabel(text);
    ui->input_wid->hide();      //输入标签框隐藏
    auto find_it = std::find(_tip_data.begin() , _tip_data.end() , text);
    if(find_it == _tip_data.end()){     //不存在重复标签
        _tip_data.push_back(text);
    }
    auto find_add = _add_labels.find(text);
    if(find_add != _add_labels.end()){          //若标签已在展示栏则标签变为选中状态
        find_add.value()->SetCurState(ClickLbState::Selected);
        return;
    }
    auto* lb = new ClickedLabel(ui->lb_list);           //新建的标签
    lb->SetState("normal", "hover", "pressed", "selected_normal",
                 "selected_hover", "selected_pressed");
    lb->setObjectName("tipslb");
    lb->setText(text);
    connect(lb , &ClickedLabel::clicked , this , &ApplyFriend::SlotChangeFriendLabelByTip);
    qDebug()<<"ui.lb_list width is "<<ui->lb_list->width();
    qDebug()<<"tip_cur_point.x is "<<_tip_cur_point.x();
    QFontMetrics fontmetrics(lb->font());
    int textwidth = fontmetrics.horizontalAdvance(lb->text());
    int textheight = fontmetrics.height();
    qDebug()<<"textwidth is "<<textwidth;
    if(_tip_cur_point.x() + textwidth + tip_offset + 3 > ui->lb_list->width()){
        _tip_cur_point.setX(5);
        _tip_cur_point.setY(_tip_cur_point.y() + textheight + 15);
    }
    auto next_point = _tip_cur_point;
    AddTipLbs(lb , _tip_cur_point , next_point , textwidth , textheight);
    _tip_cur_point = next_point;
    int diff_height = next_point.y() + textheight + tip_offset - ui->lb_list->height();
    ui->lb_list->setFixedHeight(next_point.y() + textheight + tip_offset );
    lb->SetCurState(ClickLbState::Selected);
    ui->scrollAreaWidgetContents->setFixedHeight(ui->scrollAreaWidgetContents->height() + diff_height);
}

void ApplyFriend::SLotRemoveFriendLabel(QString name)
{
    qDebug()<<"receive close signal ";
    _label_point.setX(2);
    _label_point.setY(6);
    auto find_it = _friend_labels.find(name);
    if(find_it == _friend_labels.end()){        //没找到标签
        return;
    }
    auto find_key = _friend_label_keys.end();
    for(auto it = _friend_label_keys.begin();it!=_friend_label_keys.end();it++){
        if(*it == name){
            find_key = it;
            break;
        }
    }
    if(find_key != _friend_label_keys.end()){
        _friend_label_keys.erase(find_key);     //清楚标签内容
    }
    delete find_it.value();
    _friend_labels.erase(find_it);      //从map中删除标签
    resetLabels();
    auto find_add = _add_labels.find(name);
    if(find_add == _add_labels.end()){      //想要添加的标签不在已添加标签中
        return;
    }
    find_add.value()->ResetNormalState();       //选中的标签变为正常状态
}

void ApplyFriend::SlotChangeFriendLabelByTip(QString lbtext, ClickLbState state)        //点击标已有签添加或删除新联系人的标签
{
    auto find_it = _add_labels.find(lbtext);
    if(find_it == _add_labels.end()){
        return;
    }
    if(state == ClickLbState::Selected){
        addLabel(lbtext);
        return;
    }
    if(state == ClickLbState::Normal){
        SLotRemoveFriendLabel(lbtext);
        return;
    }
}

void ApplyFriend::SlotLabelTextChange(const QString &text)
{
    if(text.isEmpty()){         //输入标签栏未有文字输入
        ui->tip_lb->setText("");
        ui->input_wid->hide();
        return;
    }
    auto it = std::find(_tip_data.begin() , _tip_data.end() , text);        //寻找输入的标签是否已存在
    if(it == _tip_data.end()){
        auto new_text = add_prefix + text;;
        ui->tip_lb->setText(new_text);
        ui->input_wid->show();
        return;
    }
    ui->tip_lb->setText(text);
    ui->input_wid->show();
}

void ApplyFriend::SlotLabelEditFinished()
{
    ui->input_wid->hide();
}

void ApplyFriend::SlotAddFriendLabelByClickTip(QString text)
{
    int index = text.indexOf(add_prefix);
    if(index != -1){
        text = text.mid(index + add_prefix.length());      //截取后面的标签内容
    }
    addLabel(text);
    auto find_it = std::find(_tip_data.begin() , _tip_data.end() , text);
    if(find_it == _tip_data.end()){     //标签库中不存在则添加
        _tip_data.push_back(text);
    }
    auto find_add = _add_labels.find(text);     //在已添加的标签中寻找
    if(find_add != _add_labels.end()){
        find_add.value()->SetCurState(ClickLbState::Selected);      //存在的标签则变为选中状态
        return;
    }

    auto* lb = new ClickedLabel(ui->lb_list);
    lb->SetState("normal", "hover", "pressed", "selected_normal",
                 "selected_hover", "selected_pressed");
    lb->setObjectName("tipslb");
    lb->setText(text);
    connect(lb , &ClickedLabel::clicked , this , &ApplyFriend::SlotChangeFriendLabelByTip);
    qDebug()<<"lb_list width is "<<ui->lb_list->width();
    qDebug()<<"_tip_cur_point x() is "<<_tip_cur_point.x();
    QFontMetrics fontmetrics(lb->font());
    int textwidth = fontmetrics.horizontalAdvance(lb->text());
    int textheight = fontmetrics.height();
    qDebug()<<"textwidth is "<<textwidth;
    if(_tip_cur_point.x() + textwidth + tip_offset > ui->lb_list->width()){
        _tip_cur_point.setX(5);
        _tip_cur_point.setY(_tip_cur_point.y() + textheight + 15);
    }
    auto next_point = _tip_cur_point;
    AddTipLbs(lb , _tip_cur_point , next_point , textwidth , textheight);
    _tip_cur_point = next_point;

    int diff_height = next_point.y() + textheight + tip_offset - ui->lb_list->height();
    ui->lb_list->setFixedHeight(next_point.y() + textheight + tip_offset);
    lb->SetCurState(ClickLbState::Selected);
    ui->scrollAreaWidgetContents->setFixedHeight(ui->scrollAreaWidgetContents->height() + diff_height);
}

void ApplyFriend::SlotApplySure()
{
    qDebug()<<"slot apply sure called";
    this->hide();
    deleteLater();
}

void ApplyFriend::SlotApplyCancel()
{
    qDebug()<<"slot apply cancel";
    this->hide();
    deleteLater();
}
