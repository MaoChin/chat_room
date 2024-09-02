#include "groupsessiondetailwidget.h"

#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

GroupSessionDetailWidget::GroupSessionDetailWidget(QWidget* parent)
    :QDialog(parent)
{
    // 基本属性
    this->setFixedSize(400, 500);
    this->setWindowTitle("会话详情");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    this->setStyleSheet("QWidget { background-color: rgb(250, 250, 250); }");
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 布局管理器
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(20, 20, 20, 0);
    vlayout->setAlignment(Qt::AlignTop | Qt::AlignVCenter);
    this->setLayout(vlayout);

    // 滚动区域
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(300, 350);
    scrollArea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 3px; background-color: rgb(230, 230, 230)}");
    scrollArea->setStyleSheet("QScrollArea { border: none; }");

    // 设置滚动区域内的QWidget
    QWidget* container = new QWidget();
    scrollArea->setWidget(container);

    // container内的布局管理器
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    container->setLayout(gridLayout);



    vlayout->addWidget(scrollArea);
}
