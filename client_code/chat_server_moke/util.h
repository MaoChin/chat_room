#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QDateTime>
#include <QFileInfo>
#include <QIcon>


// 客户端的一些工具函数
#define TAG QString("[file: %1, line: %2]").arg(getFileName(__FILE__), QString::number(__LINE__))
#define LOG() qDebug().noquote() << TAG

////////////////////////
/// \brief some util function
/// 使用static和inline修饰，避免链接时出现 函数重定义
static inline QString makeFormatTime(int64_t timestamp){
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(timestamp);
    return dateTime.toString("MM-dd HH:mm:ss");
}

static inline int64_t getTimestamp(){
    return QDateTime::currentSecsSinceEpoch();
}

// 获取当前文件名称
static inline QString getFileName(const QString& path){
    QFileInfo fileInfo(path);
    return fileInfo.fileName();
}

// QByteArray转QIcon
static inline QIcon makeQIcon(const QByteArray& byteArray){
    // 借助QPixmap
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    QIcon icon(pixmap);
    return icon;
}

// 文件操作
// 读文件到 QByteArray
static inline QByteArray readFileToByteArray(const QString& path){
    QFile file(path);
    bool ok = file.open(QFile::ReadOnly);
    if(!ok){
        LOG() << "open file: " + path + "error!";
        return QByteArray();
    }
    QByteArray content = file.readAll();
    file.close();
    return content;
}

// 写文件
static inline bool writeByteArrayToFile(const QString& path, const QByteArray& content){
    QFile file(path);
    bool ok = file.open(QFile::WriteOnly);
    if(!ok){
        LOG() << "open file: " + path + " error!";
        return false;
    }
    file.write(content);
    // 写文件时都是先写到缓冲区，再统一刷盘。这里需要手动刷新一下缓冲区
    file.flush();
    file.close();
    return true;
}

#endif // UTIL_H
