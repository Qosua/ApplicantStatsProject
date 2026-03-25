#include "priority-info.h"

int PriorityInfo::egeAdditionalScore() const { return m_egeAdditionalScore; }

void PriorityInfo::setEgeAdditionalScore(int newEgeAdditionalScore) {
    if (m_egeAdditionalScore == newEgeAdditionalScore)
	return;
    m_egeAdditionalScore = newEgeAdditionalScore;
}

int PriorityInfo::priorityNumber() const { return m_priorityNumber; }

void PriorityInfo::setPriorityNumber(int newPriorityNumber) {
    if (m_priorityNumber == newPriorityNumber)
	return;
    m_priorityNumber = newPriorityNumber;
}

QString PriorityInfo::code() const { return m_code; }

void PriorityInfo::setCode(const QString &newCode) {
    if (m_code == newCode)
	return;
    m_code = newCode;
}

QString PriorityInfo::name() const { return m_name; }

void PriorityInfo::setName(const QString &newName) {
    if (m_name == newName)
	return;
    m_name = newName;
}

StudyForm PriorityInfo::studyForm() const { return m_studyForm; }

void PriorityInfo::setStudyForm(const StudyForm &newStudyForm) {
    if (m_studyForm == newStudyForm)
	return;
    m_studyForm = newStudyForm;
}

StudyType PriorityInfo::studyType() const { return m_studyType; }

void PriorityInfo::setStudyType(const StudyType &newType) {
    if (m_studyType == newType)
	return;
    m_studyType = newType;
}

QList<int> PriorityInfo::subjectScores() const { return m_subjectScores; }

void PriorityInfo::setSubjectScores(const QList<int> &newSubjectScores) {
    if (m_subjectScores == newSubjectScores)
	return;
    m_subjectScores = newSubjectScores;
}

void PriorityInfo::addSubject(int score) {
    m_subjectScores.append(score);
    if (m_subjectScores.size() > 3)
	qDebug() << "WARNING SUBJECTS COUNT MORE THAN 3" << __FILE__ << ":" << __LINE__;
}

int PriorityInfo::id() const { return m_id; }

void PriorityInfo::setId(int newId) {
    if (m_id == newId)
	return;
    m_id = newId;
}

bool PriorityInfo::admissionFlag() const { return m_admissionFlag; }

void PriorityInfo::setAdmissionFlag(bool newAdmissionsFlag) {
    if (m_admissionFlag == newAdmissionsFlag)
	return;
    m_admissionFlag = newAdmissionsFlag;
}

bool PriorityInfo::isBVI() const { return m_isBVI; }

void PriorityInfo::setIsBVI(bool newIsBVI) {
    if (m_isBVI == newIsBVI)
	return;
    m_isBVI = newIsBVI;
}

QString PriorityInfo::division() const { return m_division; }

void PriorityInfo::setDivision(const QString &newDivision) {
    if (m_division == newDivision)
	return;
    m_division = newDivision;
}

PriorityInfo::PriorityInfo() {}

PriorityInfo::PriorityInfo(const PriorityInfo &copy) { *this = copy; }

void PriorityInfo::operator=(const PriorityInfo &copy) {
    m_egeScore = copy.m_egeScore;
    m_egeAdditionalScore = copy.m_egeAdditionalScore;
    m_priorityNumber = copy.m_priorityNumber;
    m_code = copy.m_code;
    m_name = copy.m_name;
    m_studyForm = copy.m_studyForm;
    m_studyType = copy.m_studyType;
    m_subjectScores = copy.m_subjectScores;
    m_id = copy.m_id;
    m_admissionFlag = copy.m_admissionFlag;
    m_isBVI = copy.m_isBVI;
    m_division = copy.m_division;
}

bool PriorityInfo::operator==(const PriorityInfo &copy) const {
    return ((m_egeScore == copy.m_egeScore) and
            (m_egeAdditionalScore == copy.m_egeAdditionalScore) and
            (m_priorityNumber == copy.m_priorityNumber) and (m_code == copy.m_code) and
            (m_name == copy.m_name) and (m_studyForm == copy.m_studyForm) and
            (m_studyType == copy.m_studyType) and (m_subjectScores == copy.m_subjectScores) and
            (m_id == copy.m_id) and (m_admissionFlag == copy.m_admissionFlag) and
            (m_isBVI == copy.m_isBVI) and (m_division == copy.m_division));
}

bool PriorityInfo::operator!=(const PriorityInfo &copy) const { return !(*this == copy); }

bool PriorityInfo::operator<(const PriorityInfo &copy) const {

    if (m_isBVI == false and copy.m_isBVI == true)
	return true;
    else if (m_isBVI == true and copy.m_isBVI == false)
	return false;

    if (m_egeScore < copy.m_egeScore)
	return true;
    else if (m_egeScore == copy.m_egeScore) {

	if (m_egeAdditionalScore > copy.m_egeAdditionalScore)
	    return true;
	else if (m_egeAdditionalScore == copy.m_egeAdditionalScore) {

	    if (m_subjectScores[0] < copy.m_subjectScores[0])
		return true;
	    else if (m_subjectScores[0] == copy.m_subjectScores[0]) {

		if (m_subjectScores[1] < copy.m_subjectScores[1])
		    return true;
		else if (m_subjectScores[1] == copy.m_subjectScores[1]) {

		    if (m_subjectScores[2] < copy.m_subjectScores[2])
			return true;
		    else if (m_subjectScores[2] == copy.m_subjectScores[2]) {

			// qDebug() << "Why???" << __FILE__ << ":" << __LINE__;
			return m_id >= copy.m_id;
		    } else
			return false;
		} else
		    return false;
	    } else
		return false;
	} else
	    return false;
    } else
	return false;
}

bool PriorityInfo::operator>(const PriorityInfo &copy) const {
    return (!(*this < copy) and (*this != copy));
}

bool PriorityInfo::operator<=(const PriorityInfo &copy) const { return !(*this > copy); }

bool PriorityInfo::operator>=(const PriorityInfo &copy) const { return !(*this < copy); }

int PriorityInfo::egeScore() const { return m_egeScore; }

void PriorityInfo::setEgeScore(int newEgeScore) {
    if (m_egeScore == newEgeScore)
	return;
    m_egeScore = newEgeScore;
}