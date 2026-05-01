#ifndef APPLICANTSTATSPROJECT_STATSPAGEMODEL_H
#define APPLICANTSTATSPROJECT_STATSPAGEMODEL_H

#include <QAbstractListModel>
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

    struct DirectionInfo {
	QString directionName;
	StudyForm form;
	StudyType type;
	int directionSize;
	int directionCapacity;
	int score;
    };

    QString facultyName;
    int maxSumScore = 0;
    int minSumScore = 1000;
    int meanSumScore;
    QList<DirectionInfo> directions;
};

class StatsPageModel : public QAbstractListModel {
    Q_OBJECT
public:
    StatsPageModel();

    void setFaculties(std::shared_ptr<QList<FacultyDirection>> data);
    void processDataToDirectionStats(std::shared_ptr<QList<FacultyDirection>> data);
    FacultyStats getFacultyStats(std::shared_ptr<QList<FacultyDirection>> data);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QHash<QString, DirectionStats> directionStats;
};

#endif  // APPLICANTSTATSPROJECT_STATSPAGEMODEL_H
