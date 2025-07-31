#ifndef LISTITEMBASE_H
#define LISTITEMBASE_H
#include <QWidget>
#include "global.h"

/******************************************************************************
 *
 * @file       listitembase.h
 * @brief      每个聊天。联系人条目的widget
 *
 * @author     duya
 * @date       2025/07/31
 * @history
 *****************************************************************************/


class ListItemBase:public QWidget
{
    Q_OBJECT
public:
    explicit ListItemBase(QWidget *parent = nullptr);
    void SetItemType(ListItemType itemtype);
    ListItemType GetItemType();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    ListItemType _itemtype;
};

#endif // LISTITEMBASE_H
