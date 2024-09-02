#include "sessiondetailwidget.h"

#include "debug.h"
#include "groupchoosefrienddialog.h"
#include "userinfowidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QFontMetrics>

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
SessionDetailWidget::SessionDetailWidget(QWidget* parent)
    :QDialog(parent)
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
    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(20);
    layout->setContentsMargins(20, 20, 20, 0);
    layout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    this->setLayout(layout);

    // 填充内容
    HeadPortraitItem* createGroupItem = new HeadPortraitItem(QIcon(":/resource/image/createGroupChat.png"), "添加");
    layout->addWidget(createGroupItem, 0, 1);

#if TEST_UI
    HeadPortraitItem* userItem = new HeadPortraitItem(QIcon(":/resource/image/headPortrait.png"), "小八");
    layout->addWidget(userItem, 0, 2);
#endif

    QPushButton* deleteFriendBtn = new QPushButton();
    deleteFriendBtn->setFixedHeight(40);
    deleteFriendBtn->setFont(QFont("微软雅黑", 12));
    deleteFriendBtn->setText("删除好友");

    QString btnStyle = "QPushButton { border: 1px solid rgb(100, 100, 100); border-radius: 5px; background-color: transparent; }";
    btnStyle += "QPushButton:pressed { background-color: rgb(210, 210, 210); }";
    deleteFriendBtn->setStyleSheet(btnStyle);

    layout->addWidget(deleteFriendBtn, 1, 0, 1, 3);

    // 关联信号槽
    connect(createGroupItem->getHeadPortrait(), &QPushButton::clicked, this, [=](){
        GroupChooseFriendDialog* chooseFriendDialog = new GroupChooseFriendDialog(parent);
        // 弹出模态对话框
        chooseFriendDialog->exec();
    });
    connect(userItem->getHeadPortrait(), &QPushButton::clicked, this, [=](){
        // TODO 这里需要想办法获取 userInfo
        // UserInfoWidget* userInfoWidget = new UserInfoWidget();
        // userInfoWidget->exec();
    });
}

