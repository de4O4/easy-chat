#include "httpmgr.h"
#include <QNetworkReply>

httpMgr::~httpMgr()
{

}

void httpMgr::slot_http_finish(ReqType id, QString res, ErrorCodes err, Modules mod)
{
    if(mod == Modules::REGISTERMOD){     //发送信号通知指定模块http响应结束
        emit sig_reg_mod_finish(id, res, err);
    }
    if(mod == Modules::LOGINMOD){
        emit sig_login_mod_finish(id ,res , err);       //发送信号通知登录界面http响应结束
    }
    if(mod == Modules::RESETMOD){
        //发送信号通知指定模块http响应结束
        emit sig_reset_mod_finish(id, res, err);
    }
}

httpMgr::httpMgr() {
    connect(this , &httpMgr::sig_http_finish , this , &httpMgr::slot_http_finish);
}

void httpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqType req_id, Modules mod)
{
    QByteArray data = QJsonDocument(json).toJson();     //调用 toJson() 方法将JSON文档序列化为字节数组（QByteArray），作为HTTP请求的请求体（即POST需要发送的数据）
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader , "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader , QByteArray::number(data.length()));
    auto self = shared_from_this();     //在后续的异步操作（lambda表达式）中保持对当前对象的引用，防止对象在异步执行过程中被销毁
    QNetworkReply *reply = _manager.post(request , data);
    QObject::connect(reply , &QNetworkReply::finished , [reply ,self , req_id , mod](){     //当请求完成（无论成功或失败）时，finished 信号会被触发，执行lambda中的逻辑
        if(reply->error() != QNetworkReply::NoError){
            qDebug()<<reply->errorString();
            emit self->sig_http_finish(req_id , "" , ErrorCodes::ERR_NETWORK , mod);
            reply->deleteLater();
            return;
        }
        QString res = reply->readAll();
        emit self->sig_http_finish(req_id , res , ErrorCodes::SUCCESS , mod);
        reply->deleteLater();
        return;
    });
}
