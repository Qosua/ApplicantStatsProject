#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QHash>

#include "src/supportsystem.h"
#include "tableparserbachelor.h"
#include "magichat.h"
#include "facultycell.h"

struct DirectionInfo {

    int size = 0;
    int studentsCount = 0;
    int minScore = 500;
    int maxScore = 0;
    QString name;
    QList<QPair<PriorityInfo, Applicant>> pool;
};

typedef QHash<QString, //Faculty name
              QHash<QString, // Direction name
                    QHash<StudyForm, // Personly, Personaly-NotPersonaly,...
                          DirectionInfo>>> UniversityData;

class TableManager : public QObject {
    
    Q_OBJECT
    
public:
    TableManager();
    
    void init();
    void processTable(const QString& tableName);
    
signals:
    void sendTableList(QList<QString> list);
    void waitForFinish();
    void finished(UniversityData* data);
    
private:
    void readCache(const QString& tableName);
    void makeCache(const QString& tableName);
    UniversityData* makeDataForCaching(QList<FacultyCell>* faculties);
    void makeCacheTable(UniversityData* data, const QString& tableName);
    
    void fileChanged(const QString& path);
    void directoryChanged(const QString& path);
    void updateWatcher();
    
    QFileSystemWatcher* watcher;
    
};

#endif // TABLEMANAGER_H
