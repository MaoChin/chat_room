#include "middlewindowarea.h"
#include "debug.h"
#include "model/data.h"
#include "model/datacenter.h"
#include "mainwidget.h"

#include <QScrollBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QTimer>

MiddleWindowArea::MiddleWindowArea(QWidget *parent)
    : QScrollArea{parent}
{
    // 开启滚动效果
    this->setWidgetResizable(true);
    // 设置滚动条样式
    this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 2px; background-color: rgb(70, 70, 70); }");
    this->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; background-color: rgb(46, 46, 46); }");
    this->setStyleSheet("QWidget { border: none; }");

    // 把_container和滚动区关联起来
    _container = new QWidget();
    _container->setFixedWidth(300);
    this->setWidget(_container);

    // 布局管理器
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignTop);
    _container->setLayout(layout);


// 测试使用！
#if TEST_UI
    for(int i = 0; i < 30; ++i){
        QIcon headPortrait(":/resource/image/headPortrait.png");
        addItem(FRIENDAPPLY_TYPE, QString::number(i), headPortrait, "小八", "消息");
    }

#endif
}

void MiddleWindowArea::addItem(ItemType itemType, const QString& id, const QIcon& headPortrait,
                               const QString &name, const QString &text){
    MiddleWindowAreaItem* middleWindowAreaItem = nullptr;
    if(itemType == CHATSESSION_TYPE){
        middleWindowAreaItem = new ChatSesionItem(this, headPortrait, id, name, text);
    }
    else if(itemType == FRIEND_TYPE){
        middleWindowAreaItem = new FriendItem(this, headPortrait, id, name, text);
    }
    else if(itemType == FRIENDAPPLY_TYPE){
        middleWindowAreaItem = new FriendApplyItem(this, headPortrait, id, name);
    }
    else{
        LOG() << "itemType error!";
    }
    // 把Item添加到_container的布局管理器中
    _container->layout()->addWidget(middleWindowAreaItem);
}

void MiddleWindowArea::clearAllItem(){
    QLayout* layout = _container->layout();
    // 一边遍历一边删除有类似迭代器失效的问题!!
    // for(int i = 0; i < layout->count(); ++i){
    //     QLayoutItem* layoutItem = layout->takeAt(i);
    //     if(layoutItem->widget()){
    //         delete layoutItem->widget();
    //     }
    // }

    // 解决：从后向前删除或者一直删除 0 下标的元素
    // 还有个注意点：从后向前遍历时 i 不能使用size_t类型！！否则会死循环
    for(int i = layout->count() - 1; i >= 0; --i){
        // 去掉第i个位置的元素
        QLayoutItem* layoutItem = layout->takeAt(i);
        // delete 掉
        if(layoutItem && layoutItem->widget()){
            delete layoutItem->widget();
        }
    }
}

void MiddleWindowArea::selectItem(int index){
    if(index < 0 || index >= _container->layout()->count()){
        LOG() << "selectItem: index error!";
        return;
    }
    QLayoutItem* layoutItem = _container->layout()->itemAt(index);
    if(layoutItem == nullptr || layoutItem->widget() == nullptr){
        LOG() << "selectItem: index error!";
        return;
    }
    MiddleWindowAreaItem* middleWindowAreaItem = dynamic_cast<MiddleWindowAreaItem*>(layoutItem->widget());
    middleWindowAreaItem->select();
}

void MiddleWindowArea::scrollToTop(){
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [=]() {
        // 获取到垂直滚动条的最小值
        int minValue = this->verticalScrollBar()->minimum();
        // 设置滚动条的滚动位置
        this->verticalScrollBar()->setValue(minValue);

        timer->stop();
        timer->deleteLater();
    });
    timer->start(300);
}


