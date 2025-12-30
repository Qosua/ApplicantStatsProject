#include "tablemanager.h"

TableManager::TableManager() {}

void TableManager::init() {
    
    QDir dataDir(APP_DATA_PATH);
    QList<QString> dataEntr = dataDir.entryList();
    
    for(const QString& entry : dataEntr) 
        watcher.addPath(APP_DATA_PATH + "/" + entry);
    
    watcher.addPath(APP_DATA_PATH + "/");
    
    QObject::connect(&watcher, &QFileSystemWatcher::directoryChanged,
                     this, &TableManager::directoryChanged);
    
    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged,
                     this, &TableManager::fileChanged);
    
}

void TableManager::processTable(const QString& tableName) {
    
    QFileInfo fileInfo(APP_DATA_PATH + "/" + tableName);
    QDir cacheDir(APP_CACHE_PATH);
    
    QList<QString> cacheEntr = cacheDir.entryList();
    
    for(const QString& entry : cacheEntr) {
        
        QList<QString> parts = entry.split('_');
        
        if(parts[0] != "cache" or parts[2] != tableName)
            continue;
        
        QString stringDateTime = fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
        
        if(parts[1] == stringDateTime) 
            return readCache(tableName);
    }
    
    makeCache(tableName);
    
}

void TableManager::readCache(const QString& tableName) {
    
    
    
}

void TableManager::makeCache(const QString& tableName) {
    
    
    
}

void TableManager::fileChanged(const QString &path) {
    
    qDebug() << path << "-file";
    
    if(!QFile::exists(path)) {
        watcher.removePath(path);
        return;   
    }
    
    makeCache(path.split('/').last());
    
}

void TableManager::directoryChanged(const QString &path) {
    
    
    
}
