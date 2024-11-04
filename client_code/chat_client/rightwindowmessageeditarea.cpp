#include "rightwindowmessageeditarea.h"

#include <QVBoxLayout>
#include <QScrollBar>
#include <QFileDialog>

#include "model/datacenter.h"
#include "toast.h"
#include "mainwidget.h"
#include "historymessagedialog.h"
#include "soundrecorder.h"

RightWindowMessageEditArea::RightWindowMessageEditArea(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedHeight(200);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 布局管理器
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setAlignment(Qt::AlignTop);
    // 左，上，右，下
    vlayout->setContentsMargins(10, 10, 12, 12);
    this->setLayout(vlayout);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setSpacing(15);
    hlayout->setContentsMargins(10, 0, 0, 0);
    hlayout->setAlignment(Qt::AlignLeft);
    // 垂直布局中有水平布局
    vlayout->addLayout(hlayout);

    // 按钮设置
    QString btnStyle = "QPushButton { background-color: rgb(240, 240, 240); border: none; }";
    btnStyle += "QPushButton:hover { background-color: rgb(225, 225, 225); }";
    btnStyle += "QPushButton:pressed { background-color: rgb(255, 255, 255); }";
    QSize fixedSize(24, 24);
    QSize iconSize(24, 24);
    _sendImageBtn = new QPushButton();
    _sendImageBtn->setFixedSize(fixedSize);
    _sendImageBtn->setIconSize(iconSize);
    _sendImageBtn->setIcon(QIcon(":/resource/image/imageBtn.png"));
    _sendImageBtn->setStyleSheet(btnStyle);
    hlayout->addWidget(_sendImageBtn);

    _sendFileBtn = new QPushButton();
    _sendFileBtn->setFixedSize(fixedSize);
    _sendFileBtn->setIconSize(iconSize);
    _sendFileBtn->setIcon(QIcon(":/resource/image/fileBtn.png"));
    _sendFileBtn->setStyleSheet(btnStyle);
    hlayout->addWidget(_sendFileBtn);

    _sendVoiceBtn = new QPushButton();
    _sendVoiceBtn->setFixedSize(fixedSize);
    _sendVoiceBtn->setIconSize(iconSize);
    _sendVoiceBtn->setIcon(QIcon(":/resource/image/voiceBtn.png"));
    _sendVoiceBtn->setStyleSheet(btnStyle);
    hlayout->addWidget(_sendVoiceBtn);

    _showHistoryMessageBtn = new QPushButton();
    _showHistoryMessageBtn->setFixedSize(fixedSize);
    _showHistoryMessageBtn->setIconSize(iconSize);
    _showHistoryMessageBtn->setIcon(QIcon(":/resource/image/showHistoryBtn.png"));
    _showHistoryMessageBtn->setStyleSheet(btnStyle);
    hlayout->addWidget(_showHistoryMessageBtn);

    _textEditArea = new QPlainTextEdit();
    _textEditArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QString editAreaStyle = "QPlainTextEdit { border: none; background-color: transparent; font-size: 14px; padding: 14px; }";
    editAreaStyle += "QPlainTextEdit:pressed { background-color: rgn(225, 225, 225); }";
    _textEditArea->setStyleSheet(editAreaStyle);
    _textEditArea->verticalScrollBar()->setStyleSheet("QScrollBar { width: 2px; background-color: rgb(45, 45, 45); }");
    vlayout->addWidget(_textEditArea);

    // 提示正在录制语音中的 label
    _recordingLabel = new QLabel();
    _recordingLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _recordingLabel->setText("正在录音中...");
    _recordingLabel->setAlignment(Qt::AlignCenter);
    _recordingLabel->setFont(QFont("微软雅黑", 18, 400));
    vlayout->addWidget(_recordingLabel);
    _recordingLabel->hide();

    _sendMessageBtn = new QPushButton();
    _sendMessageBtn->setText("发送");
    _sendMessageBtn->setFixedSize(120, 40);
    QString sendMessageBtnStyle = "QPushButton { font-size: 16px; color: rgb(7, 193, 96); border: none; background-color: rgb(233, 233, 233); border-radius: 10px; }";
    // 鼠标悬停效果
    sendMessageBtnStyle += "QPushButton:hover { background-color: rgb(220, 220, 220); }";
    // 鼠标按下效果
    sendMessageBtnStyle += "QPushButton:pressed {background-color: rgb(210, 210, 210); }";
    _sendMessageBtn->setStyleSheet(sendMessageBtnStyle);
    vlayout->addWidget(_sendMessageBtn, 0, Qt::AlignRight | Qt::AlignVCenter);


    // 初始化信号槽
    initSignalSlot();
}

