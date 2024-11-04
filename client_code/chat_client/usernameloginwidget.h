#ifndef USERNAMELOGINWIDGET_H
#define USERNAMELOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

#include "verifycodewidget.h"

// 注册登录界面，这两个届面差不多，就放在一个类里
class UserNameLoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserNameLoginWidget(QWidget *parent = nullptr);

    // 切换登录/注册界面
    void switchMode();

    // 点击登录/注册按钮的槽函数
    void clickSubmitBtn();
    // 登录完成时的槽函数
    void clickLoginSubmitBtnDone(bool ok, const QString& errmsg);
    // 注册完成时的槽函数
    void clickSignUpSubmitBtnDone(bool ok, const QString& errmsg);

private:
    // 标识当前是登录还是注册界面，默认是登录界面
    bool _isLoginMode = true;

    QLabel* _tipLabel;
    QLineEdit* _userNameEdit;
    QLineEdit* _passwordEdit;
    QLineEdit* _verifyCodeEdit;
    VerifyCodeWidget* _verifyCodeWidget;
    QPushButton* _submitBtn;
    QPushButton* _phoneModeBtn;
    QPushButton* _switchModeBtn;

signals:
};

#endif // USERNAMELOGINWIDGET_H
