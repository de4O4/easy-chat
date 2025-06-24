#include "textbubble.h"
#include <QTextBlock>
#include <QTimer>
#include <QtGlobal>

TextBubble::TextBubble(ChatRole role, const QString &text, QWidget *parent):BubbleFrame(role , parent),m_text(text)
{
    m_pTextEdit = new QTextEdit();
    m_pTextEdit->setReadOnly(true);
    m_pTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pTextEdit->installEventFilter(this);
   // m_pTextEdit->setWordWrapMode(QTextOption::NoWrap);

    QFont font("Microsoft YaHei");
    font.setPointSize(12);
    m_pTextEdit->setFont(font);
    setPlainText(text);
    setWidget(m_pTextEdit);
    initStyleSheet();

    // QTimer::singleShot(0 , this , [this](){
    //     if(this->parentWidget()){
    //         int maxwidth = this->parentWidget()->width() * 0.6;
    //         setPlainText(m_text , maxwidth);
    //     }else{
    //         setPlainText(m_text , 300);
    //     }
    // });
}


bool TextBubble::eventFilter(QObject *o, QEvent *e)
{
    if(m_pTextEdit == o && e->type() == QEvent::Paint){
        adjustTextHeight();
        // int maxwidth = this->parentWidget()->width() * 0.6;
        // setPlainText(m_text , maxwidth);
    }
    return BubbleFrame::eventFilter(o , e);
}

void TextBubble::adjustTextHeight()
{
    qreal doc_margin = m_pTextEdit->document()->documentMargin();
    QTextDocument* doc = m_pTextEdit->document();
    qreal text_height = 0;
    for (QTextBlock it = doc->begin(); it != doc->end(); it = it.next())
    {
        QTextLayout *pLayout = it.layout();
        QRectF text_rect = pLayout->boundingRect();                             //这段的rect
        text_height += text_rect.height();
    }
    int vMargin = this->layout()->contentsMargins().top();
    //设置这个气泡需要的高度 文本高+文本边距+TextEdit边框到气泡边框的距离
    setFixedHeight(text_height + doc_margin *2 + vMargin*2 );
}

void TextBubble::setPlainText(const QString &text)
{
   // QString wrappedtext = wrapTextToFitWidth(text , maxwidth);
    m_pTextEdit->setPlainText(text);
    qreal doc_margin = m_pTextEdit->document()->documentMargin();       // 文本编辑器文档的内边距
    int margin_left = this->layout()->contentsMargins().left();     // 当前气泡控件布局的左外边距
    int margin_right = this->layout()->contentsMargins().right();       // 当前气泡控件布局的右外边距
    QFontMetricsF fm(m_pTextEdit->font());      // 基于文本编辑器的字体，创建字体度量工具（用于测量文本宽度）
    QTextDocument* doc = m_pTextEdit->document();        // 获取文本编辑器的文档对象（包含所有文本内容）
    int max_width = 0;

    for(QTextBlock it = doc->begin() ; it != doc->end(); it = it.next()){
        int tetw = int(fm.horizontalAdvance(it.text()));
        max_width = qMax(max_width , tetw);
    }

    //setFixedHeight(maxwidth + doc_margin*2 + (margin_left + margin_right));
    setMaximumWidth(max_width + doc_margin*2 + (margin_left+margin_right));
}

void TextBubble::initStyleSheet()
{
    m_pTextEdit->setStyleSheet("QTextEdit{background:transparent;border:none}");
}

QString TextBubble::wrapTextToFitWidth(const QString &text, int maxwidth)
{
    QFontMetricsF metrics(m_pTextEdit->font());
    QString result;
    QStringList lines = text.split('\n');

    for(const QString& line : lines ){
        QString currline;
        for(int i=0 ; i< line.length();i++){
            currline.append(line[1]);
            if(metrics.horizontalAdvance(currline) > maxwidth){
                currline.chop(1);
                result.append(currline + '\n');
                currline = line[1];
            }
        }
        result.append(currline + '\n');
    }
    return result.trimmed();
}
