#include "faculty-direction.h"

FacultyDirection::FacultyDirection() {}

FacultyDirection::FacultyDirection(const FacultyDirection &copy) { *this = copy; }

void FacultyDirection::operator=(const FacultyDirection &copy) {

    m_capacity = copy.m_capacity;
    m_name = copy.m_name;
    m_code = copy.m_code;
    m_studyForm = copy.m_studyForm;
    m_studyType = copy.m_studyType;
    m_pool = copy.m_pool;
    m_division = copy.m_division;
}

QString FacultyDirection::name() const { return m_name; }

void FacultyDirection::setName(const QString &newName) {
    if (m_name == newName)
	return;
    m_name = newName;
}

QString FacultyDirection::division() const { return m_division; }

void FacultyDirection::setDivision(const QString &newName) { m_division = newName; }

int FacultyDirection::capacity() const { return m_capacity; }

void FacultyDirection::setCapacity(int newCapacity) {
    if (m_capacity == newCapacity)
	return;
    m_capacity = newCapacity;
}

QString FacultyDirection::code() const { return m_code; }

void FacultyDirection::setCode(const QString &newCode) {
    if (m_code == newCode)
	return;
    m_code = newCode;
}

StudyForm FacultyDirection::studyForm() const { return m_studyForm; }

void FacultyDirection::setStudyForm(const StudyForm &newStudyForm) {
    if (m_studyForm == newStudyForm)
	return;
    m_studyForm = newStudyForm;
}

StudyType FacultyDirection::studyType() const { return m_studyType; }

void FacultyDirection::setStudyType(const StudyType &newType) {
    if (m_studyType == newType)
	return;
    m_studyType = newType;
}

QList<QPair<PriorityInfo, Applicant>> FacultyDirection::pool() const { return m_pool; }

void FacultyDirection::setPool(const QList<QPair<PriorityInfo, Applicant>> &newPool) {
    m_pool = newPool;
}

void FacultyDirection::addToPool(const PriorityInfo &priority, const Applicant &applicant) {

    m_pool.append({priority, applicant});

    std::sort(m_pool.begin(), m_pool.end(),
              [](const QPair<PriorityInfo, Applicant> &priority1,
                 const QPair<PriorityInfo, Applicant> &priority2) {
	          return (priority1.first <= priority2.first);
              });
}

bool FacultyDirection::isAbleToAdd(PriorityInfo priority) {

    if (m_capacity <= 0)
	return false;

    if (m_name != priority.name() or m_code != priority.code() or
        m_studyForm != priority.studyForm() or m_studyType != priority.studyType()) {
	// qDebug() << "PRIORITY IN WRONG GROUP" << __FILE__ << ":" << __LINE__;
	return false;
    }

    if (m_pool.size() == 0)
	return true;

    // if(m_pool.first().first == priority)
    //     return false;

    if (m_pool.size() >= m_capacity and m_pool.first().first > priority)
	return false;
    else
	return true;
}

QPair<PriorityInfo, Applicant *> FacultyDirection::getUnsuitableApplicant() {

    if (m_pool.size() > m_capacity) {

	Applicant *applicant = new Applicant;
	*applicant = m_pool.first().second;

	PriorityInfo temp = m_pool.first().first;
	m_pool.removeFirst();

	return {temp, applicant};
    }

    return {PriorityInfo(), nullptr};
}

int FacultyDirection::getPoolSize() { return m_pool.size(); }
