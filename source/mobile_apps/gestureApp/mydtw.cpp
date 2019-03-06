#include "mydtw.h"
#include <QDebug>

MyDTW::MyDTW()
{

}

MyDTW::MyDTW(QList<QList<double>> signalA, QList<QList<double>> signalB)
{
    this->signalA = signalA;
    this->signalB = signalB;
}

MyDTW::~MyDTW()
{
    qDebug() << "kill";
}

double MyDTW::distance(int pos)
{
    QVector<double> first = getFirst(pos);
    QVector<double> second = getSecond(pos);
    int firstSize = first.size();
    int secondSize = second.size();
    double cost = 0.0;

    double dist[first.size()][second.size()];

    // initialise distance matrix
    for(int i=0; i<firstSize; i++){
        for (int j=0; j<secondSize; j++){
            dist[i][j] = 0;
        }
    }

    for(int i=0; i<firstSize; i++){
        for(int j=0; j<secondSize; j++){
            dist[i][j] = qFabs(first.at(i) - second.at(j));
        }
    }

    // initalize accumilated_cost matrix
    double accumulated_cost[first.size()][second.size()];
    for(int i=0; i<firstSize; i++){
        for (int j=0; j<secondSize; j++){
            accumulated_cost[i][j] = 0;
        }
    }
    accumulated_cost[0][0] = dist[0][0];

    for(int i=1; i<secondSize; i++){
        accumulated_cost[0][i] = dist[0][i] + accumulated_cost[0][i-1];
    }

    for(int i=1; i<firstSize; i++){
        accumulated_cost[i][0] = dist[i][0] + accumulated_cost[i-1][0];
    }

    for(int i=1; i<firstSize; i++){
        for (int j=1; j<secondSize; j++){
            accumulated_cost[i][j] = min(accumulated_cost[i-1][j-1],
                                         accumulated_cost[i][j-1],
                                         accumulated_cost[i-1][j]) + dist[i][j];
        }
    }

    int i = firstSize - 1;
    int j = secondSize - 1;
    while ((i>=0)&&(j>=0)) {
        cost += dist[i][j];
        if(i==0){
            j--;
        }
        else if (j==0) {
            i--;
        }
        else {
            if (accumulated_cost[i-1][j] == min(accumulated_cost[i-1][j-1],
                                                 accumulated_cost[i][j-1],
                                                 accumulated_cost[i-1][j])){
                i--;
            }
            else if (accumulated_cost[i][j-1] == min(accumulated_cost[i-1][j-1],
                                                     accumulated_cost[i][j-1],
                                                     accumulated_cost[i-1][j]))
                j--;
            else {
                i--;
                j--;
            }
        }
    }

    return cost;
}

QVector<double> MyDTW::getFirst(int pos)
{
    QVector<double> temp;
    for(int i=0; i<signalA.size(); i++){
        temp.append(signalA.at(i).at(pos));
    }
    return temp;
}

QVector<double> MyDTW::getSecond(int pos)
{
    QVector<double> temp;
    for(int i=0; i<signalB.size(); i++){
        temp.append(signalB.at(i).at(pos));
    }
    return temp;
}

double MyDTW::min(double x, double y, double z)
{
    double min;
    (x > y) ? min = y: min = x;
    (z > min) ? min = min: min = z;
    return min;
}


