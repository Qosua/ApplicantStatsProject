#include "magichat.h"

MagicHat::MagicHat() {

    QFile input("C:/Repos/Qt/ApplicantStatsProject/kcp.txt");
    QTextStream stream(&input);

    if(!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл " << "C:/Repos/Qt/ApplicantStatsProject/kcp.txt" << "\n Ошибка: " << input.errorString();
    }

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

    /*
    QString priorityArr[4] =
        {
        "Бюджет",
        "Особое право",
        "Отдельная квота",
        "Целевое"};

    QList<QPair<QList<QString>, QList<int>>> globalList = {

        //BIO
        QPair<QList<QString>, QList<int>>({
            {
            "04.03.01",
            "Медицинская и фармацевтическая химия",
            "Очное"},
            {40, 4, 4, 8}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "05.03.06",
             "Экологический менеджмент и аудит",
             "Очное"},
            {19, 2, 2, 2}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "06.03.01",
             "Экспериментальная биология",
             "Очное"},
            {15, 2, 2, 1}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "06.03.01",
             "Биоинженерия и биотехнология",
             "Очное"},
            {45, 5, 5, 2}
        }),
        //IVT
        QPair<QList<QString>, QList<int>>({
            {
             "01.03.02",
             "Программирование и технологии искусственного интеллекта",
             "Очное"},
            {66, 7, 7, 7}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "02.03.02",
             "Программирование и компьютерные науки",
             "Очное"},
            {50, 5, 5, 5}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "09.03.03",
             "Информационные технологии в цифровой экономике",
             "Очное"},
            {50, 5, 5, 5}
        }),
        //HISTORY
        QPair<QList<QString>, QList<int>>({
            {
             "43.03.02",
             "Туризм",
             "Очное"},
            {30, 3, 3, 2}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "46.03.01",
             "История",
             "Очное"},
            {35, 4, 4, 5}
        }),
        //MATH
        QPair<QList<QString>, QList<int>>({
            {
             "01.03.02",
             "Прикладное программирование и информационные технологии",
             "Очное"},
            {65, 7, 7, 6}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "02.03.01",
             "Программирование, алгоритмы и анализ данных",
             "Очное"},
            {25, 3, 3, 4}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "10.03.01",
             "Безопасность компьютерных систем",
             "Очное"},
            {19, 2, 2, 8}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "10.05.01",
             "Математические методы защиты информации",
             "Очное"},
            {25, 3, 3, 10}
        }),
        //PHYS
        QPair<QList<QString>, QList<int>>({
            {
             "37.03.01",
             "Психология",
             "Очное"},
            {24, 3, 3, 2}
        }),
        //PHIS
        QPair<QList<QString>, QList<int>>({
            {
             "03.00.00",
             "Физика и Радиофизика",
             "Очное"},
            {28, 4, 4, 0}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "11.00.00",
             "Электроника, радиотехника и системы связи",
             "Очное"},
            {75, 12, 12, 0}
        }),
        //LANGUAGE
        QPair<QList<QString>, QList<int>>({
            {
             "45.03.02",
             "Перевод и межкультурная коммуникация",
             "Очное"},
            {3, 1, 1, 1}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "45.03.01",
             "Зарубежная филология (английский язык и литература)",
             "Очное"},
            {3, 1, 1, 0}
        }),
        //FILOLOGI
        QPair<QList<QString>, QList<int>>({
            {
             "45.03.01",
             "Прикладная филология (русский язык)",
             "Очное"},
            {5, 1, 1, 1}
        }),
        //SOCIALOGI
        QPair<QList<QString>, QList<int>>({
            {
             "39.03.01",
             "Организация и проведение социологических и маркетинговых исследований",
             "Очное"},
            {15, 2, 2, 1}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "39.03.02",
             "Технологии социальной работы",
             "Очное"},
            {14, 2, 2, 2}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "39.03.03",
             "Управление молодежными проектами",
             "Очное"},
            {14, 2, 2, 2}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "39.03.03",
             "Управление молодежными проектами",
             "Заочная"},
            {15, 2, 2, 2}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "41.03.04",
             "Политический менеджмент",
             "Очное"},
            {15, 2, 2, 2}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "41.03.06",
             "Управление публичной политикой",
             "Очное"},
            {14, 2, 2, 1}
        }),
        //ECONOM
        QPair<QList<QString>, QList<int>>({
            {
             "38.03.01",
             "Финансовый и управленческий учет, анализ и аудит",
             "Очное"},
            {7, 1, 1, 2}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "38.03.01",
             "Мировая экономика и международный бизнес",
             "Очное"},
            {7, 1, 1, 1}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "38.03.01",
             "Финансы, инвестиции и банки",
             "Очное"},
            {6, 1, 1, 0}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "38.03.02",
             "Управление проектами",
             "Очное"},
            {7, 1, 1, 1}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "38.03.02",
             "Менеджмент в инновационном и социальном предпринимательстве",
             "Очное"},
            {7, 1, 1, 0}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "38.03.04",
             "Государственные и муниципальные финансы",
             "Очное"},
            {6, 1, 1, 1}
        }),
        //LAW
        QPair<QList<QString>, QList<int>>({
            {
             "40.03.01",
             "Юриспруденция",
             "Очное"},
            {23, 3, 3, 3}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "40.03.01",
             "Юриспруденция",
             "Заочная"},
            {17, 2, 2, 3}
        }),

    };
    */


    /*
    for(const auto& elem : globalList) {

        QString name;
        QString code;
        QString form;
        int arr[4];
        int budget;
        int right;
        int kvot;
        int goal;

        code = elem.first[0];
        name = elem.first[1];
        form  = elem.first[2];

        budget = elem.second[0];
        right = elem.second[1];
        kvot = elem.second[2];
        goal = elem.second[3];

        arr[0] = budget - right - kvot - goal;
        arr[1] = right;
        arr[2] = kvot;
        arr[3] = goal;

        for(int i = 0; i < 4; ++i){

            if(arr[i] <= 0) {
                continue;
            }

            m_faculties.append(FacultyCell());
            m_faculties.last().setName(name);
            m_faculties.last().setCode(code);
            m_faculties.last().setStudyForm(form);
            m_faculties.last().setType(priorityArr[i]);
            m_faculties.last().setCapacity(arr[i]);
        }
    }

    m_faculties.append(FacultyCell());
    m_faculties.last().setName("Радиотехника");
    m_faculties.last().setCode("11.03.01");
    m_faculties.last().setStudyForm("Очное");
    m_faculties.last().setType("Целевое");
    m_faculties.last().setCapacity(10);

    m_faculties.append(FacultyCell());
    m_faculties.last().setName("Искусственный интеллект и инфокоммуникации");
    m_faculties.last().setCode("11.03.02");
    m_faculties.last().setStudyForm("Очное");
    m_faculties.last().setType("Целевое");
    m_faculties.last().setCapacity(15);

    m_faculties.append(FacultyCell());
    m_faculties.last().setName("Инновационные материалы и технологии электроники и наноэлектроники");
    m_faculties.last().setCode("11.03.03");
    m_faculties.last().setStudyForm("Очное");
    m_faculties.last().setType("Целевое");
    m_faculties.last().setCapacity(12);

    m_faculties.append(FacultyCell());
    m_faculties.last().setName("Физика и компьютерные технологии");
    m_faculties.last().setCode("03.03.02");
    m_faculties.last().setStudyForm("Очное");
    m_faculties.last().setType("Целевое");
    m_faculties.last().setCapacity(3);

    m_faculties.append(FacultyCell());
    m_faculties.last().setName("Технологии беспроводной связи");
    m_faculties.last().setCode("03.03.03");
    m_faculties.last().setStudyForm("Очное");
    m_faculties.last().setType("Целевое");
    m_faculties.last().setCapacity(4);
    */

}

