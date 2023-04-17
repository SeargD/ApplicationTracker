
#ifndef APPLICATIONTACKERENUMS_H
#define APPLICATIONTACKERENUMS_H

#include "qtypes.h"
namespace  ApplicationTrackerEnums
{
enum class ApplicationStatus : quint8
{
    Applied,
    NoResponse,
    Rejected,
    FollowedUp,
    Interview,
    Offer
};
}

#endif // APPLICATIONTACKERENUMS_H
