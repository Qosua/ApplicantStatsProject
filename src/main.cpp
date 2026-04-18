#include <Windows.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSortFilterProxyModel>
#include <QThread>

#include "data-processing/cache-manager.h"
#include "models/tables-list-model.h"
#include "qml-helper.h"
#include "support-system.h"

void connectSignals(QmlHelper& qmlHelper, CacheManager& cacheManager) {
    QObject::connect(&qmlHelper, &QmlHelper::sendSignalToProceedTable, &cacheManager,
                     &CacheManager::processTable);
}

void moveToThread(QThread& thread, CacheManager& cacheManager) {
    cacheManager.moveToThread(&thread);
    QObject::connect(&thread, &QThread::started, &cacheManager, &CacheManager::init);
    thread.start();
}

int main(int argc, char* argv[]) {

    SetConsoleOutputCP(CP_UTF8);

    QGuiApplication app(argc, argv);
    SupportSystem::init();

    QThread cacheThread;
    TablesListModel tablesListModel;
    QSortFilterProxyModel proxyModel;
    QmlHelper qmlHelper;
    CacheManager cacheManager;

    connectSignals(qmlHelper, cacheManager);
    moveToThread(cacheThread, cacheManager);

    proxyModel.setSourceModel(&tablesListModel);
    proxyModel.setSortRole(TablesListModel::TablesListRoles::tableNameRole);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("sortFilterProxyModel", &proxyModel);
    engine.rootContext()->setContextProperty("qmlHelper", &qmlHelper);
    engine.loadFromModule("ApplicantStatsProjectModule", "Main");

    int ret = QGuiApplication::exec();

    cacheThread.quit();
    cacheThread.wait();

    return ret;
}
