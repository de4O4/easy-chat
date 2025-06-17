#include "clickedlabel.h"
#include <QMouseEvent>
#include <QEnterEvent>

ClickedLabel::ClickedLabel(QWidget *parent):_curstate(ClickLbState::Normal)
{

}

void ClickedLabel::mousePressEvent(QMouseEvent *ev)     //// 处理鼠标点击事件
{
    if(ev->button() == Qt::LeftButton){
        if(_curstate == ClickLbState::Normal){
            qDebug()<<"clicked , change to selected-hover "<<_selected_hover;
            _curstate = ClickLbState::Selected;
            setProperty("state" , _selected_hover);
            repolish(this);
            update();
        }else{
            qDebug()<<"clicked , change to normal-hover "<<_normal_hover;
            _curstate = ClickLbState::Normal;
            setProperty("state" , _normal_hover);
            repolish(this);
            update();
        }
        emit clicked();
    }
    QLabel::mousePressEvent(ev);         // 调用基类的mousePressEvent以保证正常的事件处理
}

void ClickedLabel::enterEvent(QEnterEvent *event)           // 处理鼠标悬停进入事件
{
    if(_curstate == ClickLbState::Normal){
        qDebug()<<"enter , change to normal-hover "<<_normal_hover;
        setProperty("state" , _normal_hover);
        repolish(this);
        update();
    }else{
        qDebug()<<"enter , change to selected-hover "<<_selected_hover;
        setProperty("state" , _selected_hover);
        repolish(this);
        update();
    }
    QLabel::enterEvent(event);
}

void ClickedLabel::leaveEvent(QEvent *event)
{
    if(_curstate == ClickLbState::Normal){
        qDebug()<<"leave , change to normal"<<_normal;
        setProperty("state" , _normal);
        repolish(this);
        update();
    }else{
        qDebug()<<"leave , change to selected"<<_selected;
        setProperty("state" , _selected);
        repolish(this);
        update();
    }
    QLabel::leaveEvent(event);
}

void ClickedLabel::SetState(QString normal, QString hover, QString press, QString select, QString select_hover, QString select_press)
{
    _normal = normal;
    _normal_hover = hover;
    _normal_press = press;
    _selected = select;
    _selected_hover = select_hover;
    _selected_press = select_press;
    setProperty("state",normal);
    repolish(this);
}

ClickLbState ClickedLabel::GetCurState()
{
    return _curstate;
}
