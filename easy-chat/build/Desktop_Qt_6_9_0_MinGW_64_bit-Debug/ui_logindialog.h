/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedlabel.h>

QT_BEGIN_NAMESPACE

class Ui_loginDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *errtip;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *emaillabel;
    QLineEdit *emailedit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passlabel;
    QLineEdit *passedit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    ClickedLabel *forgetlabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *loginbutton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *regitbutton;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName("loginDialog");
        loginDialog->resize(400, 600);
        loginDialog->setMinimumSize(QSize(400, 600));
        loginDialog->setMaximumSize(QSize(400, 600));
        verticalLayout_2 = new QVBoxLayout(loginDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(loginDialog);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        errtip = new QLabel(widget);
        errtip->setObjectName("errtip");
        errtip->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(errtip, 0, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName("label");
        label->setAutoFillBackground(false);
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/diary.png")));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);


        verticalLayout->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        emaillabel = new QLabel(loginDialog);
        emaillabel->setObjectName("emaillabel");
        emaillabel->setMinimumSize(QSize(0, 45));
        emaillabel->setMaximumSize(QSize(16777215, 45));

        horizontalLayout->addWidget(emaillabel);

        emailedit = new QLineEdit(loginDialog);
        emailedit->setObjectName("emailedit");
        emailedit->setMinimumSize(QSize(0, 45));
        emailedit->setMaximumSize(QSize(16777215, 45));

        horizontalLayout->addWidget(emailedit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        passlabel = new QLabel(loginDialog);
        passlabel->setObjectName("passlabel");
        passlabel->setMinimumSize(QSize(0, 45));
        passlabel->setMaximumSize(QSize(16777215, 45));

        horizontalLayout_2->addWidget(passlabel);

        passedit = new QLineEdit(loginDialog);
        passedit->setObjectName("passedit");
        passedit->setMinimumSize(QSize(0, 45));
        passedit->setMaximumSize(QSize(16777215, 45));

        horizontalLayout_2->addWidget(passedit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        forgetlabel = new ClickedLabel(loginDialog);
        forgetlabel->setObjectName("forgetlabel");
        forgetlabel->setMinimumSize(QSize(0, 45));
        forgetlabel->setMaximumSize(QSize(16777215, 45));

        horizontalLayout_3->addWidget(forgetlabel);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        loginbutton = new QPushButton(loginDialog);
        loginbutton->setObjectName("loginbutton");
        loginbutton->setMinimumSize(QSize(100, 45));
        loginbutton->setMaximumSize(QSize(100, 45));

        horizontalLayout_4->addWidget(loginbutton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        regitbutton = new QPushButton(loginDialog);
        regitbutton->setObjectName("regitbutton");
        regitbutton->setMinimumSize(QSize(100, 45));

        horizontalLayout_5->addWidget(regitbutton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(loginDialog);

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QCoreApplication::translate("loginDialog", "Dialog", nullptr));
        errtip->setText(QString());
        label->setText(QString());
        emaillabel->setText(QCoreApplication::translate("loginDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        passlabel->setText(QCoreApplication::translate("loginDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        forgetlabel->setText(QCoreApplication::translate("loginDialog", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        loginbutton->setText(QCoreApplication::translate("loginDialog", "\347\231\273\345\275\225", nullptr));
        regitbutton->setText(QCoreApplication::translate("loginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
