#include "bubbleframe.h"
#include <QColor>
const int WIDTH_SANJIAO  = 8;  //三角宽


BubbleFrame::BubbleFrame(ChatRole role, QWidget *parent):QFrame(parent),m_role(role),m_margin(3){

    m_pHLayout = new QHBoxLayout();
    if(m_role == ChatRole::Self){       //自己发送
        m_pHLayout->setContentsMargins(m_margin , m_margin , m_margin + WIDTH_SANJIAO , m_margin);      //设置边距 左上右下
    }else{
        m_pHLayout->setContentsMargins(m_margin + WIDTH_SANJIAO , m_margin , m_margin , m_margin);
    }
    this->setLayout(m_pHLayout);
}

void BubbleFrame::setMargin(int margin)
{
    m_margin = margin;
}

void BubbleFrame::setWidget(QWidget *w)         //设置气泡内具体内容
{
    if(m_pHLayout->count() > 0){
        return;
    }else{
            m_pHLayout->addWidget(w);
    }
}

void BubbleFrame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);      //关闭画笔（不绘制边框）

    if(m_role == ChatRole::Other){       //画气泡形状
        QColor bk_color(Qt::white);
        painter.setBrush(QBrush(bk_color));     // 设置画刷（填充颜色）
        QRect bk_rect = QRect(WIDTH_SANJIAO , 0 , this->width() - WIDTH_SANJIAO , this->height());      // 绘制圆角矩形（圆角半径5像素）
        painter.drawRoundedRect(bk_rect , 5 , 5);

        QPointF points[3] = {       // 绘制指向左侧的小三角
            QPointF(bk_rect.x() , 12),          // 三角顶点1（气泡左边缘，y=12）
            QPointF(bk_rect.x() , 10+WIDTH_SANJIAO+2),      // 三角顶点2（气泡左边缘，y=12+三角高度）
            QPointF(bk_rect.x() - WIDTH_SANJIAO , 10+WIDTH_SANJIAO-WIDTH_SANJIAO/2),        // 三角顶点3（向左延伸）
        };
        painter.drawPolygon(points , 3);
    } else
    {
        QColor bk_color(158,234,106);
        painter.setBrush(QBrush(bk_color));
        //画气泡
        QRect bk_rect = QRect(0, 0, this->width()-WIDTH_SANJIAO, this->height());
        painter.drawRoundedRect(bk_rect,5,5);
        //画三角
        QPointF points[3] = {
            QPointF(bk_rect.x()+bk_rect.width(), 12),
            QPointF(bk_rect.x()+bk_rect.width(), 12+WIDTH_SANJIAO +2),
            QPointF(bk_rect.x()+bk_rect.width()+WIDTH_SANJIAO, 10+WIDTH_SANJIAO-WIDTH_SANJIAO/2),
        };
        painter.drawPolygon(points, 3);
    }
    return QFrame::paintEvent(e);
}

