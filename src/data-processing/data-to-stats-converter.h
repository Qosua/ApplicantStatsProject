#ifndef APPLICANTSTATSPROJECT_DATATOSTATSCONVERTER_H
#define APPLICANTSTATSPROJECT_DATATOSTATSCONVERTER_H

#include <QHash>
#include <memory>

#include "../applicants-faculty-data/faculty-direction.h"

struct DirectionStats {
    QString name;
    QString facultyName;
    StudyForm form;
    StudyType type;
    QList<QPair<PriorityInfo, Applicant>> applicants;
    QHash<int, int> scoreDistribution;  // <score, score count>
    int size;
    int capacity;
    int maxSumScore = 0;
    int minSumScore = 1000;
    int meanSumScore;
};

struct FacultyStats {
    QString facultyName;
    int maxSumScore = 0;
    int minSumScore = 1000;
    int meanSumScore;
};

class DataToStatsConverter : public QObject {
    Q_OBJECT
public:
    DataToStatsConverter(QObject* parent = nullptr);

    void getData(std::shared_ptr<QList<FacultyDirection>> data);

signals:
    void sendStats();

private:
    FacultyStats facultyStats;
};

#endif  // APPLICANTSTATSPROJECT_DATATOSTATSCONVERTER_H
