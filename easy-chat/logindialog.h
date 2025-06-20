#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"
#include "httpmgr.h"
#include "tcpmgr.h"
#include <QUrl>
namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();
  //  bool checkUserValid();
    bool checkEmailValid();
    bool checkPwdValid();
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    int _uid;
    QString _token;
private:
    Ui::loginDialog *ui;
    QMap<TipErr, QString> _tip_errs;
    QMap<ReqType, std::function<void(const QJsonObject&)>> _handlers;
    void initHttpHandlers();
    void showTip(QString str,bool b_ok);

signals:
    void swtichregis();
    void switchReset();
    void sig_connect_tcp(ServerInfo);

private slots:
    void on_loginbutton_clicked();
    void slot_forget_pwd();
    void slot_login_mod_finish(ReqType id, QString res, ErrorCodes err);
    void slot_tcp_con_finish(bool bsuccess);
    void slot_login_failed(int err);
};

#endif // LOGINDIALOG_H
