#ifndef FACULTYCELL_H
#define FACULTYCELL_H

#include <QObject>
#include <algorithm>
#include <QPair>
#include <QDebug>
#include "applicant.h"

class FacultyCell : public QObject {

    Q_OBJECT

public:

    FacultyCell();
    FacultyCell(const FacultyCell& copy);
    void operator=(const FacultyCell& copy);

    QString name() const;
    void setName(const QString &newName);

    int capacity() const;
    void setCapacity(int newCapacity);

    QString code() const;
    void setCode(const QString &newCode);

    QString studyForm() const;
    void setStudyForm(const QString &newStudyForm);

    QString type() const;
    void setType(const QString &newType);

    QList<QPair<PriorityInfo, Applicant>> pool() const;
    void setPool(const QList<QPair<PriorityInfo, Applicant>> &newPool);
    void addToPool(const PriorityInfo& priority, const Applicant& applicant);
    
    bool isAbleToAdd(PriorityInfo priority);
    
    QPair<PriorityInfo, Applicant*> getUnsuitableApplicant();

signals:
    void nameChanged();
    void capacityChanged();
    void codeChanged();
    void studyFormChanged();
    void typeChanged();
    void poolChanged();

private:
    int m_capacity;
    QString m_name;
    QString m_code;
    QString m_studyForm; //Personal, Personal-NotPersonal,...
    QString m_type; //Budget, CompanySponsor,...
    QList<QPair<PriorityInfo, Applicant>> m_pool;

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(int capacity READ capacity WRITE setCapacity NOTIFY capacityChanged FINAL)
    Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged FINAL)
    Q_PROPERTY(QString studyForm READ studyForm WRITE setStudyForm NOTIFY studyFormChanged FINAL)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(QList<QPair<PriorityInfo, Applicant> > pool READ pool WRITE setPool NOTIFY poolChanged FINAL)
};

#endif // FACULTYCELL_H
