#include "magichat.h"

MagicHat::MagicHat() {}

QList<Applicant> MagicHat::applicantsList() const
{
    return m_applicantsList;
}

void MagicHat::setApplicantsList(const QList<Applicant> &newApplicantsList)
{
    if (m_applicantsList == newApplicantsList)
        return;
    m_applicantsList = newApplicantsList;
    m_applicantsListCopy = newApplicantsList;
    emit applicantsListChanged();
}

void MagicHat::startPriorityRoundSimulation() {
    
    QList<Applicant> priorityList;
    
    for(auto& elem : m_applicantsList){
        
        Applicant tempApplicant = elem;
        tempApplicant.priorities().clear();
        
        for(const auto& elem1 : elem.priorities()){
            
            if(elem1.type() != "Бюджет" or elem1.isBVI()) {
                
                tempApplicant.addPriority(elem1);
            }
            
            
        }
        
        priorityList.append(tempApplicant);
        
    }
    
    for(int i = -1; priorityList.size() > 0;) {
        
        if(priorityList.size() == 0)
            break;
        
        i = (i + 1) % priorityList.size();
        
        Applicant* applicant = &priorityList[i];
        PriorityInfo priority;
        
        if(applicant->priorities().size() > 0)
            priority = applicant->priorities().first();
        else {
            priorityList.removeOne(*applicant);
            continue;
        }
        
        bool deletePriority = true;
        for(int j = 0; j < m_faculties.size(); ++j){
            
            FacultyCell* facultyCell = &m_faculties[j];
            
            if(facultyCell->isAbleToAdd(priority)){
                
                deletePriority = false;
                
                applicant->priorities().removeFirst();
                facultyCell->addToPool(priority, *applicant);
                priorityList.removeOne(*applicant);
                
                QPair<PriorityInfo, Applicant*> unsuitable = facultyCell->getUnsuitableApplicant();
                
                if(unsuitable.second != nullptr){
                    
                    unsuitable.second->addPriority(unsuitable.first);
                    priorityList.append(*unsuitable.second);
                    
                    delete unsuitable.second;
                    unsuitable.second = nullptr;
                    
                }
            }
        }
        
        if(deletePriority){
            
            applicant->priorities().removeFirst();
            int a = 0;
            a += 1;
            
        }
        
    }

    for(auto& elem : m_faculties){

        for(auto& elem1 : elem.pool()) {

            for(int i = 0; i < m_applicantsList.size(); ++i) {

                if(elem1.second.id() == m_applicantsList[i].id()) {
                    m_applicantsList.remove(i);
                    --i;
                }
            }
        }
    }
    
    qDebug() << "Priority simulation completed";
    
}

void MagicHat::startGeneralRoundSimulation() {
    
    QList<Applicant> generalList;
    
    for(auto& applicant : m_applicantsList){
        
        Applicant tempApplicant = applicant;
        tempApplicant.priorities().clear();
        
        for(const auto& priority : applicant.priorities()){
            
            if(priority.type() == "Бюджет"){
                
                tempApplicant.addPriority(priority);
            }
        }
        
        generalList.append(tempApplicant);
        
    }
    
    for(int i = -1; generalList.size() > 0;) {
        
        if(generalList.size() == 0)
            break;
        
        i = (i + 1) % generalList.size();
        
        Applicant* applicant = &generalList[i];
        PriorityInfo tempPriority;
        
        if(applicant->priorities().size() > 0)
            tempPriority = applicant->priorities().first();
        else {
            m_uncountedApplicants.append(*applicant);
            generalList.removeOne(*applicant);
            continue;
        }
        
        bool deletePriority = true;
        for(int j = 0; j < m_faculties.size(); ++j){
            
            FacultyCell* facultyCell = &m_faculties[j];
            
            if(facultyCell->isAbleToAdd(tempPriority)){
                
                deletePriority = false;
                
                applicant->priorities().removeFirst();
                facultyCell->addToPool(tempPriority, *applicant);
                generalList.removeOne(*applicant);
                
                QPair<PriorityInfo, Applicant*> unsuitable = facultyCell->getUnsuitableApplicant();
                
                if(unsuitable.second != nullptr){
                    
                    unsuitable.second->addPriority(unsuitable.first);
                    generalList.append(*unsuitable.second);
                    
                    //delete unsuitable.second;
                    //unsuitable.second = nullptr;
                    
                }
            }
        }
        
        if(deletePriority){
            
            applicant->priorities().removeFirst();
            int a = 0;
            a += 1;
            
        }
        
    }
    
    qDebug() << "General simulation completed";
    
    
}

