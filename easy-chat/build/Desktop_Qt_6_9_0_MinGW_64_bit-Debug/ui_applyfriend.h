/********************************************************************************
** Form generated from reading UI file 'applyfriend.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLYFRIEND_H
#define UI_APPLYFRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickedbtn.h>
#include <clickedoncelabel.h>
#include <customizeedit.h>

QT_BEGIN_NAMESPACE

class Ui_ApplyFriend
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *apply_lb;
    QWidget *apply_wid;
    QVBoxLayout *verticalLayout_3;
    QFrame *line;
    QLabel *label;
    CustomizeEdit *name_ed;
    QLabel *label_2;
    CustomizeEdit *back_ed;
    QLabel *label_3;
    QWidget *lb_group_wid;
    QVBoxLayout *verticalLayout_4;
    QWidget *gridWidget;
    QLineEdit *lb_ed;
    QWidget *input_wid;
    QVBoxLayout *verticalLayout_5;
    ClickedOnceLabel *tip_lb;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *lb_list;
    QWidget *more_lb_wid;
    QVBoxLayout *verticalLayout_6;
    QSpacerItem *verticalSpacer_3;
    ClickedOnceLabel *more_lb;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QWidget *apply_sure_wid;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    ClickedBtn *sure_btn;
    QSpacerItem *horizontalSpacer_3;
    ClickedBtn *cancel_btn;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *ApplyFriend)
    {
        if (ApplyFriend->objectName().isEmpty())
            ApplyFriend->setObjectName("ApplyFriend");
        ApplyFriend->resize(370, 630);
        ApplyFriend->setMinimumSize(QSize(370, 630));
        ApplyFriend->setMaximumSize(QSize(370, 630));
        verticalLayout = new QVBoxLayout(ApplyFriend);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(ApplyFriend);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMinimumSize(QSize(0, 510));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 368, 508));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        apply_lb = new QLabel(scrollAreaWidgetContents);
        apply_lb->setObjectName("apply_lb");
        apply_lb->setMinimumSize(QSize(0, 25));
        apply_lb->setMaximumSize(QSize(16777215, 25));
        apply_lb->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(apply_lb);

        apply_wid = new QWidget(scrollAreaWidgetContents);
        apply_wid->setObjectName("apply_wid");
        verticalLayout_3 = new QVBoxLayout(apply_wid);
        verticalLayout_3->setObjectName("verticalLayout_3");
        line = new QFrame(apply_wid);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line);

        label = new QLabel(apply_wid);
        label->setObjectName("label");
        label->setMinimumSize(QSize(0, 25));
        label->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(label);

        name_ed = new CustomizeEdit(apply_wid);
        name_ed->setObjectName("name_ed");
        name_ed->setMinimumSize(QSize(0, 35));
        name_ed->setMaximumSize(QSize(16777215, 35));

        verticalLayout_3->addWidget(name_ed);

        label_2 = new QLabel(apply_wid);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 25));
        label_2->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(label_2);

        back_ed = new CustomizeEdit(apply_wid);
        back_ed->setObjectName("back_ed");
        back_ed->setMinimumSize(QSize(0, 35));
        back_ed->setMaximumSize(QSize(16777215, 35));

        verticalLayout_3->addWidget(back_ed);

        label_3 = new QLabel(apply_wid);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(0, 25));
        label_3->setMaximumSize(QSize(16777215, 25));

        verticalLayout_3->addWidget(label_3);

        lb_group_wid = new QWidget(apply_wid);
        lb_group_wid->setObjectName("lb_group_wid");
        lb_group_wid->setMinimumSize(QSize(0, 50));
        verticalLayout_4 = new QVBoxLayout(lb_group_wid);
        verticalLayout_4->setSpacing(10);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        gridWidget = new QWidget(lb_group_wid);
        gridWidget->setObjectName("gridWidget");
        gridWidget->setMinimumSize(QSize(0, 40));
        gridWidget->setMaximumSize(QSize(16777215, 40));
        lb_ed = new QLineEdit(gridWidget);
        lb_ed->setObjectName("lb_ed");
        lb_ed->setGeometry(QRect(2, 2, 200, 35));

        verticalLayout_4->addWidget(gridWidget);

        input_wid = new QWidget(lb_group_wid);
        input_wid->setObjectName("input_wid");
        input_wid->setMinimumSize(QSize(0, 40));
        input_wid->setMaximumSize(QSize(16777215, 40));
        verticalLayout_5 = new QVBoxLayout(input_wid);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        tip_lb = new ClickedOnceLabel(input_wid);
        tip_lb->setObjectName("tip_lb");

        verticalLayout_5->addWidget(tip_lb);


        verticalLayout_4->addWidget(input_wid);


        verticalLayout_3->addWidget(lb_group_wid);

        widget = new QWidget(apply_wid);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 60));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lb_list = new QWidget(widget);
        lb_list->setObjectName("lb_list");
        lb_list->setMinimumSize(QSize(290, 50));
        lb_list->setMaximumSize(QSize(290, 16777215));

        horizontalLayout_2->addWidget(lb_list);

        more_lb_wid = new QWidget(widget);
        more_lb_wid->setObjectName("more_lb_wid");
        more_lb_wid->setMinimumSize(QSize(40, 0));
        more_lb_wid->setMaximumSize(QSize(40, 16777215));
        verticalLayout_6 = new QVBoxLayout(more_lb_wid);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        more_lb = new ClickedOnceLabel(more_lb_wid);
        more_lb->setObjectName("more_lb");
        more_lb->setMinimumSize(QSize(30, 30));
        more_lb->setMaximumSize(QSize(30, 30));
        more_lb->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        more_lb->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(more_lb);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);


        horizontalLayout_2->addWidget(more_lb_wid);


        verticalLayout_3->addWidget(widget);


        verticalLayout_2->addWidget(apply_wid);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        apply_sure_wid = new QWidget(ApplyFriend);
        apply_sure_wid->setObjectName("apply_sure_wid");
        apply_sure_wid->setMinimumSize(QSize(0, 50));
        horizontalLayout = new QHBoxLayout(apply_sure_wid);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        sure_btn = new ClickedBtn(apply_sure_wid);
        sure_btn->setObjectName("sure_btn");
        sure_btn->setMinimumSize(QSize(130, 40));

        horizontalLayout->addWidget(sure_btn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        cancel_btn = new ClickedBtn(apply_sure_wid);
        cancel_btn->setObjectName("cancel_btn");
        cancel_btn->setMinimumSize(QSize(130, 40));

        horizontalLayout->addWidget(cancel_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(apply_sure_wid);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(ApplyFriend);

        QMetaObject::connectSlotsByName(ApplyFriend);
    } // setupUi

    void retranslateUi(QDialog *ApplyFriend)
    {
        ApplyFriend->setWindowTitle(QCoreApplication::translate("ApplyFriend", "Dialog", nullptr));
        apply_lb->setText(QCoreApplication::translate("ApplyFriend", "\347\224\263\350\257\267\345\245\275\345\217\213", nullptr));
        label->setText(QCoreApplication::translate("ApplyFriend", "\345\217\221\351\200\201\346\267\273\345\212\240\346\234\213\345\217\213\347\224\263\350\257\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("ApplyFriend", "\345\244\207\346\263\250\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("ApplyFriend", "\346\240\207\347\255\276\357\274\232", nullptr));
        tip_lb->setText(QString());
        more_lb->setText(QString());
        sure_btn->setText(QCoreApplication::translate("ApplyFriend", "\347\241\256\350\256\244", nullptr));
        cancel_btn->setText(QCoreApplication::translate("ApplyFriend", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplyFriend: public Ui_ApplyFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLYFRIEND_H
