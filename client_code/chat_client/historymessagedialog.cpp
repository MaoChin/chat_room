#include "historymessagedialog.h"

#include "debug.h"
#include "model/datacenter.h"
#include "toast.h"
#include "soundrecorder.h"

#include <QGridLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QFileDialog>

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
        contentWidget = new ImageMessageBtn(messageInfo._fileId, messageInfo._content);
    }
    else if(messageInfo._messageType == model::FILE_TYPE){
        contentWidget = new FileMessageLabel(messageInfo._fileId, messageInfo._fileName);
    }
    else if(messageInfo._messageType == model::VOICE_TYPE){
        contentWidget = new VoiceMessageLabel(messageInfo._fileId);
    }
    else{
        LOG() << "消息类型错误！";
    }

    gridLayout->addWidget(contentWidget, 1, 1, 5, 1);
    return historyMessageItem;
}

// 针对图片类型的消息的显示
ImageMessageBtn::ImageMessageBtn(const QString &fileId, const QByteArray &content)
    :_fileId(fileId)
{
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setStyleSheet("QPushButton { border: none; }");

    if (!content.isEmpty()) {
        // 直接显示到界面上
        this->updateUI(fileId, content);
    } else {
        // 通过网络来获取
        model::DataCenter* dataCenter = model::DataCenter::getInstance();
        connect(dataCenter, &model::DataCenter::getSingleFileContentAsyncDone, this, &ImageMessageBtn::updateUI);
        dataCenter->getSingleFileContentAsync(fileId);
    }
}

void ImageMessageBtn::updateUI(const QString &fileId, const QByteArray &content){
    if (this->_fileId != fileId) {
        return;
    }
    // 如果图片尺寸太大, 需要进行缩放.
    QImage image;
    image.loadFromData(content);

    int width = image.width();
    int height = image.height();
    if (image.width() >= 200) {
        // 进行缩放, 缩放之后, 宽度就是固定的 200
        width = 200;
        height = ((double)image.height() / image.width()) * width;
    }
    this->resize(width, height);
    this->setIconSize(QSize(width, height));
    QPixmap pixmap = QPixmap::fromImage(image);
    this->setIcon(QIcon(pixmap));
}

// 针对文件历史消息的显示
FileMessageLabel::FileMessageLabel(const QString &fileId, const QString &fileName)
    :_fileId(fileId),
    _fileName(fileName)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setText("[文件] " + fileName);
    this->setWordWrap(true);
    // 自动调整尺寸
    this->adjustSize();
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // if (!content.isEmpty()) {
    //     // 原则上来说, 这个条件不会触发. 因为这里的 content 是来自于请求服务器的 历史消息列表的 接口.
    //     // 请求这个接口的过程中, 拿到的 Message 对象(不是文本), content 必然为 空, 通过 fileId 做二次请求.
    //     return;
    // }

    // 需要从网络加载数据了
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    connect(dataCenter, &model::DataCenter::getSingleFileContentAsyncDone, this, &FileMessageLabel::getContentDone);
    dataCenter->getSingleFileContentAsync(this->_fileId);
}

void FileMessageLabel::getContentDone(const QString &fileId, const QByteArray &fileContent)
{
    if (fileId != this->_fileId) {
        return;
    }

    this->_content = fileContent;
    this->_loadDone = true;
}

void FileMessageLabel::mousePressEvent(QMouseEvent *event)
{
    (void) event;
    if (!this->_loadDone) {
        // 说明数据还没准备好.
        Toast::showMessage("文件内容加载中, 请稍后尝试!");
        return;
    }

    // 弹出一个对话框, 让用户来选择当前要保存的位置
    QString filePath = QFileDialog::getSaveFileName(this, "另存为", QDir::homePath(), "*");
    if (filePath.isEmpty()) {
        // 用户取消了保存
        LOG() << "cancle save file";
        return;
    }

    model::writeByteArrayToFile(filePath, _content);
}

// 针对语音历史消息的显示
VoiceMessageLabel::VoiceMessageLabel(const QString &fileId)
    :_fileId(fileId)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setText("[语音]");
    this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    // 这两个操作不太需要了, 此处只有 语音 两个字
    this->setWordWrap(true);
    this->adjustSize();

    // 历史消息都是从网络获取的，所以content一定为空，需要再从网络获取
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    connect(dataCenter, &model::DataCenter::getSingleFileContentAsyncDone, this, &VoiceMessageLabel::getContentDone);
    dataCenter->getSingleFileContentAsync(fileId);
}

void VoiceMessageLabel::getContentDone(const QString &fileId, const QByteArray &content)
{
    if (fileId != this->_fileId) {
        return;
    }
    this->_content = content;
    this->_loadDone = true;
}

void VoiceMessageLabel::mousePressEvent(QMouseEvent *event)
{
    (void) event;
    if (!this->_loadDone) {
        Toast::showMessage("语音内容加载中, 稍后重试");
        return;
    }
    SoundRecorder* soundRecorder = SoundRecorder::getInstance();
    this->setText("播放中...");
    connect(soundRecorder, &SoundRecorder::soundPlayDone, this, &VoiceMessageLabel::playDone, Qt::UniqueConnection);
    soundRecorder->startPlay(this->_content);
}

