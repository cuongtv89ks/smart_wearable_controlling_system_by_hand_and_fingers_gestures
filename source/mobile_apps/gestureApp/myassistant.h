#ifndef MYASSISTANT_H
#define MYASSISTANT_H

#include <QObject>
#include <QTextToSpeech>
#include <QVector>

class MyAssistant : public QObject
{
    Q_OBJECT
public:
    explicit MyAssistant(QObject *parent = nullptr);

signals:

public slots:
    void speak(QString say);
    void stop();



private:
    QTextToSpeech * m_speech;
    QVector<QVoice> m_voices;
};

#endif // MYASSISTANT_H
