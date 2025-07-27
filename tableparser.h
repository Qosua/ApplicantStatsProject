#ifndef TABLEPARSER_H
#define TABLEPARSER_H

#include <QList>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QHash>

#include "xlsx.h"
#include "applicant.h"

enum ApplicantsFilter {
    All,
    AdmissionsTrue,
    AdmissionsFalse,
    NoNonBudget,
    NoBudget,
    NoSpecialRight,
    NoKvot,
    NoCompanySponsor,
};

class TableParser {
    
public:
    TableParser() = delete;
    TableParser(const QString& tablePath, const QString& columnsNamesFilePath);
    ~TableParser();
    
    void parseTable();
    QList<Applicant>* getApplicants(ApplicantsFilter stats = ApplicantsFilter::All);
    
private:
    
    bool setColumnsNames();
    void printStatsToConsole();
    
    QMap<QString, int> m_columnsNames;
    QString m_tablePath;
    QString m_columnsNamesFilePath;
    QXlsx::Document* m_doc = nullptr;
    QList<Applicant>* m_applicants = nullptr;
    
};

#endif // TABLEPARSER_H

// ///////////////////TEMP/////////////////
// QString str = m_doc->read(i, m_columnsNames["Конкурсная группа"]).toString();
// if(str.contains("Внебюджет"))
//     continue;
// ///////////////////TEMP/////////////////
