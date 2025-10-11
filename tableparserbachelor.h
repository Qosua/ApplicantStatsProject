#ifndef TABLEPARSERBACHELOR_H
#define TABLEPARSERBACHELOR_H

#include <QList>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QHash>

#include "xlsx.h"
#include "applicant.h"

enum ApplicantsFilterFlags {
    All              = 1 << 0,
    AdmissionsTrue   = 1 << 1,
    AdmissionsFalse  = 1 << 2,
};

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
    
    QMap<QString, int> m_columnsNames;
    QString m_tablePath;
    QString m_columnsNamesFilePath;
    QXlsx::Document* m_doc = nullptr;
    QList<Applicant>* m_applicants = nullptr;
    
};

#endif // TABLEPARSERBACHELOR_H
