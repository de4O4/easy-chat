#include "timerbtn.h"

TimerBtn::TimerBtn(QWidget *parent):QPushButton(parent),_counter(60)
{
    _timer = new QTimer(this);      //父类为timerbtn
    connect(_timer , &QTimer::timeout , [this](){
        _counter--;
        if(_counter <= 0){
            _timer->stop();
            _counter = 60;
            this->setText("获取");
            this->setEnabled(true);
            return;
        }
        this->setText(QString::number(_counter));
    });
}

TimerBtn::~TimerBtn()
{
    _timer->stop();
}

void TimerBtn::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        qDebug()<<"鼠标左键释放！";
        this->setEnabled(false);
        this->setText(QString::number(_counter));
        _timer->start(1000);
        emit clicked();
    }
    QPushButton::mouseReleaseEvent(e);
}
