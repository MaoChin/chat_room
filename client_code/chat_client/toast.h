#ifndef TOAST_H
#define TOAST_H

#include <QDialog>
#include <QWidget>


// 对于一些重要的消息通知，在桌面显眼的位置弹出消息通知，并在一定时间后自动消失
class Toast : public QDialog
{
    Q_OBJECT
public:
    // 不用指定父窗口，全局通知的父窗口是 桌面
    Toast(const QString& message);

    // 直接通过静态函数展示通知，不需要创建该对象就直接使用了
    static void showMessage(const QString& message);


private:

};

#endif // TOAST_H
