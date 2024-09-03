#ifndef GROUPSESSIONDETAILWIDGET_H
#define GROUPSESSIONDETAILWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QGridLayout>

class HeadPortraitItem;

class GroupSessionDetailWidget : public QDialog
{
    Q_OBJECT
public:
    GroupSessionDetailWidget(QWidget* parent);

    void addGroupMember(HeadPortraitItem* headPortraitItem);

private:
    QGridLayout* _gridLayout;

    // 表示 群成员Item 放置的位置
    int _curRow = 0;
    int _curCol = 1;
};

#endif // GROUPSESSIONDETAILWIDGET_H
