#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QDebug>

#include "tableparser.h"
#include "magichat.h"
#include "facultycell.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    /*
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/ApplicantStatsProject/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app,[url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            },
        Qt::QueuedConnection);

    engine.load(url);
    */
    
    TableParser parser("C:/Repos/Qt/ApplicantStatsProject/Выгрузка все 31.07 вечер.xlsx",
                       "C:/Repos/Qt/ApplicantStatsProject/columnsNames.txt");
    parser.parseTable();
    
    QList<Applicant> list1 = parser.getApplicants(ApplicantsFilterFlags::AdmissionsTrue);
    qDebug() << list1.size();

    
    for(int i = 0; i < list1.size(); ++i) 
        list1[i].deletePriority(PrioritiesFlags::NonBudget);
    
    
    MagicHat magicHat;
    magicHat.setApplicantsList(list1);

    //magicHat.printFacultiesNames();
    //magicHat.printFaculties();
    
    magicHat.startPriorityRoundSimulation();
    magicHat.rebalanceBudgetaryPlaces();
    magicHat.startGeneralRoundSimulation();

    magicHat.printStatsToConsole();
    magicHat.printUncountedApplicants();

    return app.exec();
}





























