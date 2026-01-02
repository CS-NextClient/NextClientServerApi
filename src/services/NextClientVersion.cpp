#include "NextClientVersion.h"

NextClientVersion::NextClientVersion(size_t major, size_t minor, size_t patch) :
    major(major),
    minor(minor),
    patch(patch)
{
}

bool NextClientVersion::operator>(const NextClientVersion& other) const
{
    return Compare(other) > 0;
}

bool NextClientVersion::operator<(const NextClientVersion& other) const
{
    return Compare(other) < 0;
}

bool NextClientVersion::operator==(const NextClientVersion& other) const
{
    return Compare(other) == 0;
}

bool NextClientVersion::operator>=(const NextClientVersion& other) const
{
    return *this > other || *this == other;
}

bool NextClientVersion::operator<=(const NextClientVersion& other) const
{
    return *this < other || *this == other;
}

int NextClientVersion::Compare(const NextClientVersion& other) const
{
    if (major > other.major)
        return 1;
    if (major < other.major)
        return -1;

    if (minor > other.minor)
        return 1;
    if (minor < other.minor)
        return -1;

    if (patch > other.patch)
        return 1;
    if (patch < other.patch)
        return -1;

    return 0;
}
