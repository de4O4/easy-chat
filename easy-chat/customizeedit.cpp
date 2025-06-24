#include "customizeedit.h"



CustomizeEdit::CustomizeEdit(QWidget *parent):QLineEdit(parent),max_len(0)
{
    connect(this , &QLineEdit::textChanged , this , &CustomizeEdit::LimitTextMaxlength);
}

void CustomizeEdit::SetMaxLength(int maxlen)
{
    max_len = maxlen;
}