/////////////////////////
/// \brief MiddleWindowAreaItem
MiddleWindowAreaItem::MiddleWindowAreaItem(QWidget *onwer, const QIcon &headPortrait, const QString &name, const QString &text)
    :_onwer(onwer)
{
    this->setFixedHeight(70);
    this->setStyleSheet("QWidget { background-color: rgb(231, 231, 231); }");

    //  布局管理
    QGridLayout* layout = new QGridLayout();
    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(0);
    layout->setContentsMargins(20, 0, 0, 0);
    this->setLayout(layout);

    // 头像
    QPushButton* headPortraitBtn = new QPushButton();
    headPortraitBtn->setFixedSize(60, 60);
    headPortraitBtn->setIconSize(QSize(60, 60));
    headPortraitBtn->setIcon(headPortrait);
    headPortraitBtn->setStyleSheet("QPushButton { border: none; }");
    headPortraitBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // 名字
    QLabel* nameLabel = new QLabel();
    nameLabel->setText(name);
    nameLabel->setStyleSheet("QLabel { font-size: 18px; font-weight: 600; }");
    nameLabel->setFixedHeight(35);
    nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 消息预览
    _messageLabel = new QLabel();
    _messageLabel->setText(text);
    _messageLabel->setFixedHeight(35);
    _messageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // (0, 0)位置，占2行2列
    layout->addWidget(headPortraitBtn, 0, 0, 2, 2);
    // (0, 2)位置，占1行8列，8列主要是为了兼容好友申请按钮
    layout->addWidget(nameLabel, 0, 2, 1, 8);
    // (1, 2)位置，占1行8列
    layout->addWidget(_messageLabel, 1, 2, 1, 8);
}

// 这个重写的函数是为了使MiddleWindowAreaItem可以使用QSS样式表！
void MiddleWindowAreaItem::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MiddleWindowAreaItem::mousePressEvent(QMouseEvent *event){
    (void)event;
    select();
}

void MiddleWindowAreaItem::enterEvent(QEnterEvent *event){
    (void)event;
    // 当前项是被选中的就不用管
    if(this->_selected){
        return;
    }
    this->setStyleSheet("QWidget { background-color: rgb(220, 220, 220); }");
}

void MiddleWindowAreaItem::leaveEvent(QEvent *event){
    (void)event;
    if(this->_selected){
        return;
    }
    this->setStyleSheet("QWidget { background-color: rgb(231, 231, 231); }");
}

void MiddleWindowAreaItem::select(){
    // 同时只能有一个被选中，把之前选中的颜色改回去
    const QObjectList items = this->parentWidget()->children();
    for(QObject* item : items){
        if(!item->isWidgetType()){
            continue;
        }
        MiddleWindowAreaItem* tmpItem = dynamic_cast<MiddleWindowAreaItem*>(item);
        if(tmpItem->_selected){
            tmpItem->_selected = false;
            tmpItem->setStyleSheet("QWidget { background-color: rgb(231, 231, 231); }");
        }
    }
    this->setStyleSheet("QWidget { background-color: rgb(210, 210, 210); }");
    _selected = true;
    // 这个是多态调用
    this->active();
}

void MiddleWindowAreaItem::active(){
    // 父类的方法，不需要实现
}

// 具体的列表项
// 会话列表项
ChatSesionItem::ChatSesionItem(QWidget* owner, const QIcon& headPortrait, const QString& chatSessionId,
                               const QString& chatSessionName, const QString& lastMessage)
    : MiddleWindowAreaItem(owner, headPortrait, chatSessionName, lastMessage),
    _chatSessionId(chatSessionId),
    _showText(lastMessage)
{
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    // 处理 更新特定会话展示中最后一条消息 的信号
    connect(dataCenter, &model::DataCenter::updateLastMessage, this, &ChatSesionItem::updateLastMessage);

    // 显示未读消息信息，每次重启客户端都能走到这一段逻辑
    int unread = dataCenter->getUnreadNum(chatSessionId);
    if(unread > 0){
        this->_messageLabel->setText("[未读" + QString::number(unread) + "条]: " + _showText);
    }
}

void ChatSesionItem::active(){
    // 点击会话时的操作--右侧窗口显示这个聊天会话的历史消息
    MainWidget* mainWidget = MainWidget::getInstance();
    mainWidget->loadRecentMessage(_chatSessionId);

    // 清除这个会话的未读消息
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    dataCenter->clearUnreadMessage(_chatSessionId);
    this->_messageLabel->setText(_showText);
}

