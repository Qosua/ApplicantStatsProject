#ifndef SUPPORTSYSTEM_H
#define SUPPORTSYSTEM_H

#include <QDir>
#include <QFile>
#include <QList>
#include <QString>
#include <QStandardPaths>

#include "../applicants-faculty-data/applicant.h"
#include "../applicants-faculty-data/faculty-direction.h"

class SupportSystem {

public:
    SupportSystem();

    void toCache(QList<FacultyDirection>& faculties, QString tablePath);
    QList<FacultyDirection> fromCache(QString tablePath);
    bool isCacheExist(QString tablePath);

    void init();

    inline const static QString appRootDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Applicants-Stats-Project";
    inline const static QString appDataPath =     QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Applicants-Stats-Project/data";
    inline const static QString appConfigPath =   QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Applicants-Stats-Project/config";
    inline const static QString appCachePath =    QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/Applicants-Stats-Project/cache";
};

#endif  // SUPPORTSYSTEM_H
