#include "verifycodewidget.h"

#include "model/data.h"

#include <QPainter>
#include <QPen>

VerifyCodeWidget::VerifyCodeWidget(QWidget *parent)
    :QWidget(parent),
     _randomGenerator(model::getTimestamp())   // 设置随机数种子
{
    _verifyCode = createVerifyCode();
}

QString VerifyCodeWidget::createVerifyCode()
{
    // 生成4个随机的大写字母
    QString code;
    for (int i = 0; i < 4; ++i) {
        // 每次循环生成一个字符.
        int init = 'A';
        init += _randomGenerator.generate() % 26;
        code += static_cast<QChar>(init);
    }
    return code;
}

void VerifyCodeWidget::flushVerifyCode()
{
    // 重新生成验证码
    _verifyCode = createVerifyCode();
    // 通过 update 就可以起到 "刷新界面" , 本身就是触发 paintEvent
    this->update();
}

void VerifyCodeWidget::paintEvent(QPaintEvent *event)
{
    (void) event;
    const int width = 180;
    const int height = 80;

    QPainter painter(this);
    QPen pen;
    QFont font("楷体",25,QFont::Bold,true);
    painter.setFont(font);

    // 画点: 添加随机噪点
    for(int i = 0; i < 100; i++)
    {
        // 随机颜色
        pen = QPen(QColor(_randomGenerator.generate() % 256, _randomGenerator.generate() % 256,
                          _randomGenerator.generate() % 256));
        painter.setPen(pen);
        // 随机位置
        painter.drawPoint(_randomGenerator.generate() % width,
                          _randomGenerator.generate() % height);
    }

    // 画线: 添加随机干扰线
    for(int i = 0; i < 5; i++)
    {
        pen = QPen(QColor(_randomGenerator.generate() % 256, _randomGenerator.generate() % 256,
                          _randomGenerator.generate() % 256));
        painter.setPen(pen);
        painter.drawLine(_randomGenerator.generate() % width, _randomGenerator.generate() % height,
                         _randomGenerator.generate() % width, _randomGenerator.generate() % height);
    }

    // 绘制验证码
    for(int i = 0; i < _verifyCode.size(); i++)
    {
        pen = QPen(QColor(_randomGenerator.generate() % 255, _randomGenerator.generate() % 255,
                          _randomGenerator.generate() % 255));
        painter.setPen(pen);
        painter.drawText(5+20*i, _randomGenerator.generate() % 10, 30, 30,
                         Qt::AlignCenter, QString(_verifyCode[i]));
    }
}

void VerifyCodeWidget::mousePressEvent(QMouseEvent *event)
{
    (void) event;
    this->flushVerifyCode();
}


