#include "tablemanager.h"

TableManager::TableManager() {}

void TableManager::init() {
    
    watcher = new QFileSystemWatcher;
    
    QObject::connect(watcher, &QFileSystemWatcher::directoryChanged,
                     this, &TableManager::directoryChanged);
    
    QObject::connect(watcher, &QFileSystemWatcher::fileChanged,
                     this, &TableManager::fileChanged);
    
    updateWatcher();
    
}

void TableManager::processTable(const QString& tableName) {
    
    QFileInfo fileInfo(APP_DATA_PATH + "/" + tableName);
    QDir cacheDir(APP_CACHE_PATH);
    
    QStringList cacheEntr = cacheDir.entryList();
    
    for(const QString& entry : std::as_const(cacheEntr)) {
        
        QStringList parts = entry.split('_');
        
        if(parts[0] != "cache" or parts[2] != tableName)
            continue;
        
        QString stringDateTime = fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
        
        if(parts[1] == stringDateTime) {
            readCache(tableName);
            return;
        }
    }
    
    makeCache(tableName);
    
}

void TableManager::readCache(const QString& tableName) {
    emit waitForFinish();
    
    UniversityData* data = new UniversityData;
    
    
    
    emit finished(data);
}

void TableManager::makeCache(const QString& tableName) {
    emit waitForFinish();
    
    TableParserBachelor parserBachelor;
    MagicHat magicHatBachelor;
    
    parserBachelor.setTablePath(APP_DATA_PATH + "/" + tableName);
    parserBachelor.setColumnsNamesPath(":/settings/columnsNames.xlsx");
    parserBachelor.parseTable();
    
    QList<Applicant>* applicantsList = parserBachelor.getApplicants(ApplicantsFilterFlags::AdmissionsTrue,
                                                                    StudyType::NonBudget);
    
    magicHatBachelor.setKCP(":/settings/KCP.xlsx", "Бакалавры");
    magicHatBachelor.setApplicantsList(applicantsList);
    
    magicHatBachelor.startPriorityRoundSimulation();
    magicHatBachelor.rebalanceBudgetaryPlaces();
    magicHatBachelor.startGeneralRoundSimulation();
    
    //magicHatBachelor.printStatsToConsole();
    //magicHatBachelor.printUncountedApplicants();
    
    QList<FacultyCell>* faculties = magicHatBachelor.faculties();
    //QList<Applicant>   uncountedApplicants = magicHatBachelor.uncountedApplicants();

    UniversityData* data = makeDataForCaching(faculties);
    makeCacheTable(data);
    
    emit finished(data);
}

UniversityData* TableManager::makeDataForCaching(QList<FacultyCell> *faculties) {

    UniversityData* data = new UniversityData;

    for(const auto& faculty : std::as_const(*faculties)) {

        auto& currentElem = (*data)[faculty.division()]
                                   [faculty.name()]
                                   [faculty.studyForm()];

        if(faculty.studyType() != StudyType::Budget) {

            currentElem.size += faculty.pool().size();
            currentElem.studentsCount += faculty.pool().size();
        }
        else {

            currentElem.name = faculty.name();
            currentElem.size += faculty.pool().size();
            currentElem.studentsCount += faculty.capacity();
        }

        currentElem.pool = faculty.pool();

        if(faculty.pool().isEmpty() or faculty.studyType() != StudyType::Budget)
            continue;

        currentElem.maxScore = std::max(
            faculty.pool().last().first.egeScore(),
            currentElem.maxScore
            );

        currentElem.minScore = std::min(
            faculty.pool().first().first.egeScore(),
            currentElem.minScore
            );
    }

    return data;
}

void TableManager::makeCacheTable(UniversityData *data) {

}

void TableManager::fileChanged(const QString &path) {
    
    if(!QFile::exists(path))
        return;
    
    //makeCache(path.split('/').last());
    
}

void TableManager::directoryChanged(const QString &path) {
    
    updateWatcher();
    
}

void TableManager::updateWatcher() {
    
    QDir dataDir(APP_DATA_PATH);
    QStringList currentFiles = dataDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    QStringList watchedFiles = watcher->files();
    
    for (const QString& path : std::as_const(watchedFiles)) {
        
        if (!QFile::exists(path)) 
            watcher->removePath(path);
    }
    for (const QString& file : std::as_const(currentFiles)) {
        
        QString fullPath = dataDir.absoluteFilePath(file);
        if (!watchedFiles.contains(fullPath) and !fullPath.contains('~') and !fullPath.endsWith(".tmp")) 
            watcher->addPath(fullPath);
    }
    
    watcher->addPath(APP_DATA_PATH + "/");
    
    emit sendTableList(currentFiles);
    
}
