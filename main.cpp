#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QDebug>
#include <QApplication>

#include "tableparser.h"
#include "magichat.h"
#include "facultycell.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    TableParser parser("C:/Repos/Qt/ApplicantStatsProject/Выгрузка все 05.08 1230.xlsx",
                       "C:/Repos/Qt/ApplicantStatsProject/columnsNames.txt");
    parser.parseTable();
    
    QList<Applicant> list1 = parser.getApplicants(ApplicantsFilterFlags::AdmissionsTrue);
    
    for(int i = 0; i < list1.size(); ++i)
        list1[i].deletePriority(PrioritiesFlags::NonBudget);
    
    
    MagicHat magicHat;
    magicHat.setApplicantsList(list1);
    
    magicHat.startPriorityRoundSimulation();
    magicHat.rebalanceBudgetaryPlaces();
    magicHat.startGeneralRoundSimulation();

    // magicHat.printStatsToConsole();
    // magicHat.printUncountedApplicants();
    // magicHat.printToExcel();
    //magicHat.printFaculties();


    return app.exec();
}





























