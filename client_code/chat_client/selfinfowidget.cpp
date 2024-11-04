#include "selfinfowidget.h"
#include "debug.h"

#include "model/datacenter.h"
#include "toast.h"

#include <QGridLayout>
#include <QPushButton>
#include <QTimer>
#include <QFileDialog>

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
    _getVerifyCodeBtn = new QPushButton();
    _getVerifyCodeBtn->setText("获取验证码");
    _getVerifyCodeBtn->setFixedSize(70, 25);
    _getVerifyCodeBtn->setStyleSheet(getVeriftBtnStyle);
    _getVerifyCodeBtn->hide();

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
    layout->addWidget(_getVerifyCodeBtn, 4, 3);

#if TEST_UI
    _idLabel->setText("111");
    _nickNameLabel->setText("小八");
    _personalSignatureLabel->setText("你好");
    _phoneNumLabel->setText("1234567");
    _headPortrait->setIcon(QIcon(":/resource/image/headPortrait.png"));
#endif

    // 初始化信号槽
    initSignalSlot();

    // 从dataCenter中加载个人数据
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    model::UserInfo* mySelf = dataCenter->getMyself();
    if(mySelf){
        _idLabel->setText(mySelf->_userId);
        _nickNameLabel->setText(mySelf->_nickName);
        _personalSignatureLabel->setText(mySelf->_personalSignature);
        _phoneNumLabel->setText(mySelf->_phoneNum);
        _headPortrait->setIcon(mySelf->_headPortrait);
    }
}

void SelfInfoWidget::initSignalSlot(){
    // TODO: 这三可以封装成一个函数
    connect(_nickNameModifyBtn, &QPushButton::clicked, this, [=](){
        // 切换到昵称编辑
        QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());
        _nickNameLabel->hide();
        _nickNameModifyBtn->hide();
        layout->removeWidget(_nickNameLabel);
        layout->removeWidget(_nickNameModifyBtn);

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
        _getVerifyCodeBtn->show();
    });

    // 用户名修改提交按钮的信号槽
    connect(_nickNameConfirmModifyBtn, &QPushButton::clicked, this, &SelfInfoWidget::clickNickNameConfirmModifyBtn);
    // 个性签名修改提交按钮的信号槽
    connect(_personalSignatureConfirmModifyBtn, &QPushButton::clicked, this, &SelfInfoWidget::clickPersonalSignatureConfirmModifyBtn);
    // 获取手机验证码按钮的信号槽
    connect(_getVerifyCodeBtn, &QPushButton::clicked, this, &SelfInfoWidget::clickGetVerifyBtn);
    // 手机号修改提交按钮的信号槽
    connect(_phoneNumConfirmModifyBtn, &QPushButton::clicked, this, &SelfInfoWidget::clickPhoneNumConfirmModifyBtn);
    // 头像修改提交的信号槽
    connect(_headPortrait, &QPushButton::clicked, this, &SelfInfoWidget::clickHeadPortraitBtn);
}

void SelfInfoWidget::clickNickNameConfirmModifyBtn(){
    // 1. 从输入框中, 拿到修改后的昵称
    const QString& nickname = _nickNameEdit->text();
    if (nickname.isEmpty()) {
        Toast::showMessage("用户名不能为空");
        return;
    }
    // 2. 发送网络请求
    model::DataCenter *dataCenter = model::DataCenter::getInstance();

    // 修改昵称完成这个信号在 右侧消息显示 那里也需要关联一下进行对应的修改
    connect(dataCenter, &model::DataCenter::modifyNickNameAsyncDone, this,
            &SelfInfoWidget::clickNickNameConfirmModifyBtnDone, Qt::UniqueConnection);
    dataCenter->modifyNickNameAsync(nickname);
}

void SelfInfoWidget::clickNickNameConfirmModifyBtnDone(){
    // 切换到用户名展示
    QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());
    _nickNameEdit->hide();
    _nickNameConfirmModifyBtn->hide();
    layout->removeWidget(_nickNameEdit);
    layout->removeWidget(_nickNameConfirmModifyBtn);

    _nickNameLabel->setText(_nickNameEdit->text());
    _nickNameLabel->show();
    _nickNameModifyBtn->show();
    layout->addWidget(_nickNameLabel, 1, 2);
    layout->addWidget(_nickNameModifyBtn, 1, 3);
}

void SelfInfoWidget::clickPersonalSignatureConfirmModifyBtn(){
    // 1. 从输入框中, 拿到修改后的个性签名
    const QString& personalSignature = _personalSignatureEdit->text();
    if (personalSignature.isEmpty()) {
        // 个性签名可以为空
        // Toast::showMessage("个性签名不能为空");
        clickPersonalSignatureConfirmModifyBtnDone();
        return;
    }
    // 2. 发送网络请求
    model::DataCenter *dataCenter = model::DataCenter::getInstance();
    connect(dataCenter, &model::DataCenter::modifyPersonalSignatureAsyncDone, this,
            &SelfInfoWidget::clickPersonalSignatureConfirmModifyBtnDone, Qt::UniqueConnection);
    dataCenter->modifyPersonalSignatureAsync(personalSignature);
}

void SelfInfoWidget::clickPersonalSignatureConfirmModifyBtnDone(){
    // 切换到个性签名展示
    QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());
    _personalSignatureEdit->hide();
    _personalSignatureConfirmModifyBtn->hide();
    layout->removeWidget(_personalSignatureEdit);
    layout->removeWidget(_personalSignatureConfirmModifyBtn);

    _personalSignatureLabel->setText(_personalSignatureEdit->text());
    _personalSignatureLabel->show();
    _personalSignatureModifyBtn->show();
    layout->addWidget(_personalSignatureLabel, 2, 2);
    layout->addWidget(_personalSignatureModifyBtn, 2, 3);
}

