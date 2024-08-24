#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

// 主窗口
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    ~MainWidget();

    static MainWidget* getInstance();


private:
    // 构造函数私有化
    MainWidget(QWidget *parent = nullptr);

    void initMainWindow();
    void initLeftWindow();
    void initMiddleWindow();
    void initRightWindow();


private:
    // 搞成单例
    static MainWidget* instance;

    Ui::MainWidget *ui;
    // 窗口中的各个组件
    QWidget* windowLeft;
    QWidget* windowMiddle;
    QWidget* windowRight;
    // 用户头像按钮
    QPushButton* userHeadPortraitBtn;
    // 会话标签页按钮
    QPushButton* chatSessionTabBtn;
    // 好友标签页按钮
    QPushButton* friendTabBtn;
    // 好友申请标签页按钮
    QPushButton* friendApplyTabBtn;

};
#endif // MAINWIDGET_H
