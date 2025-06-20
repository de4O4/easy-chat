#include "chatdialog.h"
#include "ui_chatdialog.h"
#include "clickedbtn.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    ui->add_btn->SetState("normal","hover","press");

}

ChatDialog::~ChatDialog()
{
    delete ui;
}
