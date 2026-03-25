#include "applicant.h"

Applicant::Applicant() {}

Applicant::Applicant(const Applicant &copy) { *this = copy; }

int Applicant::id() const { return m_id; }

void Applicant::setId(int newId) {
    if (m_id == newId)
	return;
    m_id = newId;
}

QList<PriorityInfo> &Applicant::priorities() { return m_priorities; }

void Applicant::setPriorities(const QList<PriorityInfo> &newPriorities) {
    m_priorities = newPriorities;
}

void Applicant::addPriority(const PriorityInfo &info) {

    m_priorities.append(info);

    std::sort(m_priorities.begin(), m_priorities.end(),
              [](const PriorityInfo &info1, const PriorityInfo &info2) {
	          // old system

	          /*
	          if(info1.type() == "Целевое" and info2.type() != "Целевое")
	              return !(false);
	          else
	              if(info1.type() == "Целевое" and info2.type() == "Целевое")
	                  return (info1.priorityNumber() < info2.priorityNumber());
	              else
	                  if(info1.type() != "Целевое" and info2.type() == "Целевое")
	                      return !(true);
	                  else
	                      if((info1.type() == "Бюджет" or info1.type() == "Внебюджет") and
	                          info2.type() != "Бюджет" and info2.type() != "Внебюджет")
	                          return !(true);
	                      else
	                          if((info1.type() == "Бюджет" or info1.type() == "Внебюджет") and
	                              (info2.type() == "Бюджет" or info2.type() == "Внебюджет"))
	                              return (info1.priorityNumber() < info2.priorityNumber());
	                          else
	                              if((info1.type() != "Бюджет" and info1.type() != "Внебюджет")
	          and (info2.type() == "Бюджет" or info2.type() == "Внебюджет")) return !(false);
	                              else
	                                  return (info1.priorityNumber() < info2.priorityNumber());

	          qDebug() << "ERROR IN COMPARATOR -"  << __FILE__  << ":" << __LINE__;
	          return false;
	          */

	          if ((info1.studyType() == StudyType::Budget or
	               info1.studyType() == StudyType::NonBudget) and
	              info2.studyType() != StudyType::Budget and
	              info2.studyType() != StudyType::NonBudget)
	              return !(true);
	          else if ((info1.studyType() == StudyType::Budget or
	                    info1.studyType() == StudyType::NonBudget) and
	                   (info2.studyType() == StudyType::Budget or
	                    info2.studyType() == StudyType::NonBudget))
	              return (info1.priorityNumber() < info2.priorityNumber());
	          else if ((info1.studyType() != StudyType::Budget and
	                    info1.studyType() != StudyType::NonBudget) and
	                   (info2.studyType() == StudyType::Budget or
	                    info2.studyType() == StudyType::NonBudget))
	              return !(false);
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

    // old system

    /*
    switch(flag){
        case StudyType::Budget: {
            for(int i = 0; i < m_priorities.size(); ++i)
                if(m_priorities[i].studyType() == "Бюджет") {
                    m_priorities.removeOne(m_priorities[i]);
                    --i;
                }
        }break;

        case StudyType::NonBudget: {
            for(int i = 0; i < m_priorities.size(); ++i)
                if(m_priorities[i].studyType() == "Внебюджет") {
                    m_priorities.removeOne(m_priorities[i]);
                    --i;
                }
        }break;

        case StudyType::SpecialRight: {
            for(int i = 0; i < m_priorities.size(); ++i)
                if(m_priorities[i].studyType() == "Особое право") {
                    m_priorities.removeOne(m_priorities[i]);
                    --i;
                }
        }break;

        case StudyType::Kvot: {
            for(int i = 0; i < m_priorities.size(); ++i)
                if(m_priorities[i].studyType() == "Отдельная квота") {
                    m_priorities.removeOne(m_priorities[i]);
                    --i;
                }
        }break;

        case StudyType::CompanySponsor: {
            for(int i = 0; i < m_priorities.size(); ++i)
                if(m_priorities[i].studyType() == "Целевое") {
                    m_priorities.removeOne(m_priorities[i]);
                    --i;
                }
        }break;
    }
    */
}

QString Applicant::phoneNumber() const { return m_phoneNumber; }

void Applicant::setPhoneNumber(const QString &newPhoneNumber) {
    if (m_phoneNumber == newPhoneNumber)
	return;
    m_phoneNumber = newPhoneNumber;
}

QString Applicant::email() const { return m_email; }

void Applicant::setEmail(const QString &newEmail) {
    if (m_email == newEmail)
	return;
    m_email = newEmail;
}

QString Applicant::FIO() const { return m_FIO; }

void Applicant::setFIO(const QString &newFIO) {
    if (m_FIO == newFIO)
	return;
    m_FIO = newFIO;
}

void Applicant::operator=(const Applicant &copy) {
    m_id = copy.m_id;
    m_priorities = copy.m_priorities;
    m_FIO = copy.m_FIO;
    m_email = copy.m_email;
    m_phoneNumber = copy.m_phoneNumber;
}

bool Applicant::operator==(const Applicant &copy) const {

    if ((m_id == copy.m_id) and (m_priorities == copy.m_priorities) and (m_FIO == copy.m_FIO) and
        (m_email == copy.m_email) and (m_phoneNumber == copy.m_phoneNumber))
	return true;
    else
	return false;
}
