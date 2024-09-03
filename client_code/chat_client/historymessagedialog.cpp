#include "historymessagedialog.h"

#include "debug.h"

#include <QGridLayout>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDateTimeEdit>
#include <QScrollArea>
#include <QScrollBar>

// 具体的一条历史消息
HistoryMessageItem::HistoryMessageItem(){

}

HistoryMessageItem *HistoryMessageItem::makeHistoryMessageItem(const model::MessageInfo &messageInfo){
    HistoryMessageItem* historyMessageItem = new HistoryMessageItem();
    // Preferred 会优先保留自身尺寸，而后灵活扩展（因为消息类型不同，占据的空间也是不同的）
    historyMessageItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // 布局管理器
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(8);
    gridLayout->setVerticalSpacing(2);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    historyMessageItem->setLayout(gridLayout);

    // 组件
    QPushButton* headPortrait = new QPushButton();
    headPortrait->setFixedSize(40, 40);
    headPortrait->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    headPortrait->setIconSize(QSize(40, 40));
    headPortrait->setIcon(QIcon(messageInfo._sender._headPortrait));
    headPortrait->setStyleSheet("QPushButton { border: none; background-color: transparent; }");

    QLabel* nickNameAndSendTime = new QLabel();
    nickNameAndSendTime->setFixedHeight(20);
    nickNameAndSendTime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    nickNameAndSendTime->setStyleSheet("QLabel { font-size: 14px; font-weight: 550; }");
    nickNameAndSendTime->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    nickNameAndSendTime->setText(messageInfo._sender._nickName + " | " + messageInfo._sendTime);

    gridLayout->addWidget(headPortrait, 0, 0, 2, 1);
    gridLayout->addWidget(nickNameAndSendTime, 0, 1, 1, 1);

    // 具体的消息
    // 使用一个QWidget接收不同的消息类型
    QWidget* contentWidget = nullptr;
    if(messageInfo._messageType == model::TEXT_TYPE){
        QLabel* contentLabel = new QLabel();
        contentLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        // 自动换行
        contentLabel->setWordWrap(true);
        // 自动适应尺寸（不是那么精细，但是可以用）
        contentLabel->adjustSize();
        contentLabel->setText(messageInfo._content);
        contentWidget = contentLabel;
    }
    else if(messageInfo._messageType == model::IMAGE_TYPE){

    }
    else if(messageInfo._messageType == model::FILE_TYPE){

    }
    else if(messageInfo._messageType == model::VOICE_TYPE){

    }
    else{
        LOG() << "消息类型错误！";
    }

    gridLayout->addWidget(contentWidget, 1, 1, 5, 1);
    return historyMessageItem;
}


// 历史消息对话框
HistoryMessageDialog::HistoryMessageDialog(QWidget* parent)
    :QDialog(parent)
{
    // 基本属性
    this->setFixedSize(520, 600);
    this->setWindowTitle("历史消息");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    this->setStyleSheet("QWidget { background-color: rgb(250, 250, 250); }");
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 布局管理器
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(10);
    gridLayout->setVerticalSpacing(10);
    gridLayout->setContentsMargins(20, 20, 20, 10);
    gridLayout->setAlignment(Qt::AlignTop);
    this->setLayout(gridLayout);

    // 组件
    QRadioButton* keySearchRadioButton = new QRadioButton();
    QRadioButton* timeSearchRadioButton = new QRadioButton();
    keySearchRadioButton->setText("按照关键字查找");
    timeSearchRadioButton->setText("按照事件查找");
    // 默认按照关键字查找
    keySearchRadioButton->setChecked(true);
    timeSearchRadioButton->setChecked(false);
    gridLayout->addWidget(keySearchRadioButton, 0, 0, 1, 2);
    gridLayout->addWidget(timeSearchRadioButton, 0, 2, 1, 2);

    // 关键字查找搜索框
    QLineEdit* searchBar = new QLineEdit();
    searchBar->setFixedHeight(35);
    searchBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QString searchBarStyle = "QLineEdit { border: none; border-radius: 10px; padding-left: 10px; background-color: rgb(240, 240, 240); font-size: 13px; }";
    searchBar->setStyleSheet(searchBarStyle);
    searchBar->setPlaceholderText("请输入搜索关键字");

    QPushButton* searchBtn = new QPushButton();
    searchBtn->setFixedSize(35, 35);
    searchBtn->setIconSize(QSize(30, 30));
    searchBtn->setIcon(QIcon(":/resource/image/search.png"));
    QString searchBtnStyle = "QPushButton { border: none; border-radius: 8px; background-color: transparent; }";
    searchBtnStyle += "QPushButton:hover { background-color: rgb(240, 240, 240); }";
    searchBtnStyle += "QPushButton:pressed { background-color: rgb(220, 220, 220); }";
    searchBtn->setStyleSheet(searchBtnStyle);

    // 搜索框占1行8列
    gridLayout->addWidget(searchBar, 1, 0, 1, 8);
    // 搜索按钮占1行1列
    gridLayout->addWidget(searchBtn, 1, 8, 1, 1);

    // 时间查找控件
    QLabel* beginTimeTag = new QLabel();
    QLabel* endTimeTag = new QLabel();
    QString tagStyle = "QLabel { font-size: 14px; }";
    beginTimeTag->setStyleSheet(tagStyle);
    endTimeTag->setStyleSheet(tagStyle);
    beginTimeTag->setText("起始时间");
    endTimeTag->setText("结束时间");
    // 默认先隐藏
    beginTimeTag->hide();
    endTimeTag->hide();

    QDateTimeEdit* beginDateTime = new QDateTimeEdit();
    QDateTimeEdit* endDateTime = new QDateTimeEdit();
    beginDateTime->setFixedHeight(34);
    endDateTime->setFixedHeight(34);
    // QString dateTimeStyle = "QDateTimeEdit { border-radius: 8px; }";
    // beginDateTime->setStyleSheet(dateTimeStyle);
    // 默认先隐藏
    beginDateTime->hide();
    endDateTime->hide();

    // 显示搜索到的历史消息的滚动区域
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 2px; background-color: rgb(230, 230, 230); }");
    scrollArea->setStyleSheet(" QScrollArea { border: none; background-color: transparent; }");

    // 滚动区域内配套的QWidget
    _resultContainer = new QWidget();
    scrollArea->setWidget(_resultContainer);
    // 占1行9列
    gridLayout->addWidget(scrollArea, 2, 0, 1, 9);

    // _resultContainer的布局管理器
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(10);
    vlayout->setContentsMargins(10, 10, 25, 10);
    _resultContainer->setLayout(vlayout);

