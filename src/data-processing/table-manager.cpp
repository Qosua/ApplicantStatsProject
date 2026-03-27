#include "table-manager.h"

TableManager::TableManager() {}

TableManager::~TableManager() { delete watcher; }

void TableManager::init() {

    watcher = new QFileSystemWatcher;

    QObject::connect(watcher, &QFileSystemWatcher::directoryChanged, this,
                     &TableManager::directoryChanged);

    QObject::connect(this, &TableManager::processTable, this, &TableManager::processTableHandle);

    updateWatcher();
}

void TableManager::processTableHandle(const QString& tableName) {

    QDir cacheDir(SupportSystem::appCachePath);
    QList<QString> cacheEntry = cacheDir.entryList();

    for (const QString& entry : std::as_const(cacheEntry)) {

	QList<QString> parts = entry.split('_');

	if (parts[0] != "cache" or parts[2] != tableNameInCache(tableName))
	    continue;

	if (parts[1] == tableLastChangeDate(tableName)) {

	    QList<FacultyDirection>* data = loadCache(tableName);
	    emit sendProceededData(data);
	    return;
	}
    }

    QList<FacultyDirection>* data = makeCache(tableName);
    emit sendProceededData(data);
}

QList<FacultyDirection>* TableManager::loadCache(const QString& tableName) {
    emit waitForFinish();

    auto* data = new QList<FacultyDirection>();

    QFile file(SupportSystem::appCachePath + +"/cache_" + tableLastChangeDate(tableName) + "_"
               + tableNameInCache(tableName));

    if (!file.open(QIODevice::ReadOnly)) {
	qCritical() << file.errorString();
	return nullptr;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_6_8);

    stream >> *data;

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

    QList<Applicant>* applicantsList
        = parserBachelor.getApplicants(ApplicantsFilterFlags::AdmissionsTrue, StudyType::NonBudget);

    magicHatBachelor.setKCP(":/config/KCP.xlsx", "Бакалавры");
    magicHatBachelor.setApplicantsList(applicantsList);

    magicHatBachelor.startPriorityRoundSimulation();
    magicHatBachelor.rebalanceBudgetaryPlaces();
    magicHatBachelor.startGeneralRoundSimulation();

    QList<FacultyDirection>* data = magicHatBachelor.faculties();

    saveCache(data, tableName);

    emit finished();
    return data;
}

void TableManager::saveCache(QList<FacultyDirection>* data, const QString& tableName) {

    QFile file(SupportSystem::appCachePath + "/cache_" + tableLastChangeDate(tableName) + "_"
               + tableNameInCache(tableName));

    if (!file.open(QIODevice::WriteOnly)) {
	qCritical() << file.errorString();
	return;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_6_8);

    stream << *data;

    file.close();
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
	if (!watchedFiles.contains(fullPath) and !fullPath.contains('~')
	    and !fullPath.endsWith(".tmp"))
	    watcher->addPath(fullPath);
    }

    watcher->addPath(SupportSystem::appDataPath + "/");

    emit sendTableList(currentFiles);
}

QString TableManager::tableNameInCache(const QString& tableName) {

    QString tempName = tableName;
    tempName.replace(' ', '%');
    tempName.replace('_', '%');
    tempName += ".bin";
    return tempName;
}

QString TableManager::tableLastChangeDate(const QString& tableName) {

    QFileInfo fileInfo(SupportSystem::appDataPath + "/" + tableName);
    const QString stringDateTime = fileInfo.lastModified().toString("yyyy-MM-dd-hh-mm-ss");
    return stringDateTime;
}
