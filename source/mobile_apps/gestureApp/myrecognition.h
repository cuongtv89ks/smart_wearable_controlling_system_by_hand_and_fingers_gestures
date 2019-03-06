#ifndef MYRECOGNITION_H
#define MYRECOGNITION_H

#include <QObject>
#include <QBluetoothSocket>
#include <QTimer>
#include <QString>
#include "mydtw.h"
#include <QByteArray>
#include <QRegularExpression>
#include <QList>
#include <QDir>

static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
static const QString appDataBase(QStringLiteral("/sdcard/SmartHomeApp/data"));

class MyRecognition : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString gloveData READ gloveData WRITE setGloveData NOTIFY gloveDataChanged)
    Q_PROPERTY(bool isSocketConnected READ isSocketConnected WRITE setIsSocketConnected NOTIFY isSocketConnectedChanged)
    Q_PROPERTY(QString prediction READ prediction WRITE setPrediction NOTIFY predictionChanged)

public:
    explicit MyRecognition(QObject *parent = nullptr);
    QString gloveData();
    bool isSocketConnected();
    QString prediction();

signals:
    void gloveDataChanged();
    void isSocketConnectedChanged();
    void predictionChanged();

public slots:
    void on_gloveConnectButton_clicked();
    void on_gloveDisconnectButton_clicked();

private slots:
    void gloveIsConnected();
    void gloveReadyRead();
    void processingData();

private:
    void setGloveData(const QString &data);
    void setIsSocketConnected(bool isConnected);
    void setPrediction(const QString &predic);
    QString gesturePrediction(QList<QList<double>> testingPhase);
    void getGestureItems();
    double dtwGesture(QList<QList<double>> testingPhase, QString trainingFileName);
    QList<QList<double>> loadList(QString fileName);
    double min(QList<double> list);

private:
    QBluetoothSocket * gloveSocket;
    bool m_isSocketConnected = false;
    QString m_gloveData;
    QString m_prediction;
    QList<QList<double>> imuOrientationList;
    double imuValue[9];
    int timeStick;
    MyDTW * recognition;
    QStringList gestureItems;
    QTimer timer;
    int counter = 0;
};

#endif // MYRECOGNITION_H
