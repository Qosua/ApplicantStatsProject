#include "data-to-stats-converter.h"

DataToStatsConverter::DataToStatsConverter(QObject* parent) : QObject(parent) {}

void DataToStatsConverter::getData(std::shared_ptr<QList<FacultyDirection>> data) {

    if (data == nullptr)
	return;

    QHash<QString, QList<DirectionStats>> directions;
    QHash<QString, FacultyStats> faculties;

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

    for (const auto& facultyName : directions.keys()) {

	FacultyStats facultyStats;
	facultyStats.facultyName = facultyName;

	int scoreSum = 0;
	int studentsCount = 0;

	for (const auto& direction : directions[facultyName]) {

	    facultyStats.maxSumScore = std::max(facultyStats.maxSumScore, direction.maxSumScore);
	    facultyStats.minSumScore = std::min(facultyStats.minSumScore, direction.minSumScore);
	    facultyStats.directions.push_back({
	        .directionName = direction.name,
	        .form = direction.form,
	        .type = direction.type,
	        .directionSize = direction.size,
	        .directionCapacity = direction.capacity,
	        .score = ((direction.size == direction.capacity and direction.applicants.size())
	                      ? direction.applicants.first().first.egeScore()
	                      : -1),
	    });

	    for (const auto& elem : direction.applicants) {
		scoreSum += elem.first.egeScore();
		studentsCount += 1;
	    }
	}

	if (studentsCount != 0)
	    facultyStats.meanSumScore = scoreSum / studentsCount;

	faculties[facultyName] = facultyStats;
    }

    int a = 0;
}
