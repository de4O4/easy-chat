#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "global.h"
#include <QDialog>
#include <QListWidgetItem>
#include "statewidget.h"
#include "userdata.h"
#include <QMap>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();
    void ShowSearch(bool bsearch);
    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;
    QList<StateWidget*> _lb_list;
    void addChatUserList();
    void ClearLabelState(StateWidget *lb);
    void AddLBGroup(StateWidget *lb);
    void handleGlobalMousePress(QMouseEvent* event);
private:
    Ui::ChatDialog *ui;
    QListWidgetItem* _loadingitem;
    QMap<int, QListWidgetItem*> _chat_items_added;
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
public slots:
    void slot_loading_chat_user();
    void slot_side_chat();
    void slot_side_contact();
    void slot_text_change(const QString& str);
    void slot_friend_apply(std::shared_ptr<AddFriendApply>);
    void slot_add_auth_friend(std::shared_ptr<AuthInfo> auth_info);
    void slot_auth_rsp(std::shared_ptr<AuthRsp> auth_rsp);
};

#endif // CHATDIALOG_H
