#include "groupsessiondetailwidget.h"

#include "sessiondetailwidget.h"
#include "debug.h"
#include "model/datacenter.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QPushButton>

GroupSessionDetailWidget::GroupSessionDetailWidget(QWidget* parent)
    :QDialog(parent)
{
    // 基本属性
    this->setFixedSize(400, 550);
    this->setWindowTitle("会话详情");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    this->setStyleSheet("QWidget { background-color: rgb(250, 250, 250); }");
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 布局管理器
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(20, 20, 20, 10);
    vlayout->setAlignment(Qt::AlignTop);
    this->setLayout(vlayout);

    // 滚动区域
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(340, 350);
    scrollArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 2px; background-color: rgb(70, 70, 70)}");
    scrollArea->setStyleSheet("QScrollArea { border: none; background-color: transparent; }");

    // 设置滚动区域内的QWidget
    QWidget* container = new QWidget();
    scrollArea->setWidget(container);
    vlayout->addWidget(scrollArea);

    // container内的布局管理器
    _gridLayout = new QGridLayout();
    _gridLayout->setSpacing(6);
    _gridLayout->setContentsMargins(0, 0, 0, 0);
    _gridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    container->setLayout(_gridLayout);

    // 组件
    HeadPortraitItem* addBtn = new HeadPortraitItem(QIcon(":/resource/image/createGroupChat.png"), "添加");
    _gridLayout->addWidget(addBtn);

    QLabel* groupSessionNameTag = new QLabel();
    groupSessionNameTag->setText("群聊名称: ");
    groupSessionNameTag->setFixedHeight(50);
    groupSessionNameTag->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    groupSessionNameTag->setStyleSheet("QLabel { font-size: 14px; font-weight: 700; }");
    groupSessionNameTag->setAlignment(Qt::AlignBottom);
    vlayout->addWidget(groupSessionNameTag);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setSpacing(0);
    hlayout->setContentsMargins(0, 0, 0, 0);
    vlayout->addLayout(hlayout);

    _realGroupSessionName = new QLabel();
    _realGroupSessionName->setFixedHeight(50);
    _realGroupSessionName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _realGroupSessionName->setStyleSheet("QLabel { font-size: 15px; }");
    hlayout->addWidget(_realGroupSessionName);

    QPushButton* modifyBtn = new QPushButton();
    modifyBtn->setFixedSize(26, 26);
    modifyBtn->setIconSize(QSize(26, 26));
    modifyBtn->setIcon(QIcon(":/resource/image/modifyBtn.png"));
    QString modifyBtnStyle = "QPushButton { border: none; background-color: transparent; }";
    modifyBtnStyle += "QPushButton:pressed { background-color: rgb(230, 230, 230); }";
    modifyBtn->setStyleSheet(modifyBtnStyle);
    hlayout->addWidget(modifyBtn);

    QPushButton* exitGroupSession = new QPushButton();
    exitGroupSession->setFixedHeight(50);
    exitGroupSession->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    exitGroupSession->setText("退出群聊");
    QString exitBtnStyle = "QPushButton { border: 1px solid rgb(90, 90, 90); border-radius: 8px; font-size: 16px; background-color: transparent; }";
    exitBtnStyle += "QPushButton:pressed { background-color: rgb(230, 230, 230); }";
    exitGroupSession->setStyleSheet(exitBtnStyle);
    vlayout->addWidget(exitGroupSession);


#if TEST_UI
    realGroupSessionName->setText("群聊1");
    for(int i = 0; i < 20; ++i){
        HeadPortraitItem* item = new HeadPortraitItem(QIcon(":/resource/image/headPortrait.png"), "zhangsssssssss");
        addGroupMember(item);
    }
#endif

    initData();
}

void GroupSessionDetailWidget::initData(){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();

    // 关联获取成员列表请求完成的信号槽
    connect(dataCenter, &model::DataCenter::getChatSessionMemberListAsyncDone,
            this, &GroupSessionDetailWidget::initGroupSessionMember);
    dataCenter->getChatSessionMemberListAsync(dataCenter->getCurChatSessionId());
    _realGroupSessionName->setText("新的群聊");
}

void GroupSessionDetailWidget::initGroupSessionMember(){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    // 获取指定会话的成员列表
    QList<model::UserInfo>* groupSessionMemberList =
        dataCenter->getChatSessionMemberList(dataCenter->getCurChatSessionId());
    // 进行渲染
    for(auto& userInfo : (*groupSessionMemberList)){
        HeadPortraitItem* item = new HeadPortraitItem(userInfo._headPortrait, userInfo._nickName);
        addGroupMember(item);
    }
}

void GroupSessionDetailWidget::addGroupMember(HeadPortraitItem *headPortraitItem){
    int MAX_COL = 3;
    if(_curCol > MAX_COL){
        _curCol = 0;
        ++_curRow;
    }
    _gridLayout->addWidget(headPortraitItem, _curRow, _curCol, 1, 1);
    ++_curCol;
}
