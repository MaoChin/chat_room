#ifndef USERINFOWIDGET_H
#define USERINFOWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

#include "model/data.h"

class UserInfoWidget : public QDialog
{
    Q_OBJECT
public:
    UserInfoWidget(QWidget* parent, const model::UserInfo& userInfo);

private:
    // 头像
    QPushButton* _headPortrait;
    // id相关
    QLabel* _idTag;
    QLabel* _idLabel;
    // 昵称相关
    QLabel* _nickNameTag;
    QLabel* _nickNameLabel;
    // 电话相关
    QLabel* _phoneNumTag;
    QLabel* _phoneNumLabel;

    // 申请好友
    QPushButton* _applyFriendBtn;
    // 发送消息
    QPushButton* _sendMessageBtn;
    // 删除好友
    QPushButton* _deleteFriendBtn;



    const model::UserInfo& _userInfo;
};

#endif // USERINFOWIDGET_H
