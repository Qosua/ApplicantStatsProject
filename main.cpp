#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QFile>
#include <QStyleFactory>

#include "tableparsermaster.h"
#include "magichat.h"
#include "facultycell.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("windows11"));
    
    TableParserBachelor parserBachelor("C:/Repos/Qt/ApplicantStatsProject/data/Выгрузка все 05.08 1230.xlsx",
                                        ":/programInfo/columnsNames.txt");
    parserBachelor.parseTable();
    QList<Applicant> list1 = parserBachelor.getApplicants(ApplicantsFilterFlags::AdmissionsTrue,
                                                          PriorityType::NonBudget);
    
    MagicHat magicHatBachelor;
    magicHatBachelor.setKCP(":/programInfo/KCP.xlsx", "Бакалавры");
    magicHatBachelor.setApplicantsList(list1);
    
    magicHatBachelor.startPriorityRoundSimulation();
    magicHatBachelor.rebalanceBudgetaryPlaces();
    magicHatBachelor.startGeneralRoundSimulation();

    magicHatBachelor.printStatsToConsole();
    magicHatBachelor.printUncountedApplicants();
    
    /*
    TableParserMaster parserMaster("C:/Repos/Qt/ApplicantStatsProject/Выгрузка маги 09.08.xlsx",
                                    ":/programInfo/columnsNames.txt");
    parserMaster.parseTable();
    QList<Applicant> list11 = parserMaster.getApplicants(ApplicantsFilterFlags::All);
    QList<Applicant> list1 = parserBachelor.getApplicants(ApplicantsFilterFlags::AdmissionsTrue,
                                                          PrioritiesFlags::NonBudget);
    
    qDebug() << list11.size() << list1.size();
    
    MagicHat magicHatMaster;
    magicHatMaster.setKCP(":/programInfo/kcpMasters.txt");
    magicHatMaster.setApplicantsList(list1);
    
    magicHatMaster.startPriorityRoundSimulation();
    magicHatMaster.rebalanceBudgetaryPlaces();
    magicHatMaster.startGeneralRoundSimulation();
    
    magicHatMaster.printStatsToConsole();
    magicHatMaster.printUncountedApplicants();
    */
    
    MainWindow mainWindow;
    mainWindow.setMathStatistics(magicHatBachelor.uncountedApplicants(),magicHatBachelor.faculties());
    mainWindow.show();

    return app.exec();
}





