void MagicHat::rebalanceBudgetaryPlaces() {
    
    
    for(auto& elem : m_faculties) {

        if(elem.type() == "Бюджет") {

            for(auto& elem1 : m_faculties) {
                
                if(elem.name() != elem1.name() or (elem.name() == elem1.name() and elem.type() == elem1.type()))
                    continue;
                
                if(elem.name() == elem1.name() and
                    elem.studyForm() == elem1.studyForm() and
                    elem.code() == elem1.code() and
                    elem1.type() != "Бюджет") {

                    elem.setCapacity(elem.capacity() + (elem1.capacity() - elem1.getPoolSize()));

                }
            }
        }
    }


    // FacultyCell* phisFirst = nullptr;
    // FacultyCell* phisSecond = nullptr;

    // for(int i = 0; i < m_faculties.size(); ++i){

    //     if(m_faculties[i].name() == "Электроника, радиотехника и системы связи")
    //         phisFirst =&m_faculties[i];
    //     if(m_faculties[i].name() == "Физика и Радиофизика")
    //         phisSecond =&m_faculties[i];

    // }


    // phisSecond->setCapacity(phisSecond->capacity() + (m_faculties[m_faculties.size() - 1].capacity() - m_faculties[m_faculties.size() - 1].getPoolSize()));
    // phisSecond->setCapacity(phisSecond->capacity() + (m_faculties[m_faculties.size() - 2].capacity() - m_faculties[m_faculties.size() - 2].getPoolSize()));
    // phisFirst->setCapacity(phisFirst->capacity() + (m_faculties[m_faculties.size() - 3].capacity() - m_faculties[m_faculties.size() - 3].getPoolSize()));
    // phisFirst->setCapacity(phisFirst->capacity() + (m_faculties[m_faculties.size() - 4].capacity() - m_faculties[m_faculties.size() - 4].getPoolSize()));
    // phisFirst->setCapacity(phisFirst->capacity() + (m_faculties[m_faculties.size() - 5].capacity() - m_faculties[m_faculties.size() - 5].getPoolSize()));


}

void MagicHat::printStatsToConsole() {
    
    int globalCounter = 0;

    for(int i = 0; i < m_faculties.size(); ++i) {
        
        qDebug() << "\n>----" << m_faculties[i].code() << "|" <<  m_faculties[i].name() << "|" <<
            QString::number(m_faculties[i].pool().size()) + "/" + QString::number(m_faculties[i].capacity()) << "|"
            << m_faculties[i].type() << "|"
            << m_faculties[i].studyForm() << "----<";

        if(m_faculties[i].pool().size() == 0) {
            qDebug() << "НЕТ СТУДЕНТОВ\n";
            continue;
        }
        
        globalCounter += m_faculties[i].pool().size();
        int counter = m_faculties[i].pool().size();
        for(const auto& elem : m_faculties[i].pool()){

            qDebug() << "" << counter <<  "-" <<  elem.second.id() << "-" << elem.second.FIO() << "-" << elem.first.egeScore() << elem.first.egeAdditionalScore() << (elem.first.isBVI() ? "БВИ" : "") << "Проритет -" << elem.first.priorityNumber();
            counter -= 1;
        }

    }
    
    qDebug()  << "Зачислено -" <<  globalCounter << "\n";

}

QList<Applicant> MagicHat::uncountedApplicants() const {
    return m_uncountedApplicants;
}

void MagicHat::printUncountedApplicants() {
    
    for(auto& elem : m_uncountedApplicants){
        
        for(const auto elem1 : m_applicantsListCopy) {
            
            if(elem.id() == elem1.id())
                elem = elem1;
        }
    }
    
    std::sort(m_uncountedApplicants.begin(), m_uncountedApplicants.end(), [](Applicant& first, Applicant& second){
        
        std::sort(first.priorities().begin(), first.priorities().end(), [](const PriorityInfo& first1, const PriorityInfo& second2){
            return first1.egeScore() < second2.egeScore();
        });
        std::sort(second.priorities().begin(), second.priorities().end(), [](const PriorityInfo& first1, const PriorityInfo& second2){
            return first1.egeScore() < second2.egeScore();
        });
        
        if(first.priorities().size() == 0)
            return false;
        
        if(second.priorities().size() == 0)
            return true;
        
        return first.priorities()[0] > second.priorities()[0];
        
    });
    
    for(auto& elem : m_uncountedApplicants) {
                
            QString temp;
            for(const auto& scores : elem.priorities())
                temp += QString::number(scores.egeScore()) + " ";
            
            qDebug () << elem.id() << elem.FIO() << "{" << temp << "}" << elem.priorities()[0].name();
        
    }
    
    qDebug() << m_uncountedApplicants.size();
    
}

