#ifndef SOUNDRECORDER_H
#define SOUNDRECORDER_H

#include <QObject>
#include <QStandardPaths>
#include <QFile>
#include <QAudioSource>
#include <QAudioSink>
#include <QMediaDevices>

// 音频录制和播放(pcm文件)
class SoundRecorder : public QObject
{
    Q_OBJECT

public:
    const QString RECORD_PATH = "./localData/tmpRecord.pcm";
    const QString PLAY_PATH = "./localData/tmpPlay.pcm";

public:
    // 单例
    static SoundRecorder* getInstance();

    // 开始录制
    void startRecord();
    // 停止录制
    void stopRecord();

    // 开始播放
    void startPlay(const QByteArray& content);
    // 停止播放
    void stopPlay();

private:
    // 构造私有化
    explicit SoundRecorder(QObject *parent = nullptr);

private:
    static SoundRecorder* _instance;

    QFile _soundFile;
    // 实现录制音频(pcm文件)
    QAudioSource* _audioSource;

    // 音频播放相关
    QAudioSink *_audioSink;
    QMediaDevices *_outputDevices;
    QAudioDevice _outputDevice;
    QFile _inputFile;

signals:
    // 录制完毕后发送的信号
    void soundRecordDone(const QString& path);
    // 播放完毕发送的信号
    void soundPlayDone();
};

#endif // SOUNDRECORDER_H
