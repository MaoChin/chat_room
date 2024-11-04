#include "usernameloginwidget.h"

#include "phoneloginwidget.h"
#include "toast.h"
#include "model/datacenter.h"
#include "mainwidget.h"

#include <QGridLayout>

// 用户名登录/注册界面
UserNameLoginWidget::UserNameLoginWidget(QWidget *parent)
    : QWidget{parent}
{
    // 基本属性
    this->setFixedSize(400, 350);
    this->setWindowTitle("用户名登录");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    this->setStyleSheet("QWidget { background-color: rgb(250, 250, 250); }");

    // 设置这个 DeleteOnClose 后 该窗口必须要在堆上创建打开！！关闭窗口后自动 delete
    // 若在栈上创建该窗口并打开，则在关闭该窗口是时就会奔溃！！(delete 栈上的空间)
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 布局管理器
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(8);
    gridLayout->setContentsMargins(40, 18, 40, 10);
    this->setLayout(gridLayout);

    // 组件
    _tipLabel = new  QLabel();
    _tipLabel->setFixedHeight(50);
    _tipLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _tipLabel->setAlignment(Qt::AlignCenter);
    _tipLabel->setText("登录 | Login");
    _tipLabel->setStyleSheet("QLabel { font-size: 35px; font-weight: 600; }");

    _userNameEdit = new QLineEdit();
    QString editStyle = "QLineEdit { font-size: 14px; border: none; border-radius: 8px; padding-left: 10px; background-color: rgb(240, 240, 240); }";
    _userNameEdit->setFixedHeight(38);
    _userNameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _userNameEdit->setPlaceholderText("请输入用户名");
    _userNameEdit->setStyleSheet(editStyle);

    _passwordEdit = new QLineEdit();
    _passwordEdit->setFixedHeight(38);
    _passwordEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _passwordEdit->setPlaceholderText("请输入密码");
    _passwordEdit->setEchoMode(QLineEdit::Password);
    _passwordEdit->setStyleSheet(editStyle);

    _verifyCodeEdit = new QLineEdit();
    _verifyCodeEdit->setFixedHeight(38);
    _verifyCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _verifyCodeEdit->setPlaceholderText("请输入右侧验证码");
    _verifyCodeEdit->setStyleSheet(editStyle);

    // QPushButton* verifyCodeBtn = new QPushButton();
    // verifyCodeBtn->setFixedHeight(38);
    // verifyCodeBtn->setText("验证码");
    // verifyCodeBtn->setStyleSheet("QPushButton { border: none; }");

    _verifyCodeWidget = new VerifyCodeWidget(this);
    _verifyCodeWidget->setFixedHeight(38);

    // 提交按钮：登录/注册
    _submitBtn = new QPushButton();
    _submitBtn->setFixedHeight(45);
    _submitBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _submitBtn->setText("登录");
    QString submitBtnStyle = "QPushButton { font-size: 18px; border: none; border-radius: 10px; color: rgb(255, 255, 255); background-color: rgb(44, 182, 61); }";
    submitBtnStyle += "QPushButton:hover { background-color: rgb(220, 220, 220); }";
    submitBtnStyle += "QPushButton:pressed { background-color: rgb(200, 200, 200); }";
    _submitBtn->setStyleSheet(submitBtnStyle);

    _phoneModeBtn = new QPushButton();
    _phoneModeBtn->setFixedSize(120, 35);
    _phoneModeBtn->setText("使用手机号登录");
    QString modeBtn = "QPushButton { border: none; border-radius: 8px; background-color: transparent; font-size: 14px; }";
    modeBtn += "QPushButton:hover { background-color: rgb(240, 240, 240); }";
    modeBtn += "QPushButton:pressed { background-color: rgn(220, 220, 220); }";
    _phoneModeBtn->setStyleSheet(modeBtn);

    // 切换到登录页面或者切换到注册页面
    _switchModeBtn = new QPushButton();
    _switchModeBtn->setFixedSize(100, 35);
    _switchModeBtn->setText("用户名注册");
    _switchModeBtn->setStyleSheet(modeBtn);

    // 总共分5列
    gridLayout->addWidget(_tipLabel, 0, 0, 1, 5);
    gridLayout->addWidget(_userNameEdit, 1, 0, 1, 5);
    gridLayout->addWidget(_passwordEdit, 2, 0, 1, 5);
    gridLayout->addWidget(_verifyCodeEdit, 3, 0, 1, 4);
    gridLayout->addWidget(_verifyCodeWidget, 3, 4, 1, 1);
    gridLayout->addWidget(_submitBtn, 4, 0, 1, 5);
    gridLayout->addWidget(_phoneModeBtn, 5, 0, 1, 1);
    gridLayout->addWidget(_switchModeBtn, 5, 4, 1, 1);

    // 信号槽
    // 切换登录/注册
    connect(_switchModeBtn, &QPushButton::clicked, this, &UserNameLoginWidget::switchMode);

    // 切换到手机号登录
    connect(_phoneModeBtn, &QPushButton::clicked, this, [=]() {
        // 统一切换过去是登录界面
        PhoneLoginWidget* phoneLoginWidget = new PhoneLoginWidget(nullptr);
        // 这里用show()，非阻塞，希望show()的时候此处代码继续往下执行
        // 而exec()会阻塞
        phoneLoginWidget->show();
        // 关闭当前窗口
        this->close();
    });

    // 关联submitBtn按钮的信号槽
    connect(_submitBtn, &QPushButton::clicked, this, &UserNameLoginWidget::clickSubmitBtn);

}

