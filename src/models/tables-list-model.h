#ifndef APPLICANTSTATSPROJECT_TABLESLISTMODEL_H
#define APPLICANTSTATSPROJECT_TABLESLISTMODEL_H

#include <QAbstractListModel>
#include <QDir>
#include <QFileSystemWatcher>
#include <QList>
#include <QString>

#include "../support-system.h"

class TablesListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum TablesListRoles {
	tableNameRole = Qt::UserRole + 1,
	tableFullPathRole,
	tableIconPathRole,
	tableLastChangeDateRole,
    };
    struct TableData {
	TableData(const QString &tableName, const QString &filePath, const QString &iconPath,
	          const QString &lastChangeDate)
	    : tableName(tableName),
	      tableFullPath(filePath),
	      tableIconPath(iconPath),
	      tableLastChangeDate(lastChangeDate) {}

	QString tableName;
	QString tableFullPath;
	QString tableIconPath;
	QString tableLastChangeDate;
    };

    TablesListModel(QObject *parent = nullptr);
    ~TablesListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void updateWatcher(const QString &changedPath);
    static QString tableLastChangeDate(const QString &tableName);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<TableData> tables;
    QFileSystemWatcher *watcher;
};

#endif  // APPLICANTSTATSPROJECT_TABLESLISTMODEL_H
