#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "pion.h"
#include "plateau.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    plateau p;
    engine.rootContext()->setContextProperty("plateau",&p);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
