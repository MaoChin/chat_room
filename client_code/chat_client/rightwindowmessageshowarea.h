#ifndef RIGHTWINDOWMESSAGESHOWAREA_H
#define RIGHTWINDOWMESSAGESHOWAREA_H

#include <QScrollArea>
#include <QWidget>
#include <QLabel>
#include <QString>

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
    static QWidget* makeImageMessageItem();
    static QWidget* makeFileMessageItem();
    static QWidget* makeVoiceMessageItem();

private:
    bool _isLeft;

};

// 文本消息的正文
class TextMessageContent : public QWidget{
    Q_OBJECT
public:
    TextMessageContent(bool isLeft, const QString& textContent);
    // 文本消息的框框需要自己手动绘制！
    void paintEvent(QPaintEvent* event) override;

private:
    // 文字部分
    bool _isLeft = true;
    QLabel* _textMessage;
};



#endif // RIGHTWINDOWMESSAGESHOWAREA_H
