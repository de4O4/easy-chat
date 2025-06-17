#ifndef RESETDIALOG_H
#define RESETDIALOG_H

#include <QDialog>
#include "global.h"
#include <QMap>

namespace Ui {
class ResetDialog;
}

class ResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResetDialog(QWidget *parent = nullptr);
    ~ResetDialog();
private slots:
    void slot_reset_mod_finish(ReqType id, QString res, ErrorCodes err);
    void on_confirmbtn_clicked();
    void on_returnbtn_clicked();

    void on_getcodebtn_clicked();

private:
    bool checkUserValid();
    bool checkPassValid();
    void showTip(QString str,bool b_ok);
    bool checkEmailValid();
    bool checkVarifyValid();
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    void initHandlers();
    QMap<TipErr, QString> _tip_errs;
    QMap<ReqType, std::function<void(const QJsonObject&)>> _handlers;
    Ui::ResetDialog *ui;
signals:
    void switchLogin();
};

#endif // RESETDIALOG_H
