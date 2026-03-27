#include <QGuiApplication>

#include "support-system.h"

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);
    SupportSystem::init();

    

    return QGuiApplication::exec();
}