void RightWindowMessageEditArea::initSignalSlot(){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();

    // 点击历史消息按钮弹出历史消息对话框
    connect(_showHistoryMessageBtn, &QPushButton::clicked, this, [=](){
        if(dataCenter->getCurChatSessionId() == ""){
            Toast::showMessage("当前未选中会话");
            return;
        }
        HistoryMessageDialog* historyMessageDialog = new HistoryMessageDialog(this);
        historyMessageDialog->exec();
    });

    // 点击发送按钮进行消息发送
    connect(_sendMessageBtn, &QPushButton::clicked, this, &RightWindowMessageEditArea::sendTextMessage);

    // 发送消息完成的信号槽---自己发送消息
    connect(dataCenter, &model::DataCenter::sendMessageAsyncDone, this, &RightWindowMessageEditArea::sendMessageDone);

    // 收到别人发送的消息 处理完成后的信号槽！！
    // 正常来说这个应该放到 ...showarea.cpp 中，但是这个处理逻辑和上面的自己发送消息有点类似，就也放到这边了
    // 这两个信号槽的处理都放到 ...showarea.cpp 感觉更合理一点
    connect(dataCenter, &model::DataCenter::netClientReceiveMessageDone, this, &RightWindowMessageEditArea::receiveMessageDone);


    // 点击图片按钮进行图片消息选择
    connect(_sendImageBtn, &QPushButton::clicked, this, &RightWindowMessageEditArea::clickSendImageMessage);

    // 点击文件按钮进行文件消息选择
    connect(_sendFileBtn, &QPushButton::clicked, this, &RightWindowMessageEditArea::clickSendFileMessage);

    // 按下语音按钮：进行录音
    connect(_sendVoiceBtn, &QPushButton::pressed, this, &RightWindowMessageEditArea::pressSendVoiceMessage);
    // 释放语音按钮：结束录音, 发送语音消息
    connect(_sendVoiceBtn, &QPushButton::released, this, &RightWindowMessageEditArea::releaseSendVoiceMessage);

    // 音频录制播放相关
    SoundRecorder* soundRecorder = SoundRecorder::getInstance();
    // 语音录制完成的信号槽
    connect(soundRecorder, &SoundRecorder::soundRecordDone, this, &RightWindowMessageEditArea::sendVoiceMessage);
}

void RightWindowMessageEditArea::sendTextMessage(){
    // 判断选中的会话
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    const QString& curChatSessionId = dataCenter->getCurChatSessionId();
    if(curChatSessionId.isEmpty()){
        LOG() << "not select a chat session";
        Toast::showMessage("当前未选中会话");
        return;
    }
    // 获取到输入框的内容, trimmed 操作去除字符串两端的空格
    const QString& content = _textEditArea->toPlainText().trimmed();
    if (content.isEmpty()) {
        LOG() << "the message is empty";
        return;
    }

    // 清空输入框已有内容
    _textEditArea->setPlainText("");

    // 通过网络发送数据给服务器
    dataCenter->sendTextMessageAsync(curChatSessionId, content);
}

void RightWindowMessageEditArea::clickSendImageMessage(){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    // 1. 判定当前是否有选中的会话
    if (dataCenter->getCurChatSessionId().isEmpty()) {
        LOG() << "not select a chat session";
        Toast::showMessage("当前未选中会话");
        return;
    }

    // 2. 弹出文件对话框
    QString filter = "Image Files (*.png *.jpg *.jpeg)";
    QString imagePath = QFileDialog::getOpenFileName(this, "选择图片", QDir::homePath(), filter);
    if (imagePath.isEmpty()) {
        LOG() << "用户取消选择图片";
        return;
    }

    // 3. 读取图片的内容
    QByteArray imageContent = model::readFileToByteArray(imagePath);

    // 4. 发送请求
    dataCenter->sendImageMessageAsync(dataCenter->getCurChatSessionId(), imageContent);
}

