/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <applyfriendpage.h>
#include <chatpage.h>
#include <chatuserlist.h>
#include <clickedbtn.h>
#include <contactuserlist.h>
#include <customizeedit.h>
#include <searchlist.h>
#include <statewidget.h>

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *side_bar;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *side_head_lb;
    StateWidget *side_contact_lb;
    StateWidget *side_chat_lb;
    QSpacerItem *verticalSpacer;
    QWidget *chat_user_wid;
    QVBoxLayout *verticalLayout_3;
    QWidget *search_wid;
    QHBoxLayout *horizontalLayout_2;
    CustomizeEdit *search_edit;
    QSpacerItem *horizontalSpacer;
    ClickedBtn *add_btn;
    ChatUserList *chatuser_list;
    SearchList *search_list;
    ContactUserList *con_user_list;
    QStackedWidget *stackedWidget;
    ChatPage *chat_page;
    ApplyFriendPage *friend_apply_page;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName("ChatDialog");
        ChatDialog->resize(1060, 836);
        horizontalLayout = new QHBoxLayout(ChatDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 5, 0);
        side_bar = new QWidget(ChatDialog);
        side_bar->setObjectName("side_bar");
        side_bar->setMinimumSize(QSize(55, 0));
        side_bar->setMaximumSize(QSize(55, 16777215));
        verticalLayout = new QVBoxLayout(side_bar);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 10, 0, 0);
        widget = new QWidget(side_bar);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 0, 10, 0);
        side_head_lb = new QLabel(widget);
        side_head_lb->setObjectName("side_head_lb");
        side_head_lb->setMinimumSize(QSize(45, 45));
        side_head_lb->setMaximumSize(QSize(45, 45));
        side_head_lb->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        side_head_lb->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(side_head_lb);

        side_contact_lb = new StateWidget(widget);
        side_contact_lb->setObjectName("side_contact_lb");
        side_contact_lb->setMinimumSize(QSize(30, 30));
        side_contact_lb->setMaximumSize(QSize(30, 30));

        verticalLayout_2->addWidget(side_contact_lb);

        side_chat_lb = new StateWidget(widget);
        side_chat_lb->setObjectName("side_chat_lb");
        side_chat_lb->setEnabled(true);
        side_chat_lb->setMinimumSize(QSize(30, 30));
        side_chat_lb->setMaximumSize(QSize(30, 30));

        verticalLayout_2->addWidget(side_chat_lb);


        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(side_bar);

        chat_user_wid = new QWidget(ChatDialog);
        chat_user_wid->setObjectName("chat_user_wid");
        chat_user_wid->setMinimumSize(QSize(0, 200));
        chat_user_wid->setMaximumSize(QSize(230, 16777215));
        verticalLayout_3 = new QVBoxLayout(chat_user_wid);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        search_wid = new QWidget(chat_user_wid);
        search_wid->setObjectName("search_wid");
        search_wid->setMinimumSize(QSize(0, 45));
        search_wid->setMaximumSize(QSize(16777215, 45));
        horizontalLayout_2 = new QHBoxLayout(search_wid);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(7, 0, 7, 0);
        search_edit = new CustomizeEdit(search_wid);
        search_edit->setObjectName("search_edit");
        search_edit->setMinimumSize(QSize(0, 35));
        search_edit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_2->addWidget(search_edit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        add_btn = new ClickedBtn(search_wid);
        add_btn->setObjectName("add_btn");
        add_btn->setMinimumSize(QSize(24, 24));
        add_btn->setMaximumSize(QSize(24, 24));

        horizontalLayout_2->addWidget(add_btn);


        verticalLayout_3->addWidget(search_wid);

        chatuser_list = new ChatUserList(chat_user_wid);
        chatuser_list->setObjectName("chatuser_list");

        verticalLayout_3->addWidget(chatuser_list);

        search_list = new SearchList(chat_user_wid);
        search_list->setObjectName("search_list");

        verticalLayout_3->addWidget(search_list);

        con_user_list = new ContactUserList(chat_user_wid);
        con_user_list->setObjectName("con_user_list");

        verticalLayout_3->addWidget(con_user_list);


        horizontalLayout->addWidget(chat_user_wid);

        stackedWidget = new QStackedWidget(ChatDialog);
        stackedWidget->setObjectName("stackedWidget");
        chat_page = new ChatPage();
        chat_page->setObjectName("chat_page");
        stackedWidget->addWidget(chat_page);
        friend_apply_page = new ApplyFriendPage();
        friend_apply_page->setObjectName("friend_apply_page");
        stackedWidget->addWidget(friend_apply_page);

        horizontalLayout->addWidget(stackedWidget);


        retranslateUi(ChatDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QCoreApplication::translate("ChatDialog", "Dialog", nullptr));
        side_head_lb->setText(QString());
        add_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
