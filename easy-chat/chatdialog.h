#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include "global.h"
#include <QDialog>
#include <QListWidgetItem>


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
    void addChatUserList();

private:
    Ui::ChatDialog *ui;
    QListWidgetItem* _loadingitem;

public slots:
    void slot_loading_chat_user();
};

#endif // CHATDIALOG_H
