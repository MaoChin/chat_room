#include "selfinfowidget.h"
#include "debug.h"

#include <QGridLayout>
#include <QPushButton>

SelfInfoWidget::SelfInfoWidget(QWidget* parent)
    : QDialog(parent)
{
    this->setFixedSize(500, 200);
    this->setWindowTitle("个人信息");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    // 把窗口移动到鼠标位置
    // this->move(QCursor::pos());
    // 该窗口关闭时自动销毁这个对象，防止内存泄漏
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 布局管理器
    QGridLayout* layout = new QGridLayout();
    layout->setHorizontalSpacing(10);
    layout->setVerticalSpacing(2);
    layout->setContentsMargins(18, 18, 18, 0);
    layout->setAlignment(Qt::AlignTop);
    this->setLayout(layout);

    // 头像
    _headPortrait = new QPushButton();
    _headPortrait->setFixedSize(75, 75);
    _headPortrait->setIconSize(QSize(75, 75));
    _headPortrait->setIcon(QIcon(":/resource/image/headPortrait.png"));
    _headPortrait->setStyleSheet("QPushButton { border: none; background-color: transparent; }");
    layout->addWidget(_headPortrait, 0, 0, 3, 1);

    QString tagStyle = "QLabel { font-size: 14px; font-weight: 800; }";
    QString btnStyle = "QPushButton { border: none; background-color: transparent; }";
    btnStyle += "QPushButton:pressed { background-color: rgb(210, 210, 210); }";
    QString editStyle = "QLineEdit { border: none; border-radius: 7px; padding-left: 4px; }";
    int height = 30;
    // id
    _idTag = new QLabel();
    _idTag->setText("ID");
    _idTag->setFixedSize(50, height);
    _idTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _idTag->setStyleSheet(tagStyle);

    _idLabel = new QLabel();
    _idLabel->setFixedHeight(height);
    _idLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // nick name
    _nickNameTag = new QLabel();
    _nickNameTag->setText("昵称");
    _nickNameTag->setFixedSize(50, height);
    _nickNameTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _nickNameTag->setStyleSheet(tagStyle);

    _nickNameLabel = new QLabel();
    _nickNameLabel->setFixedHeight(height);
    _nickNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    _nickNameEdit = new QLineEdit();
    _nickNameEdit->setFixedHeight(25);
    _nickNameEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _nickNameEdit->setStyleSheet(editStyle);
    _nickNameEdit->hide();

    _nickNameModifyBtn = new QPushButton();
    _nickNameModifyBtn->setFixedSize(25, 25);
    _nickNameModifyBtn->setIconSize(QSize(25, 25));
    _nickNameModifyBtn->setIcon(QIcon(":/resource/image/modifyBtn.png"));
    _nickNameModifyBtn->setStyleSheet(btnStyle);

    _nickNameConfirmModifyBtn = new QPushButton();
    _nickNameConfirmModifyBtn->setFixedSize(25, 25);
    _nickNameConfirmModifyBtn->setIconSize(QSize(25, 25));
    _nickNameConfirmModifyBtn->setIcon(QIcon(":/resource/image/confirmModifyBtn.png"));
    _nickNameConfirmModifyBtn->setStyleSheet(btnStyle);
    _nickNameConfirmModifyBtn->hide();

    // 个性签名
    _personalSignatureTag = new QLabel();
    _personalSignatureTag->setText("个性签名");
    _personalSignatureTag->setFixedSize(70, height);
    _personalSignatureTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _personalSignatureTag->setStyleSheet(tagStyle);

    _personalSignatureLabel = new QLabel();
    _personalSignatureLabel->setFixedHeight(height);
    _personalSignatureLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    _personalSignatureEdit = new QLineEdit();
    _personalSignatureEdit->setFixedHeight(25);
    _personalSignatureEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _personalSignatureEdit->setStyleSheet(editStyle);
    _personalSignatureEdit->hide();

    _personalSignatureModifyBtn = new QPushButton();
    _personalSignatureModifyBtn->setFixedSize(25, 25);
    _personalSignatureModifyBtn->setIconSize(QSize(25, 25));
    _personalSignatureModifyBtn->setIcon(QIcon(":/resource/image/modifyBtn.png"));
    _personalSignatureModifyBtn->setStyleSheet(btnStyle);

    _personalSignatureConfirmModifyBtn = new QPushButton();
    _personalSignatureConfirmModifyBtn->setFixedSize(25, 25);
    _personalSignatureConfirmModifyBtn->setIconSize(QSize(25, 25));
    _personalSignatureConfirmModifyBtn->setIcon(QIcon(":/resource/image/confirmModifyBtn.png"));
    _personalSignatureConfirmModifyBtn->setStyleSheet(btnStyle);
    _personalSignatureConfirmModifyBtn->hide();

    // 电话
    _phoneNumTag = new QLabel();
    _phoneNumTag->setText("电话");
    _phoneNumTag->setFixedSize(50, height);
    _phoneNumTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _phoneNumTag->setStyleSheet(tagStyle);

    _phoneNumLabel = new QLabel();
    _phoneNumLabel->setFixedHeight(height);
    _phoneNumLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    _phoneNumEdit = new QLineEdit();
    _phoneNumEdit->setFixedHeight(25);
    _phoneNumEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _phoneNumEdit->setStyleSheet(editStyle);
    _phoneNumEdit->hide();

    _phoneNumModifyBtn = new QPushButton();
    _phoneNumModifyBtn->setFixedSize(25, 25);
    _phoneNumModifyBtn->setIconSize(QSize(25, 25));
    _phoneNumModifyBtn->setIcon(QIcon(":/resource/image/modifyBtn.png"));
    _phoneNumModifyBtn->setStyleSheet(btnStyle);

    _phoneNumConfirmModifyBtn = new QPushButton();
    _phoneNumConfirmModifyBtn->setFixedSize(25, 25);
    _phoneNumConfirmModifyBtn->setIconSize(QSize(25, 25));
    _phoneNumConfirmModifyBtn->setIcon(QIcon(":/resource/image/confirmModifyBtn.png"));
    _phoneNumConfirmModifyBtn->setStyleSheet(btnStyle);
    _phoneNumConfirmModifyBtn->hide();

    // 验证码
    _verifyCodeTag = new QLabel();
    _verifyCodeTag->setText("验证码");
    _verifyCodeTag->setFixedSize(50, height);
    _verifyCodeTag->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _verifyCodeTag->setStyleSheet(tagStyle);
    _verifyCodeTag->hide();

    _verifyCodeEdit = new QLineEdit();
    _verifyCodeEdit->setFixedHeight(25);
    _verifyCodeEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _verifyCodeEdit->setStyleSheet(editStyle);
    _verifyCodeEdit->hide();

    QString getVeriftBtnStyle = "QPushButton { border: none; background-color: transparent; border-radius: 5px; }";
    getVeriftBtnStyle += "QPushButton:pressed { background-color: rgb(210, 210, 210); }";
    _getVerifyBtn = new QPushButton();
    _getVerifyBtn->setText("获取验证码");
    _getVerifyBtn->setFixedSize(70, 25);
    _getVerifyBtn->setStyleSheet(getVeriftBtnStyle);
    _getVerifyBtn->hide();

    layout->addWidget(_idTag, 0, 1);
    layout->addWidget(_idLabel, 0, 2);

    layout->addWidget(_nickNameTag, 1, 1);
    layout->addWidget(_nickNameLabel, 1, 2);
    layout->addWidget(_nickNameModifyBtn, 1, 3);

    layout->addWidget(_personalSignatureTag, 2, 1);
    layout->addWidget(_personalSignatureLabel, 2, 2);
    layout->addWidget(_personalSignatureModifyBtn, 2, 3);

    layout->addWidget(_phoneNumTag, 3, 1);
    layout->addWidget(_phoneNumLabel, 3, 2);
    layout->addWidget(_phoneNumModifyBtn, 3, 3);

    layout->addWidget(_verifyCodeTag, 4, 1);
    layout->addWidget(_verifyCodeEdit, 4, 2);
    layout->addWidget(_getVerifyBtn, 4, 3);

#if TEST_UI
    _idLabel->setText("111");
    _nickNameLabel->setText("小八");
    _personalSignatureLabel->setText("你好");
    _phoneNumLabel->setText("1234567");
#endif

    // 初始化信号槽
    initSignalSlot();
}

