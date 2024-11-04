#include "phoneloginwidget.h"

#include "usernameloginwidget.h"
#include "model/datacenter.h"
#include "toast.h"
#include "mainwidget.h"

#include <QGridLayout>

// 使用手机号登录/注册界面
PhoneLoginWidget::PhoneLoginWidget(QWidget *parent)
    : QWidget{parent}
{
    // 基本属性
    this->setFixedSize(400, 350);
    this->setWindowTitle("手机号登录");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    this->setStyleSheet("QWidget { background-color: rgb(250, 250, 250); }");

    // 设置这个 DeleteOnClose 后 该窗口必须要在堆上创建打开！！关闭窗口后自动 delete
    // 若在栈上创建该窗口并打开，则在关闭该窗口是时就会奔溃！！(delete 栈上的空间)
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 布局管理器
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(12);
    gridLayout->setVerticalSpacing(2);
    gridLayout->setContentsMargins(40, 18, 40, 10);
    this->setLayout(gridLayout);

    // 组件
    _tipLabel = new QLabel();
    _tipLabel->setFixedHeight(45);
    _tipLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _tipLabel->setAlignment(Qt::AlignCenter);
    _tipLabel->setText("登录 | Login");
    _tipLabel->setStyleSheet("QLabel { font-size: 35px; font-weight: 600; }");

    _phoneEdit = new QLineEdit();
    QString editStyle = "QLineEdit { font-size: 14px; border: none; border-radius: 8px; padding-left: 10px; background-color: rgb(240, 240, 240); }";
    _phoneEdit->setFixedHeight(38);
    _phoneEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _phoneEdit->setPlaceholderText("请输入手机号");
    _phoneEdit->setStyleSheet(editStyle);

    _verifyCodeEdit = new QLineEdit();
    _verifyCodeEdit->setFixedHeight(38);
    _verifyCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _verifyCodeEdit->setPlaceholderText("请输入短信验证码");
    _verifyCodeEdit->setStyleSheet(editStyle);

    _getVerifyCodeBtn = new QPushButton();
    _getVerifyCodeBtn->setFixedHeight(40);
    _getVerifyCodeBtn->setText("获取短信验证码");
    QString getVerifyCodeBtnStyle = "QPushButton { border: none; border-radius: 6px; background-color: transparent; font-size: 14px; }";
    getVerifyCodeBtnStyle += "QPushButton:hover { background-color: rgb(240, 240, 240); }";
    getVerifyCodeBtnStyle += "QPushButton:pressed { background-color: rgb(220, 220, 220); }";
    _getVerifyCodeBtn->setStyleSheet(getVerifyCodeBtnStyle);

    _submitBtn = new QPushButton();
    _submitBtn->setFixedHeight(50);
    _submitBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _submitBtn->setText("登录");
    QString submitBtnStyle = "QPushButton { font-size: 18px; border: none; border-radius: 10px; color: rgb(255, 255, 255); background-color: rgb(44, 182, 61); }";
    submitBtnStyle += "QPushButton:hover { background-color: rgb(220, 220, 220); }";
    submitBtnStyle += "QPushButton:pressed { background-color: rgb(200, 200, 200); }";
    _submitBtn->setStyleSheet(submitBtnStyle);

    _userNameModeBtn = new QPushButton();
    _userNameModeBtn->setFixedSize(120, 35);
    _userNameModeBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _userNameModeBtn->setText("使用用户名登录");
    QString modeBtnStyle = "QPushButton { border: none; border-radius: 8px; background-color: transparent; font-size: 14px; }";
    modeBtnStyle += "QPushButton:hover { background-color: rgb(240, 240, 240); }";
    modeBtnStyle += "QPushButton:pressed { background-color: rgn(220, 220, 220); }";
    _userNameModeBtn->setStyleSheet(modeBtnStyle);

    // 切换到登录页面或者切换到注册页面
    _switchModeBtn = new QPushButton();
    _switchModeBtn->setFixedSize(100, 35);
    _switchModeBtn->setText("手机号注册");
    _switchModeBtn->setStyleSheet(modeBtnStyle);

    // 也是分成5列
    gridLayout->addWidget(_tipLabel, 0, 0, 1, 5);
    gridLayout->addWidget(_phoneEdit, 1, 0, 1, 5);
    gridLayout->addWidget(_verifyCodeEdit, 2, 0, 1, 3);
    gridLayout->addWidget(_getVerifyCodeBtn, 2, 3, 1, 2);
    gridLayout->addWidget(_submitBtn, 3, 0, 1, 5);
    gridLayout->addWidget(_userNameModeBtn, 4, 0, 1, 1);
    gridLayout->addWidget(_switchModeBtn, 4, 4, 1, 1);

    // 信号槽
    // 切换登录/注册
    connect(_switchModeBtn, &QPushButton::clicked, this, &PhoneLoginWidget::switchMode);

    // 切换到用户名登录
    connect(_userNameModeBtn, &QPushButton::clicked, this, [=]() {
        // 统一切换过去是登录界面
        UserNameLoginWidget* userNameLoginWidget = new UserNameLoginWidget(nullptr);
        // 这里用show()，非阻塞，希望show()的时候此处代码继续往下执行
        // 而exec()会阻塞
        userNameLoginWidget->show();
        // 关闭当前窗口
        this->close();
    });

    // 点击获取短信验证码的信号槽
    connect(_getVerifyCodeBtn, &QPushButton::clicked, this, &PhoneLoginWidget::clickGetVerifyCodeBtn);

    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &PhoneLoginWidget::remainTimeDown);

    connect(_submitBtn, &QPushButton::clicked, this, &PhoneLoginWidget::clickSubmitBtn);
}

