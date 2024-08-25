#ifndef MIDDLEWINDOWAREA_H
#define MIDDLEWINDOWAREA_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>

// item类型
enum ItemType{
    CHATSESSION_TYPE,
    FRIEND_TYPE,
    FRIENDAPPLY_TYPE
};

// 主窗口中间 显示会话/好友列表 的区域
// QScrollArea 可以实现滚动条效果
class MiddleWindowArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit MiddleWindowArea(QWidget *parent = nullptr);

    // 添加一个项目
    void addItem(ItemType itemType, const QString& id, const QIcon& headPortrait, const QString& name, const QString& text);
    // 清除所有项目
    void clearAllItem();
    // 选中某个item
    void selectItem(int index);

private:
    // 具体的内容widget
    QWidget* _container;


signals:
};

///////////////////////////////
/// \brief 滚动区域中具体的项，这个是父类
class MiddleWindowAreaItem : public QWidget{
    // 支持信号槽
    Q_OBJECT
public:
    // onwer表示MiddleWindowArea这个类的指针
    MiddleWindowAreaItem(QWidget* onwer, const QIcon& headPortrait, const QString& name, const QString& text);

    // 这个重写的函数是为了使MiddleWindowAreaItem可以使用QSS样式表！
    void paintEvent(QPaintEvent*) override;
    // 鼠标点击事件
    void mousePressEvent(QMouseEvent* event) override;
    void select();
    // 鼠标悬停事件
    void enterEvent(QEnterEvent* event) override;
    // 鼠标离开事件
    void leaveEvent(QEvent* event) override;

protected:
    // 这个是为了给子类继承后访问
    QLabel* messageLabel;

private:
    // 指向 MiddleWindowArea
    QWidget* _onwer;
    bool _selected = false;
};

/////////////////////////////
/// \brief 会话列表项
class ChatSesionItem : public MiddleWindowAreaItem{
    // 支持信号槽
    Q_OBJECT
public:
    ChatSesionItem(QWidget* owner, const QIcon& headPortrait, const QString& chatSessionId,
                   const QString& chatSessionName, const QString& lastMessage);


private:
    QString _chatSessionId = "";

};
////////////////////////////
/// \brief 好友列表项
class FriendItem : public MiddleWindowAreaItem{
    // 支持信号槽
    Q_OBJECT

public:
    FriendItem(QWidget* owner, const QIcon& headPortrait, const QString& userId,
                   const QString& nickName, const QString& personalSignature);


private:
    QString _userId = "";
};
///////////////////////////
/// \brief 好友申请列表项
class FriendApplyItem : public MiddleWindowAreaItem{
    // 支持信号槽
    Q_OBJECT

public:
    FriendApplyItem(QWidget* owner, const QIcon& headPortrait, const QString& userId,
                    const QString& nickName);



private:
    QString _userId = "";
};

#endif // MIDDLEWINDOWAREA_H
