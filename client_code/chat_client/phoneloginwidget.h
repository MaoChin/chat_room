#ifndef PHONELOGINWIDGET_H
#define PHONELOGINWIDGET_H

#include <QWidget>

// 使用手机号登录/注册界面
class PhoneLoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneLoginWidget(QWidget *parent = nullptr);

private:
    bool _isLoginMode = true;

signals:
};

#endif // PHONELOGINWIDGET_H
