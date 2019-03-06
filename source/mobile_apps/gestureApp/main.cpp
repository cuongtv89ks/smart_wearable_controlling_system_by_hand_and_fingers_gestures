#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mydatetime.h"
#include "myrecognition.h"
#include "smarthome.h"
#include "myassistant.h"
#include "mymediaplayer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<MyDateTime>("io.qt.mydatetime", 1, 0, "MyDateTime");
    qmlRegisterType<MyRecognition>("io.qt.myrecognition", 1, 0, "MyRecognition");
    qmlRegisterType<SmartHome>("io.qt.smarthome", 1, 0, "SmartHome");
    qmlRegisterType<MyAssistant>("io.qt.myassistant", 1, 0, "MyAssistant");
    qmlRegisterType<MyMediaPlayer>("io.qt.mymediaplayer", 1, 0, "MyMediaPlayer");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
