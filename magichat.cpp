#include "magichat.h"

MagicHat::MagicHat() {

    QString priorityArr[4] =
        {
        "Бюджет",
        "Особое право",
        "Отдельная квота",
        "Целевое обучение"};

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
             "Безопасность компьютерных систем (в сфере информационных технологий)",
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
             "11.00.00",
             "Электроника, радиотехника и системы связи",
             "Очное"},
            {112, 12, 12, 0}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "11.03.01",
             "Радиотехника",
             "Очное"},
            {0, 0, 0, 10}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "11.03.02",
             "Искусственный интеллект и инфокоммуникации",
             "Очное"},
            {0, 0, 0, 15}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "11.03.03",
             "Инновационные материалы и технологии электроники и наноэлектроники",
             "Очное"},
            {0, 0, 0, 12}
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
             "Заочная"},
            {7, 1, 1, 1}
        }),
        QPair<QList<QString>, QList<int>>({
            {
             "38.03.02",
             "Менеджмент в инновационном и социальном предпринимательстве",
             "Заочная"},
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
            m_faculties.append(FacultyCell());
            m_faculties.last().setName(name);
            m_faculties.last().setCode(code);
            m_faculties.last().setStudyForm(form);
            m_faculties.last().setType(priorityArr[i]);
            m_faculties.last().setCapacity(arr[i]);
        }
    }

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

void MagicHat::printFaculties() {

    /*
    for(const auto& elem : globalList) {

        qDebug() << elem.first[0] << elem.first[1] << elem.first[2] <<
            elem.second[0] << elem.second[1] << elem.second[2] << elem.second[3];

    }
    */
    QString tempCode = m_faculties[0].code();
    for(const auto& elem : m_faculties) {

        if(tempCode != elem.code()) {
            qDebug() << "\n";
            tempCode = elem.code();
        }

        qDebug() << elem.code() << elem.name() << elem.studyForm() <<
            elem.type() << elem.capacity();

    }

}