void RightWindowMessageEditArea::clickSendFileMessage(){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    // 1. 判定当前是否选中了会话
    if (dataCenter->getCurChatSessionId().isEmpty()) {
        LOG() << "not select a chat session";
        Toast::showMessage("当前未选中会话");
        return;
    }

    // 2. 弹出对话框, 选择文件.
    QString filter = "*";
    QString filePath = QFileDialog::getOpenFileName(this, "选择文件", QDir::homePath(), filter);
    if (filePath.isEmpty()) {
        LOG() << "用户取消选择文件";
        return;
    }

    // 3. 读取文件内容, 此处暂时不考虑大文件的情况, 比如有的文件, 几百 MB, 或者几个 GB
    //    如果是针对大文件的话, 编写专门的网络通信接口, 实现 "分片传输" 效果
    QByteArray fileContent = model::readFileToByteArray(filePath);

    // 4. 传输文件, 需要获取到 文件名
    QFileInfo fileInfo(filePath);
    const QString& fileName = fileInfo.fileName();

    // 5. 发送消息
    dataCenter->sendFileMessageAsync(dataCenter->getCurChatSessionId(), fileName, fileContent);
}

void RightWindowMessageEditArea::pressSendVoiceMessage(){
    // 判定当前是否选中会话.
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    if (dataCenter->getCurChatSessionId().isEmpty()) {
        LOG() << "not select a chat session";
        Toast::showMessage("当前未选中会话");
        return;
    }

    // 切换语音按钮的图标
    _sendVoiceBtn->setIcon(QIcon(":/resource/image/voiceBtnVoice.png"));

    // 开始录音
    SoundRecorder* soundRecorder = SoundRecorder::getInstance();
    soundRecorder->startRecord();

    _recordingLabel->show();
    _textEditArea->hide();
}

void RightWindowMessageEditArea::releaseSendVoiceMessage(){
    // 判定当前是否选中会话.
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    if (dataCenter->getCurChatSessionId().isEmpty()) {
        LOG() << "not select a chat session";
        // Toast::showMessage("当前未选中会话");
        return;
    }

    // 切换语音按钮的图标
    _sendVoiceBtn->setIcon(QIcon(":/resource/image/voiceBtn.png"));

    // 停止录音
    SoundRecorder* soundRecorder = SoundRecorder::getInstance();
    soundRecorder->stopRecord();

    _recordingLabel->hide();
    _textEditArea->show();
}

void RightWindowMessageEditArea::sendVoiceMessage(const QString &voicePath)
{
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    // 1. 读取到语音文件的内容
    QByteArray voiceContent = model::readFileToByteArray(voicePath);
    if (voiceContent.isEmpty()) {
        LOG() << "语音文件加载失败";
        return;
    }
    dataCenter->sendVoiceMessageAsync(dataCenter->getCurChatSessionId(), voiceContent);
}


void RightWindowMessageEditArea::sendMessageDone(model::MessageType messageType, const QByteArray &content, const QString &extraInfo){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    const QString& chatSessionId = dataCenter->getCurChatSessionId();
    model::UserInfo* myself = dataCenter->getMyself();
    model::MessageInfo messageInfo = model::MessageInfo::makeMessageInfo(chatSessionId, messageType, *myself, content, extraInfo);

    // 把消息添加到dataCenter中
    dataCenter->addChatSessionMessage(messageInfo);

    // 把消息显示到右侧消息显示区
    MainWidget* mainWidget = MainWidget::getInstance();
    RightWindowMessageShowArea* rightWindowShowArea = mainWidget->getRightWindowMessageShowArea();
    rightWindowShowArea->addMessage(false, messageInfo);

    // 把消息显示滚动条设置到末尾
    rightWindowShowArea->scrollToEnd();

    // 使用信号槽，使会话预览时更新最后一条消息
    emit dataCenter->updateLastMessage(chatSessionId);
}

void RightWindowMessageEditArea::receiveMessageDone(const model::MessageInfo &newMessage){
    // 把消息显示到右侧消息显示区
    MainWidget* mainWidget = MainWidget::getInstance();
    RightWindowMessageShowArea* rightWindowShowArea = mainWidget->getRightWindowMessageShowArea();
    rightWindowShowArea->addMessage(true, newMessage);

    // 把消息显示滚动条设置到末尾
    rightWindowShowArea->scrollToEnd();

    // 这里会话预览放到netclient那里统一处理
    // 使用信号槽，使会话展示时更新最后一条消息
    // emit dataCenter->updateLastMessage(chatSessionId);

    // 给个提示
    Toast::showMessage("收到新消息");
}
