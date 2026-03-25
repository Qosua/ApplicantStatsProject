#include "table-manager.h"

TableManager::TableManager() {}

TableManager::~TableManager() {

        delete watcher;
}

void TableManager::init() {

    watcher = new QFileSystemWatcher;

    QObject::connect(watcher, &QFileSystemWatcher::directoryChanged,
             this, &TableManager::directoryChanged);

    QObject::connect(watcher, &QFileSystemWatcher::fileChanged,
             this, &TableManager::fileChanged);

    QObject::connect(this, &TableManager::processTable,
                    this, &TableManager::processTableHandle);

    updateWatcher();
}

void TableManager::processTableHandle(const QString& tableName) {

    QFileInfo fileInfo(SupportSystem::appCachePath + "/" + tableName);
    QDir cacheDir(SupportSystem::appCachePath);

    QList<QString> cacheEntry = cacheDir.entryList();
    const QString stringDateTime = fileInfo.lastModified().toString("yyyy-MM-dd-hh-mm-ss");

    for (const QString& entry : std::as_const(cacheEntry)) {

	QStringList parts = entry.split('_');

	if (parts[0] != "cache" or parts[2] != tableName)
	    continue;

	if (parts[1] == stringDateTime) {

	    QList<FacultyDirection>* data = readCache(tableName);
	    emit sendProceededData(data);
	    return;
	}
    }

    QList<FacultyDirection>* data = makeCache(tableName);
    emit sendProceededData(data);
}

QList<FacultyDirection>* TableManager::readCache(const QString& tableName) {
    emit waitForFinish();

    QList<FacultyDirection>* data;



    emit finished();
    return data;
}

QList<FacultyDirection>* TableManager::makeCache(const QString& tableName) {
    emit waitForFinish();

    TableParserBachelor parserBachelor;
    MagicHat magicHatBachelor;

    parserBachelor.setTablePath(SupportSystem::appDataPath + "/" + tableName);
    parserBachelor.setColumnsNamesPath(":/config/columnsNames.xlsx");
    parserBachelor.parseTable();

    QList<Applicant>* applicantsList =
        parserBachelor.getApplicants(ApplicantsFilterFlags::AdmissionsTrue, StudyType::NonBudget);

    magicHatBachelor.setKCP(":/config/KCP.xlsx", "Бакалавры");
    magicHatBachelor.setApplicantsList(applicantsList);

    magicHatBachelor.startPriorityRoundSimulation();
    magicHatBachelor.rebalanceBudgetaryPlaces();
    magicHatBachelor.startGeneralRoundSimulation();

    QList<FacultyDirection>* data = magicHatBachelor.faculties();

    emit finished();
    return data;
}

// QList<Applicant>* TableManager::makeDataForCaching(QList<FacultyDirection>* directions) {
//
//     UniversityData* data = new UniversityData;
//
//     for (const auto& direction : std::as_const(*directions)) {
//
// 	auto& currentElem = (*data)[direction.division()][direction.name()][direction.studyForm()];
//
// 	if (direction.studyType() != StudyType::Budget) {
//
// 	    currentElem.size += direction.pool().size();
// 	    currentElem.studentsCount += direction.pool().size();
// 	} else {
//
// 	    currentElem.size += direction.pool().size();
// 	    currentElem.studentsCount += direction.capacity();
// 	}
//
// 	currentElem.pool += direction.pool();
//
// 	if (direction.pool().isEmpty() or direction.studyType() != StudyType::Budget)
// 	    continue;
//
// 	currentElem.maxScore =
// 	    std::max(direction.pool().last().first.egeScore(), currentElem.maxScore);
// 	currentElem.minScore =
// 	    std::min(direction.pool().first().first.egeScore(), currentElem.minScore);
//     }
//
//     return data;
// }

// void TableManager::makeCacheTable(UniversityData* data, const QString& tableName) {
//
//     QFileInfo fileInfo(SupportSystem::appDataPath + "/" + tableName);
//     QString stringDateTime = fileInfo.lastModified().toString("yyyy-MM-dd-hh-mm-ss");
//
//     QString savePath = SupportSystem::appCachePath + "/cache_" + stringDateTime + "_" + tableName;
//     QFile someFile(savePath);
//     someFile.open(QIODevice::WriteOnly);
//
//     QDataStream stream(&someFile);
//
//     // stream << *data;
//
//     someFile.close();
// }

void TableManager::fileChanged(const QString& path) {

    if (!QFile::exists(path))
	return;

    // makeCache(path.split('/').last());
}

void TableManager::directoryChanged(const QString& path) { updateWatcher(); }

void TableManager::updateWatcher() {

    QDir dataDir(SupportSystem::appDataPath);
    QList<QString> currentFiles = dataDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    QList<QString> watchedFiles = watcher->files();

    for (const QString& path : std::as_const(watchedFiles)) {

	if (!QFile::exists(path))
	    watcher->removePath(path);
    }
    for (const QString& file : std::as_const(currentFiles)) {

	QString fullPath = dataDir.absoluteFilePath(file);
	if (!watchedFiles.contains(fullPath) and !fullPath.contains('~') and
	    !fullPath.endsWith(".tmp"))
	    watcher->addPath(fullPath);
    }

    watcher->addPath(SupportSystem::appDataPath + "/");

    emit sendTableList(currentFiles);
}
