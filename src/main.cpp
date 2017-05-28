#include <QQmlApplicationEngine>

#include <widgets/controlwidget.h>
#include <adapters/controlqmladapter.h>
#include <QtWidgets/QApplication>

#include <QQmlContext>
#include <QDebug>
#include <QFile>
#include <loaders/electionsdataloader.h>

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

    QQmlApplicationEngine engine;

    ControlQMLAdapter controlAdapter;
    controlAdapter.setTarget(&w);
    ElectionsDataLoader edl;
    edl.open("db.db");

    engine.rootContext()->setContextProperty("Data", &edl);
    engine.rootContext()->setContextProperty("ControlAdapter", &controlAdapter);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    w.show();

    return app.exec();
}
