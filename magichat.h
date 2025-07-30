#ifndef MAGICHAT_H
#define MAGICHAT_H

#include <QObject>
#include <QMap>
#include <QList>

#include "applicant.h"
#include "facultycell.h"

class MagicHat : public QObject {

    Q_OBJECT

public:
    MagicHat();
    
    QList<Applicant> applicantsList() const;
    void setApplicantsList(const QList<Applicant> &newApplicantsList);
    void printFaculties();
    
    void startPriorityRoundSimulation();
    void startGeneralRoundSimulation();
    void rebalanceBudgetaryPlaces();

    void printStatsToConsole();

signals:
    void applicantsListChanged();

private:
    QList<Applicant> m_applicantsList;
    QList<FacultyCell> m_faculties;

    Q_PROPERTY(QList<Applicant> applicantsList READ applicantsList WRITE setApplicantsList NOTIFY applicantsListChanged FINAL)
};

#endif // MAGICHAT_H
