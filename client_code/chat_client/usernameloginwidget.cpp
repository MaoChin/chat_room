#include "usernameloginwidget.h"

#include "phoneloginwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

// 登录界面
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
    QLabel* tipLabel = new  QLabel();
    tipLabel->setFixedHeight(50);
    tipLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    tipLabel->setAlignment(Qt::AlignCenter);
    tipLabel->setText("登录 | Login");
    tipLabel->setStyleSheet("QLabel { font-size: 35px; font-weight: 600; }");

    QLineEdit* userNameEdit = new QLineEdit();
    QString editStyle = "QLineEdit { font-size: 14px; border: none; border-radius: 8px; padding-left: 10px; background-color: rgb(240, 240, 240); }";
    userNameEdit->setFixedHeight(38);
    userNameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    userNameEdit->setPlaceholderText("请输入用户名");
    userNameEdit->setStyleSheet(editStyle);

    QLineEdit* passwordEdit = new QLineEdit();
    passwordEdit->setFixedHeight(38);
    passwordEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet(editStyle);

    QLineEdit* verifyCodeEdit = new QLineEdit();
    verifyCodeEdit->setFixedHeight(38);
    verifyCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    verifyCodeEdit->setPlaceholderText("请输入右侧验证码");
    verifyCodeEdit->setStyleSheet(editStyle);

    QPushButton* verifyCodeBtn = new QPushButton();
    verifyCodeBtn->setFixedHeight(38);
    verifyCodeBtn->setText("验证码");
    verifyCodeBtn->setStyleSheet("QPushButton { border: none; }");

    // 提交按钮：登录/注册
    QPushButton* submitBtn = new QPushButton();
    submitBtn->setFixedHeight(45);
    submitBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    submitBtn->setText("登录");
    QString submitBtnStyle = "QPushButton { font-size: 18px; border: none; border-radius: 10px; color: rgb(255, 255, 255); background-color: rgb(44, 182, 61); }";
    submitBtnStyle += "QPushButton:hover { background-color: rgb(220, 220, 220); }";
    submitBtnStyle += "QPushButton:pressed { background-color: rgb(200, 200, 200); }";
    submitBtn->setStyleSheet(submitBtnStyle);

    QPushButton* phoneModeBtn = new QPushButton();
    phoneModeBtn->setFixedSize(120, 35);
    phoneModeBtn->setText("使用手机号登录");
    QString modeBtn = "QPushButton { border: none; border-radius: 8px; background-color: transparent; font-size: 14px; }";
    modeBtn += "QPushButton:hover { background-color: rgb(240, 240, 240); }";
    modeBtn += "QPushButton:pressed { background-color: rgn(220, 220, 220); }";
    phoneModeBtn->setStyleSheet(modeBtn);

    // 切换到登录页面或者切换到注册页面
    QPushButton* switchModeBtn = new QPushButton();
    switchModeBtn->setFixedSize(100, 35);
    switchModeBtn->setText("用户名注册");
    switchModeBtn->setStyleSheet(modeBtn);

    // 总共分5列
    gridLayout->addWidget(tipLabel, 0, 0, 1, 5);
    gridLayout->addWidget(userNameEdit, 1, 0, 1, 5);
    gridLayout->addWidget(passwordEdit, 2, 0, 1, 5);
    gridLayout->addWidget(verifyCodeEdit, 3, 0, 1, 4);
    gridLayout->addWidget(verifyCodeBtn, 3, 4, 1, 1);
    gridLayout->addWidget(submitBtn, 4, 0, 1, 5);
    gridLayout->addWidget(phoneModeBtn, 5, 0, 1, 1);
    gridLayout->addWidget(switchModeBtn, 5, 4, 1, 1);

    // 信号槽
    // 切换登录/注册
    connect(switchModeBtn, &QPushButton::clicked, this, [=]() {
        if(_isLoginMode){
            // 登录界面-》注册界面
            this->setWindowTitle("用户名注册");
            tipLabel->setText("注册 | Sign Up");
            submitBtn->setText("注册");
            switchModeBtn->setText("用户名登录");
        }
        else{
            // 注册界面-》登录界面
            this->setWindowTitle("用户名登录");
            tipLabel->setText("登录 | Sign Up");
            submitBtn->setText("登录");
            switchModeBtn->setText("用户名注册");
        }
        _isLoginMode = !_isLoginMode;
    });

    // 切换到手机号登录
    connect(phoneModeBtn, &QPushButton::clicked, this, [=]() {
        // 统一切换过去是登录界面
        PhoneLoginWidget* phoneLoginWidget = new PhoneLoginWidget(nullptr);
        // 这里用show()，非阻塞，希望show()的时候此处代码继续往下执行
        // 而exec()会阻塞
        phoneLoginWidget->show();
        // 关闭当前窗口
        this->close();
    });
}
