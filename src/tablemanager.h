#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QFileSystemWatcher>
#include <QTimer>

#include "src/supportsystem.h"
#include "tableparserbachelor.h"
#include "magichat.h"

class TableManager : public QObject {
    
    Q_OBJECT
    
public:
    TableManager();
    
    void init();
    
    void processTable(const QString& tableName);
    
signals:
    void sendFaculties(QList<FacultyCell> faculties);
    void sendTableList(QList<QString> list);
    void waitForFinish();
    void finished(QList<FacultyCell>* faculties);
    
private:
    void readCache(const QString& tableName);
    void makeCache(const QString& tableName);
    
    void fileChanged(const QString& path);
    void directoryChanged(const QString& path);
    void updateWatcher();
    
    QFileSystemWatcher* watcher;
    
};

#endif // TABLEMANAGER_H
