#ifndef APPLICANTSTATSPROJECT_QMLHELPER_H
#define APPLICANTSTATSPROJECT_QMLHELPER_H

#include <QDesktopServices>
#include <QObject>
#include <QUrl>

#include "support-system.h"

class QmlHelper : public QObject {
    Q_OBJECT
public:
    explicit QmlHelper(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void openFolder(const QString &path) {
	QDesktopServices::openUrl(QUrl::fromLocalFile(path));
    }

    Q_INVOKABLE void openAppDataFolder() {
	QDesktopServices::openUrl(QUrl(SupportSystem::appDataPath));
    }

signals:
    void sendSignalToProceedTable(const QString &tableName);
};

#endif  // APPLICANTSTATSPROJECT_QMLHELPER_H
