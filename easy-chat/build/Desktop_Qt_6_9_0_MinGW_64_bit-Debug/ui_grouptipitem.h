/********************************************************************************
** Form generated from reading UI file 'grouptipitem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPTIPITEM_H
#define UI_GROUPTIPITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupTipItem
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QWidget *GroupTipItem)
    {
        if (GroupTipItem->objectName().isEmpty())
            GroupTipItem->setObjectName("GroupTipItem");
        GroupTipItem->resize(400, 30);
        GroupTipItem->setMinimumSize(QSize(0, 30));
        GroupTipItem->setMaximumSize(QSize(16777215, 30));
        verticalLayout = new QVBoxLayout(GroupTipItem);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 0, 0, 0);
        label = new QLabel(GroupTipItem);
        label->setObjectName("label");

        verticalLayout->addWidget(label);


        retranslateUi(GroupTipItem);

        QMetaObject::connectSlotsByName(GroupTipItem);
    } // setupUi

    void retranslateUi(QWidget *GroupTipItem)
    {
        GroupTipItem->setWindowTitle(QCoreApplication::translate("GroupTipItem", "Form", nullptr));
        label->setText(QCoreApplication::translate("GroupTipItem", "\346\226\260\347\232\204\346\234\213\345\217\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupTipItem: public Ui_GroupTipItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPTIPITEM_H
