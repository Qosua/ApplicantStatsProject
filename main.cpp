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
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
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
    
    /*
    for(auto& elem : list1) {
        
        for(int i = 0; i < elem.priorities().size(); ++i){
            
            for(int j = i + 1; j < elem.priorities().size(); ++j){
                
                if((elem.priorities()[i].priorityNumber() == elem.priorities()[j].priorityNumber())
                    and
                    (elem.priorities()[i].type() == "Целевое" or
                     elem.priorities()[i].type() == "Особое право" or
                     elem.priorities()[i].type() == "Отдельная квота")
                    and
                    (elem.priorities()[j].type() == "Целевое" or
                     elem.priorities()[j].type() == "Особое право" or
                     elem.priorities()[j].type() == "Отдельная квота"))
                    qDebug() << elem.id() << " | ";
                
            }
        }
    }
    */
    
    /*
    for(auto& elem : list1) {
        
        for(int i = 0; i < elem.priorities().size(); ++i){
            
            for(int j = i + 1; j < elem.priorities().size(); ++j){
                
                if((elem.priorities()[i].priorityNumber() < elem.priorities()[j].priorityNumber())
                    and
                    (elem.priorities()[i].type() == "Бюджет" or
                     elem.priorities()[i].type() == "Внебюджет")
                    and
                    (elem.priorities()[j].type() == "Целевое" or
                     elem.priorities()[j].type() == "Особое право" or
                     elem.priorities()[j].type() == "Отдельная квота"))
                    qDebug() << elem.id() << " | ";
                
            }
        }
    }
    */
    
    
    MagicHat magicHat;
    magicHat.setApplicantsList(list1);

    //magicHat.printFacultiesNames();

    //magicHat.printFaculties();
    magicHat.startPriorityRoundSimulation();
    magicHat.rebalanceBudgetaryPlaces();
    magicHat.startGeneralRoundSimulation();

    magicHat.printStatsToConsole();

    //magicHat.printFaculties();

    return app.exec();
}





























