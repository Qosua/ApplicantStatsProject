#include "cache-manager.h"

CacheManager::CacheManager() {}

CacheManager::~CacheManager() {}

void CacheManager::init() {

    QObject::connect(this, &CacheManager::processTable, this, &CacheManager::processTableHandle);
}

void CacheManager::processTableHandle(const QString& tableName) {

    qDebug() << "processTable called with:" << tableName;

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

QList<FacultyDirection>* CacheManager::loadCache(const QString& tableName) {
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

QList<FacultyDirection>* CacheManager::makeCache(const QString& tableName) {
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

void CacheManager::saveCache(QList<FacultyDirection>* data, const QString& tableName) {

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

QString CacheManager::tableNameInCache(const QString& tableName) {

    QString tempName = tableName;
    tempName.replace(' ', '%');
    tempName.replace('_', '%');
    tempName += ".bin";
    return tempName;
}

QString CacheManager::tableLastChangeDate(const QString& tableName) {

    QFileInfo fileInfo(SupportSystem::appDataPath + "/" + tableName);
    const QString stringDateTime = fileInfo.lastModified().toString("yyyy-MM-dd-hh-mm-ss");
    return stringDateTime;
}
