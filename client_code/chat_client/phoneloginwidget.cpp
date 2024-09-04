#include "phoneloginwidget.h"

#include "usernameloginwidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

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
    QLabel* tipLabel = new QLabel();
    tipLabel->setFixedHeight(45);
    tipLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    tipLabel->setAlignment(Qt::AlignCenter);
    tipLabel->setText("登录 | Login");
    tipLabel->setStyleSheet("QLabel { font-size: 35px; font-weight: 600; }");

    QLineEdit* phoneEdit = new QLineEdit();
    QString editStyle = "QLineEdit { font-size: 14px; border: none; border-radius: 8px; padding-left: 10px; background-color: rgb(240, 240, 240); }";
    phoneEdit->setFixedHeight(38);
    phoneEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    phoneEdit->setPlaceholderText("请输入手机号");
    phoneEdit->setStyleSheet(editStyle);

    QLineEdit* verifyCodeEdit = new QLineEdit();
    verifyCodeEdit->setFixedHeight(38);
    verifyCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    verifyCodeEdit->setPlaceholderText("请输入短信验证码");
    verifyCodeEdit->setStyleSheet(editStyle);

    QPushButton* getVerifyCodeBtn = new QPushButton();
    getVerifyCodeBtn->setFixedHeight(40);
    getVerifyCodeBtn->setText("获取短信验证码");
    QString getVerifyCodeBtnStyle = "QPushButton { border: none; border-radius: 6px; background-color: transparent; font-size: 14px; }";
    getVerifyCodeBtnStyle += "QPushButton:hover { background-color: rgb(240, 240, 240); }";
    getVerifyCodeBtnStyle += "QPushButton:pressed { background-color: rgb(220, 220, 220); }";
    getVerifyCodeBtn->setStyleSheet(getVerifyCodeBtnStyle);

    QPushButton* submitBtn = new QPushButton();
    submitBtn->setFixedHeight(50);
    submitBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    submitBtn->setText("登录");
    QString submitBtnStyle = "QPushButton { font-size: 18px; border: none; border-radius: 10px; color: rgb(255, 255, 255); background-color: rgb(44, 182, 61); }";
    submitBtnStyle += "QPushButton:hover { background-color: rgb(220, 220, 220); }";
    submitBtnStyle += "QPushButton:pressed { background-color: rgb(200, 200, 200); }";
    submitBtn->setStyleSheet(submitBtnStyle);

    QPushButton* userNameModeBtn = new QPushButton();
    userNameModeBtn->setFixedSize(120, 35);
    userNameModeBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    userNameModeBtn->setText("使用用户名登录");
    QString modeBtnStyle = "QPushButton { border: none; border-radius: 8px; background-color: transparent; font-size: 14px; }";
    modeBtnStyle += "QPushButton:hover { background-color: rgb(240, 240, 240); }";
    modeBtnStyle += "QPushButton:pressed { background-color: rgn(220, 220, 220); }";
    userNameModeBtn->setStyleSheet(modeBtnStyle);

    // 切换到登录页面或者切换到注册页面
    QPushButton* switchModeBtn = new QPushButton();
    switchModeBtn->setFixedSize(100, 35);
    switchModeBtn->setText("手机号注册");
    switchModeBtn->setStyleSheet(modeBtnStyle);

    // 也是分成5列
    gridLayout->addWidget(tipLabel, 0, 0, 1, 5);
    gridLayout->addWidget(phoneEdit, 1, 0, 1, 5);
    gridLayout->addWidget(verifyCodeEdit, 2, 0, 1, 4);
    gridLayout->addWidget(getVerifyCodeBtn, 2, 4, 1, 1);
    gridLayout->addWidget(submitBtn, 3, 0, 1, 5);
    gridLayout->addWidget(userNameModeBtn, 4, 0, 1, 1);
    gridLayout->addWidget(switchModeBtn, 4, 4, 1, 1);

    // 信号槽
    // 切换登录/注册
    connect(switchModeBtn, &QPushButton::clicked, this, [=]() {
        if(_isLoginMode){
            // 登录界面-》注册界面
            this->setWindowTitle("手机号注册");
            tipLabel->setText("注册 | Sign Up");
            submitBtn->setText("注册");
            switchModeBtn->setText("手机号登录");
        }
        else{
            // 注册界面-》登录界面
            this->setWindowTitle("用户名登录");
            tipLabel->setText("登录 | Sign Up");
            submitBtn->setText("登录");
            switchModeBtn->setText("手机号注册");
        }
        _isLoginMode = !_isLoginMode;
    });

    // 切换到用户名登录
    connect(userNameModeBtn, &QPushButton::clicked, this, [=]() {
        // 统一切换过去是登录界面
        UserNameLoginWidget* userNameLoginWidget = new UserNameLoginWidget(nullptr);
        // 这里用show()，非阻塞，希望show()的时候此处代码继续往下执行
        // 而exec()会阻塞
        userNameLoginWidget->show();
        // 关闭当前窗口
        this->close();
    });
}
