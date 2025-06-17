#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "httpmgr.h"

registerDialog::registerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registerDialog) , _countdown(5)
{
    ui->setupUi(this);
    ui->passedit->setEchoMode(QLineEdit::Password);
    ui->confirmedit->setEchoMode(QLineEdit::Password);
    ui->errtip->setProperty("state","normal");
    repolish(ui->errtip);
    connect(httpMgr::getintance().get() , &httpMgr::sig_reg_mod_finish , this , &registerDialog::slot_reg_mod_finish);
    inithandler();

    ui->errtip->clear();
    connect(ui->useredit , &QLineEdit::editingFinished , this , [this](){
        checkUserValid();
    });
    connect(ui->emailline , &QLineEdit::editingFinished , this , [this](){
        checkEmailValid();
    });
    connect(ui->passedit , &QLineEdit::editingFinished , this , [this](){
        checkPassValid();
    });
    connect(ui->confirmedit , &QLineEdit::editingFinished ,this , [this](){
        checkConfirmValid();
    });
    connect(ui->varifyedit , &QLineEdit::editingFinished , this , [this](){
        checkVarifyValid();
    });

    ui->pass_visible->setCursor(Qt::PointingHandCursor);
    ui->confirm_visible->setCursor(Qt::PointingHandCursor);      //设置当鼠标放上标签的时候游标变为手
    ui->pass_visible->SetState("unvisible","unvisible_hover","","visible",
                               "visible_hover","");
    ui->confirm_visible->SetState("unvisible","unvisible_hover","","visible",
                                  "visible_hover","");

    connect(ui->pass_visible , &ClickedLabel::clicked , this , [this](){
        auto state = ui->pass_visible->GetCurState();
        if(state == ClickLbState::Normal){
            ui->passedit->setEchoMode(QLineEdit::Password);         //将密码隐藏
        }else{
            ui->passedit->setEchoMode(QLineEdit::Normal);           //将密码显示
        }
    });
    connect(ui->confirm_visible , &ClickedLabel::clicked , this , [this](){
        auto state = ui->pass_visible->GetCurState();
        if(state == ClickLbState::Normal){
            ui->confirmedit->setEchoMode(QLineEdit::Password);         //将密码隐藏
        }else{
            ui->confirmedit->setEchoMode(QLineEdit::Normal);           //将密码显示
        }
    });

    _countdown_time = new QTimer(this);
    connect(_countdown_time , &QTimer::timeout , [this](){              //连接返回登录界面的信号
        if(_countdown == 0){
            _countdown_time->stop();
            emit sigSwitchLogin();
            return;
        }
        _countdown--;
        auto str = QString("注册成功 ， %1S 后返回！").arg(_countdown);
        ui->tiplab->setText(str);
    });
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_getcodebut_clicked()
{
    auto email = ui->emailline->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match){
        QJsonObject json_obj;
        json_obj["email"] = email;
       // qDebug()<<gate_url_prefix;
        httpMgr::getintance()->PostHttpReq(QUrl(gate_url_prefix + "/get_varifycode") , json_obj , ReqType::ID_GET_VARIFY_CODE , Modules::REGISTERMOD);
    }else{
        showtip(tr("邮箱格式不正确！") , false);
    }
}

void registerDialog::slot_reg_mod_finish(ReqType id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showtip(tr("网络请求错误") , false);
        return;
    }
    QJsonDocument jsondoc = QJsonDocument::fromJson(res.toUtf8());  // 解析 JSON 字符串,res需转化为QByteArray
    if(jsondoc.isNull()){
        showtip(tr("json解析失败"),false);
        return;
    }
    if(!jsondoc.isObject()){
        showtip(tr("json解析错误") , false);
        return;
    }
    QJsonObject jsonObj = jsondoc.object();

    _handlers[id](jsondoc.object());
    return;
}

