#include "mainwidget.h"
#include "./model/data.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget* w = MainWidget::getInstance();
    w->show();
    return a.exec();
}
