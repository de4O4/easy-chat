#ifndef APPLYFRIEND_H
#define APPLYFRIEND_H
#include "clickedlabel.h"
#include "userdata.h"
#include <QDialog>
#include <QPoint>
#include <QMap>
#include "friendlabel.h"

namespace Ui {
class ApplyFriend;
}

class ApplyFriend : public QDialog
{
    Q_OBJECT

public:
    explicit ApplyFriend(QWidget *parent = nullptr);
    ~ApplyFriend();
    void InitTipLbs();
    void AddTipLbs(ClickedLabel* , QPoint cur_point , QPoint& next_point , int text_width , int text_height);
    bool eventFilter(QObject* obj , QEvent* event) ;
    void SetSearchInfo(std::shared_ptr<SearchInfo> si);
private:
    Ui::ApplyFriend* ui;
    void resetLabels();
    QMap<QString , ClickedLabel*> _add_labels;      //已经创建好的标签
    std::vector<QString> _add_label_keys;
    QPoint _label_point;
    QMap<QString , FriendLabel*> _friend_labels;        //用来在输入框显示添加新好友的标签
    std::vector<QString> _friend_label_keys;
    void addLabel(QString name);
    std::vector<QString> _tip_data;
    QPoint _tip_cur_point;
    std::shared_ptr<SearchInfo> _si;
public slots:
    void ShowMoreLabel();       //用于显示更多标签
    void SlotLabelEnter();      //输入label后按下回车触发将标签加入展示栏
    void SLotRemoveFriendLabel(QString);        //点击关闭，移除展示栏好友标签
    void SlotChangeFriendLabelByTip(QString , ClickLbState);        //通过点击label实现增加和减少好友标签
    void SlotLabelTextChange(const QString& text);      //输入框文本变化显示不同提示
    void SlotLabelEditFinished();           //输入框完成输入
    void SlotAddFriendLabelByClickTip(QString text);        //输入框显示提示框，点击提示框内容后添加好友标签
    void SlotApplySure();       //处理确认回调
    void SlotApplyCancel();     //处理取消回调
};

#endif // APPLYFRIEND_H
