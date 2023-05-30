
#ifndef APPLICATIONTACKERENUMS_H
#define APPLICATIONTACKERENUMS_H
#include <QtCore>

namespace  ApplicationTrackerEnums
{
enum ApplicationStatus : int
{
    Applied = 0,
    NoResponse = 1,
    Rejected = 2,
    FollowedUp = 3,
    Interview = 4,
    Offer = 5
};

enum Actions : int
{
    EmailRecruiter = 0,
    ArrangeInterview = 1,
    AttendInterview = 2,
    Wait = 3,
    ObtainFeedback = 4
};

static QString ReadAppStatus(int AppStatus)
{
    switch(AppStatus)
    {
    case ApplicationStatus::Applied:
        return QString("Applied");
    case ApplicationStatus::NoResponse:
        return QString("No Response");
    case ApplicationStatus::Rejected:
        return QString("Rejected");
    case ApplicationStatus::FollowedUp:
        return QString("Followed Up");
    case ApplicationStatus::Interview:
        return QString("Interview");
    case ApplicationStatus::Offer:
        return QString("Offer");
    default:
        return "";
    }
}

static QString ReadAction(int Action)
{
    switch(Action)
    {
    case Actions::EmailRecruiter:
        return QString("Email Recruiter");
    case Actions::ArrangeInterview:
        return QString("Arrange Interview");
    case Actions::AttendInterview:
        return QString("Attend Interview");
    case Actions::Wait:
        return QString("Wait");
    case Actions::ObtainFeedback:
        return QString("Obtain Feedback");
    default:
        return "";
    }
}
}

#endif // APPLICATIONTACKERENUMS_H
