#include "friendlabel.h"
#include "ui_friendlabel.h"
#include <QFontMetrics>


FriendLabel::FriendLabel(QWidget *parent):QFrame(parent),ui(new Ui::FriendLabel)
{
    ui->setupUi(this);
    ui->clode_lb->SetState("normal" , "hover" , "pressed" , "selected_normal" , "selected_hover" , "selected_pressed");
    connect(ui->clode_lb , &ClickedLabel::clicked , this , &FriendLabel::slot_close);
}



FriendLabel::~FriendLabel()
{
    delete ui;
}

void FriendLabel::SetText(QString text)
{
    _text = text;
    ui->tip_lb->setText(text);
    ui->clode_lb->adjustSize();

    QFontMetrics fontmetrics(ui->tip_lb->font());       //获取tip_lb的字体信息
    auto textwidth = fontmetrics.horizontalAdvance(ui->tip_lb->text());
    auto textheight = fontmetrics.height();

    qDebug()<<"tip_lb width is "<<ui->tip_lb->width();
    qDebug()<<"close_lb width is "<<ui->close_wid->width();
    qDebug()<<"textwidth is "<<textwidth;
    this->setFixedWidth(ui->tip_lb->width() + ui->clode_lb->width() + 5);
    this->setFixedHeight(textheight + 2);
    qDebug()<<"this->setfixedheght is"<<this->height();
    _width = this->width();
    _height = this->height();
}

int FriendLabel::Width()
{
    return _width;
}

int FriendLabel::Height()
{
    return _height;
}

QString FriendLabel::Text()
{
    return _text;
}

void FriendLabel::slot_close()
{
    emit sig_close(_text);
}
