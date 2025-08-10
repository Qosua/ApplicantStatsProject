#include "tableparserbachelor.h"

TableParserBachelor::TableParserBachelor(const QString& tablePath, const QString& columnsNamesFilePath) {
    
    if(!QFile::exists(tablePath)) {
        qDebug() << "CAN NOT FIND TABLE FILE" << tablePath << __FILE__ << ":" << __LINE__;
        return;
    }
    
    if(!QFile::exists(columnsNamesFilePath)) {
        qDebug() << "CAN NOT FIND COLUMNS NAMES FILE" << columnsNamesFilePath << __FILE__ << ":" << __LINE__;
        return;
    }
    
    m_tablePath = tablePath;
    m_columnsNamesFilePath = columnsNamesFilePath;
    
}

TableParserBachelor::~TableParserBachelor() {
    delete m_doc;
    m_doc = nullptr;
    
    delete m_applicants;
    m_applicants = nullptr;
}

void TableParserBachelor::parseTable() {
    
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

    qDebug() << m_doc->read(1, 1).toString();
    
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
            applicant.setFIO(m_doc->read(i, m_columnsNames["ФИО"]).toString());
            applicant.setEmail(m_doc->read(i, m_columnsNames["E-mail"]).toString());
            applicant.setPhoneNumber(m_doc->read(i, m_columnsNames["Телефон"]).toString());

            tempHash[applicantId] = applicant;
        }

        PriorityInfo info;
        QString priorityFullName = m_doc->read(i, m_columnsNames["Конкурсная группа"]).toString();

        info.setEgeScore(m_doc->read(i, m_columnsNames["Сумма баллов"]).toInt());
        info.setEgeAdditionalScore(m_doc->read(i, m_columnsNames["Сумма баллов за инд.дост.(конкурсные)"]).toInt());
        info.setPriorityNumber(m_doc->read(i, m_columnsNames["Приоритет"]).toInt());
        info.addSubject(m_doc->read(i, m_columnsNames["Предмет1"]).toInt());
        info.addSubject(m_doc->read(i, m_columnsNames["Предмет2"]).toInt());
        info.addSubject(m_doc->read(i, m_columnsNames["Предмет3"]).toInt());
        info.setCode(extractCode(priorityFullName));
        info.setName(extractName(priorityFullName));
        info.setStudyForm(extractStudyForm(priorityFullName));
        info.setType(extractType(priorityFullName));
        info.setId(applicantId);
        info.setAdmissionFlag((m_doc->read(i, m_columnsNames["Согласие на зачисление"]).toString() == "Да" ? true : false));
        info.setIsBVI(((m_doc->read(i, m_columnsNames["Без вступительных испытаний"]).toString() == "Да") ? true : false));
        info.setDivision(m_doc->read(i, m_columnsNames["Подразделение"]).toString());

        tempHash[applicantId].addPriority(info);

    }
    
    *m_applicants = tempHash.values();
    
    qDebug() << "Парсинг завершён успешно";
    
    //Just for debug
    printStatsToConsole();
    
}

QList<Applicant> TableParserBachelor::getApplicants(ApplicantsFilterFlags flag) {
    
    QList<Applicant> newList;
    
    if(flag == ApplicantsFilterFlags::All) {
        newList = *m_applicants;
        return newList;
    }
    if(flag == ApplicantsFilterFlags::AdmissionsTrue) {
        for(auto& elem : *m_applicants) {
            
            Applicant applicant = elem;
            applicant.priorities().clear();
            
            for(const auto& priority : elem.priorities()){
                if(priority.admissionFlag()){
                    applicant.addPriority(priority);
                }
            }
            
            if(applicant.priorities().size() != 0)
                newList.append(applicant);
            
        }
        return newList;
    }
    if(flag == ApplicantsFilterFlags::AdmissionsFalse) {
        for(auto& elem : *m_applicants) {
            
            Applicant applicant = elem;
            applicant.priorities().clear();
            
            for(const auto& priority : elem.priorities()){
                if(!priority.admissionFlag()){
                    applicant.addPriority(priority);
                }
            }
            
            if(applicant.priorities().size() != 0)
                newList.append(applicant);
            
        }
        return newList;
    }
    
    return QList<Applicant>();
    
}

