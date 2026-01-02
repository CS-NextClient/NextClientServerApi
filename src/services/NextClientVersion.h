#pragma once
#include <cstddef>

struct NextClientVersion
{
    size_t major{};
    size_t minor{};
    size_t patch{};

    NextClientVersion(size_t major = 0, size_t minor = 0, size_t patch = 0);

    bool operator>(const NextClientVersion& other) const;
    bool operator<(const NextClientVersion& other) const;
    bool operator==(const NextClientVersion& other) const;
    bool operator>=(const NextClientVersion& other) const;
    bool operator<=(const NextClientVersion& other) const;

private:
    int Compare(const NextClientVersion& other) const;
};
