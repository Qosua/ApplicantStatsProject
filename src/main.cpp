#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "support-system.h"

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);
    SupportSystem::init();

    QQmlApplicationEngine engine;
    engine.loadFromModule("ApplicantStatsProjectModule", "Main");

    return QGuiApplication::exec();
}
