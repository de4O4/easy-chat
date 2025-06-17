#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"
#include "resetdialog.h"
/******************************************************************************
 *
 * @file       mainwindow.h
 * @brief      主窗口
 *
 * @author     duya
 * @date       2025/05/22
 * @history
 *****************************************************************************/

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void SlotSwitchReg();               //定义槽函数，转到注册界面
    void SlotSwitchLogin();
    void SlotSwitchReset();             //切换至重置界面
    void SlotSwtichLogin2();            //从重置界面转为登录界面的槽函数

private:
    Ui::MainWindow *ui;
    loginDialog *login_dlg;
    registerDialog *regis_dlg;
    ResetDialog* reset_dlg;
};
#endif // MAINWINDOW_H
