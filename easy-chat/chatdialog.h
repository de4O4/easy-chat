#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "global.h"
#include <QDialog>
#include <QListWidgetItem>
#include "statewidget.h"

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
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
public slots:
    void slot_loading_chat_user();
    void slot_side_chat();
    void slot_side_contact();
    void slot_text_change(const QString& str);
};

#endif // CHATDIALOG_H
