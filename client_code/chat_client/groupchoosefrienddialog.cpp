#include "groupchoosefrienddialog.h"
#include "debug.h"
#include "model/datacenter.h"
#include "toast.h"

#include <QHBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QPushButton>
#include <QPainter>

// 创建群聊选择好友窗口
GroupChooseFriendDialog::GroupChooseFriendDialog(QWidget* parent, const QString& friendId)
    :QDialog(parent),
    _friendId(friendId)
{
    // 设置基本属性
    this->setWindowTitle("选择好友");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    this->setFixedSize(600, 450);
    this->setStyleSheet("QWidget { background-color: rgb(250, 250, 250); }");
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 布局管理器
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);

    // 初始化左边窗口
    initLeftWidget(layout);
    // 初始化右边窗口
    initRightWidget(layout);
    // 初始化数据
    initData();

}

void GroupChooseFriendDialog::initLeftWidget(QHBoxLayout *layout){
    // 设置滚动区域
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidgetResizable(true);
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 2px; background-color: rgb(70, 70, 70)}");
    scrollArea->setStyleSheet("QScrollArea { border: none; }");
    layout->addWidget(scrollArea, 1);  // 1 表示拉伸系数

    _totalFirend = new QWidget();
    // 使用名字选择器 只选择这一个widget，若直接使用QWidget那么该widget下的所有子控件都会被设置
    _totalFirend->setObjectName("_totalFriend");
    _totalFirend->setStyleSheet("#_totalFriend { background-color: rgb(250, 250, 250); }");
    scrollArea->setWidget(_totalFirend);

    // 左侧子窗口的布局管理器
    QVBoxLayout* leftVLayout = new QVBoxLayout();
    leftVLayout->setSpacing(0);
    leftVLayout->setContentsMargins(10, 10, 0, 10);
    leftVLayout->setAlignment(Qt::AlignTop);
    _totalFirend->setLayout(leftVLayout);

#if TEST_UI
    for(int i = 0; i < 20; ++i){
        addFriendItem(QString::number(100+i), QIcon(":/resource/image/myChat.png"), "小八", false);
    }
#endif
}

void GroupChooseFriendDialog::initRightWidget(QHBoxLayout *layout){
    // 右侧子窗口布局管理器
    QGridLayout* rightGridLayout = new QGridLayout();
    rightGridLayout->setSpacing(10);
    rightGridLayout->setContentsMargins(20, 10, 20, 20);
    layout->addLayout(rightGridLayout, 1);

    // 组件1
    QLabel* titleLabel = new QLabel();
    titleLabel->setText("选择联系人");
    titleLabel->setFixedHeight(30);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    titleLabel->setStyleSheet("QLabel { font-size: 18px; font-weight: 700; }");

    // 设置滚动区域
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setWidgetResizable(true);
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 3px; background-color: rgb(230, 230, 230)}");
    scrollArea->setStyleSheet("QScrollArea { border: none; }");

    _selectedFriend = new QWidget();
    // 使用名字选择器 只选择这一个widget，若直接使用QWidget那么该widget下的所有子控件都会被设置
    _selectedFriend->setObjectName("_selectedFriend");
    _selectedFriend->setStyleSheet("#_selectedFriend { background-color: rgb(250, 250, 250); }");
    scrollArea->setWidget(_selectedFriend);

    // 右侧子窗口中_selectedFriend的布局管理器
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->setAlignment(Qt::AlignTop);
    _selectedFriend->setLayout(vlayout);

    // 组件2
    QPushButton* okBtn = new QPushButton();
    QString btnStyle = "QPushButton { font-size: 15px; color: rgb(7, 191, 96);  border: none; border-radius: 8px; background-color: rgb(240, 240, 240); }";
    btnStyle += "QPushButton:hover { background-color: rgb(220, 220, 220); }";
    btnStyle += "QPushButton:pressed { background-color: rgb(200, 200, 200); }";
    okBtn->setFixedHeight(35);
    okBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    okBtn->setStyleSheet(btnStyle);
    okBtn->setText("完成");

    QPushButton* cancleBtn = new QPushButton();
    cancleBtn->setFixedHeight(35);
    cancleBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    cancleBtn->setStyleSheet(btnStyle);
    cancleBtn->setText("取消");

    // 这里布局有点小技巧，总共分为9列
    rightGridLayout->addWidget(titleLabel, 0, 0, 1, 9);
    rightGridLayout->addWidget(scrollArea, 1, 0, 1, 9);
    rightGridLayout->addWidget(okBtn, 2, 1, 1, 3);
    rightGridLayout->addWidget(cancleBtn, 2, 5, 1, 3);

    // 关联“完成”按钮的信号槽
    connect(okBtn, &QPushButton::clicked, this, &GroupChooseFriendDialog::clickOkBtn);
    // 关联“取消”按钮的信号槽
    connect(cancleBtn, &QPushButton::clicked, this, [=]() {
        this->close();
    });

    // 右侧的好友项通过勾选左边的好友项生成
