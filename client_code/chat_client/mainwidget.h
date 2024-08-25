#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

// 主窗口
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    ~MainWidget();

    static MainWidget* getInstance();


private:
    // 构造函数私有化
    MainWidget(QWidget *parent = nullptr);

    void initMainWindow();
    void initLeftWindow();
    void initMiddleWindow();
    void initRightWindow();
    void initSignalSlot();


    void switchTabToChatSession();
    void switchTabToFriend();
    void switchTabToFriendApply();


    void loadChatSessionTab();
    void loadFriendTab();
    void loadFriendApplyTab();


private:
    // 搞成单例
    static MainWidget* _instance;

    Ui::MainWidget *ui;

    // 窗口中的各个子窗口
    QWidget* _windowLeft;
    QWidget* _windowMiddle;
    QWidget* _windowRight;

    // 用户头像按钮
    QPushButton* _userHeadPortraitBtn;
    // 会话标签页按钮
    QPushButton* _chatSessionTabBtn;
    // 好友标签页按钮
    QPushButton* _friendTabBtn;
    // 好友申请标签页按钮
    QPushButton* _friendApplyTabBtn;

    // 搜索框
    QLineEdit* _searchBar;
    // 添加好友按钮
    QPushButton* _addFriendBtn;


    // 选中标签页
    enum ActiveTab{
        CHATSESSION_TAB,
        FRIEND_TAB,
        FRIENDAPPLY_TAB
    };
    ActiveTab _activeTab = CHATSESSION_TAB;

};
#endif // MAINWIDGET_H
