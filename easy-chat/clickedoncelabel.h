#ifndef CLICKEDONCELABEL_H
#define CLICKEDONCELABEL_H
#include <QLabel>
#include <QMouseEvent>

/******************************************************************************
 *
 * @file       clickedoncelabel.h
 * @brief      自定义一次点击的按钮，选中未选中状态的展示不同
 *
 * @author     duya
 * @date       2025/07/31
 * @history
 *****************************************************************************/


class ClickedOnceLabel:public QLabel
{
    Q_OBJECT
public:
    ClickedOnceLabel(QWidget *parent=nullptr);
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
signals:
    void clicked(QString);
};

#endif // CLICKEDONCELABEL_H
