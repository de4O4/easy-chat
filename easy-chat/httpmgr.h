#ifndef HTTPMGR_H
#define HTTPMGR_H

#include "singleton.h"
#include "global.h"
#include <memory>


class httpMgr:public QObject,public SingteTon<httpMgr> ,public std::enable_shared_from_this<httpMgr>
{
    Q_OBJECT
public:
    ~httpMgr();
    void PostHttpReq(QUrl url , QJsonObject json , ReqType req_id , Modules mod);
private slots:
    void slot_http_finish(ReqType id, QString res, ErrorCodes err, Modules mod);

private:
    friend class SingteTon<httpMgr>;
    httpMgr();
    QNetworkAccessManager _manager;


signals:
    void sig_http_finish(ReqType id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqType id , QString res , ErrorCodes err);
    void sig_reset_mod_finish(ReqType id , QString res , ErrorCodes err);
    void sig_login_mod_finish(ReqType id , QString res , ErrorCodes err);
};

#endif // HTTPMGR_H
