#ifndef GROUPSESSIONDETAILWIDGET_H
#define GROUPSESSIONDETAILWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class HeadPortraitItem;

class GroupSessionDetailWidget : public QDialog
{
    Q_OBJECT
public:
    GroupSessionDetailWidget(QWidget* parent);

    void initData();
    // 获取群聊会话成员列表请求完成的槽函数
    void initGroupSessionMember();
    void addGroupMember(HeadPortraitItem* headPortraitItem);

private:
    QGridLayout* _gridLayout;

    // 群聊名称label
    QLabel* _realGroupSessionName;

    // 表示 群成员Item 放置的位置
    int _curRow = 0;
    int _curCol = 1;
};

#endif // GROUPSESSIONDETAILWIDGET_H
