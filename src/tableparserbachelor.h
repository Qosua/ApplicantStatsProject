#ifndef TABLEPARSERBACHELOR_H
#define TABLEPARSERBACHELOR_H

#include <QList>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QHash>

#include "src/xlsx.h"
#include "src/applicant.h"
#include "src/namespaces.h"

class TableParserBachelor {
    
public:
    TableParserBachelor();
    ~TableParserBachelor();
    
    void setTablePath(const QString& path);
    void setColumnsNamesPath(const QString& path);
    
    void parseTable();
    QList<Applicant>* getApplicants(ApplicantsFilterFlags flag, StudyType infoFlag);
    
private:
    bool setColumnsNames();
    void printStatsToConsole() const;

    QString extractCode(const QString& str);
    QString extractName(const QString& str);
    StudyForm extractStudyForm(const QString& str);
    StudyType extractType(const QString& str);
    
    QString m_tablePath;
    QString m_columnsNamesFilePath;
    
    QMap<QString, int> m_columnsNames;
    QXlsx::Document*   m_applicantsTable = nullptr;
    QList<Applicant>*  m_applicantsList  = nullptr;
    
};

#endif // TABLEPARSERBACHELOR_H
