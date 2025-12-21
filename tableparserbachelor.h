#ifndef TABLEPARSERBACHELOR_H
#define TABLEPARSERBACHELOR_H

#include <QList>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QHash>

#include "xlsx.h"
#include "applicantandfaculthy/applicant.h"
#include "namespaces.h"

class TableParserBachelor {
    
public:
    TableParserBachelor() = delete;
    TableParserBachelor(const QString& tablePath, const QString& columnsNamesFilePath);
    ~TableParserBachelor();
    
    void parseTable();
    QList<Applicant> getApplicants(ApplicantsFilterFlags flag, PriorityType infoFlag);
    
private:
    bool setColumnsNames();
    void printStatsToConsole() const;

    QString extractCode(const QString& str);
    QString extractName(const QString& str);
    QString extractStudyForm(const QString& str);
    QString extractType(const QString& str);
    
    QString m_tablePath;
    QString m_columnsNamesFilePath;
    
    QMap<QString, int> m_columnsNames;
    QXlsx::Document*   m_applicantsTable = nullptr;
    QList<Applicant>*  m_applicantsList = nullptr;
    
};

#endif // TABLEPARSERBACHELOR_H
