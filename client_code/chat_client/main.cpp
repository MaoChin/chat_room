#include "mainwidget.h"

#include "usernameloginwidget.h"
#include "debug.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // 这个 QApplication 是整个应用程序窗口！！
    QApplication a(argc, argv);

#if TEST_SKIP_LOGIN
    MainWidget* mainWidget = MainWidget::getInstance();
    mainWidget->show();
#else
    // 这个 LoginWidget 设置了 DeleteOnClose，所以只能在堆上 new 出来！
    // 若在栈上创建，则在关闭窗口的时候就会奔溃（delete 栈上的空间）
    UserNameLoginWidget* userNameLoginWidget = new UserNameLoginWidget();
    userNameLoginWidget->show();
#endif

    return a.exec();
}
