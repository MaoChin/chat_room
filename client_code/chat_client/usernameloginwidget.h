#ifndef USERNAMELOGINWIDGET_H
#define USERNAMELOGINWIDGET_H

#include <QWidget>

// 注册登录界面，这两个届面差不多，就放在一个类里
class UserNameLoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserNameLoginWidget(QWidget *parent = nullptr);

private:
    // 标识当前是登录还是注册界面，默认是登录界面
    bool _isLoginMode = true;

signals:
};

#endif // USERNAMELOGINWIDGET_H
