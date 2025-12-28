#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QStyleFactory>

#include "src/magichat.h"
#include "src/facultycell.h"
#include "src/mainwindow.h"
#include "src/tableparserbachelor.h"
#include "src/supportsystem.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("windows11"));
    
    SupportSystem supportSystem;
    supportSystem.initSystem();
    
    TableParserBachelor parserBachelor;
    MagicHat magicHatBachelor;
    MainWindow mainWindow;
    QList<Applicant>* applicantsList;
    
    /*
    parserBachelor.setTablePath(":/data/maintable.xlsx");
    parserBachelor.setColumnsNamesPath(":/settings/columnsNames.xlsx");
    parserBachelor.parseTable();
    
    applicantsList = parserBachelor.getApplicants(ApplicantsFilterFlags::AdmissionsTrue,
                                                                   StudyType::NonBudget);
    
    magicHatBachelor.setKCP(":/settings/KCP.xlsx", "Бакалавры");
    magicHatBachelor.setApplicantsList(applicantsList);
    
    magicHatBachelor.startPriorityRoundSimulation();
    magicHatBachelor.rebalanceBudgetaryPlaces();
    magicHatBachelor.startGeneralRoundSimulation();

    magicHatBachelor.printStatsToConsole();
    magicHatBachelor.printUncountedApplicants();
    
    QList<FacultyCell> faculties = magicHatBachelor.faculties();
    QList<Applicant>   uncountedApplicants = magicHatBachelor.uncountedApplicants();
    
    
    TableParserMaster parserMaster("C:/Repos/Qt/ApplicantStatsProject/Выгрузка маги 09.08.xlsx",
                                    ":/settings/columnsNames.txt");
    parserMaster.parseTable();
    QList<Applicant> list11 = parserMaster.getApplicants(ApplicantsFilterFlags::All);
    QList<Applicant> list1 = parserBachelor.getApplicants(ApplicantsFilterFlags::AdmissionsTrue,
                                                          PrioritiesFlags::NonBudget);
    
    qDebug() << list11.size() << list1.size();
    
    MagicHat magicHatMaster;
    magicHatMaster.setKCP(":/settings/kcpMasters.txt");
    magicHatMaster.setApplicantsList(list1);
    
    magicHatMaster.startPriorityRoundSimulation();
    magicHatMaster.rebalanceBudgetaryPlaces();
    magicHatMaster.startGeneralRoundSimulation();
    
    magicHatMaster.printStatsToConsole();
    magicHatMaster.printUncountedApplicants();
    
    mainWindow.setFaculties(faculties);
    */
    
    mainWindow.show();

    return app.exec();
}





























