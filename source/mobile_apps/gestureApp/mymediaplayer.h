#ifndef MYMEDIAPLAYER_H
#define MYMEDIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioRecorder>

static const QString appSound(QStringLiteral("/sdcard/SmartHomeApp/sounds"));

class MyMediaPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MyMediaPlayer(QObject *parent = nullptr);

signals:

public slots:
    void setPlayMusicMedia(QString source);
    void playMusic();
    void stopPlayMusic();
    void record();
    void stopRecord();

private:
    QMediaPlayer * m_player;
    QMediaRecorder * m_audioRecorder;
};

#endif // MYMEDIAPLAYER_H
