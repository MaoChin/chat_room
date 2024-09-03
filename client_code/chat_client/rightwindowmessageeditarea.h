#ifndef RIGHTWINDOWMESSAGEEDITAREA_H
#define RIGHTWINDOWMESSAGEEDITAREA_H

#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>

// 右侧窗口下方消息编辑区
class RightWindowMessageEditArea : public QWidget
{
    Q_OBJECT
public:
    explicit RightWindowMessageEditArea(QWidget *parent = nullptr);

    // 初始化信号槽
    void initSignalSlot();


private:
    QPushButton* _sendImageBtn;
    QPushButton* _sendFileBtn;
    QPushButton* _sendVoiceBtn;
    QPushButton* _showHistoryMessageBtn;
    QPlainTextEdit* _textEditArea;
    QPushButton* _sendMessageBtn;

signals:
};

#endif // RIGHTWINDOWMESSAGEEDITAREA_H
