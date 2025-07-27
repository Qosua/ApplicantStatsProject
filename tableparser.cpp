#include "tableparser.h"

TableParser::TableParser(const QString& tablePath, const QString& columnsNamesFilePath) {
    
    if(!QFile::exists(tablePath)) {
        qDebug() << "Не удалось найти файл таблицы" << tablePath;
        return;
    }
    
    if(!QFile::exists(columnsNamesFilePath)) {
        qDebug() << "Не удалось найти файл имён столбцов" << columnsNamesFilePath;
        return;
    }
    
    m_tablePath = tablePath;
    m_columnsNamesFilePath = columnsNamesFilePath;
    
}

TableParser::~TableParser() {
    delete m_doc;
    m_doc = nullptr;
    
    delete m_applicants;
    m_applicants = nullptr;
}

void TableParser::parseTable() {
    
    if(m_doc) {
        delete m_doc;
        m_doc = nullptr;
    }
    if(m_applicants) {
        delete m_applicants;
        m_applicants = nullptr;
    }
    
    m_doc = new QXlsx::Document(m_tablePath);
    m_applicants = new QList<Applicant>;
    
    setColumnsNames();
    
    QHash<int, Applicant> tempHash;
    int applicantId = 0;
    
    //The first line is names row so we start from the second
    for(int i = 2; m_doc->read(i, 1).isValid(); ++i){
        
        applicantId = m_doc->read(i, m_columnsNames["Уникальный код"]).toInt();
        
        //Adding new applicant if not exits
        if(!tempHash.contains(applicantId)) {
            Applicant applicant;
            applicant.setId(applicantId);
            applicant.setAdmissionFlag((m_doc->read(i, m_columnsNames["Согласие на зачисление"]).toString() == "Да" ? true : false));
            
            tempHash[applicantId] = applicant;
        }

        PriorityInfo info;
        info.setEgeScore(m_doc->read(i, m_columnsNames["Сумма баллов"]).toInt());
        info.setEgeAdditionalScore(m_doc->read(i, m_columnsNames["Сумма баллов за инд.дост.(конкурсные)"]).toInt());
        info.setPriorityName(m_doc->read(i, m_columnsNames["Конкурсная группа"]).toString());
        info.setPriorityNumber(m_doc->read(i, m_columnsNames["Приоритет"]).toInt());
        tempHash[applicantId].addPriority(info);
    }
    
    *m_applicants = tempHash.values();
    
    qDebug() << "Парсинг завершён успешно";
    
    //Just for debug
    printStatsToConsole();
    
}

QList<Applicant> TableParser::getApplicants(ApplicantsFilterFlags flag) {
    
    QList<Applicant> newList;
    
    if(flag == ApplicantsFilterFlags::All) {
        newList = *m_applicants;
        return newList;
    }
    if(flag == ApplicantsFilterFlags::AdmissionsTrue) {
        for(const auto& elem : *m_applicants) {
            if(elem.admissionFlag())
                newList.append(elem);
        }
        return newList;
    }
    if(flag == ApplicantsFilterFlags::AdmissionsFalse) {
        for(const auto& elem : *m_applicants) {
            if(!elem.admissionFlag())
                newList.append(elem);
        }
        return newList;
    }
    
    return QList<Applicant>();
    
}

bool TableParser::setColumnsNames() {
    
    QFile file(m_columnsNamesFilePath);
    
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл " << m_columnsNamesFilePath << "\n Ошибка: " << file.errorString();
        return false;
    }
    
    QTextStream stream(&file);
    QString name;
    
    while(!stream.atEnd()) {
        
        name = stream.readLine();
        
        for(int i = 1; m_doc->read(1, i).isValid(); ++i){
            
            if(m_doc->read(1, i).toString() == name){
                
                m_columnsNames[name] = i;
                break;
            }
        }
    }
    
    return true;
    
}

void TableParser::printStatsToConsole() {
    
    qDebug() << ">>=====================================================================<<";
        
    int counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains("Внебюджет")) {
                counter += 1;
                break;
            }
    qDebug() << "количество абитуриентов с хотя бы одним внебюджетным заявлением -" << counter;
    
    
    counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains(", Бюджет")) {
                counter += 1;
                break;
            }
    qDebug() << "количество абитуриентов с хотя бы одним бюджетным заявлением -" << counter;
    
    
    counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains("Целевое")) {
                counter += 1;
                break;
            }
    qDebug() << "количество абитуриентов с хотя бы одним целевым заявлением -" << counter;
    
    
    counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains("Отдельная квота")) {
                counter += 1;
                break;
            }
    qDebug() << "количество абитуриентов с хотя бы одним квотным заявлением -" << counter;
    
    
    counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains("Особое право")) {
                counter += 1;
                break;
            }
    qDebug() << "количество абитуриентов с хотя бы одним особым правом -" << counter;
    qDebug() << ">-----------------------------------------------------------------------<";
    
    ////////////////////////////////////////////////////////////////////////////////////////
    counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains("Внебюджет")) {
                counter += 1;
            }
    qDebug() << "количество внебюджетных заявлений -" << counter;
    
    
    counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains(", Бюджет")) {
                counter += 1;
            }
    qDebug() << "количество бюджетных заявлений -" << counter;
    
    
    counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains("Целевое")) {
                counter += 1;
            }
    qDebug() << "количество целевых заявлений -" << counter;
    
    
    counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains("Отдельная квота")) {
                counter += 1;
            }
    qDebug() << "количество квотных заявлений -" << counter;
    
    
    counter = 0;
    for(const auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.priorityName().contains("Особое право")) {
                counter += 1;
            }
    qDebug() << "количество заявлений с особым правом -" << counter;
    qDebug() << ">>=====================================================================<<";
    
    
}



















