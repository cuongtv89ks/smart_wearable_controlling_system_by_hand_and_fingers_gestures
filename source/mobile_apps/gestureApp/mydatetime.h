#ifndef MYDATETIME_H
#define MYDATETIME_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QTimer>
#include "mymediaplayer.h"

class MyDateTime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)
    Q_PROPERTY(QString currentDate READ currentDate WRITE setCurrentDate NOTIFY currentDateChanged)
    Q_PROPERTY(QString alarmSet READ alarmSet WRITE setAlarmSet NOTIFY alarmSetChanged)

public:
    explicit MyDateTime(QObject *parent = nullptr);
    ~MyDateTime();
    QString currentTime();
    QString currentDate();
    QString alarmSet();

    void setCurrentTime(const QString &time);
    void setCurrentDate(const QString &date);
    void setAlarmSet(const QString &alarm);

public slots:
    void activeAlarm();
    void disableAlarm();
    void dismissAlarm();
    void setAlarmSound(QString source);

private slots:
    void getDateTime();

signals:
    void currentTimeChanged();
    void currentDateChanged();
    void alarmSetChanged();

private:
    QString m_currentTime;
    QString m_currentDate;
    QString m_alarmSet;
    bool isAlarmSetted = false;
    QTimer *timer;
    QDateTime *dateTime;
    MyMediaPlayer * alarmBuzzer;
    bool isDismissButtonClicked = false;
};

#endif // MYDATETIME_H
