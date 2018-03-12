#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "pion.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    pion p;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("vueObjectCpt", &p);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
