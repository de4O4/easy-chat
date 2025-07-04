#ifndef TEXTBUBBLE_H
#define TEXTBUBBLE_H

#include <QTextEdit>
#include <QHBoxLayout>
#include "bubbleframe.h"


class TextBubble : public BubbleFrame
{
    Q_OBJECT
public:
    TextBubble(ChatRole role, const QString &text, QWidget *parent = nullptr);
protected:
    bool eventFilter(QObject *o, QEvent *e);
private:
    void adjustTextHeight();
    void setPlainText(const QString &text);
    void initStyleSheet();
    QString wrapTextToFitWidth(const QString& text , int maxwidth);
private:
    QTextEdit *m_pTextEdit;
    QString m_text;
};

#endif // TEXTBUBBLE_H
