#include "rightwindowmessageshowarea.h"
#include "debug.h"
#include "selfinfowidget.h"
#include "userinfowidget.h"
#include "mainwidget.h"

#include <QScrollBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>
#include <QString>

using namespace model;

// 右侧窗口消息区
RightWindowMessageShowArea::RightWindowMessageShowArea() {
    // 设置自适应大小
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setWidgetResizable(true);
    // 设置滚动条
    this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 3px; background-color: rgb(240, 240, 240); }");
    this->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    this->setStyleSheet("QScrollArea { border: none; }");

    _container = new QWidget();
    this->setWidget(_container);

    // 布局管理器
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    _container->setLayout(layout);

#if TEST_UI
    UserInfo user;
    user._headPortrait = QIcon(":/resource/image/headPortrait.png");
    user._nickName = "小八";
    user._userId = "111";
    user._phoneNum = "12345678";
    user._personalSignature = "你好";
    MessageInfo message = MessageInfo::makeMessageInfo("", model::TEXT_TYPE, user, "aaa", "");
    this->addMessage(false, message);
    for(int i = 0; i < 10; ++i){
        UserInfo user;
        user._headPortrait = QIcon(":/resource/image/headPortrait.png");
        user._nickName = "小八";
        user._userId = "111";
        user._phoneNum = "12345678";
        user._personalSignature = "你好";
        MessageInfo message = MessageInfo::makeMessageInfo("", model::TEXT_TYPE, user, "aaa", "");
        this->addMessage(true, message);
    }
#endif
}

void RightWindowMessageShowArea::addMessage(bool isLeft, const model::MessageInfo &message){
    MessageItem* messageItem = MessageItem::makeMessageItem(isLeft, message);
    this->_container->layout()->addWidget(messageItem);
}

void RightWindowMessageShowArea::addFrontMessage(bool isLeft, const model::MessageInfo &message){
    MessageItem* messageItem = MessageItem::makeMessageItem(isLeft, message);
    QVBoxLayout* layout = dynamic_cast<QVBoxLayout*>(this->_container->layout());
    layout->insertWidget(0, messageItem);
}

void RightWindowMessageShowArea::clearMessage(){
    QLayout* layout = this->_container->layout();
    for(int i = layout->count() - 1; i >= 0; --i){
        // takeAt后delete
        QLayoutItem* layoutItem = layout->takeAt(i);
        if(layoutItem && layoutItem->widget()){
            delete layout->widget();
        }
    }
}

// 具体的消息项
MessageItem::MessageItem(bool isLeft)
    :_isLeft(isLeft)
{
}

// 工厂
MessageItem* MessageItem::makeMessageItem(bool isLeft, const model::MessageInfo &message){
    // 创建对象和布局管理器
    MessageItem* messageItem = new MessageItem(isLeft);
    QGridLayout* layout = new QGridLayout();

    layout->setSpacing(8);
    layout->setContentsMargins(30, 10, 30, 0);
    messageItem->setMinimumHeight(100);
    messageItem->setLayout(layout);

    // 头像
    QPushButton* headPortrait = new QPushButton();
    headPortrait->setFixedSize(40, 40);
    headPortrait->setIconSize(QSize(40, 40));
    headPortrait->setIcon(message._sender._headPortrait);
    headPortrait->setStyleSheet("QPushButton { border: none; }");

    // 名字和消息发送时间
    QLabel* nameAndTime = new QLabel();
    nameAndTime->setText(message._sender._nickName + " | " + message._sendTime);
    nameAndTime->setAlignment(Qt::AlignBottom);
    nameAndTime->setStyleSheet("QLabel { font-size: 12px; color: rgb(178, 178, 178); }");

    // 具体的消息
    QWidget* contentWidget = nullptr;
    switch(message._messageType){
    case TEXT_TYPE:
        contentWidget = makeTextMessageItem(isLeft, message._content);
        break;
    case IMAGE_TYPE:
        contentWidget = makeImageMessageItem();
        break;
    case FILE_TYPE:
        contentWidget = makeFileMessageItem();
        break;
    case VOICE_TYPE:
        contentWidget = makeVoiceMessageItem();
        break;
    default:
        LOG() << "message type error";
        break;
    }

    if(isLeft){
        layout->addWidget(headPortrait, 0, 0, 2, 1, Qt::AlignTop | Qt::AlignLeft);
        layout->addWidget(nameAndTime, 0, 1, 1, 1);
        layout->addWidget(contentWidget, 1, 1, 1, 1);
    }
    else{
        layout->addWidget(headPortrait, 0, 1, 2, 1, Qt::AlignTop | Qt::AlignRight);
        layout->addWidget(nameAndTime, 0, 0, 1, 1, Qt::AlignRight);
        layout->addWidget(contentWidget, 1, 0, 1, 1);
    }

    // 连接信号槽
    // 点击用户头像显示用户信息
    // BUG：不能在这里 getInstance!!!!否则会死循环的，在初始化的时候又调用初始化！！
    // MainWidget* mainWidget = MainWidget::getInstance();
    if(isLeft){
        // 点击别人的头像显示他人详细信息界面
        connect(headPortrait, &QPushButton::clicked, messageItem, [=](){
            // 其父控件设置成主窗口
            // 只能在内部getInstance，这时候已经初始化完了
            MainWidget* mainWidget = MainWidget::getInstance();
            UserInfoWidget* userInfoWidget = new UserInfoWidget(mainWidget, message._sender);
            // 弹出非模态对话框（非阻塞）
            // userInfoWidget->show();
            // 弹出模态对话框（阻塞）
            userInfoWidget->exec();
        });
    }
    else{
        // 点击自己头像显示个人信息界面
        connect(headPortrait, &QPushButton::clicked, messageItem, [=](){
            MainWidget* mainWidget = MainWidget::getInstance();
            SelfInfoWidget* selfInfoWidget = new SelfInfoWidget(mainWidget);
            // 弹出非模态对话框（非阻塞）
            // selfInfoWidget->show();
            // 弹出模态对话框（阻塞）
            selfInfoWidget->exec();
        });
    }

    return messageItem;
}

