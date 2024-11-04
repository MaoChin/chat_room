#ifndef VERIFYCODEWIDGET_H
#define VERIFYCODEWIDGET_H

#include <QWidget>
#include <QRandomGenerator>


class VerifyCodeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VerifyCodeWidget(QWidget *parent = nullptr);

    // 生成验证码
    QString createVerifyCode();

    // 重新生成验证码并显示在界面上
    void flushVerifyCode();

    // 校验验证码
    bool checkVerifyCode(const QString& verifyCode){
        // 使用compare可以控制 忽略大小写 等功能；返回值为0表示相等
        return _verifyCode.compare(verifyCode, Qt::CaseInsensitive) == 0;
    }

    void paintEvent(QPaintEvent *event) override;

    // 用户点击验证码时就刷新验证码
    void mousePressEvent(QMouseEvent *event) override;

private:
    // 随机数生成器
    QRandomGenerator _randomGenerator;

    // 生成的验证码
    QString _verifyCode;


signals:

};

#endif // VERIFYCODEWIDGET_H
