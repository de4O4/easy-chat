#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile qss(":/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug()<<"打开成功！";
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug()<<"打卡失败！";
    }
    QString app_path = QCoreApplication::applicationDirPath();      //获取当前项目路径
    QString filename = "config.ini";
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + filename);         //拼接为配置文件的路径
    QSettings settings(config_path , QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;

    w.show();
    return a.exec();
}
