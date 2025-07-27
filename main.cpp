#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QDebug>

#include "xlsx.h"
#include "tableparser.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // QQmlApplicationEngine engine;
    // const QUrl url(QStringLiteral("qrc:/ApplicantStatsProject/main.qml"));
    // QObject::connect(
    //     &engine,
    //     &QQmlApplicationEngine::objectCreated,
    //     &app,
    //     [url](QObject *obj, const QUrl &objUrl) {
    //         if (!obj && url == objUrl)
    //             QCoreApplication::exit(-1);
    //     },
    //     Qt::QueuedConnection);
    // engine.load(url);
    
    // QXlsx::Document doc("C:/Repos/Qt/ApplicantStatsProject/test.xlsx");
    // QString str = doc.read("A1").toString();
    
    // qDebug() << str;
    
    TableParser parser("C:/Repos/Qt/ApplicantStatsProject/test.xlsx",
                       "C:/Repos/Qt/ApplicantStatsProject/columnsNames.txt");
    parser.parseTable();
    
    auto list1 = parser.getApplicants();
    qDebug() << list1->size();
    
    auto list2 = parser.getApplicants(ApplicantsFilter::AdmissionsTrue);
    qDebug() << list2->size();
    
    auto list3 = parser.getApplicants(ApplicantsFilter::AdmissionsFalse);
    qDebug() << list3->size();

    return app.exec();
}





























