#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "widgets/controlwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    // load styles
    QFile styleFile(":/assets/styles/style.qss");
    if(styleFile.open(QIODevice::ReadOnly)) {
        const QString styleSheet = QString(styleFile.readAll());
        app.setStyleSheet(styleSheet);
    }

    else
        qDebug() << "Could not open style file.";

    ControlWidget w;
    w.show();

    //QQmlApplicationEngine engine;

    //qmlRegisterType<CloneableItem>("CI", 1, 0, "CI");

    //engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
