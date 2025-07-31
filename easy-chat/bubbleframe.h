#ifndef BUBBLEFRAME_H
#define BUBBLEFRAME_H
#include <QFrame>
#include "global.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>


/******************************************************************************
 *
 * @file       bubbleframe.h
 * @brief      聊天气泡的基类，完成聊天气泡图形的绘制
 *
 * @author     duya
 * @date       2025/07/31
 * @history
 *****************************************************************************/




class BubbleFrame:public QFrame
{
    Q_OBJECT
public:
    BubbleFrame(ChatRole role, QWidget *parent = nullptr);
    void setMargin(int margin);
    //inline int margin(){return margin;}
    void setWidget(QWidget *w);
protected:
    void paintEvent(QPaintEvent *e);
private:
    QHBoxLayout *m_pHLayout;
    ChatRole m_role;
    int      m_margin;
};

#endif // BUBBLEFRAME_H