void PhoneLoginWidget::switchMode(){
    if(_isLoginMode){
        // 登录界面-》注册界面
        this->setWindowTitle("手机号注册");
        _tipLabel->setText("注册 | Sign Up");
        _submitBtn->setText("注册");
        _switchModeBtn->setText("手机号登录");
    }
    else{
        // 注册界面-》登录界面
        this->setWindowTitle("用户名登录");
        _tipLabel->setText("登录 | Login");
        _submitBtn->setText("登录");
        _switchModeBtn->setText("手机号注册");
    }
    _isLoginMode = !_isLoginMode;
}

void PhoneLoginWidget::clickGetVerifyCodeBtn(){
    // 1. 获取用户输入的手机号码
    const QString& phoneNum = this->_phoneEdit->text();
    if (phoneNum.isEmpty()) {
        Toast::showMessage("请输入手机号！");
        return;
    }
    // 记录下接收验证码的手机号，后续注册/登录的时候用这个手机号，不能再从编辑框获取！！
    this->_curPhoneNum = phoneNum;

    // 2. 发送网络请求, 获取验证码
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    connect(dataCenter, &model::DataCenter::getPhoneVerifyCodeAsyncDone, this,
            &PhoneLoginWidget::clickGetVerifyCodeBtnDone, Qt::UniqueConnection);
    dataCenter->getPhoneVerifyCodeAsync(phoneNum);

    // 3. 开启定时器, 开始倒计时
    remainTimeDown();
    _timer->start(1000);
}

void PhoneLoginWidget::clickGetVerifyCodeBtnDone(){
    Toast::showMessage("短信验证码发送成功！");
}

// 每秒执行一次
void PhoneLoginWidget::remainTimeDown(){
    if (_remainTime <= 1) {
        // 时间到, 发送按钮设为可用状态, 并且停止定时器
        _getVerifyCodeBtn->setEnabled(true);
        _getVerifyCodeBtn->setText("获取短信验证码");
        _timer->stop();
        _remainTime = 61;
        return;
    }

    _remainTime -= 1;
    _getVerifyCodeBtn->setText(QString::number(_remainTime) + " s");
    if (_getVerifyCodeBtn->isEnabled()) {
        _getVerifyCodeBtn->setEnabled(false);
    }
}

void PhoneLoginWidget::clickSubmitBtn(){
    // 1. 从输入框中拿到必要的内容
    //    此处不要从输入框直接获取手机号， 可能用户故意搞事情,
    //    输入验证码的时候, 输入了一个手机号, 点击提交的时候, 换了个手机号！
    const QString& phoneNum = this->_curPhoneNum;
    const QString& verifyCode = _verifyCodeEdit->text();
    if (phoneNum.isEmpty() || verifyCode.isEmpty()) {
        Toast::showMessage("电话或验证码格式不正确");
        return;
    }

    // 2. 发送请求
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    if (_isLoginMode) {
        // 登录
        connect(dataCenter, &model::DataCenter::phoneLoginAsyncDone, this,
                &PhoneLoginWidget::clickLoginSubmitBtnDone, Qt::UniqueConnection);
        dataCenter->phoneLoginAsync(phoneNum, verifyCode);
    } else {
        // 注册
        connect(dataCenter, &model::DataCenter::phoneSignUpAsyncDone, this,
                &PhoneLoginWidget::clickSignUpSubmitBtnDone, Qt::UniqueConnection);
        dataCenter->phoneSignUpAsync(phoneNum, verifyCode);
    }
}

void PhoneLoginWidget::clickLoginSubmitBtnDone(bool ok, const QString &errmsg){
    if (!ok) {
        Toast::showMessage("登录失败: " + errmsg);
        return;
    }
    Toast::showMessage("登录成功！");
    // 跳转到主窗口
    MainWidget* mainWidget = MainWidget::getInstance();
    mainWidget->show();
    // 关闭当前窗口
    this->close();
}

void PhoneLoginWidget::clickSignUpSubmitBtnDone(bool ok, const QString &errmsg){
    // 是否注册成功
    if (!ok) {
        Toast::showMessage("注册失败: " + errmsg);
        return;
    }
    Toast::showMessage("注册成功!");

    // 跳转到登录界面
    switchMode();

    // 清空手机号验证码
    _verifyCodeEdit->clear();

    // 处理一下倒计时
    _remainTime = 1;
}
