#include "tcpmgr.h"
#include <QDataStream>

TcpMgr::TcpMgr():_host(""),_port(0),b_recv_pending(false),_message_id(0),_message_len(0)
{
    QObject::connect(&_socket , &QTcpSocket::connected , [&](){
        qDebug()<<"连接成功！";
        emit sig_conn_success(true);
    });

    QObject::connect(&_socket , &QTcpSocket::readyRead , [&]{
        _buffer.append(_socket.readAll());
        QDataStream stream(&_buffer , QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_6_9);
        forever{
            if(b_recv_pending){
                if(_buffer.size() < static_cast<int>(sizeof(quint16) * 2));         //收到的数据未达到消息头大小
                return;
            }
            stream<<_message_id<<_message_len;
            _buffer = _buffer.mid(sizeof(quint16) * 2);           //将buffer的前4个字节截取掉，留下后面的字节
            qDebug()<<"message id is :"<<_message_id<<"  message len is :"<<_message_len;
        }
        if(_buffer.size() < _message_len){          //消息体长度小于发送长度
            b_recv_pending = true;
            return;             //继续接受消息
        }
        b_recv_pending = false;
        QByteArray messagebody = _buffer.mid(0 , _message_len);         //将buffer的前message_len字节赋值给messagebody
        qDebug()<<"message is :"<<messagebody;
        _buffer = _buffer.mid(_message_len);                            //将bufferd的前_message_len字节截取，只留下后面的字节
    });

    QObject::connect(&_socket,                  //捕捉连接时的错误
                     qOverload<QAbstractSocket::SocketError>(&QTcpSocket::errorOccurred),
                     [&](QAbstractSocket::SocketError socketError) {
                         qDebug() << "Socket Error Code:" << socketError;
                         qDebug() << "Error Description:" << _socket.errorString();

                         // 根据错误类型进行处理
                         switch(socketError) {
                         case QAbstractSocket::ConnectionRefusedError:
                             qDebug() << "Connection refused";
                             break;
                         case QAbstractSocket::RemoteHostClosedError:
                             qDebug() << "Remote host closed connection";
                             break;
                         case QAbstractSocket::HostNotFoundError:
                             qDebug() << "Host not found";
                             break;
                         default:
                             qDebug() << "Other socket error";
                             break;
                         }
                     });

    QObject::connect(&_socket , &QTcpSocket::disconnected , [&](){
        qDebug()<<"server disconnection!";
    });

    QObject::connect(this , &TcpMgr::sig_send_data , this , &TcpMgr::slot_send_data);
}

void TcpMgr::slot_tcp_connect(ServerInfo si)
{
    qDebug()<<"进行连接服务器中！";
    _host = si.Host;
    _port = static_cast<uint16_t>(si.Port.toUInt());
    _socket.connectToHost(_host , _port);           //连接聊天服务器
}

void TcpMgr::slot_send_data(ReqType reqid, QString data)
{
    uint16_t id = reqid;
    QByteArray databytes = data.toUtf8();       //转换为字符串数组
    quint16 len = static_cast<quint16>(databytes.size());
    QByteArray block;
    QDataStream out(&block , QIODevice::WriteOnly);
    out<<id<<len;       //将发送长度，与类型写入数组中
    block.append(databytes);
    _socket.write(block);
}


