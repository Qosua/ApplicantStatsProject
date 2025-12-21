#ifndef NAMESPACES_H
#define NAMESPACES_H

enum ApplicantsFilterFlags {
    All              = 1 << 0, //Take all admissions from applicants
    AdmissionsTrue   = 1 << 1, //Take applicants only with accepted admissions
    AdmissionsFalse  = 1 << 2, //Take applicants only with denied admissions
};

enum PriorityType {
    NonBudget      = 1 << 3,
    Budget         = 1 << 4,
    SpecialRight   = 1 << 5,
    Kvot           = 1 << 6,
    CompanySponsor = 1 << 7,
};

#endif // NAMESPACES_H
