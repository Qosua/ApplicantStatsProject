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
    
    QList<Applicant> uncountedApplicants() const;
    QList<FacultyCell> faculties() const;
    
    void printUncountedApplicants();
    void printStatsToConsole();
    void printToExcel();
    
    void setKCP(const QString& path, const QString& sheet);
    
signals:
    void applicantsListChanged();
    void uncountedApplicantsChanged();
    void facultiesChanged();
    
private:
    QList<Applicant> m_applicantsListCopy;
    QList<Applicant> m_applicantsList;
    QList<FacultyCell> m_facultyCells;
    QList<Applicant> m_uncountedApplicants;

    // Q_PROPERTY(QList<Applicant> applicantsList READ applicantsList NOTIFY applicantsListChanged FINAL)
    // Q_PROPERTY(QList<Applicant> uncountedApplicants READ uncountedApplicants NOTIFY uncountedApplicantsChanged FINAL)
    // Q_PROPERTY(QList<FacultyCell> faculties READ faculties NOTIFY facultiesChanged FINAL)
};

#endif // MAGICHAT_H