void MagicHat::printToExcel() {

    QXlsx::Document newDoc;
    newDoc.addSheet("ПМИ");
    newDoc.addSheet("МКН");
    newDoc.addSheet("ИБ");
    newDoc.addSheet("КБ");

    int globalCounter = 0;

    newDoc.selectSheet("ПМИ");
    for(int i = 0; i < m_faculties.size(); ++i) {

        if(m_faculties[i].name() == "Прикладное программирование и информационные технологии" and m_faculties[i].type() == "Бюджет") {

            globalCounter += m_faculties[i].pool().size();
            int counter = m_faculties[i].pool().size();
            for(int j = 0; j < m_faculties[i].pool().size() ; ++j){

                newDoc.write(j + 1, 1, m_faculties[i].pool()[j].second.id());
                newDoc.write(j + 1, 2, m_faculties[i].pool()[j].second.FIO());
                newDoc.write(j + 1, 3, m_faculties[i].pool()[j].first.egeScore());
                newDoc.write(j + 1, 4, m_faculties[i].pool()[j].first.egeAdditionalScore());
                newDoc.write(j + 1, 5, m_faculties[i].pool()[j].first.name());
            }
        }
    }


    newDoc.selectSheet("МКН");
    for(int i = 0; i < m_faculties.size(); ++i) {

        if(m_faculties[i].name() == "Программирование, алгоритмы и анализ данных" and m_faculties[i].type() == "Бюджет") {

            globalCounter += m_faculties[i].pool().size();
            int counter = m_faculties[i].pool().size();
            for(int j = 0; j < m_faculties[i].pool().size() ; ++j){

                newDoc.write(j + 1, 1, m_faculties[i].pool()[j].second.id());
                newDoc.write(j + 1, 2, m_faculties[i].pool()[j].second.FIO());
                newDoc.write(j + 1, 3, m_faculties[i].pool()[j].first.egeScore());
                newDoc.write(j + 1, 4, m_faculties[i].pool()[j].first.egeAdditionalScore());
                newDoc.write(j + 1, 5, m_faculties[i].pool()[j].first.name());
            }
        }
    }


    newDoc.selectSheet("ИБ");
    for(int i = 0; i < m_faculties.size(); ++i) {

        if(m_faculties[i].name() == "Безопасность компьютерных систем" and m_faculties[i].type() == "Бюджет") {

            globalCounter += m_faculties[i].pool().size();
            int counter = m_faculties[i].pool().size();
            for(int j = 0; j < m_faculties[i].pool().size() ; ++j){

                newDoc.write(j + 1, 1, m_faculties[i].pool()[j].second.id());
                newDoc.write(j + 1, 2, m_faculties[i].pool()[j].second.FIO());
                newDoc.write(j + 1, 3, m_faculties[i].pool()[j].first.egeScore());
                newDoc.write(j + 1, 4, m_faculties[i].pool()[j].first.egeAdditionalScore());
                newDoc.write(j + 1, 5, m_faculties[i].pool()[j].first.name());
            }
        }
    }



    newDoc.selectSheet("КБ");
    for(int i = 0; i < m_faculties.size(); ++i) {
        if(m_faculties[i].name() == "Математические методы защиты информации" and m_faculties[i].type() == "Бюджет") {

            globalCounter += m_faculties[i].pool().size();
            int counter = m_faculties[i].pool().size();
            for(int j = 0; j < m_faculties[i].pool().size() ; ++j){

                newDoc.write(j + 1, 1, m_faculties[i].pool()[j].second.id());
                newDoc.write(j + 1, 2, m_faculties[i].pool()[j].second.FIO());
                newDoc.write(j + 1, 3, m_faculties[i].pool()[j].first.egeScore());
                newDoc.write(j + 1, 4, m_faculties[i].pool()[j].first.egeAdditionalScore());
                newDoc.write(j + 1, 5, m_faculties[i].pool()[j].first.name());
            }
        }
    }

    if(newDoc.saveAs("newDoc1.xlsx")){
        qDebug() << "OK";
    }
    else{
        qDebug() << "NOT OK";
    }

}

void MagicHat::setKCP(const QString &path) {
    
    QFile input(path);
    
    if(!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл " << path << "\n Ошибка: " << input.errorString();
    }
    
    QTextStream stream(&input);
    QString line = stream.readLine();//read title line
    line = stream.readLine();//read first line
    
    while(line.isEmpty() or line[0] != "/") {
        
        if(!line.isEmpty()) {
            
            QList<QString> arr = line.split("\"");
            
            for(int i = 0; i < arr.size(); ++i)
                if(arr[i].isEmpty() or arr[i] == " ") {
                    arr.removeAt(i);
                    --i;
                }
            
            QString code = arr[0];
            QString name = arr[1];
            QString studyForm = arr[2];
            QString type = arr[3];
            QString kcp = arr[4];
            
            m_faculties.append(FacultyCell());
            m_faculties.last().setName(name);
            m_faculties.last().setCode(code);
            m_faculties.last().setStudyForm(studyForm);
            m_faculties.last().setType(type);
            m_faculties.last().setCapacity(kcp.toInt());
            
        }
        
        line = stream.readLine();
        
    }
    
}

QList<FacultyCell> MagicHat::faculties() const
{
    return m_faculties;
}

void MagicHat::printFaculties() {

    qDebug() << "\n";

    QString tempCode = m_faculties[0].code();
    for(const auto& elem : m_faculties) {

        if(tempCode != elem.code()) {
            qDebug() << "\n";
            tempCode = elem.code();
        }

        qDebug() << elem.code() + " " + elem.name() + "-" + elem.studyForm() + "-" +
                        elem.type() + "-" + QString::number(elem.capacity()) + "-" +  QString::number(elem.pool().size()) + "-" +
                        QString::number((elem.pool().size() != 0 ? elem.pool()[0].first.egeScore() : 0));

    }

}






















