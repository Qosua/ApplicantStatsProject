#ifndef APPLICANT_H
#define APPLICANT_H

#include <QObject>
#include <QString>
#include <QList>

class PriorityInfo : public QObject {
    
    Q_OBJECT
    
public:
    
    PriorityInfo();
    PriorityInfo(const PriorityInfo& copy);
    void operator=(const PriorityInfo& copy);
    
    int egeScore() const;
    void setEgeScore(int newEgeScore);
    
    int egeAdditionalScore() const;
    void setEgeAdditionalScore(int newEgeAdditionalScore);
    
    int priorityNumber() const;
    void setPriorityNumber(int newPriorityNumber);
    
    QString priorityName() const;
    void setPriorityName(const QString &newPriorityName);
    
signals:
    void egeScoreChanged();
    void egeAdditionalScoreChanged();
    void priorityNumberChanged();
    void priorityNameChanged();
    
private:
    int m_egeScore;
    int m_egeAdditionalScore;
    int m_priorityNumber;
    QString m_priorityName;
    
    Q_PROPERTY(int egeScore READ egeScore WRITE setEgeScore NOTIFY egeScoreChanged FINAL)
    Q_PROPERTY(int egeAdditionalScore READ egeAdditionalScore WRITE setEgeAdditionalScore NOTIFY egeAdditionalScoreChanged FINAL)
    Q_PROPERTY(int priorityNumber READ priorityNumber WRITE setPriorityNumber NOTIFY priorityNumberChanged FINAL)
    Q_PROPERTY(QString priorityName READ priorityName WRITE setPriorityName NOTIFY priorityNameChanged FINAL)
};

class Applicant : public QObject {
    
    Q_OBJECT
    
public:
    
    Applicant();
    void operator=(const Applicant& copy);
    Applicant(const Applicant& copy);
    
    int id() const;
    void setId(int newId);
    
    bool admissionFlag() const;
    void setAdmissionFlag(bool newAdmissionFlag);
    
    QList<PriorityInfo> priorities() const;
    void setPriorities(const QList<PriorityInfo> &newPriorities);
    void addPriority(const PriorityInfo& info);
    
signals:
    void idChanged();
    void admissionFlagChanged();
    void prioritiesChanged();
    
private:
    
    int m_id;
    bool m_admissionFlag;
    QList<PriorityInfo> m_priorities;
    
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(bool admissionFlag READ admissionFlag WRITE setAdmissionFlag NOTIFY admissionFlagChanged FINAL)
    Q_PROPERTY(QList<PriorityInfo> priorities READ priorities WRITE setPriorities NOTIFY prioritiesChanged FINAL)
};

#endif // APPLICANT_H
