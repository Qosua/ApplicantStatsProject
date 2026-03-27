#ifndef APPLICANT_H
#define APPLICANT_H

#include <QList>
#include <QObject>
#include <QString>
#include <algorithm>

#include "namespaces.h"
#include "priority-info.h"
#include "qdebug.h"

class Applicant {

public:
    Applicant();
    Applicant(const Applicant& copy);
    void operator=(const Applicant& copy);

    bool operator==(const Applicant& copy) const;

    int id() const;
    void setId(int newId);

    QList<PriorityInfo>& priorities();
    void setPriorities(const QList<PriorityInfo>& newPriorities);
    void addPriority(const PriorityInfo& info);
    void deletePriority(StudyType flag);

    QString phoneNumber() const;
    void setPhoneNumber(const QString& newPhoneNumber);

    QString email() const;
    void setEmail(const QString& newEmail);

    QString FIO() const;
    void setFIO(const QString& newFIO);

    friend QDataStream& operator<<(QDataStream& out, const Applicant& p);
    friend QDataStream& operator>>(QDataStream& in, Applicant& p);

private:
    int m_id;
    QList<PriorityInfo> m_priorities;
    QString m_phoneNumber;
    QString m_email;
    QString m_FIO;
};
#endif  // APPLICANT_H