void VoiceMessageLabel::playDone(){
    if (this->text() == "播放中...") {
        this->setText("[语音]");
    }
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
    _keySearchRadioButton = new QRadioButton();
    _timeSearchRadioButton = new QRadioButton();
    _keySearchRadioButton->setText("按照关键字查找");
    _timeSearchRadioButton->setText("按照时间区间查找");
    // 默认按照关键字查找
    _keySearchRadioButton->setChecked(true);
    _timeSearchRadioButton->setChecked(false);
    gridLayout->addWidget(_keySearchRadioButton, 0, 0, 1, 2);
    gridLayout->addWidget(_timeSearchRadioButton, 0, 2, 1, 2);

    // 关键字查找搜索框
    _searchBar = new QLineEdit();
    _searchBar->setFixedHeight(35);
    _searchBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QString searchBarStyle = "QLineEdit { border: none; border-radius: 10px; padding-left: 10px; background-color: rgb(240, 240, 240); font-size: 13px; }";
    _searchBar->setStyleSheet(searchBarStyle);
    _searchBar->setPlaceholderText("请输入搜索关键字");

    QPushButton* searchBtn = new QPushButton();
    searchBtn->setFixedSize(35, 35);
    searchBtn->setIconSize(QSize(30, 30));
    searchBtn->setIcon(QIcon(":/resource/image/search.png"));
    QString searchBtnStyle = "QPushButton { border: none; border-radius: 8px; background-color: transparent; }";
    searchBtnStyle += "QPushButton:hover { background-color: rgb(240, 240, 240); }";
    searchBtnStyle += "QPushButton:pressed { background-color: rgb(220, 220, 220); }";
    searchBtn->setStyleSheet(searchBtnStyle);

    // 搜索框占1行8列
    gridLayout->addWidget(_searchBar, 1, 0, 1, 8);
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

    _beginDateTime = new QDateTimeEdit();
    _endDateTime = new QDateTimeEdit();
    _beginDateTime->setFixedHeight(34);
    _endDateTime->setFixedHeight(34);
    // QString dateTimeStyle = "QDateTimeEdit { border-radius: 8px; }";
    // beginDateTime->setStyleSheet(dateTimeStyle);
    // 默认先隐藏
    _beginDateTime->hide();
    _endDateTime->hide();

    // 显示搜索到的历史消息的滚动区域
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { height: 0px; }");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 2px; background-color: rgb(70, 70, 70); }");
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
    connect(_keySearchRadioButton, &QRadioButton::clicked, this, [=]() {
        gridLayout->removeWidget(beginTimeTag);
        gridLayout->removeWidget(_beginDateTime);
        gridLayout->removeWidget(endTimeTag);
        gridLayout->removeWidget(_endDateTime);
        beginTimeTag->hide();
        _beginDateTime->hide();
        endTimeTag->hide();
        _endDateTime->hide();

        gridLayout->addWidget(_searchBar, 1, 0, 1, 8);
        _searchBar->show();
    });

    // 点击“按时间查找”切换到时间相关控件
    connect(_timeSearchRadioButton, &QRadioButton::clicked, this, [=]() {
        gridLayout->removeWidget(_searchBar);
        _searchBar->hide();

        // 占1行1列
        gridLayout->addWidget(beginTimeTag, 1, 0, 1, 1);
        // 占1行3列
        gridLayout->addWidget(_beginDateTime, 1, 1, 1, 3);
        gridLayout->addWidget(endTimeTag, 1, 4, 1, 1);
        gridLayout->addWidget(_endDateTime, 1, 5, 1, 3);
        beginTimeTag->show();
        _beginDateTime->show();
        endTimeTag->show();
        _endDateTime->show();
    });

    // 点击搜索按钮的信号槽
    connect(searchBtn, &QPushButton::clicked, this, &HistoryMessageDialog::clickSearchBtn);
}

void HistoryMessageDialog::clickSearchBtn(){
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    connect(dataCenter, &model::DataCenter::searchHistoryMessageAsyncDone, this,
            &HistoryMessageDialog::clickSearchBtnDone);

    if(_keySearchRadioButton->isChecked()){
        // 按关键字搜索
        const QString& searchKey = _searchBar->text();
        if (searchKey.isEmpty()) {
            return;
        }
        dataCenter->searchHistoryMessageBySearchKeyAsync(searchKey);
    }
    else{
        // 按时间搜索
        auto beginTime = _beginDateTime->dateTime();
        auto endTime = _endDateTime->dateTime();
        if (beginTime >= endTime) {
            Toast::showMessage("选择时间错误! 开始时间大于结束时间!");
            return;
        }
        dataCenter->searchHistoryMessageByTimeAsync(beginTime, endTime);
    }
}

void HistoryMessageDialog::clickSearchBtnDone()
{
    // 1. 从 DataCenter 中拿到消息搜索的结果列表
    model::DataCenter* dataCenter = model::DataCenter::getInstance();
    QList<model::MessageInfo>* historyMessageList = dataCenter->getSearchHistoryMessageList();
    if (historyMessageList == nullptr) {
        return;
    }

    // 2. 把搜索结果的数据, 显示到界面上
    this->clear();

    for (const model::MessageInfo& messageInfo : (*historyMessageList)) {
        this->addHistoryMessageItem(messageInfo);
    }
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







