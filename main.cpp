#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "GpioController/gpiocontroller.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<GpioController>("My.Gpio", 1, 0, "GpioController");
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("New_Control", "Main");

    return app.exec();
}
