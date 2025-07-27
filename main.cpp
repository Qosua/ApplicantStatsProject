#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>
#include <QDebug>

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
    
    QList<Applicant> list1 = parser.getApplicants(ApplicantsFilterFlags::All);
    qDebug() << list1.size();

    return app.exec();
}





