bool TableParserBachelor::setColumnsNames() {
    
    QFile file(m_columnsNamesFilePath);
    
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл " << m_columnsNamesFilePath << "\n Ошибка: " << file.errorString();
        return false;
    }

    qDebug() << "\n Ошибка: " << file.errorString();
    
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

void TableParserBachelor::printStatsToConsole() const {
    
    qDebug() << ">>=====================================================================<<";
        
    int counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Внебюджет")) {
                counter += 1;
                break;
            }
    qDebug() << " applicants count with at least one nonbudget priority -" << counter;
    
    
    counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Бюджет")) {
                counter += 1;
                break;
            }
    qDebug() << " applicants count with at least one budget priority -" << counter;
    
    
    counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Целевое")) {
                counter += 1;
                break;
            }
    qDebug() << " applicants count with at least one goal priority -" << counter;
    
    
    counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Отдельная квота")) {
                counter += 1;
                break;
            }
    qDebug() << " applicants count with at least one kvot priority -" << counter;
    
    
    counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Особое право")) {
                counter += 1;
                break;
            }
    qDebug() << " applicants count with at least one special right -" << counter;
    qDebug() << ">-----------------------------------------------------------------------<";
    
    ////////////////////////////////////////////////////////////////////////////////////////
    counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Внебюджет")) {
                counter += 1;
            }
    qDebug() << " nonbudget priority count -" << counter;
    
    
    counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Бюджет")) {
                counter += 1;
            }
    qDebug() << " bidget priority count -" << counter;
    
    
    counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Целевое")) {
                counter += 1;
            }
    qDebug() << " goal priority count -" << counter;
    
    
    counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Отдельная квота")) {
                counter += 1;
            }
    qDebug() << " kvot priority count -" << counter;
    
    
    counter = 0;
    for(auto& elem : *m_applicants)
        for(const auto& priority : elem.priorities())
            if(priority.type().contains("Особое право")) {
                counter += 1;
            }
    qDebug() << " special right priority count -" << counter;
    qDebug() << ">>=====================================================================<<\n";
    
    
}

QString TableParserBachelor::extractCode(const QString& str) {
    return str.mid(0,8);
}

QString TableParserBachelor::extractName(const QString& str) {
    
    QString ans;
    
    for(int i = 9; (str.mid(i+2,4) != "Заоч" and str.mid(i+2,4) != "Очно" and str.mid(i+2,4) != "Очна");++i) {
        
        if(str[i - 1] == str[i] and str[i] == " ")
            continue;


        ans += str[i];
        
    }
    
    return ans;
    
}

QString TableParserBachelor::extractStudyForm(const QString& str) {
    
    if(str.contains("Очное") or str.contains("Очная")){
        return "Очное";
    }
    if(str.contains("Заочная") or str.contains("Заочное")){
        return "Заочная";
    }
    if(str.contains("Очно-заочная") or str.contains("Очно-заочное")){
        return "Очно-заочная";
    }
    return "ОШИБКА ФОРМЫ ОБУЧЕНИЯ";
}

QString TableParserBachelor::extractType(const QString& str) {
    if(str.contains("Бюджет")){
        return "Бюджет";
    }
    if(str.contains("Отдельная квота")){
        return "Отдельная квота";
    }
    if(str.contains("Особое право")){
        return "Особое право";
    }
    if(str.contains("Внебюджет")){
        return "Внебюджет";
    }
    if(str.contains("Целевое")){
        return "Целевое";
    }
    return "ОШИБКА ТИПА";
}



















