/********************************************************************************
** Form generated from reading UI file 'resetdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETDIALOG_H
#define UI_RESETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ResetDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_7;
    QLabel *errtip;
    QHBoxLayout *horizontalLayout_3;
    QLabel *userlabel;
    QLineEdit *useredit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *emaillabel;
    QLineEdit *emailedit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *newpasslab;
    QLineEdit *newpassedit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *codelabel;
    QLineEdit *codeedit;
    QPushButton *getcodebtn;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *confirmbtn;
    QPushButton *returnbtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *ResetDialog)
    {
        if (ResetDialog->objectName().isEmpty())
            ResetDialog->setObjectName("ResetDialog");
        ResetDialog->resize(400, 600);
        ResetDialog->setMinimumSize(QSize(400, 600));
        ResetDialog->setMaximumSize(QSize(400, 600));
        horizontalLayout = new QHBoxLayout(ResetDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        widget = new QWidget(ResetDialog);
        widget->setObjectName("widget");
        horizontalLayout_7 = new QHBoxLayout(widget);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        errtip = new QLabel(widget);
        errtip->setObjectName("errtip");
        errtip->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        errtip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_7->addWidget(errtip);


        verticalLayout->addWidget(widget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        userlabel = new QLabel(ResetDialog);
        userlabel->setObjectName("userlabel");
        userlabel->setMinimumSize(QSize(0, 35));
        userlabel->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_3->addWidget(userlabel);

        useredit = new QLineEdit(ResetDialog);
        useredit->setObjectName("useredit");
        useredit->setMinimumSize(QSize(0, 35));
        useredit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_3->addWidget(useredit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        emaillabel = new QLabel(ResetDialog);
        emaillabel->setObjectName("emaillabel");
        emaillabel->setMinimumSize(QSize(0, 35));

        horizontalLayout_4->addWidget(emaillabel);

        emailedit = new QLineEdit(ResetDialog);
        emailedit->setObjectName("emailedit");
        emailedit->setMinimumSize(QSize(0, 35));
        emailedit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_4->addWidget(emailedit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        newpasslab = new QLabel(ResetDialog);
        newpasslab->setObjectName("newpasslab");
        newpasslab->setMinimumSize(QSize(0, 35));
        newpasslab->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_5->addWidget(newpasslab);

        newpassedit = new QLineEdit(ResetDialog);
        newpassedit->setObjectName("newpassedit");
        newpassedit->setMinimumSize(QSize(0, 35));
        newpassedit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_5->addWidget(newpassedit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        codelabel = new QLabel(ResetDialog);
        codelabel->setObjectName("codelabel");
        codelabel->setMinimumSize(QSize(0, 35));
        codelabel->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_6->addWidget(codelabel);

        codeedit = new QLineEdit(ResetDialog);
        codeedit->setObjectName("codeedit");
        codeedit->setMinimumSize(QSize(0, 35));
        codeedit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_6->addWidget(codeedit);

        getcodebtn = new QPushButton(ResetDialog);
        getcodebtn->setObjectName("getcodebtn");
        getcodebtn->setMinimumSize(QSize(0, 35));
        getcodebtn->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_6->addWidget(getcodebtn);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        confirmbtn = new QPushButton(ResetDialog);
        confirmbtn->setObjectName("confirmbtn");

        horizontalLayout_8->addWidget(confirmbtn);

        returnbtn = new QPushButton(ResetDialog);
        returnbtn->setObjectName("returnbtn");

        horizontalLayout_8->addWidget(returnbtn);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(ResetDialog);

        QMetaObject::connectSlotsByName(ResetDialog);
    } // setupUi

    void retranslateUi(QDialog *ResetDialog)
    {
        ResetDialog->setWindowTitle(QCoreApplication::translate("ResetDialog", "Dialog", nullptr));
        errtip->setText(QString());
        userlabel->setText(QCoreApplication::translate("ResetDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        emaillabel->setText(QCoreApplication::translate("ResetDialog", "\351\202\256\347\256\261", nullptr));
        newpasslab->setText(QCoreApplication::translate("ResetDialog", "\346\226\260\345\257\206\347\240\201", nullptr));
        codelabel->setText(QCoreApplication::translate("ResetDialog", "\351\252\214\350\257\201\347\240\201", nullptr));
        getcodebtn->setText(QCoreApplication::translate("ResetDialog", "\350\216\267\345\217\226", nullptr));
        confirmbtn->setText(QCoreApplication::translate("ResetDialog", "\347\241\256\350\256\244", nullptr));
        returnbtn->setText(QCoreApplication::translate("ResetDialog", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResetDialog: public Ui_ResetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETDIALOG_H
