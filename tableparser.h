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

enum ApplicantsFilterFlags {
    All              = 1 << 0,
    AdmissionsTrue   = 1 << 1,
    AdmissionsFalse  = 1 << 2,
};

class TableParser {
    
public:
    TableParser() = delete;
    TableParser(const QString& tablePath, const QString& columnsNamesFilePath);
    ~TableParser();
    
    void parseTable();
    QList<Applicant> getApplicants(ApplicantsFilterFlags flag);
    
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

#endif // TABLEPARSER_H