void SelfInfoWidget::clickGetVerifyBtn(){
    // 1. 获取到输入框中的手机号码
    const QString& phone = _phoneNumEdit->text();
    if (phone.isEmpty()) {
        Toast::showMessage("请输入正确的手机号");
        return;
    }

    // 2. 给服务器发起请求.
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    connect(dataCenter, &model::DataCenter::getPhoneVerifyCodeAsyncDone, this, [=]() {
        // 不需要做其他的处理, 只需要提示一下, 验证码已经发送
        Toast::showMessage("短信验证码已发送");
    });
    dataCenter->getPhoneVerifyCodeAsync(phone);

    // 3. 保存收到验证码的手机号，方便后续进行对比验证：要修改的手机号 必须和 收到验证码的手机号一致
    this->_phoneAfterChange = phone;

    // 4. 禁用发送验证码按钮, 并给出倒计时，即两次发送之间的时间间隔(设成100s)
    this->_getVerifyCodeBtn->setEnabled(false);
    _remainTime = 100;
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        if (_remainTime <= 1) {
            // 倒计时结束了
            _getVerifyCodeBtn->setEnabled(true);
            _getVerifyCodeBtn->setText("获取验证码");
            timer->stop();
            // 这个别忘了，后续自动删除 timer
            timer->deleteLater();
            return;
        }
        --_remainTime;
        _getVerifyCodeBtn->setText(QString::number(_remainTime) + "s");
    });
    timer->start(1000);
}

void SelfInfoWidget::clickPhoneNumConfirmModifyBtn(){
    // 1. 先判定, 当前验证码是否已经收到.
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    // 这里不用 const & 因为后续会清空 dataCenter 中的 这个值！！（不能影响这里）
    QString verifyCodeId = dataCenter->getPhoneVerifyCodeId();
    if (verifyCodeId.isEmpty()) {
        // 服务器这边还没有返回验证码ID响应
        Toast::showMessage("未点击获取验证码 或 服务器尚未返回响应, 稍后重试!");
        return;
    }

    // 2. 获取用户输入的验证码
    QString verifyCode = _verifyCodeEdit->text();
    if (verifyCode.isEmpty()) {
        Toast::showMessage("验证码有误");
        return;
    }

    // 3. 发送网络请求
    connect(dataCenter, &model::DataCenter::modifyPhoneNumAsyncDone, this,
            &SelfInfoWidget::clickPhoneNumConfirmModifyBtnDone, Qt::UniqueConnection);
    // 这里手机号不能从编辑框中获取，而是使用获取验证码时保存的手机号
    dataCenter->modifyPhoneNumAsync(this->_phoneAfterChange, verifyCodeId, verifyCode);

    // 4. 让验证码按钮的倒计时停止. 把 leftTime 设为 1, 就可以停止了
    _remainTime = 1;
    // 把dataCenter中的相关值清空，确保下次点击提交按钮的时候, 上述逻辑仍然有效
    dataCenter->setPhoneVerifyCodeId("");
    // 把验证码输入框中的值清空
    _verifyCodeEdit->setText("");
}

void SelfInfoWidget::clickPhoneNumConfirmModifyBtnDone(){
    // 切换到电话展示
    QGridLayout* layout = dynamic_cast<QGridLayout*>(this->layout());

    // 隐藏验证码
    _verifyCodeTag->hide();
    _verifyCodeEdit->hide();
    _getVerifyCodeBtn->hide();

    _phoneNumEdit->hide();
    _phoneNumConfirmModifyBtn->hide();
    layout->removeWidget(_phoneNumEdit);
    layout->removeWidget(_phoneNumConfirmModifyBtn);

    // 这里填充的也是当时保存的那个收到验证码的电话
    _phoneNumLabel->setText(this->_phoneAfterChange);
    _phoneNumLabel->show();
    _phoneNumModifyBtn->show();
    layout->addWidget(_phoneNumLabel, 3, 2);
    layout->addWidget(_phoneNumModifyBtn, 3, 3);
}

void SelfInfoWidget::clickHeadPortraitBtn(){
    // 1. 弹出 文件 选择对话框
    // 过滤，只能选择这些后缀的文件
    QString filter = "Image Files (*.png *.jpg *.jpeg)";
    QString imagePath = QFileDialog::getOpenFileName(this, "选择头像", QDir::homePath(), filter);
    if (imagePath.isEmpty()) {
        // 用户取消了
        LOG() << "用户未选择任何头像";
        return;
    }

    // 2. 根据路径, 读取到图片的内容.
    QByteArray newHeadPortraitBytes = model::readFileToByteArray(imagePath);

    // 3. 发送请求, 修改头像
    // 修改头像完成这个信号要在 左侧长条界面 和 右侧消息显示界面 都关联一下进行对应的修改！
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    connect(dataCenter, &model::DataCenter::modifyHeadPortraitAsyncDone, this,
            &SelfInfoWidget::clickHeadPortraitBtnDone, Qt::UniqueConnection);
    dataCenter->modifyHeadPortraitAsync(newHeadPortraitBytes);
}

void SelfInfoWidget::clickHeadPortraitBtnDone(){
    // 把新头像更新到对应位置
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    _headPortrait->setIcon(dataCenter->getMyself()->_headPortrait);
}
