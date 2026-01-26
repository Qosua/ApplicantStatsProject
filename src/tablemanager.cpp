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
        
        QString stringDateTime = fileInfo.lastModified().toString("yyyy-MM-dd-hh-mm-ss");
        
        if(parts[1] == stringDateTime) {
            readCache(tableName);
            return;
        }
    }
    
    //TODO: Take in account file date
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
    makeCacheTable(data, tableName);
    
    emit finished(data);
}

UniversityData* TableManager::makeDataForCaching(QList<FacultyCell> *faculties) {

    UniversityData* data = new UniversityData;

    for(auto& direction : *faculties) {

        auto& currentElem = (*data)[direction.division()]
                                   [direction.name()]
                                   [direction.studyForm()];

        if(direction.studyType() != StudyType::Budget) {

            currentElem.size += direction.pool().size();
            currentElem.studentsCount += direction.pool().size();
        }
        else {

            currentElem.name = direction.name();
            currentElem.size += direction.pool().size();
            currentElem.studentsCount += direction.capacity();
        }

        currentElem.pool += direction.pool();

        if(direction.pool().isEmpty() or direction.studyType() != StudyType::Budget)
            continue;

        currentElem.maxScore = std::max(
            direction.pool().last().first.egeScore(),
            currentElem.maxScore
        );

        currentElem.minScore = std::min(
            direction.pool().first().first.egeScore(),
            currentElem.minScore
        );
    }

    return data;
}

void TableManager::makeCacheTable(UniversityData *data, const QString& tableName) {

    QXlsx::Document xlsx;

    for(auto faculty = data->constBegin(); faculty != data->constEnd(); ++faculty) {

        int column = 1;
        int row = 1;

        xlsx.addSheet(faculty.key());
        xlsx.selectSheet(faculty.key());

        auto directionBegin = faculty.value().constBegin();
        auto directionEnd = faculty.value().constEnd();

        for(auto direction = directionBegin; direction != directionEnd; ++direction) {

            auto directionInfoBegin = direction.value().constBegin();
            auto directionInfoEnd = direction.value().constEnd();

            for(auto directionInfo = directionInfoBegin; directionInfo != directionInfoEnd; ++directionInfo) {

                auto poolBegin = directionInfo.value().pool.constBegin();
                auto poolEnd = directionInfo.value().pool.constEnd();

                for(auto applicant = poolBegin; applicant != poolEnd; ++applicant) {

                    QString studyType;
                    QString studyForm;

                    switch(applicant->first.studyType()){
                    case StudyType::Budget:         studyType = "Общий конкурс"; break;
                    case StudyType::Kvot:           studyType = "Квота"; break;
                    case StudyType::CompanySponsor: studyType = "Целевое"; break;
                    case StudyType::SpecialRight:   studyType = "Особое право"; break;
                    }

                    switch(applicant->first.studyForm()){
                    case StudyForm::Personal:            studyForm = "Очное"; break;
                    case StudyForm::PersonalNotPersonal: studyForm = "Очно-заочное"; break;
                    case StudyForm::NotPersonal:         studyForm = "Заочное"; break;
                    }

                    xlsx.write(row, column++, applicant->second.id());
                    xlsx.write(row, column++, applicant->second.FIO());
                    xlsx.write(row, column++, applicant->first.name());
                    xlsx.write(row, column++, applicant->first.code());
                    xlsx.write(row, column++, applicant->first.priorityNumber());
                    xlsx.write(row, column++, studyType);
                    xlsx.write(row, column++, studyForm);
                    xlsx.write(row, column++, (applicant->first.isBVI() ? "БВИ" : "не БВИ"));
                    xlsx.write(row, column++, applicant->first.egeScore());
                    xlsx.write(row, column++, applicant->first.subjectScores()[0]);
                    xlsx.write(row, column++, applicant->first.subjectScores()[1]);
                    xlsx.write(row, column++, applicant->first.subjectScores()[2]);

                    column = 1;
                    row += 1;
                }
            }
        }
    }

    QString savePath = APP_CACHE_PATH +
                       "/cache_" +
                       QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") +
                       "_" + tableName;

    if(xlsx.saveAs(savePath)) {
        qDebug() << "CACHING DONE SUCCESFUL";
    }
    else {
        qDebug() << "CACHING ERROR";
    }

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
