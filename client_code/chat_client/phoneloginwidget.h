#ifndef PHONELOGINWIDGET_H
#define PHONELOGINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>

// 使用手机号登录/注册界面
class PhoneLoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneLoginWidget(QWidget *parent = nullptr);

    // 切换登录/注册界面
    void switchMode();

    // 点击获取短信验证码的槽函数
    void clickGetVerifyCodeBtn();
    // 点击获取短信验证码 处理结束的槽函数
    void clickGetVerifyCodeBtnDone();

    // 两次 获取验证码 之间的间隔时间相关
    void remainTimeDown();

    // 点击登录/注册按钮的槽函数
    void clickSubmitBtn();

    // 登录完成时的槽函数
    void clickLoginSubmitBtnDone(bool ok, const QString& errmsg);
    // 注册完成时的槽函数
    void clickSignUpSubmitBtnDone(bool ok, const QString& errmsg);

private:
    bool _isLoginMode = true;

    QLabel* _tipLabel;
    QLineEdit* _phoneEdit;
    QLineEdit* _verifyCodeEdit;
    QPushButton* _getVerifyCodeBtn;
    QPushButton* _submitBtn;
    QPushButton* _userNameModeBtn;
    QPushButton* _switchModeBtn;

    // 保存一下当前的手机号码
    QString _curPhoneNum = "";

    // 两次 获取验证码 之间的间隔时间相关
    QTimer* _timer;
    int _remainTime = 61;

signals:
};

#endif // PHONELOGINWIDGET_H
