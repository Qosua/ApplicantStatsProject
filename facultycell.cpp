#include "facultycell.h"

FacultyCell::FacultyCell() {}

QString FacultyCell::name() const {
    return m_name;
}

void FacultyCell::setName(const QString &newName) {
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

int FacultyCell::capacity() const {
    return m_capacity;
}

void FacultyCell::setCapacity(int newCapacity) {
    if (m_capacity == newCapacity)
        return;
    m_capacity = newCapacity;
    emit capacityChanged();
}

QString FacultyCell::code() const {
    return m_code;
}

void FacultyCell::setCode(const QString &newCode) {
    if (m_code == newCode)
        return;
    m_code = newCode;
    emit codeChanged();
}

QString FacultyCell::studyForm() const {
    return m_studyForm;
}

void FacultyCell::setStudyForm(const QString &newStudyForm) {
    if (m_studyForm == newStudyForm)
        return;
    m_studyForm = newStudyForm;
    emit studyFormChanged();
}

QString FacultyCell::type() const {
    return m_type;
}

void FacultyCell::setType(const QString &newType) {
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

QList<QPair<PriorityInfo, Applicant>> FacultyCell::pool() const {
    return m_pool;
}

void FacultyCell::setPool(const QList<QPair<PriorityInfo, Applicant>> &newPool) {
    m_pool = newPool;
    emit poolChanged();
}

void FacultyCell::addToPool(const PriorityInfo &priority, const Applicant &applicant) {
    
    m_pool.append({priority, applicant});
    std::sort(m_pool.begin(), m_pool.end(), [](const QPair<PriorityInfo, Applicant>& priority1, const QPair<PriorityInfo, Applicant>& priority2){
        
        return priority1.first >= priority2.first;
        
    });
    
}

bool FacultyCell::isAbleToAdd(PriorityInfo priority) {
    
    if(m_name != priority.name() or
        m_code != priority.code() or
        m_studyForm != priority.studyForm() or
        m_type != priority.type())
        qDebug() << "PRIORITY IN WRONG GROUP" << __FILE__ << ":" << __LINE__;
    
    if((m_pool.first().first) < priority and m_pool.size() == m_capacity)
        return false;
    else
        return true;
    
}

Applicant *FacultyCell::getUnsuitableApplicant() {
    
    if(m_pool.size() > m_capacity){
        
        Applicant* applicant = new Applicant;
        *applicant = m_pool.first().second;
        return applicant;
        
    }
    
    return nullptr;
}





























