#include "soundrecorder.h"

#include <QDir>
#include <QMediaDevices>
// #include <QtAudio>

#include "model/data.h"
#include "toast.h"

// 单例
SoundRecorder* SoundRecorder::_instance = nullptr;

SoundRecorder *SoundRecorder::getInstance()
{
    if (_instance == nullptr) {
        _instance = new SoundRecorder();
    }
    return _instance;
}

// 播放参考 https://www.cnblogs.com/tony-yang-flutter/p/16477212.html
// 录制参考 https://doc.qt.io/qt-6/qaudiosource.html
SoundRecorder::SoundRecorder(QObject *parent)
    : QObject{parent}
{
    // 1. 创建目录
    QDir soundRootPath("./");
    soundRootPath.mkdir("localData");

    // 2. 初始化录制模块
    _soundFile.setFileName(RECORD_PATH);

    QAudioFormat inputFormat;
    inputFormat.setSampleRate(16000);
    inputFormat.setChannelCount(1);
    inputFormat.setSampleFormat(QAudioFormat::Int16);

    QAudioDevice info = QMediaDevices::defaultAudioInput();
    if (!info.isFormatSupported(inputFormat)) {
        LOG() << "录制设备, 格式不支持!";
        return;
    }

    _audioSource = new QAudioSource(inputFormat, this);
    connect(_audioSource, &QAudioSource::stateChanged, this, [=](QAudio::State state) {
        if (state == QAudio::StoppedState) {
            // 录制完毕
            if (_audioSource->error() != QAudio::NoError) {
                LOG() << _audioSource->error();
            }
        }
    });

    // 3. 初始化播放模块
    _outputDevices = new QMediaDevices(this);
    _outputDevice = _outputDevices->defaultAudioOutput();
    QAudioFormat outputFormat;
    outputFormat.setSampleRate(16000);
    outputFormat.setChannelCount(1);
    outputFormat.setSampleFormat(QAudioFormat::Int16);
    if (!_outputDevice.isFormatSupported(outputFormat)) {
        LOG() << "播放设备, 格式不支持";
        return;
    }
    _audioSink = new QAudioSink(_outputDevice, outputFormat);

    connect(_audioSink, &QAudioSink::stateChanged, this, [=](QAudio::State state) {
        if (state == QAudio::IdleState) {
            LOG() << "IdleState";
            this->stopPlay();
            emit this->soundPlayDone();
        }
        else if(state == QAudio::ActiveState) {
            LOG() << "ActiveState";
        }
        else if(state == QAudio::StoppedState) {
            LOG() << "StoppedState";
            if (_audioSink->error() != QAudio::NoError) {
                LOG() << _audioSink->error();
            }
        }
    });
}

void SoundRecorder::startRecord() {
    _soundFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    _audioSource->start(&_soundFile);
}

void SoundRecorder::stopRecord() {
    _audioSource->stop();
    _soundFile.close();
    emit this->soundRecordDone(RECORD_PATH);
}

void SoundRecorder::startPlay(const QByteArray& content) {
    if (content.isEmpty()) {
        Toast::showMessage("数据加载中, 请稍后播放");
        return;
    }
    // 1. 把数据写入到临时文件
    model::writeByteArrayToFile(PLAY_PATH, content);

    // 2. 播放语音
    _inputFile.setFileName(PLAY_PATH);
    _inputFile.open(QIODevice::ReadOnly);
    _audioSink->start(&_inputFile);
}

void SoundRecorder::stopPlay() {
    _audioSink->stop();
    _inputFile.close();
}
