#include "myassistant.h"
#include <QDebug>

MyAssistant::MyAssistant(QObject *parent) : QObject(parent)
{
    QStringList engines = QTextToSpeech::availableEngines();
    qDebug() << "Available engines:";
    for (auto engine : engines) {
        qDebug() << "  " << engine;
    }

    // Create an instance using the default engine/plugin.
    m_speech = new QTextToSpeech();

    // List the available locales.
    qDebug() << "Available locales:";
    for (auto locale : m_speech->availableLocales()) {
        qDebug() << "  " << locale;
    }

    // Set locale.
    m_speech->setLocale(QLocale(QLocale::English, QLocale::LatinScript, QLocale::UnitedStates));

    // List the available voices.
    qDebug() << "Available voices:";
    for (auto voice : m_speech->availableVoices()) {
        qDebug() << "  " << voice.name();
    }
    // set rate
    m_speech->setRate(0.0);

    // Display properties.
    qDebug() << "Locale:" << m_speech->locale();
    qDebug() << "Pitch:" << m_speech->pitch();
    qDebug() << "Rate:" << m_speech->rate();
    qDebug() << "Voice:" << m_speech->voice().name();
    qDebug() << "Volume:" << m_speech->volume();
    qDebug() << "State:" << m_speech->state();
}

void MyAssistant::speak(QString say)
{
    m_speech->say(say);
}

void MyAssistant::stop()
{
    m_speech->stop();
}