// #if TEST_UI
//     for(int i = 0; i < 20; ++i){
//         addSelectedFriendItem(QString::number(100+i), QIcon(":/resource/image/myChat.png"), "小八");
//     }
// #endif
}

void GroupChooseFriendDialog::clickOkBtn(){
    // 1. 根据选中的好友列表中的元素, 得到所有的要创建群聊会话的用户 id 列表
    QList<QString> groupSessionIdList = getGroupSessionMemberList();
    if (groupSessionIdList.size() < 3) {
        Toast::showMessage("群聊成员不足三个, 无法创建群聊");
        return;
    }

    // 2. 发送网络请求, 创建群聊
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    dataCenter->createGroupChatSessionAsync(groupSessionIdList);

    // 3. 关闭当前窗口
    this->close();
}

QList<QString> GroupChooseFriendDialog::getGroupSessionMemberList(){
    QList<QString> result;
    // 1. 先把自己添加到结果中
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    model::UserInfo* myself = dataCenter->getMyself();
    if (myself == nullptr) {
        LOG() << "myself is nullptr";
        return result;
    }
    result.push_back(myself->_userId);

    // 2. 遍历选中的列表
    QVBoxLayout* vLayout = dynamic_cast<QVBoxLayout*>(_selectedFriend->layout());
    for (int i = 0; i < vLayout->count(); ++i) {
        auto* item = vLayout->itemAt(i);
        if (item == nullptr || item->widget() == nullptr) {
            continue;
        }
        auto* groupFriendItem = dynamic_cast<GroupFriendItem*>(item->widget());
        result.push_back(groupFriendItem->getUserId());
    }
    return result;
}

void GroupChooseFriendDialog::initData(){
    // 遍历 好友列表, 把好友列表中的所有的元素, 添加到这个窗口界面上.
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    QList<model::UserInfo>* friendUserList = dataCenter->getFriendUserList();
    if (friendUserList == nullptr) {
        LOG() << "the friendUserList is nullptr";
        return;
    }
    for (auto it = friendUserList->begin(); it != friendUserList->end(); ++it) {
        if (it->_userId == this->_friendId) {
            // 这个要设成被选中状态
            this->addSelectedFriendItem(it->_userId, it->_headPortrait, it->_nickName);
            this->addFriendItem(it->_userId, it->_headPortrait, it->_nickName, true);
        } else {
            this->addFriendItem(it->_userId, it->_headPortrait, it->_nickName, false);
        }
    }
}


void GroupChooseFriendDialog::addFriendItem(const QString& userId, const QIcon &headPortraitIcon, const QString &nickName, bool checked){
    GroupFriendItem* friendItem = new GroupFriendItem(this, userId, headPortraitIcon, nickName, checked);
    _totalFirend->layout()->addWidget(friendItem);
}

void GroupChooseFriendDialog::addSelectedFriendItem(const QString& userId, const QIcon &headPortraitIcon, const QString &nickName){
    GroupFriendItem* friendItem = new GroupFriendItem(this, userId, headPortraitIcon, nickName, true);
    _selectedFriend->layout()->addWidget(friendItem);
}

