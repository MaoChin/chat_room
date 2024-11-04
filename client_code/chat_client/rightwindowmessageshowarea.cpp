#include "rightwindowmessageshowarea.h"
#include "debug.h"
#include "selfinfowidget.h"
#include "userinfowidget.h"
#include "mainwidget.h"
#include "toast.h"
#include "soundrecorder.h"

#include <QScrollBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>
#include <QString>
#include <QTimer>
#include <QFileDialog>
#include <QMenu>

#include "model/datacenter.h"

using namespace model;

// 右侧窗口消息区
RightWindowMessageShowArea::RightWindowMessageShowArea() {
    // 设置自适应大小
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setWidgetResizable(true);
    // 设置滚动条
    this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 2px; background-color: rgb(70, 70, 70); }");
    this->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    this->setStyleSheet("QScrollArea { border: none; border-bottom: 1px solid rgb(220, 220, 220); }");

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
            delete layoutItem->widget();
        }
    }
}

void RightWindowMessageShowArea::scrollToEnd(){
    // 实现思路:
    // 拿到滚动区域中的滚动条(垂直滚动条)
    // 获取到滚动条的最大值
    // 根据最大值, 设置滚动条的滚动位置.
    // 为了使滚动效果更佳, 能够在界面绘制好之后(界面绘制是异步的)进行滚动条的设置
    // 给这里的滚动操作, 加上个 "延时"
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [=]() {
        // 获取到垂直滚动条的最大值
        int maxValue = this->verticalScrollBar()->maximum();
        // 设置滚动条的滚动位置
        this->verticalScrollBar()->setValue(maxValue);

        timer->stop();
        timer->deleteLater();
    });
    timer->start(500);
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
        contentWidget = makeImageMessageItem(isLeft, message._fileId, message._content);
        break;
    case FILE_TYPE:
        contentWidget = makeFileMessageItem(isLeft, message);
        break;
    case VOICE_TYPE:
        contentWidget = makeVoiceMessageItem(isLeft, message);
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

    // 当修改个人昵称和头像时，这里要同步进行修改
    if(!isLeft){
        model::DataCenter* dataCenter = model::DataCenter::getInstance();
        connect(dataCenter, &model::DataCenter::modifyNickNameAsyncDone, messageItem, [=]() {
            nameAndTime->setText(dataCenter->getMyself()->_nickName + " | " + message._sendTime);
        });
        connect(dataCenter, &model::DataCenter::modifyHeadPortraitAsyncDone, messageItem, [=]() {
            headPortrait->setIcon(dataCenter->getMyself()->_headPortrait);
        });
    }
    return messageItem;
}

QWidget* MessageItem::makeTextMessageItem(bool isLeft, const QString& textContent){
    TextMessageContent* textMessageContent = new TextMessageContent(isLeft, textContent,
            model::TEXT_TYPE, "", QByteArray());
    return textMessageContent;
}

QWidget* MessageItem::makeImageMessageItem(bool isLeft, const QString& fileId, const QByteArray& imageContent){
    ImageMessageContent* imageMessageContent = new ImageMessageContent(isLeft, fileId, imageContent);
    return imageMessageContent;
}

QWidget* MessageItem::makeFileMessageItem(bool isLeft, const model::MessageInfo& messageInfo){
    TextMessageContent* fileMessageContent = new TextMessageContent(isLeft, "[文件] " + messageInfo._fileName,
            messageInfo._messageType, messageInfo._fileId, messageInfo._content);
    return fileMessageContent;
}

QWidget* MessageItem::makeVoiceMessageItem(bool isLeft, const model::MessageInfo& messageInfo){
    TextMessageContent* voiceMessageContent = new TextMessageContent(isLeft, "[语音]",
            messageInfo._messageType, messageInfo._fileId, messageInfo._content);
    return voiceMessageContent;
}

