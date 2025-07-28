#include "facultycell.h"

FacultyCell::FacultyCell() {}

QString FacultyCell::name() const
{
    return m_name;
}

void FacultyCell::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

int FacultyCell::capacity() const
{
    return m_capacity;
}

void FacultyCell::setCapacity(int newCapacity)
{
    if (m_capacity == newCapacity)
        return;
    m_capacity = newCapacity;
    emit capacityChanged();
}

QString FacultyCell::code() const
{
    return m_code;
}

void FacultyCell::setCode(const QString &newCode)
{
    if (m_code == newCode)
        return;
    m_code = newCode;
    emit codeChanged();
}

QString FacultyCell::studyForm() const
{
    return m_studyForm;
}

void FacultyCell::setStudyForm(const QString &newStudyForm)
{
    if (m_studyForm == newStudyForm)
        return;
    m_studyForm = newStudyForm;
    emit studyFormChanged();
}

QString FacultyCell::type() const
{
    return m_type;
}

void FacultyCell::setType(const QString &newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

QList<Applicant> FacultyCell::pool() const
{
    return m_pool;
}

void FacultyCell::setPool(const QList<Applicant> &newPool) {
    m_pool = newPool;
    emit poolChanged();
}

void FacultyCell::addToPool(const Applicant &applicant) {

    m_pool.append(applicant);
    std::sort(m_pool.begin(), m_pool.end(), [&](const Applicant &applicant1, const Applicant &applicant2) {

        PriorityInfo priority1;
        PriorityInfo priority2;

        for(auto elem : applicant1.priorities()){
            if(elem.code() == m_code and
                elem.name() == m_name and
                elem.type() == m_type and
                elem.studyForm() == m_studyForm)
                priority1 = elem;
        }
        for(auto elem : applicant2.priorities()){
            if(elem.code() == m_code and
                elem.name() == m_name and
                elem.type() == m_type and
                elem.studyForm() == m_studyForm)
                priority2 = elem;
        }

        if(priority1.egeScore() < priority2.egeScore())
            return true;
        else
            if( priority1.egeScore() == priority2.egeScore() and
                priority1.egeAdditionalScore() > priority2.egeAdditionalScore())
                return true;
            else


    });

}


