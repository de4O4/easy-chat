#ifndef TCPMGR_H
#define TCPMGR_H
#include "global.h"
#include <QAbstractSocket>
#include <QTcpSocket>
#include "singleton.h"
#include <QMap>
#include "userdata.h"

class TcpMgr:public QObject,public::SingteTon<TcpMgr>,public std::enable_shared_from_this<TcpMgr>
{
        friend class SingteTon<TcpMgr>;
    Q_OBJECT
public:
    TcpMgr();
private:
    QString _host;
    QTcpSocket _socket;
    uint16_t _port;
    bool b_recv_pending;
    QByteArray _buffer;
    quint16 _message_id;
    quint16 _message_len;
    void handleMsg(ReqType id, int len, QByteArray data);
    void initHandlers();
    QMap<ReqType, std::function<void(ReqType id, int len, QByteArray data)>> _handlers;
signals:
    void sig_conn_success(bool bsueccess);
    void sig_send_data(ReqType reqid, QString data);
    void sig_login_failed(int err);
    void sig_swich_chatdlg();
    void sig_user_search(std::shared_ptr<SearchInfo> si);
    void sig_friend_apply(std::shared_ptr<AddFriendApply>);
    void sig_add_auth_friend(std::shared_ptr<AuthInfo>);
    void sig_auth_rsp(std::shared_ptr<AuthRsp>);
public slots:
    void slot_tcp_connect(ServerInfo si);
    void slot_send_data(ReqType reqid, QString data);
};

#endif // TCPMGR_H
