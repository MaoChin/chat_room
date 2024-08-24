#include "mainwidget.h"
#include "./ui_mainwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

// 单例
MainWidget* MainWidget::instance = nullptr;
MainWidget* MainWidget::getInstance(){
    // 这个主窗口单例创建的时间很早，所以不用考虑线程安全问题
    if(instance == nullptr){
        // new的时候不传参数表示以 桌面 作为父窗口
        instance = new MainWidget();
    }
    return instance;
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

    windowLeft = new QWidget();
    windowMiddle = new QWidget();
    windowRight = new QWidget();

    windowLeft->setFixedWidth(70);
    windowMiddle->setFixedWidth(300);
    windowRight->setMinimumWidth(500);

    windowLeft->setStyleSheet("QWidget {background-color: rgb(46, 46, 46)}");
    windowMiddle->setStyleSheet("QWidget {background-color: rgb(230, 230, 230)}");
    windowRight->setStyleSheet("QWidget {background-color: rgb(245, 245, 245)}");

    layout->addWidget(windowLeft);
    layout->addWidget(windowMiddle);
    layout->addWidget(windowRight);
}
void MainWidget::initLeftWindow(){
    QVBoxLayout* layout = new QVBoxLayout();
    windowLeft->setLayout(layout);

    userHeadPortraitBtn = new QPushButton();
    userHeadPortraitBtn->setFixedSize(48, 48);
    userHeadPortraitBtn->setIconSize(QSize(48, 48));
    userHeadPortraitBtn->setIcon(QIcon(":/resource/image/headPortrait.png"));

    chatSessionTabBtn = new QPushButton();
    chatSessionTabBtn->setFixedSize(48, 48);
    chatSessionTabBtn->setIconSize(QSize(48, 48));
    chatSessionTabBtn->setIcon(QIcon(":/resource/image/chatSessionTab.png"));

    friendTabBtn = new QPushButton();
    friendTabBtn->setFixedSize(48, 48);
    friendTabBtn->setIconSize(QSize(48, 48));
    friendTabBtn->setIcon(QIcon(":/resource/image/friendTab.png"));

    friendApplyTabBtn = new QPushButton();
    friendApplyTabBtn->setFixedSize(48, 48);
    friendApplyTabBtn->setIconSize(QSize(48, 48));
    friendApplyTabBtn->setIcon(QIcon(":/resource/image/friendApplyTab.png"));

    layout->addWidget(userHeadPortraitBtn);
    layout->addWidget(chatSessionTabBtn);
    layout->addWidget(friendTabBtn);
    layout->addWidget(friendApplyTabBtn);
}
void MainWidget::initMiddleWindow(){

}
void MainWidget::initRightWindow(){

}
