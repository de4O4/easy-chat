#include "findsuccessdlg.h"
#include "ui_findsuccessdlg.h"
#include <QDir>
#include <QPixmap>

FindSuccessDlg::~FindSuccessDlg()
{
    qDebug()<<"FindSuccessDlg destruct";
    delete ui;
}

void FindSuccessDlg::SetSearchInfo(std::shared_ptr<SearchInfo> si)
{
    _si = si;
    ui->name_lb->setText(si->_name);
}

FindSuccessDlg::FindSuccessDlg(QWidget *parent):QDialog(parent),ui(new Ui::FindSuccessDlg)
{
    ui->setupUi(this);
    setWindowTitle("添加");
    setWindowFlags(Qt::FramelessWindowHint | windowFlags() );
    QString app_path = QCoreApplication::applicationDirPath();      //当前路径
    QString pix_path = QDir::toNativeSeparators(app_path +
                                                QDir::separator() + "static"+QDir::separator()+"head_1.jpg");
    QPixmap head_pix(pix_path);
    head_pix = head_pix.scaled(ui->head_lb->size() , Qt::KeepAspectRatio , Qt::SmoothTransformation);
    ui->head_lb->setPixmap(head_pix);
    ui->add_friend_btn->SetState("normal","hover","press");
    this->setModal(true);
}

void FindSuccessDlg::on_add_friend_btn_clicked()
{

}

