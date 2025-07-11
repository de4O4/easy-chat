/********************************************************************************
** Form generated from reading UI file 'chatpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATPAGE_H
#define UI_CHATPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <chatview.h>
#include <clickedbtn.h>
#include <clickedlabel.h>
#include <messagetextedit.h>

QT_BEGIN_NAMESPACE

class Ui_ChatPage
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *chat_data_wid;
    QVBoxLayout *verticalLayout_4;
    QWidget *title_wid;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *title_lab;
    ChatView *chat_data_list;
    QWidget *tool_wid;
    QHBoxLayout *horizontalLayout_4;
    ClickedLabel *emo_lab;
    QSpacerItem *horizontalSpacer_3;
    ClickedLabel *file_lab;
    QSpacerItem *horizontalSpacer_2;
    MessageTextEdit *chat_edit;
    QWidget *send_wid;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    ClickedBtn *recv_btn;
    QSpacerItem *horizontalSpacer_6;
    ClickedBtn *send_btn;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *ChatPage)
    {
        if (ChatPage->objectName().isEmpty())
            ChatPage->setObjectName("ChatPage");
        ChatPage->resize(775, 789);
        verticalLayout = new QVBoxLayout(ChatPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        chat_data_wid = new QWidget(ChatPage);
        chat_data_wid->setObjectName("chat_data_wid");
        verticalLayout_4 = new QVBoxLayout(chat_data_wid);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(5, 0, 0, 10);
        title_wid = new QWidget(chat_data_wid);
        title_wid->setObjectName("title_wid");
        title_wid->setMaximumSize(QSize(16777215, 50));
        verticalLayout_5 = new QVBoxLayout(title_wid);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(title_wid);
        widget_2->setObjectName("widget_2");
        widget_2->setMinimumSize(QSize(0, 30));
        widget_2->setMaximumSize(QSize(16777215, 30));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        title_lab = new QLabel(widget_2);
        title_lab->setObjectName("title_lab");
        title_lab->setMinimumSize(QSize(0, 25));
        title_lab->setMaximumSize(QSize(50, 25));

        horizontalLayout_3->addWidget(title_lab);


        verticalLayout_5->addWidget(widget_2);


        verticalLayout_4->addWidget(title_wid);

        chat_data_list = new ChatView(chat_data_wid);
        chat_data_list->setObjectName("chat_data_list");
        chat_data_list->setMinimumSize(QSize(0, 400));
        chat_data_list->setMaximumSize(QSize(16777215, 400));

        verticalLayout_4->addWidget(chat_data_list);

        tool_wid = new QWidget(chat_data_wid);
        tool_wid->setObjectName("tool_wid");
        tool_wid->setMinimumSize(QSize(0, 40));
        tool_wid->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_4 = new QHBoxLayout(tool_wid);
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(6, 0, 0, 3);
        emo_lab = new ClickedLabel(tool_wid);
        emo_lab->setObjectName("emo_lab");
        emo_lab->setMinimumSize(QSize(35, 30));
        emo_lab->setMaximumSize(QSize(35, 30));
        emo_lab->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(emo_lab);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        file_lab = new ClickedLabel(tool_wid);
        file_lab->setObjectName("file_lab");
        file_lab->setMinimumSize(QSize(35, 30));
        file_lab->setMaximumSize(QSize(35, 30));
        file_lab->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_4->addWidget(file_lab);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_4->addWidget(tool_wid);

        chat_edit = new MessageTextEdit(chat_data_wid);
        chat_edit->setObjectName("chat_edit");
        chat_edit->setMaximumSize(QSize(16777215, 170));

        verticalLayout_4->addWidget(chat_edit);

        send_wid = new QWidget(chat_data_wid);
        send_wid->setObjectName("send_wid");
        send_wid->setMinimumSize(QSize(0, 40));
        send_wid->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_5 = new QHBoxLayout(send_wid);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        recv_btn = new ClickedBtn(send_wid);
        recv_btn->setObjectName("recv_btn");
        recv_btn->setMinimumSize(QSize(110, 30));
        recv_btn->setMaximumSize(QSize(110, 30));

        horizontalLayout_5->addWidget(recv_btn);

        horizontalSpacer_6 = new QSpacerItem(15, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        send_btn = new ClickedBtn(send_wid);
        send_btn->setObjectName("send_btn");
        send_btn->setMinimumSize(QSize(110, 30));
        send_btn->setMaximumSize(QSize(110, 30));

        horizontalLayout_5->addWidget(send_btn);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_4->addWidget(send_wid);


        verticalLayout->addWidget(chat_data_wid);


        retranslateUi(ChatPage);

        QMetaObject::connectSlotsByName(ChatPage);
    } // setupUi

    void retranslateUi(QWidget *ChatPage)
    {
        ChatPage->setWindowTitle(QCoreApplication::translate("ChatPage", "Form", nullptr));
        title_lab->setText(QCoreApplication::translate("ChatPage", "test", nullptr));
        emo_lab->setText(QString());
        file_lab->setText(QString());
        recv_btn->setText(QCoreApplication::translate("ChatPage", "\346\216\245\346\224\266", nullptr));
        send_btn->setText(QCoreApplication::translate("ChatPage", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatPage: public Ui_ChatPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATPAGE_H
