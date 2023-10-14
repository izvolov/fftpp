#include <fftpp/concept/subscriptable.hpp>

#include <doctest/doctest.h>

#include <cstdint>
#include <list>
#include <vector>

TEST_CASE("Pointer is subscriptable")
{
    CHECK(fftpp::subscriptable<int *>);
    CHECK(fftpp::subscriptable<int *>);
}

TEST_CASE("Iterator of vector is subscriptable")
{
    CHECK(fftpp::subscriptable<std::vector<int>::iterator>);
    CHECK(fftpp::subscriptable<std::vector<int>::const_iterator>);
}

TEST_CASE("Vector is subscriptable itself")
{
    CHECK(fftpp::subscriptable<std::vector<int>>);
    CHECK(fftpp::subscriptable<std::vector<int>>);
}

TEST_CASE("Iterator of list is not subscriptable")
{
    CHECK_FALSE(fftpp::subscriptable<std::list<int>::iterator>);
    CHECK_FALSE(fftpp::subscriptable<std::list<int>::const_iterator>);
}

struct SubscriptMe
{
    SubscriptMe & operator [] (std::ptrdiff_t)
    {
        return *this;
    }
};

TEST_CASE("Custom class with 'operator[]' is subscriptable")
{
    CHECK(fftpp::subscriptable<SubscriptMe>);
}

struct SubscriptMeConst
{
    const SubscriptMeConst & operator [] (std::ptrdiff_t) const
    {
        return *this;
    }
};

TEST_CASE("Custom class with 'operator[] const' is subscriptable")
{
    CHECK(fftpp::subscriptable<SubscriptMeConst>);
}

struct CallButNotSubscriptMe
{
    const CallButNotSubscriptMe & operator () (std::ptrdiff_t) const
    {
        return *this;
    }
};

TEST_CASE("Custom class without 'operator[]' is not subscriptable")
{
    CHECK_FALSE(fftpp::subscriptable<CallButNotSubscriptMe>);
}

