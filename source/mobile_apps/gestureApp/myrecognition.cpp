#include "myrecognition.h"
#include <QDebug>

MyRecognition::MyRecognition(QObject *parent) : QObject(parent)
{
    // Bluetooth
    gloveSocket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    // timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(processingData()));
    timer.setSingleShot(true);

    // get gesture items
    getGestureItems();
}

void MyRecognition::setGloveData(const QString &data)
{
    if (data == m_gloveData)
        return;
    m_gloveData = data;
    emit gloveDataChanged();
}

void MyRecognition::setIsSocketConnected(bool isConnected)
{
    if (isConnected == m_isSocketConnected)
        return;
    m_isSocketConnected = isConnected;
    emit isSocketConnectedChanged();
}

void MyRecognition::setPrediction(const QString &predic)
{
    //if (predic == m_prediction)
        //return;
    m_prediction = predic;
    emit predictionChanged();
}

QString MyRecognition::gesturePrediction(QList<QList<double> > testingPhase)
{
    QList<double> dist;
    double dist_min;
    QString predic;
    foreach (const QString &trainingFileName, gestureItems) {
        dist.append(dtwGesture(testingPhase, trainingFileName));
    }
    //qDebug() << dist;
    dist_min = min(dist);
    predic = gestureItems[dist.indexOf(dist_min)];
    return predic;
}

void MyRecognition::getGestureItems()
{
    QDir dir(appDataBase);
    QStringList entryList = dir.entryList();
    QString temp;
    for(int i=2; i<entryList.size(); i++){
        temp = entryList.at(i);
        gestureItems.append(temp.remove(".dat"));
    }
    //qDebug() <<gestureItems;
}

double MyRecognition::dtwGesture(QList<QList<double> > testingPhase, QString trainingFileName)
{
    QList<QList<double>> trainingPhase = loadList(trainingFileName);
    recognition = new MyDTW(testingPhase, trainingPhase);
    double dist_0 = recognition->distance(0);
    double dist_1 = recognition->distance(1);
    double dist_2 = recognition->distance (2);
    double dist = dist_0 + dist_1 + dist_2;
    delete recognition;
    return dist;
}

QList<QList<double> > MyRecognition::loadList(QString fileName)
{
    QList<QList<double>> list;
    QFile file(appDataBase + "/" + fileName + ".dat");
    if (!file.open(QIODevice::ReadOnly)){
        qDebug() << file.errorString();
        //return;
    }
    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_9);
    stream >> list;
    file.close();
    return list;
}

double MyRecognition::min(QList<double> list)
{
    int i=0;
    double temp = list.at(0);
    for (i=0; i<list.size(); i++){
        if (temp > list.at(i))
            temp = list.at(i);
    }
    return temp;
}

QString MyRecognition::gloveData()
{
    return m_gloveData;
}

bool MyRecognition::isSocketConnected()
{
    return m_isSocketConnected;
}

QString MyRecognition::prediction()
{
    return m_prediction;
}

void MyRecognition::on_gloveConnectButton_clicked()
{
    gloveSocket->connectToService(QBluetoothAddress("20:16:04:14:12:36"),
                                  QBluetoothUuid(serviceUuid),
                                  QIODevice::ReadOnly);
    connect(gloveSocket, SIGNAL(connected()),
            this, SLOT(gloveIsConnected()));
    connect(gloveSocket, SIGNAL(readyRead()),
            this, SLOT(gloveReadyRead()));
    timer.start(5);
}

void MyRecognition::gloveIsConnected()
{
    setIsSocketConnected(true);
}

void MyRecognition::gloveReadyRead()
{
    if (!gloveSocket)
        return;
    while(gloveSocket->canReadLine()){
        QByteArray line = gloveSocket->readLine();
        QString rawData = QString::fromUtf8(line.data()).remove(QRegularExpression("[\r\n]"));
        setGloveData(rawData);
        QStringList data = rawData.split(",");
        if (data.length() == 10){
            bool ok;
            timeStick = QString(data.at(0)).toInt(&ok, 10);
            for (int i=0; i<9; i++){
                imuValue[i] =  QString(data.at(i+1)).toDouble(&ok);
            }
        }
    }
}

void MyRecognition::processingData()
{
    static int lastTime = 0;
    static QList<double> imuOrient;

    if (timeStick != lastTime){
        for (int i=0; i<9; i++){
            imuOrient.append(imuValue[i]);
        }
        imuOrientationList.append(imuOrient);
        //imuOrient.clear();

        counter++;
        //qDebug() << counter << ": " << imuOrient;
        imuOrient.clear();
        if (counter > 49){
            QString prediction = gesturePrediction(imuOrientationList);
            //qDebug() << prediction;
            setPrediction(prediction);
            imuOrient.clear();
            imuOrientationList.clear();
            counter = 0;
        }
    } else {
        counter = 0;
        imuOrient.clear();
        imuOrientationList.clear();
    }
    lastTime = timeStick;
    timer.start(35);
}

void MyRecognition::on_gloveDisconnectButton_clicked()
{
    gloveSocket->close();
    setIsSocketConnected(false);
}


