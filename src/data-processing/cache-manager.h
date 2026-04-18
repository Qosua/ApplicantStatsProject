#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QDir>
#include <QFileSystemWatcher>
#include <QHash>
#include <QString>
#include <memory>

#include "../applicants-faculty-data/faculty-direction.h"
#include "../applicants-faculty-data/namespaces.h"
#include "../applicants-faculty-data/table-parser-bachelor.h"
#include "../support-system.h"
#include "magic-hat.h"

class CacheManager : public QObject {
    Q_OBJECT
public:
    void init();

    static QString tableNameInCache(const QString& tableName);
    static QString tableLastChangeDate(const QString& tableName);

signals:
    void processTable(const QString& tableName);
    void sendProceededData(std::shared_ptr<QList<FacultyDirection>> data);
    void waitForFinish();
    void finished();

private:
    void processTableHandle(const QString& tableName);
    std::shared_ptr<QList<FacultyDirection>> loadCache(const QString& tableName);
    std::shared_ptr<QList<FacultyDirection>> makeCache(const QString& tableName);
    static void saveCache(const std::shared_ptr<QList<FacultyDirection>>& data,
                          const QString& tableName);
};

#endif  // TABLEMANAGER_H
