#ifndef HISTORYMESSAGEDIALOG_H
#define HISTORYMESSAGEDIALOG_H

#include "model/data.h"

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QLabel>

// 具体的一条历史消息
class HistoryMessageItem : public QWidget{
    Q_OBJECT
public:
    HistoryMessageItem();

    // 因为消息的种类有很多，所以使用工厂模式
    static HistoryMessageItem* makeHistoryMessageItem(const model::MessageInfo& messageInfo);

private:

};

// 针对图片类型的消息的显示
class ImageMessageBtn : public QPushButton {
public:
    ImageMessageBtn(const QString& fileId, const QByteArray& content);
    void updateUI(const QString& fileId, const QByteArray& content);

private:
    // 根据fileId再次发起http请求获取其内容
    QString _fileId;
};

// 针对文件历史消息的显示
class FileMessageLabel : public QLabel {
public:
    FileMessageLabel(const QString& fileId, const QString& fileName);

    void getContentDone(const QString& fileId, const QByteArray& fileContent);

    // 通过这个函数, 来处理鼠标点击操作---文件另存为
    void mousePressEvent(QMouseEvent* event) override;

private:
    QString _fileId;
    QByteArray _content;
    QString _fileName;
    // 文件有可能为空，所以是否加载完数据不能根据content是否为空来进行判断，需要给个标记位
    bool _loadDone = false;
};

// 针对语音历史消息的显示
class VoiceMessageLabel : public QLabel {
public:
    VoiceMessageLabel(const QString& fileId);

    void getContentDone(const QString& fileId, const QByteArray& content);

    // 通过这个函数处理鼠标点击---播放语音
    void mousePressEvent(QMouseEvent* event) override;

    // 语音播放完毕的操作
    void playDone();


private:
    QString _fileId;
    QByteArray _content;
    // 文件有可能为空，所以是否加载完数据不能根据content是否为空来进行判断，需要给个标记位
    bool _loadDone = false;
};


// 历史消息对话框
class HistoryMessageDialog : public QDialog
{
    Q_OBJECT
public:
    HistoryMessageDialog(QWidget* parent);

    // 点击搜索按钮的槽函数
    void clickSearchBtn();
    // 点击搜索按钮结束时渲染数据到界面
    void clickSearchBtnDone();

    // 添加一条历史消息
    void addHistoryMessageItem(const model::MessageInfo& messageInfo);
    // 清空历史消息
    void clear();

private:
    // 搜索到的所有具体历史消息QWidget
    QWidget* _resultContainer;

    // 关键字搜索框
    QLineEdit* _searchBar;
    // 开始时间的编辑框
    QDateTimeEdit* _beginDateTime;
    // 结束时间的编辑框
    QDateTimeEdit* _endDateTime;
    // 按关键字搜索的复选框
    QRadioButton* _keySearchRadioButton;
    // 按时间搜索的复选框
    QRadioButton* _timeSearchRadioButton;

};

#endif // HISTORYMESSAGEDIALOG_H
