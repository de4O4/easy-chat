#ifndef CONUSERITEM_H
#define CONUSERITEM_H

#include <QWidget>
#include "listitembase.h"
#include "userdata.h"

/******************************************************************************
 *
 * @file       conuseritem.h
 * @brief      自定义的联系人条目
 *
 * @author     duya
 * @date       2025/07/31
 * @history
 *****************************************************************************/


namespace Ui {
class ConUserItem;
}

class ConUserItem : public ListItemBase
{
    Q_OBJECT

public:
    explicit ConUserItem(QWidget *parent = nullptr);
    ~ConUserItem();
    QSize sizeHint() const override;
    void SetInfo(std::shared_ptr<AuthInfo> auth_info);
    void SetInfo(std::shared_ptr<AuthRsp> auth_rsp);
    void SetInfo(int uid, QString name, QString icon);
    void ShowRedPoint(bool show = false);
    std::shared_ptr<UserInfo> GetInfo();

private:
    Ui::ConUserItem *ui;
    std::shared_ptr<UserInfo> _info;
};

#endif // CONUSERITEM_H
