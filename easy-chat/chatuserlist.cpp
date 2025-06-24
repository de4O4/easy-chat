#include "chatuserlist.h"


ChatUserList::ChatUserList(QWidget *parent):QListWidget(parent)
{
    Q_UNUSED(parent);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->viewport()->installEventFilter(this);     //安装事件过滤器 将当前对象（this）注册为视口的事件监听者，允许在eventFilter函数中拦截并处理视口的事件（如鼠标按下、移动、释放等）

}

bool ChatUserList::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->viewport()){        // 检查事件是否是鼠标悬浮进入或离开
        if(event->type() == QEvent::Enter){     //鼠标在视窗内悬浮
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        }else if(event->type() == QEvent::Leave){           //鼠标不在视窗内
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }
    if(watched == this->viewport() && event->type() == QEvent::Wheel){      // 检查事件是否是鼠标滚轮事件
        QWheelEvent* wheelevent = static_cast<QWheelEvent *>(event);
        int numDegrees = wheelevent->angleDelta().y() / 8;
        int numSteps = numDegrees / 15; // 计算滚动步数
        // 设置滚动幅度
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numSteps);

        QScrollBar* scrollbar = this->verticalScrollBar();
        int maxscrollvalue = scrollbar->maximum();
        int currentvalue = scrollbar->value();      //当前滚动位置
      //  int threshold = 5;      //设置临界值
        if(maxscrollvalue - currentvalue <= 0){
            qDebug()<<"load more chat user";
            //发送信号通知聊天界面加载更多聊天内容
            emit sig_loading_chat_user();
        }
        return true;
    }
    return QListWidget::eventFilter(watched , event);
}
