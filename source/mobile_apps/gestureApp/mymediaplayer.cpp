#include "mymediaplayer.h"
#include <QUrl>

MyMediaPlayer::MyMediaPlayer(QObject *parent) : QObject(parent)
{
    m_player = new QMediaPlayer;
    m_player->setVolume(75);

    m_audioRecorder = new QAudioRecorder;
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::HighQuality);
    m_audioRecorder->setEncodingSettings(audioSettings);
}

void MyMediaPlayer::setPlayMusicMedia(QString source)
{
    m_player->setMedia(QUrl::fromLocalFile(appSound + source));
}

void MyMediaPlayer::playMusic()
{
    m_player->play();
}

void MyMediaPlayer::stopPlayMusic()
{
    m_player->stop();
}

void MyMediaPlayer::record()
{
    m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(appSound + "/record/record.amr"));
    m_audioRecorder->record();
}

void MyMediaPlayer::stopRecord()
{
    m_audioRecorder->stop();
}
