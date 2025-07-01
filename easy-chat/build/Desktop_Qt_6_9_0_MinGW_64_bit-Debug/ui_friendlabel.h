/********************************************************************************
** Form generated from reading UI file 'friendlabel.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDLABEL_H
#define UI_FRIENDLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedlabel.h>

QT_BEGIN_NAMESPACE

class Ui_FriendLabel
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *tip_lb;
    QWidget *close_wid;
    QVBoxLayout *verticalLayout;
    ClickedLabel *close_lb;

    void setupUi(QWidget *FriendLabel)
    {
        if (FriendLabel->objectName().isEmpty())
            FriendLabel->setObjectName("FriendLabel");
        FriendLabel->resize(469, 50);
        FriendLabel->setMinimumSize(QSize(0, 35));
        FriendLabel->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(FriendLabel);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tip_lb = new QLabel(FriendLabel);
        tip_lb->setObjectName("tip_lb");
        tip_lb->setMinimumSize(QSize(0, 35));

        horizontalLayout->addWidget(tip_lb);

        close_wid = new QWidget(FriendLabel);
        close_wid->setObjectName("close_wid");
        close_wid->setMinimumSize(QSize(30, 30));
        close_wid->setMaximumSize(QSize(30, 30));
        verticalLayout = new QVBoxLayout(close_wid);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        close_lb = new ClickedLabel(close_wid);
        close_lb->setObjectName("close_lb");
        close_lb->setMinimumSize(QSize(20, 20));
        close_lb->setMaximumSize(QSize(20, 20));

        verticalLayout->addWidget(close_lb);


        horizontalLayout->addWidget(close_wid);


        retranslateUi(FriendLabel);

        QMetaObject::connectSlotsByName(FriendLabel);
    } // setupUi

    void retranslateUi(QWidget *FriendLabel)
    {
        FriendLabel->setWindowTitle(QCoreApplication::translate("FriendLabel", "Form", nullptr));
        tip_lb->setText(QString());
        close_lb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendLabel: public Ui_FriendLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDLABEL_H
