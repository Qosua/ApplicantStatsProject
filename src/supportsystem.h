#ifndef SUPPORTSYSTEM_H
#define SUPPORTSYSTEM_H

#include <QFile>
#include <QDir>
#include <QList>
#include <QString>

#include "src/applicant.h"
#include "src/facultycell.h"

const QString APP_PATH = "C:/ProgramData/ApplicantStatsProject";
const QString APP_DATA_PATH = "C:/ProgramData/ApplicantStatsProject/data";
const QString APP_CACHE_PATH = "C:/ProgramData/ApplicantStatsProject/cache";

class SupportSystem {
    
public:
    SupportSystem();
    
    void toCache(QList<FacultyCell>& faculties, QString tablePath);
    QList<FacultyCell> fromCache(QString tablePath);
    bool isCacheExist(QString tablePath);
    
    void init();
    
private:
    
    
};

#endif // SUPPORTSYSTEM_H
