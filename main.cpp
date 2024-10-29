#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>

#include "controlblock.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QWidget *widget = new ControlBlock();
    QWindow *window = widget->windowHandle();
    QQuickItem *item = QQuickItem::createWindowContainer(window);

    ControlBlock block;
    block.show();

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.loadFromModule("vx_engine", "Main");

    return app.exec();
}
