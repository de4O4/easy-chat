#include "chatitembase.h"
#include <QFont>
#include <QSpacerItem>

ChatItemBase::ChatItemBase(ChatRole role, QWidget *parent):QWidget(parent),m_role(role)
{
    m_pNameLabel = new QLabel();
    m_pNameLabel->setObjectName("chat_user_name");
    QFont font("Microsoft YaHei");
    font.setPointSize(9);           //设置字体大小
    m_pNameLabel->setFont(font);
    m_pNameLabel->setFixedHeight(20);       //设置固定高度

    m_pIconLabel = new QLabel();
    m_pIconLabel->setScaledContents(true);  //填充图片
    m_pIconLabel->setFixedSize(42,42);      //头像设置固定大小 42*42

    m_pBubble = new QWidget();      //聊天气泡
    QGridLayout *pGLayout = new QGridLayout();      //创建网格布局
    pGLayout->setVerticalSpacing(3);
    pGLayout->setHorizontalSpacing(3);
    pGLayout->setContentsMargins(3,3,3,3);

    QSpacerItem* pSpacer = new QSpacerItem(40 , 20 , QSizePolicy::Expanding , QSizePolicy::Minimum);        //水平可扩展、垂直保持最小的间隔项

    if(m_role == ChatRole::Self){       //自己发送消息
        m_pNameLabel->setContentsMargins(0,0,8,0);
        m_pNameLabel->setAlignment(Qt::AlignRight);
        pGLayout->addWidget(m_pNameLabel , 0 , 1 , 1, 1);
        pGLayout->addWidget(m_pIconLabel , 0 , 2 , 2, 1 , Qt::AlignTop);
        pGLayout->addItem(pSpacer , 1 , 0, 1, 1);
        pGLayout->addWidget(m_pBubble , 1 , 1, 1, 1);
        pGLayout->setColumnStretch(0 , 2);
        pGLayout->setColumnStretch(1 , 3);
    }else{                                                  //对方发送的消息气泡
        m_pNameLabel->setContentsMargins(8,0,0,0);
        m_pNameLabel->setAlignment(Qt::AlignLeft);
        pGLayout->addWidget(m_pNameLabel , 0 , 1 , 1, 1);
        pGLayout->addWidget(m_pIconLabel , 0 , 0 , 2, 1 , Qt::AlignTop);
        pGLayout->addItem(pSpacer , 2 , 2, 1, 1);
        pGLayout->addWidget(m_pBubble , 1 , 1, 1, 1);
        pGLayout->setColumnStretch(2 , 2);
        pGLayout->setColumnStretch(1 , 3);
    }
    this->setLayout(pGLayout);
}

void ChatItemBase::setUserName(const QString &name)
{
    m_pNameLabel->setText(name);
}

void ChatItemBase::setUserIcon(const QPixmap &icon)
{
    m_pIconLabel->setPixmap(icon);
}

void ChatItemBase::setWidget(QWidget *w)
{
    QGridLayout *pGLayout = (qobject_cast<QGridLayout *>(this->layout()));
    pGLayout->replaceWidget(m_pBubble , w);     //替换气泡部件
    delete m_pBubble;
    m_pBubble = w;
}
