#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"
#include <QMap>

namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = nullptr);
    ~registerDialog();

signals:
    void sigSwitchLogin();

private slots:
    void on_getcodebut_clicked();
    void slot_reg_mod_finish(ReqType id, QString res, ErrorCodes err);

    void on_confirmbut_clicked();

    void on_returnbtn_clicked();

    void on_cancelbut_clicked();

private:
    Ui::registerDialog *ui;
    void showtip(QString text , bool b_ok);
    QMap<ReqType , std::function<void(const QJsonObject&)>> _handlers;
    void inithandler();
    QMap<TipErr, QString> _tip_errs;    //缓存各个输入框输入完成后提示的错误
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPassValid();
    bool checkVarifyValid();
    bool checkConfirmValid();
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    void ChangeTipPage();
    QTimer* _countdown_time;
    int _countdown;
};

#endif // REGISTERDIALOG_H
