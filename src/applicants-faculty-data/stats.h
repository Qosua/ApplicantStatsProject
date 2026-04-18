#ifndef APPLICANTSTATSPROJECT_STATS_H
#define APPLICANTSTATSPROJECT_STATS_H

#include <QList>
#include <QObject>

#include "applicant.h"

struct Stats {
    QString facultyName;
    QString directionName;
    int maxScore = 0;
    int minScore = 0;
    int applicantsCount = 0;
    int applicantsCapacity = 0;
    double meanScore = 0;
    QList<QPair<PriorityInfo, Applicant>> applicants;
};

#endif  // APPLICANTSTATSPROJECT_STATS_H
