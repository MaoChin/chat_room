#ifndef SELFINFOWIDGET_H
#define SELFINFOWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>

// 用户个人信息界面
class SelfInfoWidget : public QDialog
{
    Q_OBJECT
public:
    SelfInfoWidget(QWidget* parent);

private:
    void initSignalSlot();

private:
    // 头像
    QPushButton* _headPortrait;
    // id相关
    QLabel* _idTag;
    QLabel* _idLabel;
    // 昵称相关
    QLabel* _nickNameTag;
    QLabel* _nickNameLabel;
    QLineEdit* _nickNameEdit;
    QPushButton* _nickNameModifyBtn;
    QPushButton* _nickNameConfirmModifyBtn;
    // 个性签名相关
    QLabel* _personalSignatureTag;
    QLabel* _personalSignatureLabel;
    QLineEdit* _personalSignatureEdit;
    QPushButton* _personalSignatureModifyBtn;
    QPushButton* _personalSignatureConfirmModifyBtn;
    // 电话相关
    QLabel* _phoneNumTag;
    QLabel* _phoneNumLabel;
    QLineEdit* _phoneNumEdit;
    QPushButton* _phoneNumModifyBtn;
    QPushButton* _phoneNumConfirmModifyBtn;
    // 电话验证码
    QLabel* _verifyCodeTag;
    QLineEdit* _verifyCodeEdit;
    QPushButton* _getVerifyBtn;

};

#endif // SELFINFOWIDGET_H
