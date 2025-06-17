#include "resetdialog.h"
#include "ui_resetdialog.h"
#include <QDebug>
#include <QRegularExpression>
#include "httpmgr.h"

ResetDialog::ResetDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ResetDialog)
{
    ui->setupUi(this);
    connect(ui->useredit , &QLineEdit::editingFinished , this , [this](){
        checkUserValid();
    });
    connect(ui->emailedit , &QLineEdit::editingFinished , this , [this](){
        checkEmailValid();
    });
    connect(ui->newpassedit , &QLineEdit::editingFinished , this , [this](){
        checkPassValid();
    });
    connect(ui->codeedit , &QLineEdit::editingFinished , this , [this](){
        checkVarifyValid();
    });
    initHandlers();
    connect(httpMgr::getintance().get() , &httpMgr::sig_reset_mod_finish , this , &ResetDialog::slot_reset_mod_finish);
}

ResetDialog::~ResetDialog()
{
    delete ui;
}

void ResetDialog::slot_reset_mod_finish(ReqType id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络错误！") , false);
        return;
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());      //解析 JSON 字符串,res需转化为QByteArray
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }
    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }
    //调用对应的逻辑,根据id回调。
    _handlers[id](jsonDoc.object());
    return;
}

bool ResetDialog::checkUserValid()
{
    if(ui->useredit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}
bool ResetDialog::checkPassValid()
{
    auto pass = ui->newpassedit->text();
    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }
    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }
    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}
bool ResetDialog::checkEmailValid()
{
    //验证邮箱的地址正则表达式
    auto email = ui->emailedit->text();
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
bool ResetDialog::checkVarifyValid()
{
    auto pass = ui->codeedit->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VARIFY_ERR, tr("验证码不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}
void ResetDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}
void ResetDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->errtip->clear();
        return;
    }
    showTip(_tip_errs.first(), false);
}

void ResetDialog::initHandlers()
{
    _handlers.insert(ReqType::ID_RESET_PWD , [this](QJsonObject json){          //注册重置密码回包逻辑
        int error = json["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = json["email"].toString();
        showTip(tr("重置成功,点击返回登录"), true);
        qDebug()<< "email is " << email ;
        qDebug()<< "user uuid is " <<  json["uuid"].toString();
    });
    _handlers.insert(ReqType::ID_GET_VARIFY_CODE ,[this](QJsonObject json){     //注册获取验证码回包逻辑
        int error = json["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }
        auto email = json["email"].toString();
        showTip(tr("验证码已发送到邮箱，注意查收"), true);
        qDebug()<< "email is " << email ;
    });
}

void ResetDialog::showTip(QString str, bool b_ok)
{
    if(b_ok){
        ui->errtip->setProperty("state","normal");
    }else{
        ui->errtip->setProperty("state","err");
    }
    ui->errtip->setText(str);
    repolish(ui->errtip);
}

void ResetDialog::on_confirmbtn_clicked()
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
    //发送http重置用户请求
    QJsonObject json_obj;
    json_obj["user"] = ui->useredit->text();
    json_obj["email"] = ui->emailedit->text();
    json_obj["passwd"] = ui->newpassedit->text();
    json_obj["varifycode"] = ui->codeedit->text();
    httpMgr::getintance()->PostHttpReq(QUrl(gate_url_prefix+"/reset_pwd"),
                                        json_obj, ReqType::ID_RESET_PWD,Modules::RESETMOD);
}




void ResetDialog::on_returnbtn_clicked()
{
    qDebug() << "sure btn clicked ";
    emit switchLogin();
}


void ResetDialog::on_getcodebtn_clicked()
{
    qDebug()<<"receive varify btn clicked ";
    auto email = ui->emailedit->text();
    auto bcheck = checkEmailValid();
    if(!bcheck){
        return;
    }

    //发送http请求获取验证码
    QJsonObject json_obj;
    json_obj["email"] = email;
    httpMgr::getintance()->PostHttpReq(QUrl(gate_url_prefix+"/get_varifycode"),
                                        json_obj, ReqType::ID_GET_VARIFY_CODE,Modules::RESETMOD);
}

