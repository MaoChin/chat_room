#include "sessiondetailwidget.h"

#include "debug.h"
#include "groupchoosefrienddialog.h"
#include "userinfowidget.h"
#include "model/datacenter.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QFontMetrics>
#include <QMessageBox>

// 详情页中头像+标签的组合
HeadPortraitItem::HeadPortraitItem(const QIcon& headIcon, const QString& name)
{
    this->setFixedSize(70, 90);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignHCenter);
    this->setLayout(layout);

    _headProtrait = new QPushButton();
    _headProtrait->setFixedSize(50, 50);
    _headProtrait->setIconSize(QSize(50, 50));
    _headProtrait->setIcon(headIcon);
    _headProtrait->setStyleSheet("QPushButton { border: none; }");

    QFont font("微软雅黑", 12);
    _nameLabel = new QLabel();
    _nameLabel->setFixedSize(50, 20);
    _nameLabel->setText(name);
    _nameLabel->setFont(font);
    _nameLabel->setAlignment(Qt::AlignHCenter);
    _nameLabel->setStyleSheet("QLabel { border: none; border-radius: 5px; background-color: rgb(); }");

    // 名字等描述信息进行截断
    const int MAX_WIDTH = 50;
    // 计算出总宽度
    QFontMetrics fontMetrics(font);
    int realWidth = fontMetrics.horizontalAdvance(name);
    if(realWidth > MAX_WIDTH){
        // 截断
        QString tail = "...";
        int tailWidth = fontMetrics.horizontalAdvance(tail);
        int availableWidth = MAX_WIDTH - tailWidth;
        int availableSize = name.size() * ((double)availableWidth / realWidth);
        QString newName = name.left(availableSize);
        _nameLabel->setText(newName + tail);
    }

    layout->addWidget(_headProtrait);
    layout->addWidget(_nameLabel);
}

// 单聊会话详情页
SessionDetailWidget::SessionDetailWidget(QWidget* parent, const model::UserInfo& friendInfo)
    :QDialog(parent),
    _friendInfo(friendInfo)
{
    // 基本属性
    this->setFixedSize(300, 250);
    this->setWindowTitle("会话详情");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    this->setStyleSheet("QWidget { background-color: rgb(250, 250, 250); }");
    this->setAttribute(Qt::WA_DeleteOnClose);
    // this->move(QCursor::pos());

    // 布局管理器
    QGridLayout* layout = new QGridLayout();
    layout->setSpacing(5);
    layout->setContentsMargins(50, 0, 50, 0);
    this->setLayout(layout);

    // 填充内容
    HeadPortraitItem* createGroupItem = new HeadPortraitItem(QIcon(":/resource/image/createGroupChat.png"), "添加");
    layout->addWidget(createGroupItem, 0, 0);

#if TEST_UI
    HeadPortraitItem* friendItem = new HeadPortraitItem(QIcon(":/resource/image/headPortrait.png"), "小八");
    layout->addWidget(friendItem, 0, 2);
#endif

    HeadPortraitItem* friendItem = new HeadPortraitItem(friendInfo._headPortrait, friendInfo._nickName);
    layout->addWidget(friendItem, 0, 1);

    QPushButton* deleteFriendBtn = new QPushButton();
    deleteFriendBtn->setFixedHeight(40);
    deleteFriendBtn->setFont(QFont("微软雅黑", 12));
    deleteFriendBtn->setText("删除好友");

    QString btnStyle = "QPushButton { border: 1px solid rgb(100, 100, 100); border-radius: 5px; background-color: transparent; }";
    btnStyle += "QPushButton:pressed { background-color: rgb(210, 210, 210); }";
    deleteFriendBtn->setStyleSheet(btnStyle);

    layout->addWidget(deleteFriendBtn, 1, 0, 1, 2);

    // 关联创建群聊信号槽
    connect(createGroupItem->getHeadPortrait(), &QPushButton::clicked, this, [=](){
        GroupChooseFriendDialog* chooseFriendDialog = new GroupChooseFriendDialog(parent, _friendInfo._userId);
        // 弹出模态对话框
        chooseFriendDialog->exec();
    });

    // 关联 点击好友头像弹出好友详细信息对话框 的信号槽
    // connect(friendItem->getHeadPortrait(), &QPushButton::clicked, this, [=](){
    //     // 要是用户在这个页面进行了操作还需要通过信号槽机制回到这边进行对应的操作！！
    //     UserInfoWidget* userInfoWidget = new UserInfoWidget(this, friendInfo);
    //     userInfoWidget->exec();
    // });

    // 关联删除好友信号槽
    connect(deleteFriendBtn, &QPushButton::clicked, this, &SessionDetailWidget::clickDeleteFriendBtn);
}

void SessionDetailWidget::clickDeleteFriendBtn(){
    // 弹出对话框, 让用户确认是否真的要删除
    auto result = QMessageBox::warning(this, "确认删除", "确认删除当前好友?", QMessageBox::Ok | QMessageBox::Cancel);
    if (result != QMessageBox::Ok) {
        LOG() << "calcel delete friend";
        return;
    }

    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    dataCenter->deleteFriendAsync(_friendInfo._userId);

    // 关闭这个单聊会话详情页
    this->close();
}

