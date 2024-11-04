#include "toast.h"


#include <QScreen>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>

// 对于一些重要的消息通知，在桌面显眼的位置弹出消息通知，并在一定时间后自动消失
Toast::Toast(const QString& message){
    // 基本属性
    this->setFixedSize(560, 140);
    this->setWindowTitle("消息通知");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    this->setStyleSheet("QWidget { background-color: rgb(250, 250, 250); }");
    // 这个接口可以去掉窗口的标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 设置窗口位置
    // 获取当前机器主窗口
    QScreen* screen = QApplication::primaryScreen();
    int width = screen->size().width();
    int height = screen->size().height();
    int x = (width - this->width()) / 2;
    int y = height - this->height() - 100;   // 100 是窗口距离下边界的距离
    this->move(x, y);

    // 布局管理器
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(vlayout);

    // 组件
    QLabel* messageLabel = new QLabel();
    messageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    messageLabel->setAlignment(Qt::AlignCenter);
    messageLabel->setText(message);
    messageLabel->setStyleSheet("QLabel { font-size: 22px; }");
    vlayout->addWidget(messageLabel);

    // 使用定时器实现2s后自动关闭该窗口
    QTimer* timer = new QTimer(this);
    // 连接信号槽
    connect(timer, &QTimer::timeout, this, [=]() {
        timer->stop();
        this->close();
    });
    timer->start(3000);
}

void Toast::showMessage(const QString &message){
    Toast* toast = new Toast(message);
    toast->show();
}
