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

int PriorityInfo::egeScore() const {
    return m_egeScore;
}

void PriorityInfo::setEgeScore(int newEgeScore) {
    if (m_egeScore == newEgeScore)
        return;
    m_egeScore = newEgeScore;
    emit egeScoreChanged();
}
