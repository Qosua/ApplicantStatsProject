#include "magichat.h"

MagicHat::MagicHat() {}

QList<Applicant> MagicHat::getApplicantsList() const
{
    return applicantsList;
}

void MagicHat::setApplicantsList(const QList<Applicant> &newApplicantsList)
{
    if (applicantsList == newApplicantsList)
        return;
    applicantsList = newApplicantsList;
    emit applicantsListChanged();
}