// 切换登录/注册界面
void UserNameLoginWidget::switchMode(){
    if(_isLoginMode){
        // 登录界面-》注册界面
        this->setWindowTitle("用户名注册");
        _tipLabel->setText("注册 | Sign Up");
        _submitBtn->setText("注册");
        _switchModeBtn->setText("用户名登录");
    }
    else{
        // 注册界面-》登录界面
        this->setWindowTitle("用户名登录");
        _tipLabel->setText("登录 | Login");
        _submitBtn->setText("登录");
        _switchModeBtn->setText("用户名注册");
    }
    _isLoginMode = !_isLoginMode;
}

void UserNameLoginWidget::clickSubmitBtn(){
    // 1. 先从输入框拿到需要的内容
    const QString& userName = _userNameEdit->text();
    const QString& password = _passwordEdit->text();
    const QString& verifyCode = _verifyCodeEdit->text();
    if (userName.isEmpty() || password.isEmpty() || verifyCode.isEmpty()) {
        Toast::showMessage("输入的内容不能为空!");
        return;
    }

    // 2. 对比验证码是否正确
    if (!_verifyCodeWidget->checkVerifyCode(verifyCode)) {
        Toast::showMessage("输入的验证码错误!");
        return;
    }

    // 3. 真正去发送网络请求.
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    if (_isLoginMode) {
        // 登录
        connect(dataCenter, &model::DataCenter::userNameLoginAsyncDone, this,
                &UserNameLoginWidget::clickLoginSubmitBtnDone);
        dataCenter->userNameLoginAsync(userName, password);
    } else {
        // 注册
        connect(dataCenter, &model::DataCenter::userNameSignUpAsyncDone, this,
                &UserNameLoginWidget::clickSignUpSubmitBtnDone);
        dataCenter->userNameSignUpAsync(userName, password);
    }
}

void UserNameLoginWidget::clickLoginSubmitBtnDone(bool ok, const QString& errmsg){
    // 此处区分一下是否登录成功.
    // 登录失败, 给用户反馈失败原因.
    if (!ok) {
        Toast::showMessage("登录失败: " + errmsg);
        return;
    }
    Toast::showMessage("登录成功!");
    // 登录成功, 需要跳转到主界面.
    MainWidget* mainWidget = MainWidget::getInstance();
    mainWidget->show();

    this->close();
}

void UserNameLoginWidget::clickSignUpSubmitBtnDone(bool ok, const QString& errmsg){
    if (!ok) {
        Toast::showMessage("注册失败: " + errmsg);
        return;
    }
    Toast::showMessage("注册成功!");

    // 切换到登录界面
    this->switchMode();

    // 清空 密码 和 验证码输入框 的内容的，用户名就不清空了
    _passwordEdit->clear();
    _verifyCodeEdit->clear();

    // 刷新验证码
    _verifyCodeWidget->flushVerifyCode();
}
