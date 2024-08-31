#include "rightwindowmessageeditarea.h"

#include <QVBoxLayout>

RightWindowMessageEditArea::RightWindowMessageEditArea(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedHeight(200);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 布局管理器
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    // 左，上，右，下
    vlayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(vlayout);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->setSpacing(0);
    hlayout->setContentsMargins(0, 0, 0, 0);
    // 垂直布局中有水平布局
    vlayout->addLayout(hlayout);

}
