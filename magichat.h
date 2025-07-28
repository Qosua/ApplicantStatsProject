#ifndef MAGICHAT_H
#define MAGICHAT_H

#include <QObject>

#include "applicant.h"

class MagicHat : public QObject {

    Q_OBJECT

public:
    MagicHat();
    
    QList<Applicant> getApplicantsList() const;
    void setApplicantsList(const QList<Applicant> &newApplicantsList);
    
signals:
    void applicantsListChanged();
    
private:
    
    QList<Applicant> applicantsList;
    
    Q_PROPERTY(QList<Applicant> applicantsList READ getApplicantsList WRITE setApplicantsList NOTIFY applicantsListChanged FINAL)
};

#endif // MAGICHAT_H
