#ifndef TCPMGR_H
#define TCPMGR_H
#include "global.h"
#include <QAbstractSocket>
#include <QTcpSocket>
#include "singleton.h"



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
signals:
    void sig_conn_success(bool bsueccess);
    void sig_send_data(ReqType reqid, QString data);
public slots:
    void slot_tcp_connect(ServerInfo si);
    void slot_send_data(ReqType reqid, QString data);
};

#endif // TCPMGR_H
