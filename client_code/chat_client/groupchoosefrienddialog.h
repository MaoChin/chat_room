#ifndef GROUPCHOOSEFRIENDDIALOG_H
#define GROUPCHOOSEFRIENDDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>

// 选择好友窗口中的一个好友项
class GroupFriendItem : public QWidget{
    Q_OBJECT
public:
    GroupFriendItem(QWidget* owner, const QString& userId, const QIcon& headPortraitIcon, const QString& nickName, bool checked);

    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

    inline const QString& getUserId(){
        return _userId;
    }
    inline QCheckBox* getCheckBox(){
        return _checkBox;
    }

private:
    QCheckBox* _checkBox;
    QPushButton* _headProtrait;
    QLabel* _nickName;
    QString _userId = "";

    // 记录 QWidget，其类型是 GroupChooseFriendDialog
    QWidget* _owner;

    // 用于判断鼠标是否进入该区域
    bool _isHover = false;
};

// 创建群聊选择好友窗口
class GroupChooseFriendDialog : public QDialog
{
    Q_OBJECT
public:
    GroupChooseFriendDialog(QWidget* parent);

    void initLeftWidget(QHBoxLayout* layout);
    void initRightWidget(QHBoxLayout* layout);

    void addFriendItem(const QString& userId, const QIcon &headPortraitIcon, const QString &nickName, bool checked);
    void addSelectedFriendItem(const QString& userId, const QIcon &headPortraitIcon, const QString &nickName);
    // 根据userId删除
    void deleteSelectedFriendItem(const QString& userId);

private:
    // 左侧列出全部好友
    QWidget* _totalFirend;
    // 右侧列出选中的好友
    QWidget* _selectedFriend;
};

#endif // GROUPCHOOSEFRIENDDIALOG_H
