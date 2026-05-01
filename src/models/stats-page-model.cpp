#include "stats-page-model.h"

StatsPageModel::StatsPageModel() {}

void StatsPageModel::setFaculties(std::shared_ptr<QList<FacultyDirection>> data) {}

void StatsPageModel::processDataToDirectionStats(std::shared_ptr<QList<FacultyDirection>> data) {

    if (data == nullptr)
	return;

    QHash<QString, QList<DirectionStats>> directions;

    for (const auto& direction : *data) {

	DirectionStats directionStats;
	directionStats.name = direction.name();
	directionStats.facultyName = direction.division();
	directionStats.form = direction.studyForm();
	directionStats.type = direction.studyType();
	directionStats.applicants = direction.pool();
	directionStats.size = direction.pool().size();
	directionStats.capacity = direction.capacity();

	for (int i = 100; i <= 310; i += 10) directionStats.scoreDistribution[i] = 0;

	int meanSumScore = 0;

	for (const auto& elem : directionStats.applicants) {
	    directionStats.maxSumScore
	        = std::max(directionStats.maxSumScore, elem.first.egeScore());

	    directionStats.minSumScore
	        = std::min(directionStats.minSumScore, elem.first.egeScore());

	    meanSumScore += elem.first.egeScore();

	    directionStats.scoreDistribution[(elem.first.egeScore() / 10) * 10] += 1;
	}

	if (directionStats.size != 0)
	    directionStats.meanSumScore = meanSumScore / directionStats.size;

	directions[directionStats.facultyName].append(directionStats);
    }
}

FacultyStats StatsPageModel::getFacultyStats(std::shared_ptr<QList<FacultyDirection>> data) {}

int StatsPageModel::rowCount(const QModelIndex& parent) const {}

QVariant StatsPageModel::data(const QModelIndex& parent, int role) const {}

QHash<int, QByteArray> StatsPageModel::roleNames() const { return QAbstractListModel::roleNames(); }