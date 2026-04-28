#ifndef APPLICANTSTATSPROJECT_QMLHELPER_H
#define APPLICANTSTATSPROJECT_QMLHELPER_H

#include <QDesktopServices>
#include <QFileDialog>
#include <QFileInfo>
#include <QObject>
#include <QUrl>

#include "support-system.h"

class QmlHelper : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentTablePath READ currentTablePath WRITE setCurrentTablePath NOTIFY
                   currentTablePathChanged)
    Q_PROPERTY(QString fileSizeString READ fileSizeString WRITE setCurrentTablePath NOTIFY
                   currentTablePathChanged)
    Q_PROPERTY(QString appVersion READ appVersion WRITE setAppVersion)
public:
    explicit QmlHelper(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void openFolder(const QString &path) {
	QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }
    Q_INVOKABLE void openAppDataFolder() {
	QDesktopServices::openUrl(QUrl(SupportSystem::appDataPath));
    }
    Q_INVOKABLE void addTableFromExploler() {

	QFileDialog fileDialog;
	fileDialog.setDirectory(SupportSystem::downloadPath);

	QString src = fileDialog.getOpenFileName(nullptr, "", SupportSystem::downloadPath,
	                                         "Выберите таблицу (*.xlsx)");
	if (!src.isEmpty())
	    copyFileToAppdata(src);
    }
    Q_INVOKABLE void copyFileToAppdata(QString src) {
	QString dest = SupportSystem::appDataPath + "/" + src.split('/').last();

	if (QFile::exists(dest))
	    QFile::remove(dest);
	QFile::copy(src, dest);
    }

    QString currentTablePath() const { return m_currentTablePath; }
    QString fileSizeString() const { return QString::number(QFileInfo(m_fileSizeString).size()); }
    QString appVersion() const { return m_version; }

    void setCurrentTablePath(const QString &path) {
	if (m_currentTablePath == path)
	    return;
	m_currentTablePath = path;
	emit currentTablePathChanged();
    }
    void setFileSizeString(const QString &sizeString) {
	if (m_fileSizeString == sizeString)
	    return;
	m_fileSizeString = sizeString;
	emit fileSizeStringChanged();
    }
    void setAppVersion(const QString &version) {
	if (m_version == version)
	    return;
	m_version = version;
    }

private:
    QString m_currentTablePath;
    QString m_fileSizeString;
    QString m_version;

signals:
    void sendSignalToProceedTable(const QString &tableName);
    void sendTreeElemName(const QString &elemName, bool isDivision);
    void currentTablePathChanged();
    void fileSizeStringChanged();
};

#endif  // APPLICANTSTATSPROJECT_QMLHELPER_H