void SelfInfoWidget::initSignalSlot(){
    // TODO: 这三可以封装成一个函数
    connect(_nickNameModifyBtn, &QPushButton::clicked, this, [=](){
        // 切换到昵称编辑
        QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());
        _nickNameLabel->hide();
        _nickNameModifyBtn->hide();
        layout->removeWidget(_nickNameLabel);
        layout->removeWidget(_nickNameConfirmModifyBtn);

        _nickNameEdit->setText(_nickNameLabel->text());
        _nickNameEdit->show();
        _nickNameConfirmModifyBtn->show();
        layout->addWidget(_nickNameEdit, 1, 2);
        layout->addWidget(_nickNameConfirmModifyBtn, 1, 3);
    });

    connect(_personalSignatureModifyBtn, &QPushButton::clicked, this, [=](){
        // 切换到个性签名编辑
        QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());
        _personalSignatureLabel->hide();
        _personalSignatureModifyBtn->hide();
        layout->removeWidget(_personalSignatureLabel);
        layout->removeWidget(_personalSignatureModifyBtn);

        _personalSignatureEdit->setText(_personalSignatureLabel->text());
        _personalSignatureEdit->show();
        _personalSignatureConfirmModifyBtn->show();
        layout->addWidget(_personalSignatureEdit, 2, 2);
        layout->addWidget(_personalSignatureConfirmModifyBtn, 2, 3);
    });

    connect(_phoneNumModifyBtn, &QPushButton::clicked, this, [=](){
        // 切换到电话编辑
        QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());
        _phoneNumLabel->hide();
        _phoneNumModifyBtn->hide();
        layout->removeWidget(_phoneNumLabel);
        layout->removeWidget(_phoneNumModifyBtn);

        _phoneNumEdit->setText(_phoneNumLabel->text());
        _phoneNumEdit->show();
        _phoneNumConfirmModifyBtn->show();
        layout->addWidget(_phoneNumEdit, 3, 2);
        layout->addWidget(_phoneNumConfirmModifyBtn, 3, 3);

        // 显示验证码
        _verifyCodeTag->show();
        _verifyCodeEdit->show();
        _getVerifyBtn->show();
    });


}