void registerDialog::showtip(QString text, bool b_ok)
    {
        if(b_ok){
            ui->errtip->setProperty("state" , "normal");
        }else {
            ui->errtip->setProperty("state" , "err");
        }
        ui->errtip->setText(text);
        repolish(ui->errtip);
    }

 void registerDialog::inithandler()
 {
     _handlers.insert(ReqType::ID_GET_VARIFY_CODE , [this](QJsonObject jsonobj){
         int error = jsonobj["error"].toInt();
         if(error != ErrorCodes::SUCCESS){
             showtip(tr("参数错误"),false);
             return;
         }
         auto email = jsonobj["email"].toString();
         showtip(tr("验证码以发至邮箱，请查收") , true);
         qDebug()<<"email is "<<email;
     });

     _handlers.insert(ReqType::ID_REG_USER , [this](QJsonObject jsonobj){           //完成注册完成回调函数
         int error = jsonobj["error"].toInt();
         if(error != ErrorCodes::SUCCESS){
             showtip(tr("参数错误"),false);
             return;
         }
         auto email = jsonobj["email"].toString();
         showtip(tr("用户注册成功！") , true);
         ChangeTipPage();
     });
 }

 bool registerDialog::checkUserValid()
 {
     if(ui->useredit->text() == ""){            //用户名为空
         AddTipErr(TipErr::TIP_USER_ERR , tr("用户名不能为空！"));
         return false;
     }
     DelTipErr(TipErr::TIP_USER_ERR);
     return true;
 }

 bool registerDialog::checkEmailValid()
 {
     auto email = ui->emailline->text();
     // 邮箱地址的正则表达式
     QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
     bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
     if(!match){
         //提示邮箱不正确
         AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
         return false;
     }
     DelTipErr(TipErr::TIP_EMAIL_ERR);
     return true;
 }

 bool registerDialog::checkPassValid()
 {
     auto pass = ui->passedit->text();
     if(pass.length() < 6 || pass.length() > 15){
         AddTipErr(TipErr::TIP_PWD_ERR , tr("密码长度需为6-15位"));
         return false;
     }
     QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");           //密码长度至少6，可以是字母、数字和特定的特殊字符
     bool match = regExp.match(pass).hasMatch();
     if(!match){
         AddTipErr(TipErr::TIP_PWD_ERR , tr("不能包含非法字符"));
             return false;
     }
     DelTipErr(TipErr::TIP_PWD_ERR);
     return true;
 }

 bool registerDialog::checkVarifyValid()
 {
     auto pass = ui->varifyedit->text();
     if(pass.isEmpty()){
         AddTipErr(TipErr::TIP_VARIFY_ERR, tr("验证码不能为空"));
         return false;
     }

     DelTipErr(TipErr::TIP_VARIFY_ERR);
     return true;
 }

 bool registerDialog::checkConfirmValid()
 {
     auto pass = ui->passedit->text();
     auto confirm = ui->confirmedit->text();

     if(confirm.length() < 6 || confirm.length() > 15 ){
         //提示长度不准确
         AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("密码长度应为6~15"));
         return false;
     }


     // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
     QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*.]{6,15}$");
     bool match = regExp.match(confirm).hasMatch();
     if(!match){
         //提示字符非法
         AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("不能包含非法字符"));
         return false;
     }

     DelTipErr(TipErr::TIP_CONFIRM_ERR);

     if(pass != confirm){
         //提示密码不匹配
         AddTipErr(TipErr::TIP_PWD_CONFIRM, tr("确认密码和密码不匹配"));
         return false;
     }else{
         DelTipErr(TipErr::TIP_PWD_CONFIRM);
     }
     return true;
 }

 void registerDialog::AddTipErr(TipErr te, QString tips)
 {
     _tip_errs[te] = tips;
     showtip(tips,false);
 }

 void registerDialog::DelTipErr(TipErr te)
 {
     _tip_errs.remove(te);
     if(_tip_errs.empty()){
         ui->errtip->clear();
         return;
     }
     showtip(_tip_errs.first() , false);
 }

 void registerDialog::ChangeTipPage()
 {
     _countdown_time->stop();
     ui->stackedWidget->setCurrentWidget(ui->page_2);
     _countdown_time->start(1000);
 }


 void registerDialog::on_confirmbut_clicked()
 {
     bool valid = checkUserValid();
     if(!valid){
         return;
     }
     valid = checkEmailValid();
     if(!valid){
         return;
     }
     valid = checkPassValid();
     if(!valid){
         return;
     }
     valid = checkVarifyValid();
     if(!valid){
         return;
     }

     QJsonObject json_obj;
     json_obj["user"] = ui->useredit->text();
     json_obj["email"] = ui->emailline->text();
     json_obj["passwd"] = ui->passedit->text();
     json_obj["confirm"] = ui->confirmedit->text();
     json_obj["varifycode"] = ui->varifyedit->text();
     httpMgr::getintance()->PostHttpReq(QUrl(gate_url_prefix+"/user_register"),
                                         json_obj, ReqType::ID_REG_USER,Modules::REGISTERMOD);
 }


 void registerDialog::on_returnbtn_clicked()
 {
     _countdown_time->stop();
     emit sigSwitchLogin();
 }


 void registerDialog::on_cancelbut_clicked()
 {
     _countdown_time->stop();
     emit sigSwitchLogin();
 }

