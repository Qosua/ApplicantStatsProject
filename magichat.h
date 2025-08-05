#ifndef MAGICHAT_H
#define MAGICHAT_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QFile>
#include <QTextStream>

#include "applicant.h"
#include "facultycell.h"
#include "xlsx.h"

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
    void printFacultiesNames();
    
    QList<Applicant> uncountedApplicants() const;
    void setUncountedApplicants(const QList<Applicant> &newUncountedApplicants);
    
    void printUncountedApplicants();

    void printToExcel();
    
signals:
    void applicantsListChanged();
    void uncountedApplicantsChanged();
    
private:
    QList<Applicant> m_applicantsListCopy;
    QList<Applicant> m_applicantsList;
    QList<FacultyCell> m_faculties;
    QList<Applicant> m_uncountedApplicants;

    Q_PROPERTY(QList<Applicant> applicantsList READ applicantsList WRITE setApplicantsList NOTIFY applicantsListChanged FINAL)
    Q_PROPERTY(QList<Applicant> uncountedApplicants READ uncountedApplicants WRITE setUncountedApplicants NOTIFY uncountedApplicantsChanged FINAL)
};

#endif // MAGICHAT_H
