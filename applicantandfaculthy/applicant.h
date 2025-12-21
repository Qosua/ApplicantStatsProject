#ifndef APPLICANT_H
#define APPLICANT_H

#include <QObject>
#include <QString>
#include <QList>

#include "namespaces.h"

class PriorityInfo : public QObject {
    
    Q_OBJECT
    
public:
    PriorityInfo();
    PriorityInfo(const PriorityInfo& copy);
    void operator=(const PriorityInfo& copy);
    
    bool operator==(const PriorityInfo& copy) const;
    bool operator!=(const PriorityInfo& copy) const;
    bool operator <(const PriorityInfo& copy) const;
    bool operator >(const PriorityInfo& copy) const;
    bool operator<=(const PriorityInfo& copy) const;
    bool operator>=(const PriorityInfo& copy) const;
    
    int egeScore() const;
    void setEgeScore(int newEgeScore);
    
    int egeAdditionalScore() const;
    void setEgeAdditionalScore(int newEgeAdditionalScore);
    
    int priorityNumber() const;
    void setPriorityNumber(int newPriorityNumber);
    
    QString code() const;
    void setCode(const QString &newCode);
    
    QString name() const;
    void setName(const QString &newName);
    
    QString studyForm() const;
    void setStudyForm(const QString &newStudyForm);
    
    QString type() const;
    void setType(const QString &newType);
    
    QList<int> subjectScores() const;
    void setSubjectScores(const QList<int> &newSubjectScores);
    void addSubject(int score);
    
    int id() const;
    void setId(int newId);
    
    bool admissionFlag() const;
    void setAdmissionFlag(bool newAdmissionsFlag);
    
    bool isBVI() const;
    void setIsBVI(bool newIsBVI);
    
    QString division() const;
    void setDivision(const QString &newDivision);

private:
    int m_id;
    int m_egeScore;
    int m_egeAdditionalScore;
    int m_priorityNumber;
    QString m_code;
    QString m_name;
    QString m_studyForm; //Personal, Personal-NotPersonal,...
    QString m_type; //Budget, NonBudget,...
    QString m_division;
    QList<int> m_subjectScores;
    bool m_admissionFlag;
    bool m_isBVI;
    
signals:
    void egeScoreChanged();
    void egeAdditionalScoreChanged();
    void priorityNumberChanged();
    void priorityNameChanged();
    void codeChanged();
    void nameChanged();
    void studyFormChanged();
    void typeChanged();
    void subjectScoresChanged();
    void idChanged();
    void admissionFlagChanged();
    void isBVIChanged();
    void divisionChanged();
    
    // Q_PROPERTY(int egeScore READ egeScore WRITE setEgeScore NOTIFY egeScoreChanged FINAL)
    // Q_PROPERTY(int egeAdditionalScore READ egeAdditionalScore WRITE setEgeAdditionalScore NOTIFY egeAdditionalScoreChanged FINAL)
    // Q_PROPERTY(int priorityNumber READ priorityNumber WRITE setPriorityNumber NOTIFY priorityNumberChanged FINAL)
    // Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged FINAL)
    // Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    // Q_PROPERTY(QString studyForm READ studyForm WRITE setStudyForm NOTIFY studyFormChanged FINAL)
    // Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged FINAL)
    // Q_PROPERTY(QList<int> subjectScores READ subjectScores WRITE setSubjectScores NOTIFY subjectScoresChanged FINAL)
    // Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    // Q_PROPERTY(bool m_admissionFlag READ admissionFlag WRITE setAdmissionFlag NOTIFY admissionFlagChanged FINAL)
    // Q_PROPERTY(bool isBVI READ isBVI WRITE setIsBVI NOTIFY isBVIChanged FINAL)
    // Q_PROPERTY(QString division READ division WRITE setDivision NOTIFY divisionChanged FINAL)
};

//////////////////////////////////////////////////////////////////////

class Applicant : public QObject {
    
    Q_OBJECT
    
public:
    Applicant();
    Applicant(const Applicant& copy);
    void operator=(const Applicant& copy);
    
    bool operator==(const Applicant& copy) const;
    
    int id() const;
    void setId(int newId);
    
    QList<PriorityInfo>& priorities();
    void setPriorities(const QList<PriorityInfo> &newPriorities);
    void addPriority(const PriorityInfo& info);
    void deletePriority(PriorityType flag);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &newPhoneNumber);

    QString email() const;
    void setEmail(const QString &newEmail);

    QString FIO() const;
    void setFIO(const QString &newFIO);

private:
    int m_id;
    QList<PriorityInfo> m_priorities;
    QString m_phoneNumber;
    QString m_email;
    QString m_FIO;
    
signals:
    void idChanged();
    void prioritiesChanged();
    void phoneNumberChanged();
    void emailChanged();
    void FIOChanged();
    
    // Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    // Q_PROPERTY(QList<PriorityInfo> priorities READ priorities WRITE setPriorities NOTIFY prioritiesChanged FINAL)
    // Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged FINAL)
    // Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged FINAL)
    // Q_PROPERTY(QString FIO READ FIO WRITE setFIO NOTIFY FIOChanged FINAL)
};
#endif // APPLICANT_H