void ChatSesionItem::updateLastMessage(const QString &chatSessionId){
    if(this->_chatSessionId != chatSessionId){
        // 不是这个会话
        return;
    }
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    QList<model::MessageInfo>* messageList = dataCenter->getChatSessionRecentMessage(chatSessionId);
    if(messageList == nullptr || messageList->size() == 0){
        // 没有消息
        return;
    }

    // 获取显示内容
    const model::MessageInfo& lastMessage = messageList->back();
    if(lastMessage._messageType == model::MessageType::TEXT_TYPE){
        _showText = lastMessage._content;
    }
    else if(lastMessage._messageType == model::MessageType::FILE_TYPE){
        _showText = "[文件] " + lastMessage._fileName;
    }
    else if(lastMessage._messageType == model::MessageType::IMAGE_TYPE){
        _showText = "[图片] " + lastMessage._fileName;
    }
    else if(lastMessage._messageType == model::MessageType::VOICE_TYPE){
        _showText = "[语音] ";
    }
    else{
        LOG() << "message type error: " << lastMessage._messageType;
        return;
    }

    // 进行渲染，要判断这个会话是不是 当前选中的会话
    if(dataCenter->getCurChatSessionId() == chatSessionId){
        this->_messageLabel->setText(_showText);
    }
    else{
        int unread = dataCenter->getUnreadNum(chatSessionId);
        if(unread > 0){
            this->_messageLabel->setText("[未读" + QString::number(unread) + "条]: " + _showText);
        }
    }
}

// 好友列表项
FriendItem::FriendItem(QWidget* owner, const QIcon& headPortrait, const QString& userId,
                       const QString& nickName, const QString& personalSignature)
    : MiddleWindowAreaItem(owner, headPortrait, nickName, personalSignature),
    _userId(userId)
{

}

void FriendItem::active(){
    // 点击好友时的操--切换到会话列表项，并且右侧窗口显示对应的聊天历史消息
    MainWidget* mainWidget = MainWidget::getInstance();
    mainWidget->clickFriendInFriendItem(_userId);
}

// 好友申请列表项
FriendApplyItem::FriendApplyItem(QWidget *owner, const QIcon &headPortrait, const QString &userId,
                                 const QString &nickName)
    : MiddleWindowAreaItem(owner, headPortrait, nickName, ""),
    _userId(userId)
{
    // 对于好友申请列表，需要有“接受”和“拒绝”的按钮
    // 这里先把 _messageLabel删掉，其实感觉留下更好，可以用来表示验证信息
    QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());
    layout->removeWidget(_messageLabel);
    // 别忘了delete
    delete _messageLabel;

    QString btnStyle = "QPushButton { font-size: 14px; }";
    btnStyle += "QPushButton:hover { background-color: rgb(200, 200, 200); }";
    btnStyle += "QPushButton:pressed { background-color: rgb(220, 220, 220); }";

    QPushButton* acceptBtn = new QPushButton();
    acceptBtn->setStyleSheet(btnStyle);
    acceptBtn->setText("接受");
    QPushButton* refuseBtn = new QPushButton();
    refuseBtn->setStyleSheet(btnStyle);
    refuseBtn->setText("拒绝");

    // 在(1, 2)位置，占一行一列
    layout->addWidget(acceptBtn, 1, 2, 1, 1);
    // 在(1, 4)位置，占一行一列
    layout->addWidget(refuseBtn, 1, 4, 1, 1);

    // 点击“接受”按钮的信号槽
    connect(acceptBtn, &QPushButton::clicked, this, &FriendApplyItem::acceptAddFriendApply);
    // 点击“拒绝”按钮的信号槽
    connect(refuseBtn, &QPushButton::clicked, this, &FriendApplyItem::refuseAddFriendApply);
}

void FriendApplyItem::active(){

}

void FriendApplyItem::acceptAddFriendApply(){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    // 这个操作完成的处理需要更新申请列表和好友列表，放到mainWidget中进行
    dataCenter->acceptAddFriendApplyAsync(_userId);
}

void FriendApplyItem::refuseAddFriendApply(){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    dataCenter->refuseAddFriendApplyAsync(_userId);
}
