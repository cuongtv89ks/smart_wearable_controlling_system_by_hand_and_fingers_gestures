#include "smarthome.h"
#include "myrecognition.h"

SmartHome::SmartHome(QObject *parent) : QObject(parent)
{
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
}

bool SmartHome::isSocketConnected()
{
    return m_isSocketConnected;
}

QString SmartHome::readData()
{
    return m_readData;
}

void SmartHome::on_smartHomeSocketConnectButton_clicked()
{
    socket->connectToService(QBluetoothAddress("20:16:04:12:25:30"),
                             QBluetoothUuid(serviceUuid),
                             QIODevice::ReadWrite);
    connect(socket, SIGNAL(connected()),
            this, SLOT(isSmartHomeConnected()));
    connect(socket, SIGNAL(readyRead()),
            this, SLOT(socketReadyRead()));
}

void SmartHome::on_smartHomeSocketDisconnectButton_clicked()
{
    socket->close();
    setIsSocketConnected(false);
}

void SmartHome::sendMessage(const QString &message)
{
    QByteArray text = message.toUtf8() + '\n';
    socket->write(text);
}

void SmartHome::socketReadyRead()
{
    if(!socket)
        return;
    while(socket->canReadLine()){
        QByteArray line = socket->readLine();
        QString rawData = QString::fromUtf8(line.data()).remove(QRegularExpression("[\r\n]"));
        setReadData(rawData);
    }
}

void SmartHome::isSmartHomeConnected()
{
    setIsSocketConnected(true);
}

void SmartHome::setReadData(const QString &data)
{
    if(data == m_readData)
        return;
    m_readData = data;
    emit readDataChanged();
}

void SmartHome::setIsSocketConnected(bool isConnected)
{
    if (isConnected == m_isSocketConnected)
        return;
    m_isSocketConnected = isConnected;
    emit isSocketConnectedChanged();
}
