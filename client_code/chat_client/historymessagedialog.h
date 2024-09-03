#ifndef HISTORYMESSAGEDIALOG_H
#define HISTORYMESSAGEDIALOG_H

#include "model/data.h"

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>

// 具体的一条历史消息
class HistoryMessageItem : public QWidget{
    Q_OBJECT
public:
    HistoryMessageItem();

    // 因为消息的种类有很多，所以使用工厂模式
    static HistoryMessageItem* makeHistoryMessageItem(const model::MessageInfo& messageInfo);

private:


};

// 历史消息对话框
class HistoryMessageDialog : public QDialog
{
    Q_OBJECT
public:
    HistoryMessageDialog(QWidget* parent);

    // 添加一条历史消息
    void addHistoryMessageItem(const model::MessageInfo& messageInfo);
    // 清空历史消息
    void clear();

private:
    // 搜索到的所有具体历史消息QWidget
    QWidget* _resultContainer;

};

#endif // HISTORYMESSAGEDIALOG_H
