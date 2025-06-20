#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"tcpmgr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login_dlg = new loginDialog(this);
    login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(login_dlg);
    connect(login_dlg , &loginDialog::swtichregis , this , &MainWindow::SlotSwitchReg);
    connect(login_dlg , &loginDialog::switchReset , this , &MainWindow::SlotSwitchReset);
    //connect(reset_dlg , &ResetDialog::switchLogin , this , &MainWindow::SlotSwtichLogin2);


    connect(TcpMgr::getintance().get() , &TcpMgr::sig_swich_chatdlg , this , &MainWindow::SlotSwitchChat);
    emit TcpMgr::getintance()->sig_swich_chatdlg();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::SlotSwitchReg()
{
    regis_dlg = new registerDialog(this);
    regis_dlg->hide();
    regis_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(regis_dlg, &registerDialog::sigSwitchLogin, this, &MainWindow::SlotSwitchLogin);
    setCentralWidget(regis_dlg);
    login_dlg->hide();
    regis_dlg->show();

}

void MainWindow::SlotSwitchLogin()
{
    login_dlg = new loginDialog(this);
    login_dlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(login_dlg);
    regis_dlg->hide();
    login_dlg->show();
    connect(login_dlg , &loginDialog::swtichregis , this , &MainWindow::SlotSwitchReg);
    connect(login_dlg , &loginDialog::switchReset , this , &MainWindow::SlotSwitchReset);
}

void MainWindow::SlotSwitchReset()
{
    reset_dlg = new ResetDialog(this);
    reset_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(reset_dlg);
    login_dlg->hide();
    reset_dlg->show();
    connect(reset_dlg , &ResetDialog::switchLogin ,this, &MainWindow::SlotSwtichLogin2);
}

void MainWindow::SlotSwtichLogin2()
{
    login_dlg = new loginDialog(this);
    login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(login_dlg);
    reset_dlg->hide();
    login_dlg->show();
    connect(login_dlg , &loginDialog::swtichregis , this , &MainWindow::SlotSwitchReg);
    connect(login_dlg , &loginDialog::switchReset , this , &MainWindow::SlotSwitchReset);
}

void MainWindow::SlotSwitchChat()
{
    chat_dlg = new ChatDialog(this);
    chat_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(chat_dlg);
    login_dlg->hide();
    chat_dlg->show();
    this->setMinimumSize(QSize(800,650));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}

