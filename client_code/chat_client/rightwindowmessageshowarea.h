#ifndef RIGHTWINDOWMESSAGESHOWAREA_H
#define RIGHTWINDOWMESSAGESHOWAREA_H

#include <QScrollArea>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>

#include "model/data.h"

// 右侧窗口 消息区
// QScrollArea 支持滚动
class RightWindowMessageShowArea : public QScrollArea
{
    Q_OBJECT
public:
    RightWindowMessageShowArea();
    // 尾插
    void addMessage(bool isLeft, const model::MessageInfo& message);
    // 头插
    void addFrontMessage(bool isLeft, const model::MessageInfo& message);
    // 清空消息
    void clearMessage();

    // 把历史消息的滚动条滚动到末尾
    void scrollToEnd();

private:
    // 实际存放内容的 widget
    QWidget* _container;

};

// 具体的一个消息项
class MessageItem : public QWidget
{
    Q_OBJECT
public:
    MessageItem(bool isLeft);

public:
    // 工厂模式
    static MessageItem* makeMessageItem(bool isLeft, const model::MessageInfo& message);

    static QWidget* makeTextMessageItem(bool isLeft, const QString& textContent);
    static QWidget* makeImageMessageItem(bool isLeft, const QString& fileId, const QByteArray& imageContent);
    static QWidget* makeFileMessageItem(bool isLeft,  const model::MessageInfo& messageInfo);
    static QWidget* makeVoiceMessageItem(bool isLeft, const model::MessageInfo& messageInfo);

private:
    bool _isLeft;

};

// 文本消息的正文显示，文件消息显示，语音消息显示
class TextMessageContent : public QWidget{
    Q_OBJECT
public:
    TextMessageContent(bool isLeft, const QString& textContent, model::MessageType messageType,
                const QString& fileId, const QByteArray& content);

    // 更新界面显示
    void updateUI(const QString& fileId, const QByteArray& imageContent);

    // 对于文件/语音类型的数据，鼠标点击时的操作: 另存为/播放语音
    void mousePressEvent(QMouseEvent* event) override;

    // 保存文件
    void saveFile(const QByteArray& content);

    // 语音播放完毕
    void playDone();

    // 右键语音消息弹出语音转文字的功能
    void contextMenuEvent(QContextMenuEvent *event) override;
    // 语音转文字完成
    void voiceConvertTextDone(const QString &fileId, const QString &text);

    // 文本消息的框框需要自己手动绘制！
    void paintEvent(QPaintEvent* event) override;

private:
    // 文字部分
    bool _isLeft = true;
    // 显示文本内容的组件
    QLabel* _textMessage;

    // 文件类型
    model::MessageType _messageType;
    // 文件id
    QString _fileId;
    // 文件/语音内容
    QByteArray _content;

    // 表示加载状态
    bool _loadContentDone = false;
};

// 图片消息的显示
class ImageMessageContent : public QWidget{
    Q_OBJECT
public:
    ImageMessageContent(bool isLeft, const QString& fileId, const QByteArray& imageContent);

    // 更新界面显示
    void updateUI(const QString& fileId, const QByteArray& imageContent);

    // 将 图片消息 显示在界面上
    void paintEvent(QPaintEvent* event) override;

private:
    bool _isLeft = true;

    // 用btn展示图片
    QPushButton* _imageBtn;
    // 图片的 fileId
    QString _fileId;
    // 图片内容
    QByteArray _imageContent;
};


#endif // RIGHTWINDOWMESSAGESHOWAREA_H
