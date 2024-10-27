#include "mainwidget.h"
#include "middlewindowarea.h"
#include "./ui_mainwidget.h"
#include "debug.h"
#include "selfinfowidget.h"
#include "sessiondetailwidget.h"
#include "groupsessiondetailwidget.h"
#include "addfrineddialog.h"
#include "model/datacenter.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

// 单例
MainWidget* MainWidget::_instance = nullptr;
MainWidget* MainWidget::getInstance(){
    // 这个主窗口单例创建的时间很早，所以不用考虑线程安全问题
    if(_instance == nullptr){
        // new的时候不传参数表示以 桌面 作为父窗口
        _instance = new MainWidget();
    }
    return _instance;
}

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("MyChat");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));

    initMainWindow();
    LOG() << "test0";
    initLeftWindow();
    LOG() << "test1";
    initMiddleWindow();
    LOG() << "test2";
    initRightWindow();
    LOG() << "test3";
    initSignalSlot();

    // 获取当前用户好友列表
    loadFriendTab();

    // 获取当前用户会话列表
    loadChatSessionTab();

    // 获取当前用户好友申请列表
    loadApplyUserTab();

}


MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initMainWindow(){
    QHBoxLayout* layout = new QHBoxLayout();
    // 设置布局管理器内部元素的距离
    layout->setSpacing(0);
    // 设置布局管理器整体和边界的距离
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    _windowLeft = new QWidget();
    _windowMiddle = new QWidget();
    _windowRight = new QWidget();

    _windowLeft->setFixedWidth(70);
    _windowMiddle->setFixedWidth(300);
    _windowRight->setMinimumWidth(600);

    _windowLeft->setStyleSheet("QWidget { background-color: rgb(46, 46, 46); }");
    _windowMiddle->setStyleSheet("QWidget { background-color: rgb(240, 240, 240); }");
    _windowRight->setStyleSheet("QWidget { background-color: rgb(240, 240, 240); }");

    layout->addWidget(_windowLeft);
    layout->addWidget(_windowMiddle);
    layout->addWidget(_windowRight);
}
void MainWidget::initLeftWindow(){
    // 垂直布局
    QVBoxLayout* layout = new QVBoxLayout();
    _windowLeft->setLayout(layout);
    layout->setSpacing(25);
    layout->setContentsMargins(0, 30, 0, 0);

    _userHeadPortraitBtn = new QPushButton();
    _userHeadPortraitBtn->setFixedSize(48, 48);
    _userHeadPortraitBtn->setIconSize(QSize(48, 48));
    // 头像应该从服务器获取
    // _userHeadPortraitBtn->setIcon(QIcon(":/resource/image/headPortrait.png"));
    _userHeadPortraitBtn->setStyleSheet("QWidget { background-color: transparent; }");

    _chatSessionTabBtn = new QPushButton();
    _chatSessionTabBtn->setFixedSize(44, 44);
    _chatSessionTabBtn->setIconSize(QSize(34, 34));
    _chatSessionTabBtn->setIcon(QIcon(":/resource/image/chatSessionTabActive.png"));
    _chatSessionTabBtn->setStyleSheet("QWidget { background-color: transparent; }");

    _friendTabBtn = new QPushButton();
    _friendTabBtn->setFixedSize(44, 44);
    _friendTabBtn->setIconSize(QSize(34, 34));
    _friendTabBtn->setIcon(QIcon(":/resource/image/friendTabNotActive.png"));
    _friendTabBtn->setStyleSheet("QWidget { background-color: transparent; }");

    _friendApplyTabBtn = new QPushButton();
    _friendApplyTabBtn->setFixedSize(44, 44);
    _friendApplyTabBtn->setIconSize(QSize(34, 34));
    _friendApplyTabBtn->setIcon(QIcon(":/resource/image/friendApplyTabNotActive.png"));
    _friendApplyTabBtn->setStyleSheet("QWidget { background-color: transparent; }");

    layout->addWidget(_userHeadPortraitBtn, 1, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(_chatSessionTabBtn, 1, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(_friendTabBtn, 1, Qt::AlignTop | Qt::AlignHCenter);
    layout->addWidget(_friendApplyTabBtn, 1, Qt::AlignTop | Qt::AlignHCenter);
    layout->addStretch(20);
}
void MainWidget::initMiddleWindow(){
    // 网格布局
    QGridLayout* layout = new QGridLayout();
    // 设置布局内部元素距离
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(15);
    // 设置边距：左，上，右，下
    layout->setContentsMargins(0, 15, 0, 0);
    _windowMiddle->setLayout(layout);

    _searchBar = new QLineEdit();
    _searchBar->setFixedHeight(30);
    _searchBar->setPlaceholderText("搜索");
    _searchBar->setStyleSheet("QLineEdit { border-radius: 5px; background-color: rgb(210, 210, 210); padding-left: 10px; }");

    _addFriendBtn = new QPushButton();
    _addFriendBtn->setFixedSize(30, 30);
    _addFriendBtn->setIconSize(QSize(25, 25));
    _addFriendBtn->setIcon(QIcon(":/resource/image/addFriend.png"));
    QString styleSheet = "QPushButton { border-radius: 5px; background-color: rgb(210, 210, 210); }";
    styleSheet += "QPushButton:hover { background-color: rgb(230, 230, 230); }";
    styleSheet += " QPushButton:pressed {background-color: rgb(245, 245, 245); }";
    _addFriendBtn->setStyleSheet(styleSheet);

    // 设置一些空白区域，仅仅是为了占位，使搜索框和边框之间有空白
    QWidget* space1 = new QWidget();
    QWidget* space2 = new QWidget();
    QWidget* space3 = new QWidget();
    space1->setFixedWidth(10);
    space2->setFixedWidth(10);
    space3->setFixedWidth(10);

    _middleWindowArea = new MiddleWindowArea();

    layout->addWidget(space1, 0, 0);
    layout->addWidget(_searchBar, 0, 1);
    layout->addWidget(space2, 0, 2);
    layout->addWidget(_addFriendBtn, 0, 3);
    layout->addWidget(space3, 0, 4);
    // (1, 0)位置，占1行5列
    layout->addWidget(_middleWindowArea, 1, 0, 1, 5);
}

void MainWidget::initRightWindow(){
    // 垂直布局管理器
    QVBoxLayout* rightWindowLayout = new QVBoxLayout();
    rightWindowLayout->setSpacing(0);
    rightWindowLayout->setContentsMargins(0, 0, 0, 0);
    rightWindowLayout->setAlignment(Qt::AlignTop);
    _windowRight->setLayout(rightWindowLayout);

    // 最上方的标题页
    _titleWidget = new QWidget();
    _titleWidget->setFixedHeight(62);
    _titleWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _titleWidget->setObjectName("_titleWidget");
    _titleWidget->setStyleSheet("#_titleWidget { border-left: 1px solid rgb(220, 220, 220); border-bottom: 1px solid rgb(220, 220, 220); }");
    rightWindowLayout->addWidget(_titleWidget);
    // _titleWidget内部的布局管理器
    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(10, 0, 10, 0);
    _titleWidget->setLayout(titleLayout);

    _titleName = new QLabel();
    _titleName->setStyleSheet("QLabel { font-size: 20px; border-bottom: 1px solid rgb(230, 230, 230); }");
    titleLayout->addWidget(_titleName);

#if TEST_UI
    _titleName->setText("小八");
#endif

    _extraBtn = new QPushButton();
    _extraBtn->setFixedSize(35, 40);
    _extraBtn->setIconSize(QSize(35, 35));
    _extraBtn->setIcon(QIcon(":/resource/image/more.png"));
    QString extraBtnStyle = "QPushButton { border: none; background-color: transparent; }";
    extraBtnStyle += "QPushButton:hover { background-color: rgb(235, 235, 235); }";
    extraBtnStyle += "QPushButton:pressed { background-color: rgb(220, 220, 220); }";
    _extraBtn->setStyleSheet(extraBtnStyle);
    titleLayout->addWidget(_extraBtn);

    // 中间的消息展示区
    _rightWindowMessageShowArea = new RightWindowMessageShowArea();
    rightWindowLayout->addWidget(_rightWindowMessageShowArea);
    // 下方的消息编辑区
    _rightWindowMessageEditArea = new RightWindowMessageEditArea();
    rightWindowLayout->addWidget(_rightWindowMessageEditArea, 0, Qt::AlignBottom);
}

// 信号槽的初始化
void MainWidget::initSignalSlot(){
    // 标签页状态切换
    connect(_chatSessionTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToChatSession);
    connect(_friendTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToFriend);
    connect(_friendApplyTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToFriendApply);

    // 点击自己头像显示个人信息界面
    connect(_userHeadPortraitBtn, &QPushButton::clicked, this, [=](){
        SelfInfoWidget* selfInfoWidget = new SelfInfoWidget(this);
        // 弹出非模态对话框（非阻塞）
        // selfInfoWidget->show();
        // 弹出模态对话框（阻塞）
        selfInfoWidget->exec();
    });

    // 点击右侧页面的会话详情按钮弹出会话详情页
    connect(_extraBtn, &QPushButton::clicked, this, [=](){
        // TODO 具体是单聊还是群聊后续判断
        bool isSignalSession = true;

#if TEST_GROUP_SESSION_DETAIL
        isSignalSession = false;
#endif

        if(isSignalSession){
            // 单聊详情页
            SessionDetailWidget* sessionDetailWidget = new SessionDetailWidget(this);
            // 弹出模态对话框（阻塞）
            sessionDetailWidget->exec();
        }
        else{
            // 群聊详情页
            GroupSessionDetailWidget* groupSessionDetailWidget = new GroupSessionDetailWidget(this);
            // 弹出模态对话框（阻塞）
            groupSessionDetailWidget->exec();
        }
    });

    // 点击中间页面添加好友按钮弹出添加好友搜索框
    connect(_addFriendBtn, &QPushButton::clicked, this, [=](){
        AddFrinedDialog* addFriendDialog = new AddFrinedDialog(this);
        addFriendDialog->exec();
    });

    // 在中间页面搜索框输入时就跳转到添加好友页面
    // QLineEdit 有两个信号：textEdit和textChanged
    // textEdit是用户编辑内容时触发；textChanged是只要内容有变化就触发，包括在代码中setText
    // 若使用textChanged，就会在槽函数中setText时再次触发信号 -》无限死循环了！！
    connect(_searchBar, &QLineEdit::textEdited, this, [=](){
        const QString searchKey = _searchBar->text();
        AddFrinedDialog* addFriendDialog = new AddFrinedDialog(this);
        // 设置添加好友页面的搜索框内容
        addFriendDialog->setSearchBarContent(searchKey);
        // 把主页面的搜索框内容清空
        _searchBar->setText("");
        addFriendDialog->exec();
    });


    ///////////////////////////////
    /// 前后端交互！！
    // 获取当前用户信息, 大体的数据流向: 网络(NetClient)->DataCenter->界面显示
    model::DataCenter* dataCenter = model::DataCenter::getInstance();

    // 先连接 HTTP 响应处理完成的自定义的信号槽
    connect(dataCenter, &model::DataCenter::getMyselfAsyncDone, this, [=]() {
        // 这里已经处理完 getMyself 的响应了,即对应的数据已经在 DataCenter 里了!!
        // 直接把数据设置到界面即可
        model::UserInfo* userInfo = dataCenter->getMyself();
        _userHeadPortraitBtn->setIcon(userInfo->_headPortrait);
    });

    // 再异步调用,调用后网络和DataCenter模块会发送网络请求,接收响应并处理响应,处理完响应后就触发getMyselfDone信号!
    dataCenter->getMyselfAsync();

}

// 切换到会话页
void MainWidget::switchTabToChatSession(){
    _activeTab = CHATSESSION_TAB;
    _chatSessionTabBtn->setIcon(QIcon(":/resource/image/chatSessionTabActive.png"));
    _friendTabBtn->setIcon(QIcon(":/resource/image/friendTabNotActive.png"));
    _friendApplyTabBtn->setIcon(QIcon(":/resource/image/friendApplyTabNotActive.png"));

    this->loadChatSessionTab();
}
// 切换到好友页
void MainWidget::switchTabToFriend(){
    _activeTab = FRIEND_TAB;
    _friendTabBtn->setIcon(QIcon(":/resource/image/friendTabActive.png"));
    _chatSessionTabBtn->setIcon(QIcon(":/resource/image/chatSessionTabNotActive.png"));
    _friendApplyTabBtn->setIcon(QIcon(":/resource/image/friendApplyTabNotActive.png"));

    this->loadFriendTab();
}
// 切换到好友申请页
void MainWidget::switchTabToFriendApply(){
    _activeTab = FRIENDAPPLY_TAB;
    _friendApplyTabBtn->setIcon(QIcon(":/resource/image/friendApplyTabActive.png"));
    _chatSessionTabBtn->setIcon(QIcon(":/resource/image/chatSessionTabNotActive.png"));
    _friendTabBtn->setIcon(QIcon(":/resource/image/friendTabNotActive.png"));

    this->loadApplyUserTab();
}

void MainWidget::loadChatSessionTab(){
    // 如果 DataCenter 中有数据就直接加载，否则从服务器获取数据
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    if(dataCenter->getChatSessionList() == nullptr){
        // 通过网络获取
        // 先连接 HTTP 响应处理完成的自定义的信号槽
        connect(dataCenter, &model::DataCenter::getChatSessionListAsyncDone, this, &MainWidget::loadChatSessionListFromDataCenter, Qt::UniqueConnection);
        // 再异步调用,调用后网络和DataCenter模块会发送网络请求,接收响应并处理响应,处理完响应后就触发getChatSessionListAsyncDone信号!
        dataCenter->getChatSessionListAsync();
    }
    else{
        // 直接加载DataCenter中的_chatSessionList
        loadChatSessionListFromDataCenter();
    }

}

void MainWidget::loadFriendTab(){
    // 如果 DataCenter 中有数据就直接加载，否则从服务器获取数据
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    if(dataCenter->getFriendUserList() == nullptr){
        // 先连接 HTTP 响应处理完成的自定义的信号槽
        // 因为每次切换到好友列表页都会调用这个函数，多次调用后会使这个信号绑定多个相同的槽函数！所以最后加一个 Qt::UniqueConnection
        connect(dataCenter, &model::DataCenter::getFriendUserListAsyncDone, this, &MainWidget::loadFriendListFromDataCenter, Qt::UniqueConnection);

        // 再异步调用,调用后网络和DataCenter模块会发送网络请求,接收响应并处理响应,处理完响应后就触发getFriendUserListAsyncDone信号!
        dataCenter->getFriendUserListAsync();
    }
    else{
        // 直接加载DataCenter中的数据到界面即可
        loadFriendListFromDataCenter();
    }
}

void MainWidget::loadApplyUserTab(){
    // 如果 DataCenter 中有数据就直接加载，否则从服务器获取数据
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    if(dataCenter->getApplyUserList() == nullptr){
        // 发送网络请求获取数据
        connect(dataCenter, &model::DataCenter::getApplyUserListAsyncDone, this, &MainWidget::loadApplyUserListFromDataCenter, Qt::UniqueConnection);

        dataCenter->getApplyUserListAsync();
    }
    else{
        // 直接从DataCenter中加载数据
        loadApplyUserListFromDataCenter();
    }
}

void MainWidget::loadFriendListFromDataCenter(){
    if(_activeTab != FRIEND_TAB){
        return;
    }

    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    QList<model::UserInfo>* friendUserList = dataCenter->getFriendUserList();
    if(friendUserList == nullptr){
        return;
    }

    // 测试连接信号槽中 Qt::UniqueConnection的作用
    // LOG() << "test Qt::UniqueConnection";

    // 先清空页面原有的数据
    _middleWindowArea->clearAllItem();
    // 遍历List，把数据加载到界面
    for(const model::UserInfo& userInfo : *friendUserList){
        _middleWindowArea->addItem(FRIEND_TYPE, userInfo._userId, userInfo._headPortrait, userInfo._nickName, userInfo._personalSignature);
    }
}

void MainWidget::loadChatSessionListFromDataCenter(){
    if(_activeTab != CHATSESSION_TAB){
        // 当前不是会话页
        return;
    }

    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    QList<model::ChatSessionInfo>* chatSessionList = dataCenter->getChatSessionList();
    if(chatSessionList == nullptr){
        return;
    }

    // 先清空页面原有的数据
    _middleWindowArea->clearAllItem();
    for(const model::ChatSessionInfo& chatSessionInfo : *chatSessionList){
        model::MessageType curMessageType = chatSessionInfo._lastMessage._messageType;

        if(curMessageType == model::TEXT_TYPE){
            _middleWindowArea->addItem(CHATSESSION_TYPE, chatSessionInfo._chatSessionId, chatSessionInfo._headPortrait, chatSessionInfo._chatSessionName, chatSessionInfo._lastMessage._content);
        }
        else if(curMessageType == model::IMAGE_TYPE){
            _middleWindowArea->addItem(CHATSESSION_TYPE, chatSessionInfo._chatSessionId, chatSessionInfo._headPortrait, chatSessionInfo._chatSessionName, "[图片]");
        }
        else if(curMessageType == model::FILE_TYPE){
            _middleWindowArea->addItem(CHATSESSION_TYPE, chatSessionInfo._chatSessionId, chatSessionInfo._headPortrait, chatSessionInfo._chatSessionName, "[文件] " + chatSessionInfo._lastMessage._fileName);
        }
        else if(curMessageType == model::VOICE_TYPE){
            _middleWindowArea->addItem(CHATSESSION_TYPE, chatSessionInfo._chatSessionId, chatSessionInfo._headPortrait, chatSessionInfo._chatSessionName, "[语音]");
        }
        else{
            LOG() << "消息类型错误: " << curMessageType;
        }
    }
}

void MainWidget::loadApplyUserListFromDataCenter(){
    if(_activeTab != FRIENDAPPLY_TAB){
        return;
    }

    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    QList<model::UserInfo>* applyUserList = dataCenter->getApplyUserList();
    if(applyUserList == nullptr){
        return;
    }

    // 清空页面原有的数据
    _middleWindowArea->clearAllItem();
    for(const model::UserInfo& applyUserInfo : *applyUserList){
        _middleWindowArea->addItem(FRIENDAPPLY_TYPE, applyUserInfo._userId, applyUserInfo._headPortrait, applyUserInfo._nickName, "");
    }
}
