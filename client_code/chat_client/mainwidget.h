#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

#include "rightwindowmessageshowarea.h"
#include "rightwindowmessageeditarea.h"
#include "middlewindowarea.h"

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


    RightWindowMessageShowArea* getRightWindowMessageShowArea(){
        return _rightWindowMessageShowArea;
    }

public:
    void switchTabToChatSession();
    void switchTabToFriend();
    void switchTabToFriendApply();

    void clickFriendInFriendItem(const QString& friendId);

    void loadChatSessionTab();
    void loadFriendTab();
    void loadApplyUserTab();
    void loadRecentMessage(const QString& chatSessionId);

    // 初始化websocket
    void initWebsocket();

    // 和DataCenter的交互
    // 直接从DataCenter中加载好友列表
    void loadFriendListFromDataCenter();

    // 直接从DataCenter中加载会话列表
    void loadChatSessionListFromDataCenter();

    // 直接从DataCenter中加载好友申请列表
    void loadApplyUserListFromDataCenter();

    // 直接从DataCenter中加载会话最近消息列表
    void loadRecentMessageFromDataCenter(const QString& chatSessionId);

private:
    // 构造函数私有化
    MainWidget(QWidget *parent = nullptr);

    void initMainWindow();
    void initLeftWindow();
    void initMiddleWindow();
    void initRightWindow();
    void initSignalSlot();

private:
    // 搞成单例
    static MainWidget* _instance;

    Ui::MainWidget *ui;

    // 窗口中的各个子窗口
    QWidget* _windowLeft = nullptr;
    QWidget* _windowMiddle = nullptr;
    QWidget* _windowRight = nullptr;

    // 左侧窗口
    // 用户头像按钮
    QPushButton* _userHeadPortraitBtn = nullptr;
    // 会话标签页按钮
    QPushButton* _chatSessionTabBtn = nullptr;
    // 好友标签页按钮
    QPushButton* _friendTabBtn = nullptr;
    // 好友申请标签页按钮
    QPushButton* _friendApplyTabBtn = nullptr;

    // 中间窗口
    // 搜索框
    QLineEdit* _searchBar = nullptr;
    // 添加好友按钮
    QPushButton* _addFriendBtn = nullptr;
    // 好友/会话/申请好友 列表区
    MiddleWindowArea* _middleWindowArea = nullptr;

    // 右侧窗口
    // 上方的标题页
    QWidget* _titleWidget = nullptr;
    // 标题名
    QLabel* _titleName = nullptr;
    // 会话详情按钮
    QPushButton* _extraBtn = nullptr;
    // 消息展示区
    RightWindowMessageShowArea* _rightWindowMessageShowArea = nullptr;
    // 消息编辑区
    RightWindowMessageEditArea* _rightWindowMessageEditArea = nullptr;



    // 选中标签页
    enum ActiveTab{
        CHATSESSION_TAB,
        FRIEND_TAB,
        FRIENDAPPLY_TAB
    };
    ActiveTab _activeTab = CHATSESSION_TAB;

};
#endif // MAINWIDGET_H
