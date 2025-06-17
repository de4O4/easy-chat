/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedlabel.h>
#include <timerbtn.h>

QT_BEGIN_NAMESPACE

class Ui_registerDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QLabel *errtip;
    QHBoxLayout *horizontalLayout;
    QLabel *userlabel;
    QLineEdit *useredit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *emaillabel;
    QLineEdit *emailline;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passlabel;
    QLineEdit *passedit;
    ClickedLabel *pass_visible;
    QHBoxLayout *horizontalLayout_4;
    QLabel *confirmlabel;
    QLineEdit *confirmedit;
    ClickedLabel *confirm_visible;
    QHBoxLayout *horizontalLayout_5;
    QLabel *varifylabel;
    QLineEdit *varifyedit;
    TimerBtn *getcodebut;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *confirmbut;
    QPushButton *cancelbut;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_6;
    QLabel *tiplab;
    QSpacerItem *verticalSpacer_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *returnbtn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *registerDialog)
    {
        if (registerDialog->objectName().isEmpty())
            registerDialog->setObjectName("registerDialog");
        registerDialog->resize(458, 600);
        registerDialog->setMinimumSize(QSize(400, 600));
        registerDialog->setMaximumSize(QSize(458, 600));
        verticalLayout_2 = new QVBoxLayout(registerDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(registerDialog);
        stackedWidget->setObjectName("stackedWidget");
        page = new QWidget();
        page->setObjectName("page");
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        widget = new QWidget(page);
        widget->setObjectName("widget");
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        errtip = new QLabel(widget);
        errtip->setObjectName("errtip");
        errtip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(errtip);


        verticalLayout_3->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        userlabel = new QLabel(page);
        userlabel->setObjectName("userlabel");
        userlabel->setMinimumSize(QSize(0, 35));
        userlabel->setMaximumSize(QSize(16777215, 35));

        horizontalLayout->addWidget(userlabel);

        useredit = new QLineEdit(page);
        useredit->setObjectName("useredit");
        useredit->setMinimumSize(QSize(0, 35));
        useredit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout->addWidget(useredit);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        emaillabel = new QLabel(page);
        emaillabel->setObjectName("emaillabel");
        emaillabel->setMinimumSize(QSize(0, 35));
        emaillabel->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_2->addWidget(emaillabel);

        emailline = new QLineEdit(page);
        emailline->setObjectName("emailline");
        emailline->setMinimumSize(QSize(0, 35));
        emailline->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_2->addWidget(emailline);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        passlabel = new QLabel(page);
        passlabel->setObjectName("passlabel");
        passlabel->setMinimumSize(QSize(0, 35));
        passlabel->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_3->addWidget(passlabel);

        passedit = new QLineEdit(page);
        passedit->setObjectName("passedit");
        passedit->setMinimumSize(QSize(0, 35));
        passedit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_3->addWidget(passedit);

        pass_visible = new ClickedLabel(page);
        pass_visible->setObjectName("pass_visible");
        pass_visible->setMinimumSize(QSize(35, 0));
        pass_visible->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_3->addWidget(pass_visible);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        confirmlabel = new QLabel(page);
        confirmlabel->setObjectName("confirmlabel");
        confirmlabel->setMinimumSize(QSize(0, 35));
        confirmlabel->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_4->addWidget(confirmlabel);

        confirmedit = new QLineEdit(page);
        confirmedit->setObjectName("confirmedit");
        confirmedit->setMinimumSize(QSize(0, 35));
        confirmedit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_4->addWidget(confirmedit);

        confirm_visible = new ClickedLabel(page);
        confirm_visible->setObjectName("confirm_visible");
        confirm_visible->setMinimumSize(QSize(35, 0));
        confirm_visible->setMaximumSize(QSize(35, 16777215));

        horizontalLayout_4->addWidget(confirm_visible);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        varifylabel = new QLabel(page);
        varifylabel->setObjectName("varifylabel");
        varifylabel->setMinimumSize(QSize(0, 35));
        varifylabel->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_5->addWidget(varifylabel);

        varifyedit = new QLineEdit(page);
        varifyedit->setObjectName("varifyedit");
        varifyedit->setMinimumSize(QSize(0, 35));
        varifyedit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_5->addWidget(varifyedit);

        getcodebut = new TimerBtn(page);
        getcodebut->setObjectName("getcodebut");
        getcodebut->setMinimumSize(QSize(0, 35));
        getcodebut->setMaximumSize(QSize(70, 35));

        horizontalLayout_5->addWidget(getcodebut);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        confirmbut = new QPushButton(page);
        confirmbut->setObjectName("confirmbut");
        confirmbut->setMinimumSize(QSize(0, 35));
        confirmbut->setMaximumSize(QSize(265, 35));

        horizontalLayout_6->addWidget(confirmbut);

        cancelbut = new QPushButton(page);
        cancelbut->setObjectName("cancelbut");
        cancelbut->setMinimumSize(QSize(0, 35));
        cancelbut->setMaximumSize(QSize(265, 35));

        horizontalLayout_6->addWidget(cancelbut);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout_5 = new QVBoxLayout(page_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);

        tiplab = new QLabel(page_2);
        tiplab->setObjectName("tiplab");

        verticalLayout_5->addWidget(tiplab);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);

        widget_2 = new QWidget(page_2);
        widget_2->setObjectName("widget_2");
        horizontalLayout_7 = new QHBoxLayout(widget_2);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalSpacer = new QSpacerItem(229, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        returnbtn = new QPushButton(widget_2);
        returnbtn->setObjectName("returnbtn");
        returnbtn->setMinimumSize(QSize(100, 35));
        returnbtn->setMaximumSize(QSize(100, 35));

        horizontalLayout_7->addWidget(returnbtn);

        horizontalSpacer_2 = new QSpacerItem(229, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        verticalLayout_5->addWidget(widget_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(registerDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(registerDialog);
    } // setupUi

    void retranslateUi(QDialog *registerDialog)
    {
        registerDialog->setWindowTitle(QCoreApplication::translate("registerDialog", "Dialog", nullptr));
        errtip->setText(QCoreApplication::translate("registerDialog", "\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        userlabel->setText(QCoreApplication::translate("registerDialog", "\347\224\250\346\210\267\357\274\232", nullptr));
        emaillabel->setText(QCoreApplication::translate("registerDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        passlabel->setText(QCoreApplication::translate("registerDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        pass_visible->setText(QString());
        confirmlabel->setText(QCoreApplication::translate("registerDialog", "\347\241\256\350\256\244\357\274\232", nullptr));
        confirm_visible->setText(QString());
        varifylabel->setText(QCoreApplication::translate("registerDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        getcodebut->setText(QCoreApplication::translate("registerDialog", "\350\216\267\345\217\226", nullptr));
        confirmbut->setText(QCoreApplication::translate("registerDialog", "\347\241\256\350\256\244", nullptr));
        cancelbut->setText(QCoreApplication::translate("registerDialog", "\345\217\226\346\266\210", nullptr));
        tiplab->setText(QCoreApplication::translate("registerDialog", "\346\263\250\345\206\214\346\210\220\345\212\237\357\274\214 5S\345\220\216\350\277\224\345\233\236\347\231\273\345\275\225\357\274\214\345\217\257\347\202\271\345\207\273\350\277\224\345\233\236\346\214\211\351\222\256\347\233\264\346\216\245\350\277\224\345\233\236\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        returnbtn->setText(QCoreApplication::translate("registerDialog", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registerDialog: public Ui_registerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
