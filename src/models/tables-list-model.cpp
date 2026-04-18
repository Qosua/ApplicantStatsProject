#include "tables-list-model.h"

TablesListModel::TablesListModel(QObject *parent) : QAbstractListModel(parent) {

    watcher = new QFileSystemWatcher(this);

    QObject::connect(watcher, &QFileSystemWatcher::directoryChanged, this,
                     &TablesListModel::updateWatcher);

    updateWatcher("");
}

TablesListModel::~TablesListModel() {}

int TablesListModel::rowCount(const QModelIndex &parent) const {

    Q_UNUSED(parent)
    return tables.size();
}

QVariant TablesListModel::data(const QModelIndex &index, int role) const {

    if (index.row() < 0 or index.row() >= tables.count())
	return QVariant();

    const TableData &table = tables[index.row()];

    switch (role) {
	case TablesListRoles::tableNameRole:
	    return table.tableName;
	    break;
	case TablesListRoles::tableFullPathRole:
	    return table.tableFullPath;
	    break;
	case TablesListRoles::tableIconPathRole:
	    return table.tableIconPath;
	    break;
	case TablesListRoles::tableLastChangeDateRole:
	    return table.tableLastChangeDate;
	    break;
	default:
	    return QVariant();
	    break;
    }
}

QHash<int, QByteArray> TablesListModel::roleNames() const {

    QHash<int, QByteArray> roles;
    roles[TablesListRoles::tableNameRole] = "tableName";
    roles[TablesListRoles::tableFullPathRole] = "tableFullPath";
    roles[TablesListRoles::tableIconPathRole] = "tableIconPath";
    roles[TablesListRoles::tableLastChangeDateRole] = "tableLastChangeDate";
    return roles;
}

void TablesListModel::updateWatcher(const QString &changedPath) {

    Q_UNUSED(changedPath);

    const QDir dataDir(SupportSystem::appDataPath);
    const QList<QString> currentFiles = dataDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    const QList<QString> watchedFiles = watcher->files();

    for (const QString &path : watchedFiles)
	if (!QFile::exists(path))
	    watcher->removePath(path);

    for (const QString &file : currentFiles) {

	QString fullPath = dataDir.absoluteFilePath(file);
	if (!watchedFiles.contains(fullPath) and !fullPath.contains('~')
	    and !fullPath.endsWith(".tmp"))
	    watcher->addPath(fullPath);
    }

    watcher->addPath(SupportSystem::appDataPath + "/");

    if (!tables.isEmpty()) {
	beginRemoveRows(QModelIndex(), 0, tables.size() - 1);
	tables.clear();
	endRemoveRows();
    }

    beginInsertRows(QModelIndex(), 0, currentFiles.size() - 1);
    for (const QString &tableName : currentFiles)
	tables.append(TableData(tableName, dataDir.absoluteFilePath(tableName),
	                        "qrc:/resources/icons/excel-icon.png",
	                        tableLastChangeDate(tableName)));
    endInsertRows();
}

QString TablesListModel::tableLastChangeDate(const QString &tableName) {

    const QFileInfo fileInfo(SupportSystem::appDataPath + "/" + tableName);
    const QString stringDateTime = fileInfo.lastModified().toString("yyyy.MM.dd hh:mm:ss");
    return stringDateTime;
}