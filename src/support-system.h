#ifndef SUPPORTSYSTEM_H
#define SUPPORTSYSTEM_H

#include <QDir>
#include <QStandardPaths>
#include <QString>

class SupportSystem {

public:
    SupportSystem();

    static void init();

    inline const static QString appRootDataPath
        = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
          + "/Applicants-Stats-Project";

    inline const static QString appDataPath
        = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
          + "/Applicants-Stats-Project/data";

    inline const static QString appConfigPath
        = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
          + "/Applicants-Stats-Project/config";

    inline const static QString appCachePath
        = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
          + "/Applicants-Stats-Project/cache";
};

#endif  // SUPPORTSYSTEM_H
