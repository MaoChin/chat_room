#include "addfrineddialog.h"

#include "debug.h"
#include "model/datacenter.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QLabel>


// 搜索到的好友结果中的一个好友项
ResultFriendItem::ResultFriendItem(const model::UserInfo &userInfo)
    :_userInfo(userInfo)   // const & 类型的变量必须通过初始化列表初始化
{
    // 基本属性
    this->setFixedHeight(70);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 布局管理器
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setHorizontalSpacing(10);
    gridLayout->setVerticalSpacing(4);
    gridLayout->setContentsMargins(10, 10, 15, 10);
    this->setLayout(gridLayout);

    // 组件
    QPushButton* headPortrait = new QPushButton();
    headPortrait->setFixedSize(50, 50);
    headPortrait->setIconSize(QSize(50, 50));
    headPortrait->setIcon(userInfo._headPortrait);
    headPortrait->setStyleSheet("QPushButton { border: none; background-color: transparent; }");

    QLabel* nickNameLabel = new QLabel();
    nickNameLabel->setFixedHeight(35);
    nickNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    nickNameLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    nickNameLabel->setStyleSheet("QLabel { font-size: 14px; font-weight: 700; }");
    nickNameLabel->setText(userInfo._nickName);

    QLabel* personalSignatureLabel = new QLabel();
    personalSignatureLabel->setFixedHeight(35);
    personalSignatureLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    personalSignatureLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    personalSignatureLabel->setStyleSheet("QLabel { font-size: 14px; }");
    personalSignatureLabel->setText(userInfo._personalSignature);

    QPushButton* addBtn = new QPushButton();
    addBtn->setFixedSize(90, 30);
    addBtn->setText("添加好友");
    QString addBtnStyle = "QPushButton { border: none; border-radius: 8px; font-size: 18px; color: rgb(255, 255, 255); background-color: rgb(137, 217, 97); }";
    addBtnStyle += "QPushButton:hover { background-color: rgb(200, 200, 200); }";
    addBtnStyle += "QPushButton:pressed { background-color: rgb(220, 220, 220); }";
    addBtn->setStyleSheet(addBtnStyle);

    gridLayout->addWidget(headPortrait, 0, 0, 2, 1);
    gridLayout->addWidget(nickNameLabel, 0, 1, 1, 1);
    gridLayout->addWidget(personalSignatureLabel, 1, 1, 1, 1);
    gridLayout->addWidget(addBtn, 0, 3, 2, 1);

    // 关联 addBtn 按钮的信号槽
    connect(addBtn, &QPushButton::clicked, this, [=]() {
        model::DataCenter* dataCenter = model::DataCenter::getInstance();
        dataCenter->addFriendApplyAsync(_userInfo._userId);

        // 点击后把这个按钮设置成不能被点击
        addBtn->setEnabled(false);
        addBtn->setText("已申请");
        QString addBtnStyle = "QPushButton { border: none; border-radius: 8px; "
                              "font-size: 18px; color: rgb(255, 255, 255); "
                              "background-color: rgb(200, 200, 200); }";
        addBtn->setStyleSheet(addBtnStyle);
    });

}


