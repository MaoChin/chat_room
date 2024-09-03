#ifndef ADDFRINEDDIALOG_H
#define ADDFRINEDDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>

#include "model/data.h"

// 搜索到的好友结果中的一个好友项
class ResultFriendItem : public QWidget{
    Q_OBJECT
public:
    ResultFriendItem(const model::UserInfo& userInfo);


private:
    const model::UserInfo& _userInfo;
};

// 添加好友页面
class AddFrinedDialog : public QDialog
{
    Q_OBJECT
public:
    AddFrinedDialog(QWidget* parent);

    void addResultFriendItem(const model::UserInfo& userInfo);
    void clearResultFriendItem();

    // 修改搜索框中的内容
    void setSearchBarContent(const QString& searchKey);

private:
    // 搜索框
    QLineEdit* _searchBar;
    // 总的网格布局
    QGridLayout* _gridLayout;
    // 搜索结果的QWidget
    QWidget* _resultContainer;
};

#endif // ADDFRINEDDIALOG_H
