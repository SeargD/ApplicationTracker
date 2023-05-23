
#ifndef APPLICATIONTACKERENUMS_H
#define APPLICATIONTACKERENUMS_H


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


}

#endif // APPLICATIONTACKERENUMS_H