#if TEST_UI
    model::UserInfo userInfo;
    userInfo._headPortrait = QIcon(":/resource/image/headPortrait.png");
    userInfo._nickName = "小八";
    userInfo._personalSignature = "我的个性签名";
    userInfo._phoneNum = "11223345";
    QString content = "这是一条消息";

    for(int i = 0; i < 20; ++i){
        userInfo._userId = QString::number(1000 + i);
        // 这个messageInfo 就不需要 new 了！！没有类会保存这个对象
        model::MessageInfo messageInfo = model::MessageInfo::makeMessageInfo(QString::number(i), model::TEXT_TYPE, userInfo, content.toUtf8(), "");
        addHistoryMessageItem(messageInfo);
    }
#endif

    // 信号槽
    // 点击“按关键字查找”切换到关键字相关控件
    connect(keySearchRadioButton, &QRadioButton::clicked, this, [=]() {
        gridLayout->removeWidget(beginTimeTag);
        gridLayout->removeWidget(beginDateTime);
        gridLayout->removeWidget(endTimeTag);
        gridLayout->removeWidget(endDateTime);
        beginTimeTag->hide();
        beginDateTime->hide();
        endTimeTag->hide();
        endDateTime->hide();

        gridLayout->addWidget(searchBar, 1, 0, 1, 8);
        searchBar->show();
    });

    // 点击“按时间查找”切换到时间相关控件
    connect(timeSearchRadioButton, &QRadioButton::clicked, this, [=]() {
        gridLayout->removeWidget(searchBar);
        searchBar->hide();

        // 占1行1列
        gridLayout->addWidget(beginTimeTag, 1, 0, 1, 1);
        // 占1行3列
        gridLayout->addWidget(beginDateTime, 1, 1, 1, 3);
        gridLayout->addWidget(endTimeTag, 1, 4, 1, 1);
        gridLayout->addWidget(endDateTime, 1, 5, 1, 3);
        beginTimeTag->show();
        beginDateTime->show();
        endTimeTag->show();
        endDateTime->show();
    });
}

void HistoryMessageDialog::addHistoryMessageItem(const model::MessageInfo &messageInfo){
    HistoryMessageItem* historyMessageItem = HistoryMessageItem::makeHistoryMessageItem(messageInfo);
    _resultContainer->layout()->addWidget(historyMessageItem);
}

void HistoryMessageDialog::clear(){
    QVBoxLayout* vlayout = dynamic_cast<QVBoxLayout*>(_resultContainer->layout());
    for(int i = vlayout->count() - 1; i >= 0; --i){
        auto* item = vlayout->takeAt(i);
        if(item == nullptr || item->widget() == nullptr){
            continue;
        }
        delete item->widget();
    }
}

