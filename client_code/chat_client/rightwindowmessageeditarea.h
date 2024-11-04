#ifndef RIGHTWINDOWMESSAGEEDITAREA_H
#define RIGHTWINDOWMESSAGEEDITAREA_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLabel>

#include "model/data.h"

// 右侧窗口下方消息编辑区
class RightWindowMessageEditArea : public QWidget
{
    Q_OBJECT
public:
    explicit RightWindowMessageEditArea(QWidget *parent = nullptr);

    // 初始化信号槽
    void initSignalSlot();

    // 发送文本消息的操作
    void sendTextMessage();
    // 发送图片消息的槽函数
    void clickSendImageMessage();
    // 发送文件消息的槽函数
    void clickSendFileMessage();
    // 按下语音按钮：进行语音录制
    void pressSendVoiceMessage();
    // 释放语音按钮：结束语音录制，发送语音
    void releaseSendVoiceMessage();
    // 发送语音消息的操作
    void sendVoiceMessage(const QString& voicePath);

    // 自己发送消息结束时的处理
    void sendMessageDone(model::MessageType messageType, const QByteArray& content, const QString& extraInfo);

    // 收到别人发送的消息，网络处理完成后的槽函数
    void receiveMessageDone(const model::MessageInfo& newMessage);


private:
    QPushButton* _sendImageBtn;
    QPushButton* _sendFileBtn;
    QPushButton* _sendVoiceBtn;
    QPushButton* _showHistoryMessageBtn;
    QPlainTextEdit* _textEditArea;
    // 表示正在录制语音中！
    QLabel* _recordingLabel;

    QPushButton* _sendMessageBtn;

signals:
};

#endif // RIGHTWINDOWMESSAGEEDITAREA_H
