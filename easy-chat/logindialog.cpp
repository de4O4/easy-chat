#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    ui->forgetlabel->setCursor(QCursor(Qt::PointingHandCursor));
   // ui->forgetlabel->SetState("normal","hover","","selected","selected_hover","")
    connect(ui->regitbutton ,&QPushButton::clicked, this , &loginDialog::swtichregis);      //当在登录界面点击注册时将发出信号，告诉登录界面该转为注册界面
    connect(ui->forgetlabel, &ClickedLabel::clicked, this, &loginDialog::slot_forget_pwd);      //将忘记密码绑定槽函数
    initHttpHandlers();
    connect(httpMgr::getintance().get() , &httpMgr::sig_login_mod_finish , this , &loginDialog::slot_login_mod_finish);
    connect(this , &loginDialog::sig_connect_tcp , TcpMgr::getintance().get() , &TcpMgr::slot_tcp_connect);
    connect(TcpMgr::getintance().get() , &TcpMgr::sig_conn_success , this , &loginDialog::slot_tcp_con_finish);
    ui->passedit->setEchoMode(QLineEdit::Password);
}

loginDialog::~loginDialog()
{
    delete ui;
}

bool loginDialog::checkEmailValid()
{
    auto email = ui->emailedit->text();
    if(email.isEmpty()){
        qDebug() << "email empty " ;
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱不能为空"));
        return false;
    }

    return true;
}

bool loginDialog::checkPwdValid()
{
    auto pwd = ui->passedit->text();
    if(pwd.isEmpty()){
        qDebug() << "pass empty " ;
        AddTipErr(TipErr::TIP_PWD_ERR , tr("密码不能为空"));
        return false;
    }
    return true;
}

void loginDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void loginDialog::initHttpHandlers()
{
    _handlers.insert(ReqType::ID_LOGIN_USER , [this](QJsonObject json){
        int error = json["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = json["email"].toString();
        ServerInfo si;
        si.Uid = json["uid"].toInt();
        si.Host = json["host"].toString();
        si.Port = json["port"].toString();
        si.Token = json["token"].toString();

        _uid = si.Uid;
        _token = si.Token;
        qDebug()<< "email is " << email << " uid is " << si.Uid <<" host is "
                 << si.Host << " Port is " << si.Port << " Token is " << si.Token;
        emit sig_connect_tcp(si);           //路由服务器返回的聊天服务器信息，发送信号，连接聊天服务器
    });
}

void loginDialog::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->errtip->setProperty("state","normal");
    }else{
        ui->errtip->setProperty("state","err");
    }

    ui->errtip->setText(str);

    repolish(ui->errtip);
}

void loginDialog::slot_forget_pwd()
{
    qDebug()<<"slot forget pwd";
    emit switchReset();

}

void loginDialog::slot_login_mod_finish(ReqType id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误！") , false);
    }
    QJsonDocument json = QJsonDocument::fromJson(res.toUtf8());
    if(json.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }
    if(!json.isObject()){
        showTip(tr("json解析失败"),false);
        return;
    }
    _handlers[id](json.object());
    return;
}

void loginDialog::slot_tcp_con_finish(bool bsuccess)                //聊天服务器连接后，登陆界面执行的槽函数
{
    if(bsuccess){
        showTip(tr("连接服务器成功！") , true);
        QJsonObject jsonobj;
        jsonobj["uid"] = _uid;
        jsonobj["token"] = _token;
        QJsonDocument doc(jsonobj);     //将qjsonobj类型先转换为qjsondocument类型
        QString jsonstr = doc.toJson(QJsonDocument::Indented);      //在将qjsonducument类型转为qstring类型
        emit TcpMgr::getintance()->sig_send_data(ReqType::ID_CHAT_LOGIN , jsonstr);

    }else{
        showTip(tr("网络错误！") , false);
    }
}

void loginDialog::on_loginbutton_clicked()
{
    qDebug()<<"loginbtn clicked";
    auto email = ui->emailedit->text();
    auto pwd = ui->passedit->text();

    if(checkEmailValid() == false){
        return;
    }
    if(checkPwdValid() == false){
        return;
    }
    QJsonObject json;
    json["email"] = email;
    json["passwd"] = pwd;
    httpMgr::getintance()->PostHttpReq(QUrl(gate_url_prefix+"/user_login") , json, ReqType::ID_LOGIN_USER , Modules::LOGINMOD);         //发送post请求
}