void GroupChooseFriendDialog::deleteSelectedFriendItem(const QString &userId){
    // 根据userId 删除
    // 遍历右侧布局管理器，删除掉对应的GroupFriendItem。从后向前遍历
    QVBoxLayout* vLayoutRight = dynamic_cast<QVBoxLayout*>(_selectedFriend->layout());
    for(int i = vLayoutRight->count() - 1; i >= 0; --i){
        auto* item = vLayoutRight->itemAt(i);
        if(item == nullptr || item->widget() == nullptr){
            continue;
        }
        GroupFriendItem* friendItem = dynamic_cast<GroupFriendItem*>(item->widget());
        if(friendItem->getUserId() == userId){
            vLayoutRight->removeWidget(friendItem);
            // BUG：这里不能直接delete，会影响到信号槽的后续操作！！信号槽可能还在使用friendItem内的组件
            // delete friendItem;
            // 把delete操作交给Qt内部，让其自动在合适的时候delete
            friendItem->deleteLater();
        }
    }

    // 还要遍历左侧的布局管理器，把对应的GroupFriendItem的勾选状态取消
    QVBoxLayout* vLayoutLeft = dynamic_cast<QVBoxLayout*>(_totalFirend->layout());
    for(int i = vLayoutLeft->count() - 1; i >= 0; --i){
        auto* item = vLayoutLeft->itemAt(i);
        if(item == nullptr || item->widget() == nullptr){
            continue;
        }
        GroupFriendItem* friendItem = dynamic_cast<GroupFriendItem*>(item->widget());
        if(friendItem->getUserId() == userId){
            QCheckBox* checkBox = friendItem->getCheckBox();
            checkBox->setChecked(false);
        }
    }
}

// 选择好友窗口中的一个好友项 的类
GroupFriendItem::GroupFriendItem(QWidget* owner, const QString& userId, const QIcon& headPortraitIcon, const QString& nickName, bool checked)
    :_userId(userId)
{
    // 基本属性
    this->setFixedHeight(50);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // 布局管理器
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing(1);
    layout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(layout);
    // 组件
    _checkBox = new QCheckBox();
    _checkBox->setChecked(checked);
    _checkBox->setFixedSize(25, 25);
    QString checkBoxStyle = "QCheckBox { background-color: transparent; }";
    checkBoxStyle += "QCheckBox::indicator { width: 18px; height: 18px; image: url(:/resource/image/unchecked.png); }";
    checkBoxStyle += "QCheckBox::indicator:checked { image: url(:/resource/image/checked.png); }";
    _checkBox->setStyleSheet(checkBoxStyle);

    _headProtrait = new QPushButton();
    _headProtrait->setFixedSize(40, 40);
    _headProtrait->setIconSize(QSize(40, 40));
    _headProtrait->setIcon(headPortraitIcon);
    _headProtrait->setStyleSheet("QPushButton { border: none; background-color: transparent; }");

    _nickName = new QLabel();
    _nickName->setText(nickName);
    _nickName->setFont(QFont("微软雅黑", 10));
    _nickName->setStyleSheet("QLabel { background-color: transparent; }");

    layout->addWidget(_checkBox);
    layout->addWidget(_headProtrait);
    layout->addWidget(_nickName);

    // 连接信号槽
    GroupChooseFriendDialog* chooseFriendDialog = dynamic_cast<GroupChooseFriendDialog*>(owner);
    connect(_checkBox, &QCheckBox::toggled, this, [=](bool checked){
        if(checked){
            chooseFriendDialog->addSelectedFriendItem(userId, headPortraitIcon, nickName);
        }
        else {
            chooseFriendDialog->deleteSelectedFriendItem(userId);
        }
    });
}

void GroupFriendItem::paintEvent(QPaintEvent *event){
    // 鼠标进入到区域内时换个背景色
    (void)event;
    QPainter painter(this);
    if(_isHover){
        painter.fillRect(this->rect(), QColor(230, 230, 230));
    }
    else{
        painter.fillRect(this->rect(), QColor(250, 250, 250));
    }
}

void GroupFriendItem::enterEvent(QEnterEvent *event){
    (void)event;
    _isHover = true;
    // 更新一下界面，就可以触发paintEvent事件
    this->update();
}

void GroupFriendItem::leaveEvent(QEvent *event){
    (void)event;
    _isHover = false;
    // 更新一下界面，就可以触发paintEvent事件
    this->update();
}
