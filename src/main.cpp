#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "widgets/controlwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    ControlWidget w;
    w.show();

    //QQmlApplicationEngine engine;

    //qmlRegisterType<CloneableItem>("CI", 1, 0, "CI");

    //engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
