#include "mainwidget.h"
#include "middlewindowarea.h"
#include "./ui_mainwidget.h"

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
    initLeftWindow();
    initMiddleWindow();
    initRightWindow();
    initSignalSlot();

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
    _windowRight->setMinimumWidth(500);

    _windowLeft->setStyleSheet("QWidget { background-color: rgb(46, 46, 46); }");
    _windowMiddle->setStyleSheet("QWidget { background-color: rgb(240, 240, 240); }");
    _windowRight->setStyleSheet("QWidget { background-color: rgb(245, 245, 245); }");

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
    _userHeadPortraitBtn->setIcon(QIcon(":/resource/image/headPortrait.png"));
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
    _searchBar->setStyleSheet("QLineEdit { border-radius: 5px; background-color: rgb(205, 205, 205); padding-left: 10px; }");

    _addFriendBtn = new QPushButton();
    _addFriendBtn->setFixedSize(30, 30);
    _addFriendBtn->setIconSize(QSize(30, 30));
    _addFriendBtn->setIcon(QIcon(":/resource/image/addFriend.png"));
    QString styleSheet = "QPushButton { border-radius: 5px; background-color: rgb(200, 200, 200); }";
    styleSheet += " QPushButton:pressed {background-color: rgb(240, 240, 240); }";
    _addFriendBtn->setStyleSheet(styleSheet);

    // 设置一些空白区域，仅仅是为了占位，使搜索框和边框之间有空白
    QWidget* space1 = new QWidget();
    QWidget* space2 = new QWidget();
    QWidget* space3 = new QWidget();
    space1->setFixedWidth(10);
    space2->setFixedWidth(10);
    space3->setFixedWidth(10);

    MiddleWindowArea* middleWindowArea = new MiddleWindowArea();

    layout->addWidget(space1, 0, 0);
    layout->addWidget(_searchBar, 0, 1);
    layout->addWidget(space2, 0, 2);
    layout->addWidget(_addFriendBtn, 0, 3);
    layout->addWidget(space3, 0, 4);
    // (1, 0)位置，占1行5列
    layout->addWidget(middleWindowArea, 1, 0, 1, 5);
}
void MainWidget::initRightWindow(){

}

// 信号槽的初始化
void MainWidget::initSignalSlot(){
    // 标签页状态切换
    connect(_chatSessionTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToChatSession);
    connect(_friendTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToFriend);
    connect(_friendApplyTabBtn, &QPushButton::clicked, this, &MainWidget::switchTabToFriendApply);






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

    this->loadFriendApplyTab();
}

void MainWidget::loadChatSessionTab(){

}

void MainWidget::loadFriendTab(){

}
void MainWidget::loadFriendApplyTab(){

}
