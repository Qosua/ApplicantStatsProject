#ifndef APPLICANT_H
#define APPLICANT_H

#include <QObject>
#include <QString>
#include <QList>
#include <algorithm>

enum PrioritiesFlags {
    NonBudget      = 1 << 3,
    Budget         = 1 << 4,
    SpecialRight   = 1 << 5,
    Kvot           = 1 << 6,
    CompanySponsor = 1 << 7,
};

class PriorityInfo : public QObject {
    
    Q_OBJECT
    
public:
    
    PriorityInfo();
    PriorityInfo(const PriorityInfo& copy);
    void operator=(const PriorityInfo& copy);
    
    bool operator==(const PriorityInfo& copy) const;
    
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

private:
    int m_egeScore;
    int m_egeAdditionalScore;
    int m_priorityNumber;
    QString m_code;
    QString m_name;
    QString m_studyForm; //Personal, Personal-NotPersonal,...
    QString m_type; //Budget, NonBudget,...
    QList<int> m_subjectScores;
    
    Q_PROPERTY(int egeScore READ egeScore WRITE setEgeScore NOTIFY egeScoreChanged FINAL)
    Q_PROPERTY(int egeAdditionalScore READ egeAdditionalScore WRITE setEgeAdditionalScore NOTIFY egeAdditionalScoreChanged FINAL)
    Q_PROPERTY(int priorityNumber READ priorityNumber WRITE setPriorityNumber NOTIFY priorityNumberChanged FINAL)
    Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString studyForm READ studyForm WRITE setStudyForm NOTIFY studyFormChanged FINAL)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(QList<int> subjectScores READ subjectScores WRITE setSubjectScores NOTIFY subjectScoresChanged FINAL)
};

//////////////////////////////////////////////////////////////////////

class Applicant : public QObject {
    
    Q_OBJECT
    
public:
    
    Applicant();
    Applicant(const Applicant& copy);
    void operator=(const Applicant& copy);
    
    int id() const;
    void setId(int newId);
    
    bool admissionFlag() const;
    void setAdmissionFlag(bool newAdmissionFlag);
    
    QList<PriorityInfo> priorities() const;
    void setPriorities(const QList<PriorityInfo> &newPriorities);
    void addPriority(const PriorityInfo& info);
    void deletePriority(PrioritiesFlags flag);

    QString phoneNumber() const;
    void setPhoneNumber(const QString &newPhoneNumber);

    QString email() const;
    void setEmail(const QString &newEmail);

    QString FIO() const;
    void setFIO(const QString &newFIO);

signals:
    void idChanged();
    void admissionFlagChanged();
    void prioritiesChanged();
    void phoneNumberChanged();
    void emailChanged();
    void FIOChanged();

private:
    
    int m_id;
    bool m_admissionFlag;
    QList<PriorityInfo> m_priorities;

    QString m_phoneNumber;
    QString m_email;
    QString m_FIO;
    
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(bool admissionFlag READ admissionFlag WRITE setAdmissionFlag NOTIFY admissionFlagChanged FINAL)
    Q_PROPERTY(QList<PriorityInfo> priorities READ priorities WRITE setPriorities NOTIFY prioritiesChanged FINAL)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged FINAL)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged FINAL)
    Q_PROPERTY(QString FIO READ FIO WRITE setFIO NOTIFY FIOChanged FINAL)
};
#endif // APPLICANT_H
