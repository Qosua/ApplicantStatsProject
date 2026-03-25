#include "support-system.h"

SupportSystem::SupportSystem() {}

void SupportSystem::init() {

    bool result = true;
    
    if(!QDir().exists(SupportSystem::appRootDataPath))
        result *= QDir().mkdir(SupportSystem::appRootDataPath);
    
    if(!QDir().exists(SupportSystem::appCachePath))
        result *= QDir().mkdir(SupportSystem::appCachePath);
    
    if(!QDir().exists(SupportSystem::appDataPath))
        result *= QDir().mkdir(appDataPath);

    if(!QDir().exists(SupportSystem::appConfigPath))
        result *= QDir().mkdir(appConfigPath);

    if(!result)
        qDebug() << "SupportSystem INIT ERROR";
}
