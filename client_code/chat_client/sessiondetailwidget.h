#ifndef SESSIONDETAILWIDGET_H
#define SESSIONDETAILWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QLabel>

#include "model/data.h"

// 详情页中头像+标签的组合
class HeadPortraitItem : public QWidget
{
    Q_OBJECT
public:
    HeadPortraitItem(const QIcon& headIcon, const QString& name);

    inline QPushButton* getHeadPortrait(){
        return _headProtrait;
    }

private:
    QPushButton* _headProtrait;
    QLabel* _nameLabel;

};

// 单聊会话详情页
class SessionDetailWidget : public QDialog
{
    Q_OBJECT
public:
    SessionDetailWidget(QWidget* parent, const model::UserInfo& friendInfo);

    // 删除好友的槽函数
    void clickDeleteFriendBtn();

private:
    // 会话中的好友信息
    model::UserInfo _friendInfo;

};

#endif // SESSIONDETAILWIDGET_H
