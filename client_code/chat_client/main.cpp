#include "mainwidget.h"

#include "usernameloginwidget.h"
#include "debug.h"
#include "model/datacenter.h"

#include <QApplication>

FILE* output = nullptr;
// 针对qDebug打印的回调！！把日志输出到文件中！
void msgHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    (void) type;
    (void) context;
    const QByteArray& log = msg.toUtf8();
    fprintf(output, "%s\n", log.constData());
    // 确保数据落入硬盘
    fflush(output);
}

int main(int argc, char *argv[])
{
    // 这个 QApplication 是整个应用程序窗口！！
    QApplication a(argc, argv);

#if LOG_TO_FILE
    // 日志文件，追加写
    output = fopen("./log.txt", "a");
    qInstallMessageHandler(msgHandler);
#endif

    // 登录测试
#if TEST_SKIP_LOGIN
    MainWidget* mainWidget = MainWidget::getInstance();
    mainWidget->show();
#else
    // 这个 LoginWidget 设置了 DeleteOnClose，所以只能在堆上 new 出来！
    // 若在栈上创建，则在关闭窗口的时候就会奔溃（delete 栈上的空间）
    UserNameLoginWidget* userNameLoginWidget = new UserNameLoginWidget();
    userNameLoginWidget->show();
#endif

    // model::DataCenter* dataCenter = model::DataCenter::getInstance();
    // dataCenter->initDataFile();
    // dataCenter->writeToDataFile();

    // 网络连通性测试
#if TEST_NETWORK
    // network::NetClient netClient(nullptr);
    // netClient.ping();
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    dataCenter->ping();
#endif

    return a.exec();
}
