#ifndef SMARTHOME_H
#define SMARTHOME_H
#include <QBluetoothSocket>
#include <QString>

#include <QObject>

class SmartHome : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isSocketConnected READ isSocketConnected WRITE setIsSocketConnected NOTIFY isSocketConnectedChanged)
    Q_PROPERTY(QString readData READ readData WRITE setReadData NOTIFY readDataChanged)

public:
    explicit SmartHome(QObject *parent = nullptr);
    bool isSocketConnected();
    QString readData();

signals:
    void readDataChanged();
    void isSocketConnectedChanged();

public slots:
    void on_smartHomeSocketConnectButton_clicked();
    void on_smartHomeSocketDisconnectButton_clicked();
    void sendMessage(const QString &message);

private slots:
    void socketReadyRead();
    void isSmartHomeConnected();

private:
    void setIsSocketConnected(bool isConnected);
    void setReadData(const QString &data);

private:
    QBluetoothSocket * socket;
    bool m_isSocketConnected = false;
    QString m_readData;
};

#endif // SMARTHOME_H
