#ifndef APPLICANTSTATSPROJECT_PRIORITYINFO_H
#define APPLICANTSTATSPROJECT_PRIORITYINFO_H

#include <QDataStream>
#include <QList>
#include <QString>
#include <algorithm>

#include "namespaces.h"
#include "qdebug.h"

class PriorityInfo {

public:
    PriorityInfo();
    PriorityInfo(const PriorityInfo& copy);
    void operator=(const PriorityInfo& copy);

    bool operator==(const PriorityInfo& copy) const;
    bool operator!=(const PriorityInfo& copy) const;
    bool operator<(const PriorityInfo& copy) const;
    bool operator>(const PriorityInfo& copy) const;
    bool operator<=(const PriorityInfo& copy) const;
    bool operator>=(const PriorityInfo& copy) const;

    int egeScore() const;
    void setEgeScore(int newEgeScore);

    int egeAdditionalScore() const;
    void setEgeAdditionalScore(int newEgeAdditionalScore);

    int priorityNumber() const;
    void setPriorityNumber(int newPriorityNumber);

    QString code() const;
    void setCode(const QString& newCode);

    QString name() const;
    void setName(const QString& newName);

    QList<int> subjectScores() const;
    void setSubjectScores(const QList<int>& newSubjectScores);
    void addSubject(int score);

    int id() const;
    void setId(int newId);

    bool admissionFlag() const;
    void setAdmissionFlag(bool newAdmissionsFlag);

    bool isBVI() const;
    void setIsBVI(bool newIsBVI);

    QString division() const;
    void setDivision(const QString& newDivision);

    StudyForm studyForm() const;
    void setStudyForm(const StudyForm& newStudyForm);

    StudyType studyType() const;
    void setStudyType(const StudyType& newType);

    friend QDataStream& operator<<(QDataStream& out, const PriorityInfo& p);
    friend QDataStream& operator>>(QDataStream& in, PriorityInfo& p);

private:
    int m_id;
    int m_egeScore;
    int m_egeAdditionalScore;
    int m_priorityNumber;
    QString m_code;
    QString m_name;
    QString m_division;
    QList<int> m_subjectScores;
    bool m_admissionFlag;
    bool m_isBVI;
    StudyForm m_studyForm;  // Personal, Personal-NotPersonal,...
    StudyType m_studyType;  // Budget, NonBudget,...
};

#endif  // APPLICANTSTATSPROJECT_PRIORITYINFO_H
