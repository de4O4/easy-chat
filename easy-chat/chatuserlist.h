#ifndef CHATUSERLIST_H
#define CHATUSERLIST_H
#include <QListWidget>
#include <QWheelEvent>
#include <QEvent>
#include <QScrollBar>
#include <QDebug>

/******************************************************************************
 *
 * @file       chatuserlist.h
 * @brief      自定义的聊天对象列表
 *
 * @author     duya
 * @date       2025/07/31
 * @history
 *****************************************************************************/



class ChatUserList:public QListWidget
{
    Q_OBJECT
public:
    ChatUserList(QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject* watched , QEvent* event) override;
private:
    bool _load_pending;
signals:
    void sig_loading_chat_user();
};

#endif // CHATUSERLIST_H