QWidget* MessageItem::makeTextMessageItem(bool isLeft, const QString& textContent){
    TextMessageContent* textMessageContent = new TextMessageContent(isLeft, textContent);
    return textMessageContent;
}

QWidget* MessageItem::makeImageMessageItem(){
    return nullptr;
}

QWidget* MessageItem::makeFileMessageItem(){
    return nullptr;

}

QWidget* MessageItem::makeVoiceMessageItem(){
    return nullptr;

}

// 文本消息
TextMessageContent::TextMessageContent(bool isLeft, const QString &textContent)
    : _isLeft(isLeft)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(16);

    this->_textMessage = new QLabel(this);
    this->_textMessage->setText(textContent);
    this->_textMessage->setFont(font);
    this->_textMessage->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    this->_textMessage->setWordWrap(true);  // 自动换行
    // 1.2 类似行间距，transparent表示背景色和父控件一致
    this->_textMessage->setStyleSheet("QLabel { padding: 0 10px; line-height: 1.2; background-color: transparent; }");

}

// 自己手动绘制文本消息的框框，这个函数在控件显示的时候自动调用
void TextMessageContent::paintEvent(QPaintEvent *event){
    (void)event;

    // 计算宽度
    // 获取到单行的最大宽度，设置成父控件总宽度的55%
    QObject* object = this->parent();
    if(!object->isWidgetType()){
        return;
    }
    QWidget* parent = dynamic_cast<QWidget*>(object);
    int width = parent->width() * 0.55;

    // 计算当前文本 一行显示 的宽度
    QFontMetrics fontMetrics(this->_textMessage->font());
    int totalWidth = fontMetrics.horizontalAdvance(this->_textMessage->text());
    // 计算行数，40是左右留出的间距
    int lineNum = (totalWidth / (width - 40)) + 1;
    if(lineNum == 1){
        // 只有一行时可能更短
        width = totalWidth + 40;
    }

    // 计算高度
    // 1.2 是行间距，20是上下边框
    int height = lineNum * (this->_textMessage->font().pixelSize() * 1.2) + 20;

    // 绘制框框
    QPainter painter(this);
    QPainterPath path;
    // 设置 "抗锯齿"
    painter.setRenderHint(QPainter::Antialiasing);
    if (this->_isLeft) {
        painter.setPen(QPen(QColor(255, 255, 255)));
        painter.setBrush(QColor(255, 255, 255));

        // 绘制圆角矩形
        painter.drawRoundedRect(10, 0, width, height, 10, 10);
        // 绘制箭头
        path.moveTo(10, 15);
        path.lineTo(0, 20);
        path.lineTo(10, 25);
        path.closeSubpath();   // 绘制的线形成闭合的多边形, 才能进行使用 Brush 填充颜色.
        painter.drawPath(path);  // 不要忘记真正的绘制操作

        this->_textMessage->setGeometry(10, 0, width, height);
    }
    else {
        painter.setPen(QPen(QColor(137, 217, 97)));
        painter.setBrush(QColor(137, 217, 97));

        // 圆角矩形左侧边的横坐标位置
        int leftPos = this->width() - width - 10; // 10 是用来容纳 箭头 的宽度
        // 圆角矩形右侧边的横坐标位置
        int rightPos = this->width() - 10;
        // 绘制圆角矩形
        painter.drawRoundedRect(leftPos, 0, width, height, 10, 10);
        // 绘制箭头
        path.moveTo(rightPos, 15);
        path.lineTo(rightPos + 10, 20);
        path.lineTo(rightPos, 25);
        path.closeSubpath();
        painter.drawPath(path);

        this->_textMessage->setGeometry(leftPos, 0, width, height);
    }
    // 父控件的高度也要调一下
    parent->setFixedHeight(height + 50);
}
