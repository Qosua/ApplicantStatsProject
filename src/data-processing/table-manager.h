#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QDir>
#include <QFileSystemWatcher>
#include <QHash>
#include <QString>

#include "../applicants-faculty-data/faculty-direction.h"
#include "../applicants-faculty-data/namespaces.h"
#include "../applicants-faculty-data/table-parser-bachelor.h"
#include "../data-processing/support-system.h"
#include "magic-hat.h"

class TableManager : public QObject {
    Q_OBJECT
public:
    TableManager();
    ~TableManager();

    void init();

signals:
    void sendTableList(QList<QString> list);
    void processTable(const QString& tableName);
    void sendProceededData(QList<FacultyDirection>* data);
    void waitForFinish();
    void finished();

private:
    void processTableHandle(const QString& tableName);
    QList<FacultyDirection>* readCache(const QString& tableName);
    QList<FacultyDirection>* makeCache(const QString& tableName);
    //QList<FacultyDirection>* makeDataForCaching(QList<FacultyDirection>* directions);
    //void makeCacheTable(QList<Applicant>* data, const QString& tableName);

    void fileChanged(const QString& path);
    void directoryChanged(const QString& path);
    void updateWatcher();

    QFileSystemWatcher* watcher;
};

#endif  // TABLEMANAGER_H
