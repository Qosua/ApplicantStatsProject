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
        
        if(parts[1] == stringDateTime) 
            return readCache(tableName);
    }
    
    makeCache(tableName);
    
}

void TableManager::readCache(const QString& tableName) {
    emit waitForFinish();
    
    QList<FacultyCell>* list = new QList<FacultyCell>;
    
    
    
    emit finished(list);
    list = nullptr;
}

void TableManager::makeCache(const QString& tableName) {
    emit waitForFinish();
    
    TableParserBachelor parserBachelor;
    MagicHat magicHatBachelor;
    
    parserBachelor.setTablePath(":/data/maintable.xlsx");
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
    
    emit finished(faculties);
    faculties = nullptr;
}

void TableManager::fileChanged(const QString &path) {
    
    if(!QFile::exists(path))
        return;
    
    makeCache(path.split('/').last());
    
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
