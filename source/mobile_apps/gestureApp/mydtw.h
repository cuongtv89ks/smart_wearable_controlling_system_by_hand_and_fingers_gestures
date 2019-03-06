#ifndef MYDTW_H
#define MYDTW_H

#include <QtMath>
#include <QtAlgorithms>
#include <QVector>
#include <QList>


class MyDTW
{
public:
    MyDTW();

    MyDTW(QList<QList<double>> signalA, QList<QList<double>> signalB);
    ~MyDTW();

    double distance(int pos);

    QVector<double> getFirst(int pos);
    QVector<double> getSecond(int pos);

private:
    QList<QList<double>> signalA;
    QList<QList<double>> signalB;
    double min(double x, double y, double z);
};

#endif // MYDTW_H
