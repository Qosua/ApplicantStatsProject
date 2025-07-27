#include "applicant.h"
#include "qdebug.h"

Applicant::Applicant() {
    
}

Applicant::Applicant(const Applicant &copy) {
    *this = copy;
}

int Applicant::id() const {
    return m_id;
}

void Applicant::setId(int newId) {
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

bool Applicant::admissionFlag() const {
    return m_admissionFlag;
}

void Applicant::setAdmissionFlag(bool newAdmissionFlag) {
    if (m_admissionFlag == newAdmissionFlag)
        return;
    m_admissionFlag = newAdmissionFlag;
    emit admissionFlagChanged();
}

QList<PriorityInfo> Applicant::priorities() const {
    return m_priorities;
}

void Applicant::setPriorities(const QList<PriorityInfo> &newPriorities) {
    m_priorities = newPriorities;
    emit prioritiesChanged();
}

void Applicant::addPriority(const PriorityInfo &info) {
    m_priorities.append(info);
    std::sort(m_priorities.begin(), m_priorities.end(),
        [](const PriorityInfo &info1, const PriorityInfo &info2){
            return info1.priorityNumber() < info2.priorityNumber();
    });
    
}

void Applicant::deletePriority(PrioritiesFlags flag) {
    
    switch(flag){
        case PrioritiesFlags::Budget: {
            for(const auto& elem : m_priorities)
                if(elem.priorityName().contains("Бюджет"))
                    m_priorities.removeOne(elem);
        }break;
            
        case PrioritiesFlags::NonBudget: {
            for(const auto& elem : m_priorities)
                if(elem.priorityName().contains("Внебюджет"))
                    m_priorities.removeOne(elem);
        }break;
            
        case PrioritiesFlags::SpecialRight: {
            for(const auto& elem : m_priorities)
                if(elem.priorityName().contains("Особое право"))
                    m_priorities.removeOne(elem);
        }break;
            
        case PrioritiesFlags::Kvot: {
            for(const auto& elem : m_priorities)
                if(elem.priorityName().contains("Отдельная квота"))
                    m_priorities.removeOne(elem);
        }break;
            
        case PrioritiesFlags::CompanySponsor: {
            for(const auto& elem : m_priorities)
                if(elem.priorityName().contains("Целевое"))
                    m_priorities.removeOne(elem);
        }break;
    }
}

void Applicant::operator=(const Applicant &copy) {
    m_id = copy.m_id;
    m_admissionFlag = copy.m_admissionFlag;
    m_priorities = copy.m_priorities; 
}

//////////////////////////////////////////////////////////////////////

int PriorityInfo::egeAdditionalScore() const {
    return m_egeAdditionalScore;
}

void PriorityInfo::setEgeAdditionalScore(int newEgeAdditionalScore) {
    if (m_egeAdditionalScore == newEgeAdditionalScore)
        return;
    m_egeAdditionalScore = newEgeAdditionalScore;
    emit egeAdditionalScoreChanged();
}

int PriorityInfo::priorityNumber() const {
    return m_priorityNumber;
}

void PriorityInfo::setPriorityNumber(int newPriorityNumber) {
    if (m_priorityNumber == newPriorityNumber)
        return;
    m_priorityNumber = newPriorityNumber;
    emit priorityNumberChanged();
}

QString PriorityInfo::priorityName() const {
    return m_priorityName;
}

void PriorityInfo::setPriorityName(const QString &newPriorityName) {
    if (m_priorityName == newPriorityName)
        return;
    m_priorityName = newPriorityName;
    emit priorityNameChanged();
}

PriorityInfo::PriorityInfo() {
    
}

PriorityInfo::PriorityInfo(const PriorityInfo &copy) {
    *this = copy;
}

void PriorityInfo::operator=(const PriorityInfo &copy) {
    m_egeScore = copy.m_egeScore;
    m_egeAdditionalScore = copy.m_egeAdditionalScore;
    m_priorityNumber = copy.m_priorityNumber;
    m_priorityName = copy.m_priorityName;
}

bool PriorityInfo::operator==(const PriorityInfo &copy) const {
    return ((m_egeScore == copy.m_egeScore) and
            (m_egeAdditionalScore == copy.m_egeAdditionalScore) and
            (m_priorityNumber == copy.m_priorityNumber) and
            (m_priorityName == copy.m_priorityName));
}

int PriorityInfo::egeScore() const {
    return m_egeScore;
}

void PriorityInfo::setEgeScore(int newEgeScore) {
    if (m_egeScore == newEgeScore)
        return;
    m_egeScore = newEgeScore;
    emit egeScoreChanged();
}
