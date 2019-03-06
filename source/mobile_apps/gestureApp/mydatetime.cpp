#include "mydatetime.h"
#include <QDebug>

MyDateTime::MyDateTime(QObject *parent) :
    QObject(parent)
{
    dateTime = new QDateTime;
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(getDateTime()));
    timer->start(1000);
}

MyDateTime::~MyDateTime()
{
    delete timer;
    delete dateTime;
}

QString MyDateTime::currentTime()
{
    return m_currentTime;
}


QString MyDateTime::currentDate()
{
    return m_currentDate;
}

QString MyDateTime::alarmSet()
{
    return m_alarmSet;
}


void MyDateTime::setCurrentTime(const QString &time)
{
    if(time == m_currentTime)
        return;
    m_currentTime = time;
    emit currentTimeChanged();
}

void MyDateTime::setCurrentDate(const QString &date)
{
    if(date == m_currentDate)
        return;
    m_currentDate = date;
    emit currentDateChanged();
}

void MyDateTime::setAlarmSet(const QString &alarm)
{
    if(alarm == m_alarmSet)
        return;
    m_alarmSet = alarm;
    qDebug() << m_alarmSet;
    emit alarmSetChanged();
}

void MyDateTime::activeAlarm()
{
    isAlarmSetted = true;
    alarmBuzzer = new MyMediaPlayer;
}

void MyDateTime::disableAlarm()
{
    isAlarmSetted = false;
    delete alarmBuzzer;
}

void MyDateTime::dismissAlarm()
{
    alarmBuzzer->stopPlayMusic();
    isDismissButtonClicked = true;
}

void MyDateTime::setAlarmSound(QString source)
{
    alarmBuzzer->setPlayMusicMedia(source);
}

void MyDateTime::getDateTime()
{
    setCurrentTime(dateTime->currentDateTime().toString("hh:mm AP"));
    setCurrentDate(dateTime->currentDateTime().toString("ddd dd MMM yy"));
    if(isAlarmSetted){
        if(m_alarmSet == dateTime->currentDateTime().toString("h:m ap")){
            if ((!isDismissButtonClicked))
                alarmBuzzer->playMusic();
        } else {
            isDismissButtonClicked = false;
        }
    }
}