// 文本消息/文件消息/语音消息的显示
TextMessageContent::TextMessageContent(bool isLeft, const QString &textContent, model::MessageType messageType,
                const QString& fileId, const QByteArray& content)
    : _isLeft(isLeft),
    _messageType(messageType),
    _fileId(fileId),
    _content(content)
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

    // 针对文件消息, 并且 content 为空的情况下, 通过网络来加载数据
    if (messageType == model::TEXT_TYPE) {
        return;
    }

    if (this->_content.isEmpty()) {
        // 这是服务器主动推送的文件数据，还需要拿着 fileId, 去服务器获取文件内容
        // 通过这种方式减少 客户端--服务端 之间的网络带宽
        model::DataCenter* dataCenter = model::DataCenter::getInstance();
        connect(dataCenter, &DataCenter::getSingleFileContentAsyncDone, this, &TextMessageContent::updateUI);
        dataCenter->getSingleFileContentAsync(_fileId);
    }
    else {
        // content 不为空, 说明当前的这个数据就在客户端，直接就把 表示加载状态的变量设为 true
        this->_loadContentDone = true;
    }
}

void TextMessageContent::updateUI(const QString &fileId, const QByteArray &fileContent){
    // 判定收到的数据是否属于当前 fileId 的
    if (fileId != this->_fileId) {
        return;
    }
    this->_content = fileContent;
    this->_loadContentDone = true;
    // 对于文件消息来说, 要在界面上显示 "[文件] test.txt" 这样形式, 这个内容和文件 content 无关
    // 在从服务器拿到文件正文之前, 界面内容应该就是绘制好了, 此时拿到正文之后, 界面应该也不必做出任何实质性的调整
    // 所以下列的 this->update(), 没有也行
    this->update();
}

void TextMessageContent::mousePressEvent(QMouseEvent *event){
    // 实现鼠标点击之后, 触发文件另存为/语音播放
    if (event->button() == Qt::LeftButton) {
        // 左键按下
        if (this->_messageType == model::FILE_TYPE){
            // 触发另存为
            if (!this->_loadContentDone) {
                Toast::showMessage("数据尚未加载成功, 请稍后重试");
                return;
            }
            saveFile(this->_content);
        }
        else if(this->_messageType == model::VOICE_TYPE) {
            // 触发语音播放
            if (!this->_loadContentDone) {
                Toast::showMessage("数据尚未加载成功, 请稍后重试");
                return;
            }
            SoundRecorder* soundRecorder = SoundRecorder::getInstance();
            this->_textMessage->setText("播放中...");
            connect(soundRecorder, &SoundRecorder::soundPlayDone, this, &TextMessageContent::playDone, Qt::UniqueConnection);
            soundRecorder->startPlay(this->_content);
        }
        else{
            // 普通的文本消息, 啥都不做
        }
    }
}

void TextMessageContent::saveFile(const QByteArray &content){
    // 弹出对话框, 让用户选择路径
    QString filePath = QFileDialog::getSaveFileName(this, "另存为", QDir::homePath(), "*");
    if (filePath.isEmpty()) {
        LOG() << "cancle save file";
        return;
    }
    writeByteArrayToFile(filePath, content);
}

void TextMessageContent::playDone(){
    if (this->_textMessage->text() == "播放中...") {
        this->_textMessage->setText("[语音]");
    }
}

void TextMessageContent::contextMenuEvent(QContextMenuEvent *event){
    (void) event;
    if (_messageType != model::VOICE_TYPE) {
        LOG() << "not the voice message!";
        return;
    }

    QMenu* menu = new QMenu(this);
    QAction* action = menu->addAction("语音转文字");
    menu->setStyleSheet("QMenu { color: rgb(0, 0, 0); }");

    // 点击菜单项 -- 语音转文字  时触发的槽函数
    connect(action, &QAction::triggered, this, [=]() {
        model::DataCenter* dataCenter = model::DataCenter::getInstance();
        // 转换完成时的槽函数
        connect(dataCenter, &DataCenter::voiceConvertTextAsyncDone, this,
                &TextMessageContent::voiceConvertTextDone, Qt::UniqueConnection);

        dataCenter->voiceConvertTextAsync(this->_fileId, this->_content);
    });

    // 此处弹出 "模态对话框" 显示菜单/菜单项，exec 会阻塞用户的进一步操作
    menu->exec(event->globalPos());
    delete menu;
}