QList<Applicant> MagicHat::applicantsList() const
{
    return m_applicantsList;
}

void MagicHat::setApplicantsList(const QList<Applicant> &newApplicantsList)
{
    if (m_applicantsList == newApplicantsList)
        return;
    m_applicantsList = newApplicantsList;
    emit applicantsListChanged();
}


void MagicHat::startPriorityRoundSimulation() {
    
    QList<Applicant> priorityList;
    
    for(auto& elem : m_applicantsList){
        
        Applicant tempApplicant = elem;
        tempApplicant.priorities().clear();
        
        for(const auto& elem1 : elem.priorities()){
            
            if(elem1.type() != "Бюджет"){
                
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


                if(elem1.second.id() == 4525667)
                    qDebug() << "asdasd";

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

        if(applicant->id() == 4239707){
            qDebug() << "asdasd";
        }
        
        if(applicant->priorities().size() > 0)
            tempPriority = applicant->priorities().first();
        else {
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

                if(elem.name() == elem1.name() and elem.type() == elem1.type())
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


    FacultyCell* phisFirst = nullptr;
    FacultyCell* phisSecond = nullptr;

    for(int i = 0; i < m_faculties.size(); ++i){

        if(m_faculties[i].name() == "Электроника, радиотехника и системы связи")
            phisFirst =&m_faculties[i];
        if(m_faculties[i].name() == "Физика и Радиофизика")
            phisSecond =&m_faculties[i];

    }


    phisSecond->setCapacity(phisSecond->capacity() + (m_faculties[m_faculties.size() - 1].capacity() - m_faculties[m_faculties.size() - 1].getPoolSize()));
    phisSecond->setCapacity(phisSecond->capacity() + (m_faculties[m_faculties.size() - 2].capacity() - m_faculties[m_faculties.size() - 2].getPoolSize()));
    phisFirst->setCapacity(phisFirst->capacity() + (m_faculties[m_faculties.size() - 3].capacity() - m_faculties[m_faculties.size() - 3].getPoolSize()));
    phisFirst->setCapacity(phisFirst->capacity() + (m_faculties[m_faculties.size() - 4].capacity() - m_faculties[m_faculties.size() - 4].getPoolSize()));
    phisFirst->setCapacity(phisFirst->capacity() + (m_faculties[m_faculties.size() - 5].capacity() - m_faculties[m_faculties.size() - 5].getPoolSize()));


}

void MagicHat::printStatsToConsole() {

    for(int i = 0; i < m_faculties.size(); ++i) {
        
        qDebug() << "\n>----" << m_faculties[i].code() << "|" <<  m_faculties[i].name() << "|" <<
            QString::number(m_faculties[i].pool().size()) + "/" + QString::number(m_faculties[i].capacity()) << "|"
            << m_faculties[i].type() << "|"
            << m_faculties[i].studyForm() << "----<";

        if(m_faculties[i].pool().size() == 0) {
            qDebug() << "НЕТ СТУДЕНТОВ\n";
            continue;
        }
        
        int counter = m_faculties[i].pool().size();
        for(const auto& elem : m_faculties[i].pool()){

            qDebug() << "" << counter <<  "-" <<  elem.second.id() << "-" << elem.second.FIO() << "-" << elem.first.egeScore();
            counter -= 1;
        }

        qDebug() << "\n";

    }

}

void MagicHat::printFacultiesNames() {

    for(const auto& elem : m_faculties){

        qDebug() << elem.code() << elem.name() << elem.studyForm() << elem.type() << elem.capacity();

    }

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






















