#include "rightwindowmessageeditarea.h"
#include "historymessagedialog.h"

#include <QVBoxLayout>
#include <QScrollBar>

RightWindowMessageEditArea::RightWindowMessageEditArea(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedHeight(200);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 布局管理器
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setAlignment(Qt::AlignTop);
    // 左，上，右，下
    vlayout->setContentsMargins(10, 10, 12, 12);
    this->setLayout(vlayout);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setSpacing(15);
    hlayout->setContentsMargins(10, 0, 0, 0);
    hlayout->setAlignment(Qt::AlignLeft);
    // 垂直布局中有水平布局
    vlayout->addLayout(hlayout);

    // 按钮设置
    QString btnStyle = "QPushButton { background-color: rgb(240, 240, 240); border: none; }";
    btnStyle += "QPushButton:hover { background-color: rgb(225, 225, 225); }";
    btnStyle += "QPushButton:pressed { background-color: rgb(255, 255, 255); }";
    QSize fixedSize(24, 24);
    QSize iconSize(24, 24);
    _sendImageBtn = new QPushButton();
    _sendImageBtn->setFixedSize(fixedSize);
    _sendImageBtn->setIconSize(iconSize);
    _sendImageBtn->setIcon(QIcon(":/resource/image/imageBtn.png"));
    _sendImageBtn->setStyleSheet(btnStyle);
    hlayout->addWidget(_sendImageBtn);

    _sendFileBtn = new QPushButton();
    _sendFileBtn->setFixedSize(fixedSize);
    _sendFileBtn->setIconSize(iconSize);
    _sendFileBtn->setIcon(QIcon(":/resource/image/fileBtn.png"));
    _sendFileBtn->setStyleSheet(btnStyle);
    hlayout->addWidget(_sendFileBtn);

    _sendVoiceBtn = new QPushButton();
    _sendVoiceBtn->setFixedSize(fixedSize);
    _sendVoiceBtn->setIconSize(iconSize);
    _sendVoiceBtn->setIcon(QIcon(":/resource/image/voiceBtn.png"));
    _sendVoiceBtn->setStyleSheet(btnStyle);
    hlayout->addWidget(_sendVoiceBtn);

    _showHistoryMessageBtn = new QPushButton();
    _showHistoryMessageBtn->setFixedSize(fixedSize);
    _showHistoryMessageBtn->setIconSize(iconSize);
    _showHistoryMessageBtn->setIcon(QIcon(":/resource/image/showHistoryBtn.png"));
    _showHistoryMessageBtn->setStyleSheet(btnStyle);
    hlayout->addWidget(_showHistoryMessageBtn);

    _textEditArea = new QPlainTextEdit();
    _textEditArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QString editAreaStyle = "QPlainTextEdit { border: none; background-color: transparent; font-size: 14px; padding: 14px; }";
    editAreaStyle += "QPlainTextEdit:pressed { background-color: rgn(225, 225, 225); }";
    _textEditArea->setStyleSheet(editAreaStyle);
    _textEditArea->verticalScrollBar()->setStyleSheet("QScrollBar { width: 2px; background-color: rgb(45, 45, 45); }");
    vlayout->addWidget(_textEditArea);

    _sendMessageBtn = new QPushButton();
    _sendMessageBtn->setText("发送");
    _sendMessageBtn->setFixedSize(120, 40);
    QString sendMessageBtnStyle = "QPushButton { font-size: 16px; color: rgb(7, 193, 96); border: none; background-color: rgb(233, 233, 233); border-radius: 10px; }";
    // 鼠标悬停效果
    sendMessageBtnStyle += "QPushButton:hover { background-color: rgb(220, 220, 220); }";
    // 鼠标按下效果
    sendMessageBtnStyle += "QPushButton:pressed {background-color: rgb(210, 210, 210); }";
    _sendMessageBtn->setStyleSheet(sendMessageBtnStyle);
    vlayout->addWidget(_sendMessageBtn, 0, Qt::AlignRight | Qt::AlignVCenter);

    // 初始化信号槽
    initSignalSlot();
}

void RightWindowMessageEditArea::initSignalSlot(){
    // 点击历史消息按钮弹出历史消息对话框
    connect(_showHistoryMessageBtn, &QPushButton::clicked, this, [=](){
        HistoryMessageDialog* historyMessageDialog = new HistoryMessageDialog(this);
        historyMessageDialog->exec();
    });

}