void TextMessageContent::voiceConvertTextDone(const QString &fileId, const QString &text){
    if (this->_fileId != fileId) {
        // 这个结果不是针对这一条语音消息的结果
        return;
    }
    // 修改界面内容
    this->_textMessage->setText("[语音转文字] " + text);
    this->update();
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


// 图片消息的显示
ImageMessageContent::ImageMessageContent(bool isLeft, const QString &fileId, const QByteArray &imageContent)
    :_isLeft(isLeft),
    _fileId(fileId),
    _imageContent(imageContent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    _imageBtn = new QPushButton(this);
    _imageBtn->setStyleSheet("QPushButton { border: none; }");

    if (imageContent.isEmpty()) {
        // 这是服务器主动推送的图片数据，还需要拿着 fileId, 去服务器获取图片内容
        // 通过这种方式减少 客户端--服务端 之间的网络带宽
        model::DataCenter* dataCenter = model::DataCenter::getInstance();
        connect(dataCenter, &DataCenter::getSingleFileContentAsyncDone, this, &ImageMessageContent::updateUI);
        dataCenter->getSingleFileContentAsync(fileId);
    }
}

void ImageMessageContent::updateUI(const QString& fileId, const QByteArray& imageContent){
    if (this->_fileId != fileId) {
        // 当前响应的图片是其他的 图片消息
        return;
    }
    this->_imageContent = imageContent;

    // 把图片绘制到界面上
    this->update();
}


void ImageMessageContent::paintEvent(QPaintEvent *event){
    (void) event;
    // 1. 先拿到该元素的父元素, 看父元素(就是整个消息展示区)的宽度是多少
    //    此处显示的图片宽度的上限为父元素宽度的 50%
    QObject* object = this->parent();
    if (!object->isWidgetType()) {
        return;
    }
    QWidget* parent = dynamic_cast<QWidget*>(object);
    int maxWidth = parent->width() * 0.5;

    // 2. 加载二进制数据为图片对象
    QImage image;
    if (_imageContent.isEmpty()) {
        // 此时图片的响应数据还没回来, 先拿一个 "固定默认图片" 顶替一下
        QByteArray tmpContent = readFileToByteArray(":/resource/image/image.png");
        image.loadFromData(tmpContent);
    }
    else{
        // 此处的 load 操作 QImage 能够自动识别当前图片是啥类型的 (png, jpg....)
        image.loadFromData(_imageContent);
    }

    // 3. 针对图片进行缩放.
    int maxHeight = 0;
    if (image.width() > maxWidth) {
        // 图片更宽, 需要把图片缩放一下, 使用 width 作为实际的宽度
        // 等比例缩放.
        maxHeight = ((double)image.height() / image.width()) * maxWidth;
    }
    else{
        // 图片本身不太宽, 不需要缩放.
        maxWidth = image.width();
        maxHeight = image.height();
    }

    // pixmap 只是一个中间变量. QImage 不能直接转成 QIcon, 需要 QPixmap 中转一下
    QPixmap pixmap = QPixmap::fromImage(image);
    // _imageBtn->setFixedSize(width, height);
    _imageBtn->setIconSize(QSize(maxWidth, maxHeight));
    _imageBtn->setIcon(QIcon(pixmap));

    // 4. 由于图片高度是计算出来的，该元素的父对象的高度, 要能够容纳下当前的元素
    //    此处 + 50 是为了能够容纳下 上方的 "名字" 部分，同时留下一点 冗余 空间
    parent->setFixedHeight(maxHeight + 50);

    // 5. 确定消息所在的位置，左侧消息, 和右侧消息, 要显示的位置是不同的.
    if (_isLeft) {
        _imageBtn->setGeometry(10, 0, maxWidth, maxHeight);
    }
    else {
        int leftPos = this->width() - maxWidth - 10;
        _imageBtn->setGeometry(leftPos, 0, maxWidth, maxHeight);
    }
}


