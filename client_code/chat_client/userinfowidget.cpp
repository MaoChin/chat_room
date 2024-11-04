#include "userinfowidget.h"
#include "mainwidget.h"

#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>

#include "model/datacenter.h"

UserInfoWidget::UserInfoWidget(QWidget* parent, const model::UserInfo& userInfo)
    : QDialog(parent),
    _userInfo(userInfo)
{
    this->setFixedSize(400, 200);
    this->setWindowTitle("用户详情");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    // 把窗口移动到鼠标位置
    this->move(QCursor::pos());
    // 该窗口关闭时自动销毁这个对象，防止内存泄漏
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 布局管理器
    QGridLayout* layout = new QGridLayout();
    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(2);
    layout->setContentsMargins(25, 25, 25, 0);
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    this->setLayout(layout);

    // 头像
    _headPortrait = new QPushButton();
    _headPortrait->setFixedSize(80, 80);
    _headPortrait->setIconSize(QSize(80, 80));
    _headPortrait->setIcon(_userInfo._headPortrait);
    _headPortrait->setStyleSheet("QPushButton { border: none; background-color: transparent; }");
    layout->addWidget(_headPortrait, 0, 0, 3, 1);

    QString tagStyle = "QLabel { font-size: 14px; font-weight: 800; }";
    QString btnStyle = "QPushButton { border: 1px solid rgb(100, 100, 100); background-color: rgb(240, 240, 240); border-radius: 5px; }";
    btnStyle += "QPushButton:pressed { background-color: rgb(210, 210, 210); }";
    int height = 30;
    // id
    _idTag = new QLabel();
    _idTag->setText("ID");
    _idTag->setFixedSize(80, height);
    _idTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _idTag->setStyleSheet(tagStyle);

    _idLabel = new QLabel();
    _idLabel->setFixedHeight(height);
    _idLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _idLabel->setText(userInfo._userId);
    // 昵称
    _nickNameTag = new QLabel();
    _nickNameTag->setText("昵称");
    _nickNameTag->setFixedSize(80, height);
    _nickNameTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _nickNameTag->setStyleSheet(tagStyle);

    _nickNameLabel = new QLabel();
    _nickNameLabel->setFixedHeight(height);
    _nickNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _nickNameLabel->setText(userInfo._nickName);
    // 电话
    _phoneNumTag = new QLabel();
    _phoneNumTag->setText("电话");
    _phoneNumTag->setFixedSize(80, height);
    _phoneNumTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _phoneNumTag->setStyleSheet(tagStyle);

    _phoneNumLabel = new QLabel();
    _phoneNumLabel->setFixedHeight(height);
    _phoneNumLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _phoneNumLabel->setText(userInfo._phoneNum);
    // 申请好友
    _applyFriendBtn = new QPushButton();
    _applyFriendBtn->setFixedSize(80, 30);
    _applyFriendBtn->setStyleSheet(btnStyle);
    _applyFriendBtn->setText("申请好友");
    // 发送消息
    _sendMessageBtn = new QPushButton();
    _sendMessageBtn->setFixedSize(80, 30);
    _sendMessageBtn->setStyleSheet(btnStyle);
    _sendMessageBtn->setText("发送消息");
    // 删除好友
    _deleteFriendBtn = new QPushButton();
    _deleteFriendBtn->setFixedSize(80, 30);
    _deleteFriendBtn->setStyleSheet(btnStyle);
    _deleteFriendBtn->setText("删除好友");

    // 默认就是占据一行一列
    layout->addWidget(_idTag, 0, 1);
    layout->addWidget(_idLabel, 0, 2);

    layout->addWidget(_nickNameTag, 1, 1);
    layout->addWidget(_nickNameLabel, 1, 2);

    layout->addWidget(_phoneNumTag, 2, 1);
    layout->addWidget(_phoneNumLabel, 2, 2);

    layout->addWidget(_applyFriendBtn, 3, 0);
    layout->addWidget(_sendMessageBtn, 3, 1);
    layout->addWidget(_deleteFriendBtn, 3, 2);

    // 判断页面中三个按钮的可用状态
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    model::UserInfo* friendInfo = dataCenter->findFriendById(_userInfo._userId);
    if(friendInfo == nullptr){
        // 这个用户不是我的好友
        _sendMessageBtn->setEnabled(false);
        _deleteFriendBtn->setEnabled(false);
    }
    else{
        // 是我的好友
        _applyFriendBtn->setEnabled(false);
    }

    initSignalSlot();
}

void UserInfoWidget::initSignalSlot(){
    // 申请好友按钮的信号槽
    connect(_applyFriendBtn, &QPushButton::clicked, this, &UserInfoWidget::clickApplyFriendBtn);

    // 发送消息按钮的信号槽
    connect(_sendMessageBtn, &QPushButton::clicked, this, [=]() {
        // 直接调用主界面的点击好友的函数就好
        MainWidget* mainWidget = MainWidget::getInstance();
        mainWidget->clickFriendInFriendItem(_userInfo._userId);

        // 关闭这个好友详情页面
        this->close();
    });

    // 删除好友按钮的信号槽
    connect(_deleteFriendBtn, &QPushButton::clicked, this, &UserInfoWidget::clickDeleteFriendBtn);
}

void UserInfoWidget::clickApplyFriendBtn(){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    dataCenter->addFriendApplyAsync(_userInfo._userId);

    // 关闭这个好友详情页面
    this->close();
}

void UserInfoWidget::clickDeleteFriendBtn(){
    // 弹出对话框, 让用户确认是否真的要删除
    auto result = QMessageBox::warning(this, "确认删除", "确认删除当前好友?", QMessageBox::Ok | QMessageBox::Cancel);
    if (result != QMessageBox::Ok) {
        LOG() << "calcel delete friend";
        return;
    }

    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    dataCenter->deleteFriendAsync(_userInfo._userId);

    // 关闭这个好友详情页面
    this->close();
}
