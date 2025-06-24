#ifndef CUSTOMIZEEDIT_H
#define CUSTOMIZEEDIT_H

#include <QLineEdit>
#include <QDebug>
#include <QFocusEvent>
#include <QByteArray>

class CustomizeEdit : public QLineEdit
{
    Q_OBJECT
public:
    CustomizeEdit(QWidget *parent = nullptr);
    void SetMaxLength(int maxlen);
protected:
    void focusOutEvent(QFocusEvent *event) override{        // 执行失去焦点时的处理逻辑
        QLineEdit::focusOutEvent(event);
        emit sig_focus_out();
    }
signals:
    void sig_focus_out();
private:
    void LimitTextMaxlength(QString text){
        if(max_len <= 0){           //对输入长度无限制
            return;
        }
        QByteArray data = text.toUtf8();
        if(data.size() > max_len){
            data = data.left(max_len);          //截取为最大长度
            this->setText(QString::fromUtf8(data));
        }
    }
    int max_len;
};
#endif // CUSTOMIZEEDIT_H
