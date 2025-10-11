#ifndef TABLEPARSERMASTER_H
#define TABLEPARSERMASTER_H

#include <QList>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QHash>

#include "xlsx.h"
#include "applicant.h"
#include "tableparserbachelor.h"

class TableParserMaster {
    
public:
    TableParserMaster() = delete;
    TableParserMaster(const QString& tablePath, const QString& columnsNamesFilePath);
    ~TableParserMaster();
    
    void parseTable();
    QList<Applicant> getApplicants(ApplicantsFilterFlags flag, PrioritiesFlags priorityToDelete);
    
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

#endif // TABLEPARSERMASTER_H
