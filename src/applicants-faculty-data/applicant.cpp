#include "applicant.h"

Applicant::Applicant() {}

Applicant::Applicant(const Applicant &copy) { *this = copy; }

int Applicant::id() const { return m_id; }

void Applicant::setId(int newId) { m_id = newId; }

QList<PriorityInfo> &Applicant::priorities() { return m_priorities; }

void Applicant::setPriorities(const QList<PriorityInfo> &newPriorities) {
    m_priorities = newPriorities;
}

void Applicant::addPriority(const PriorityInfo &info) {

    m_priorities.append(info);

    std::sort(m_priorities.begin(), m_priorities.end(),
              [](const PriorityInfo &info1, const PriorityInfo &info2) {
	          if ((info1.studyType() == StudyType::Budget
	               or info1.studyType() == StudyType::NonBudget)
	              and info2.studyType() != StudyType::Budget
	              and info2.studyType() != StudyType::NonBudget)
	              return false;
	          else if ((info1.studyType() == StudyType::Budget
	                    or info1.studyType() == StudyType::NonBudget)
	                   and (info2.studyType() == StudyType::Budget
	                        or info2.studyType() == StudyType::NonBudget))
	              return (info1.priorityNumber() < info2.priorityNumber());
	          else if ((info1.studyType() != StudyType::Budget
	                    and info1.studyType() != StudyType::NonBudget)
	                   and (info2.studyType() == StudyType::Budget
	                        or info2.studyType() == StudyType::NonBudget))
	              return true;
	          else
	              return (info1.priorityNumber() < info2.priorityNumber());

	          qDebug() << "ERROR IN COMPARATOR -" << __FILE__ << ":" << __LINE__;
	          return false;
              });
}

void Applicant::deletePriority(StudyType flag) {

    for (int i = 0; i < m_priorities.size(); ++i) {

	if (m_priorities[i].studyType() == flag) {
	    m_priorities.removeOne(m_priorities[i]);
	    --i;
	}
    }
}

QString Applicant::phoneNumber() const { return m_phoneNumber; }

void Applicant::setPhoneNumber(const QString &newPhoneNumber) { m_phoneNumber = newPhoneNumber; }

QString Applicant::email() const { return m_email; }

void Applicant::setEmail(const QString &newEmail) { m_email = newEmail; }

QString Applicant::FIO() const { return m_FIO; }

void Applicant::setFIO(const QString &newFIO) { m_FIO = newFIO; }

QDataStream &operator<<(QDataStream &out, const Applicant &p) {
    out << p.m_id;
    out << p.m_priorities;
    out << p.m_email;
    out << p.m_phoneNumber;
    out << p.m_FIO;

    return out;
}

QDataStream &operator>>(QDataStream &in, Applicant &p) {
    in >> p.m_id;
    in >> p.m_priorities;
    in >> p.m_email;
    in >> p.m_phoneNumber;
    in >> p.m_FIO;
    return in;
}

void Applicant::operator=(const Applicant &copy) {
    m_id = copy.m_id;
    m_priorities = copy.m_priorities;
    m_FIO = copy.m_FIO;
    m_email = copy.m_email;
    m_phoneNumber = copy.m_phoneNumber;
}

bool Applicant::operator==(const Applicant &copy) const {

    if ((m_id == copy.m_id) and (m_priorities == copy.m_priorities) and (m_FIO == copy.m_FIO)
        and (m_email == copy.m_email) and (m_phoneNumber == copy.m_phoneNumber))
	return true;
    else
	return false;
}