// 添加好友页面
AddFriendDialog::AddFriendDialog(QWidget* parent)
    :QDialog(parent)
{
    // 基本属性
    this->setFixedSize(400, 550);
    this->setWindowTitle("添加朋友");
    this->setWindowIcon(QIcon(":/resource/image/myChat.png"));
    this->setStyleSheet("QWidget { background-color: rgb(250, 250, 250); }");
    this->setAttribute(Qt::WA_DeleteOnClose);

    // 布局管理器
    _gridLayout = new QGridLayout();
    _gridLayout->setHorizontalSpacing(10);
    _gridLayout->setContentsMargins(20, 15, 20, 20);
    _gridLayout->setAlignment(Qt::AlignTop);
    this->setLayout(_gridLayout);

    // 组件
    _searchBar = new QLineEdit();
    _searchBar->setFixedHeight(35);
    _searchBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QString lineEditStyle = "QLineEdit { border: none; border-radius: 10px; font-size: 13px; background-color: rgb(240, 240, 240); padding-left: 8px; }";
    _searchBar->setStyleSheet(lineEditStyle);
    _searchBar->setPlaceholderText("按照手机号/用户名/Id查找");

    QPushButton* searchBtn = new QPushButton();
    searchBtn->setFixedSize(35, 35);
    searchBtn->setIconSize(QSize(30, 30));
    searchBtn->setIcon(QIcon(":/resource/image/search.png"));
    QString searchBtnStyle = "QPushButton { border: none; border-radius: 8px; background-color: transparent; }";
    searchBtnStyle += "QPushButton:hover { background-color: rgb(240, 240, 240); }";
    searchBtnStyle += "QPushButton:pressed { background-color: rgb(220, 220, 220); }";
    searchBtn->setStyleSheet(searchBtnStyle);

    // 搜索框占1行8列
    _gridLayout->addWidget(_searchBar, 0, 0, 1, 8);
    // 搜索按钮占一行一列
    _gridLayout->addWidget(searchBtn, 0, 8, 1, 1);

    // 搜索结果滚动框
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 2px; background-color: rgb(70, 70, 70); }");
    scrollArea->setStyleSheet("QScrollArea { border: none; background-color: transparent; }");
    // 搜索结果占1行9列
    _gridLayout->addWidget(scrollArea, 1, 0, 1, 9);

    // 搜索框配套的QWidget
    _resultContainer = new QWidget();
    // 使用名称选择器只选择这一个QWidget，不影响到其内部的其他控件
    _resultContainer->setObjectName("resultContainer");
    _resultContainer->setStyleSheet("#resultContainer { background-color: transparent; }");
    scrollArea->setWidget(_resultContainer);

    // resultContainer的垂直布局管理器
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSpacing(0);
    vlayout->setContentsMargins(0, 0, 0, 0);
    _resultContainer->setLayout(vlayout);

#if TEST_UI
    for(int i = 0; i < 10; ++i){
        // 这里的构造的 userInfo 必须 new 出来！因为要赋值给 ResultFriendItem 中的 UserInfo&
        // 若这里在栈上，这边栈帧销毁后 ResultFriendItem 里的数据也就没了！！！
        model::UserInfo* userInfo = new model::UserInfo();
        userInfo->_headPortrait = QIcon(":/resource/image/headPortrait.png");
        userInfo->_nickName = "小八";
        userInfo->_personalSignature = "你好";
        userInfo->_userId = QString::number(i);
        addResultFriendItem(*userInfo);
    }
#endif


    // 关联searchBtn的信号槽
    connect(searchBtn, &QPushButton::clicked, this, &AddFriendDialog::clickSearchBtn);
}

void AddFriendDialog::clickSearchBtn(){
    // 1. 拿到输入框的内容
    const QString& searchKey = _searchBar->text();
    if (searchKey.isEmpty()) {
        return;
    }

    // 2. 给服务器发起请求
    model::DataCenter *dataCenter = model::DataCenter::getInstance();
    connect(dataCenter, &model::DataCenter::searchUserAsyncDone, this,
            &AddFriendDialog::clickSearchBtnDone, Qt::UniqueConnection);
    dataCenter->searchUserAsync(searchKey);
}

void AddFriendDialog::clickSearchBtnDone(){
    // 1. 拿到 DataCenter 中的搜索结果列表
    model::DataCenter *dataCenter = model::DataCenter::getInstance();
    QList<model::UserInfo>* searchUserList = dataCenter->getSearchUserList();
    if (searchUserList == nullptr) {
        return;
    }

    this->clearResultFriendItem();
    for (const auto& userInfo : *searchUserList) {
        this->addResultFriendItem(userInfo);
    }
}

void AddFriendDialog::addResultFriendItem(const model::UserInfo &userInfo){
    ResultFriendItem* resultFriendItem = new ResultFriendItem(userInfo);
    _resultContainer->layout()->addWidget(resultFriendItem);
}

void AddFriendDialog::clearResultFriendItem(){
    QVBoxLayout* vlayout = dynamic_cast<QVBoxLayout*>(_resultContainer->layout());
    for(int i = vlayout->count() - 1; i >= 0; --i){
        auto* item = vlayout->takeAt(i);
        if(item == nullptr || item->widget() == nullptr){
            continue;
        }
        delete item->widget();
    }
}

void AddFriendDialog::setSearchBarContent(const QString& searchKey){
    _searchBar->setText(searchKey);
}

