#include <type_traits>
#include <catch.hpp>

#include <geo/point.hpp>
#include <geo/standard_kernel.hpp>


template<typename T, unsigned N>
using point = geo::point<geo::standard_kernel<T, N>>;


// Type requirements -----------------------------------------------------------

TEST_CASE("geo::point - No padding")
{
    CHECK(sizeof(point<float, 1>) == sizeof(float[1]));
    CHECK(sizeof(point<float, 2>) == sizeof(float[2]));
    CHECK(sizeof(point<float, 3>) == sizeof(float[3]));
    CHECK(sizeof(point<float, 4>) == sizeof(float[4]));
    CHECK(sizeof(point<float, 5>) == sizeof(float[5]));
    CHECK(sizeof(point<float, 6>) == sizeof(float[6]));

    CHECK(sizeof(point<double, 1>) == sizeof(double[1]));
    CHECK(sizeof(point<double, 2>) == sizeof(double[2]));
    CHECK(sizeof(point<double, 3>) == sizeof(double[3]));
    CHECK(sizeof(point<double, 4>) == sizeof(double[4]));
    CHECK(sizeof(point<double, 5>) == sizeof(double[5]));
    CHECK(sizeof(point<double, 6>) == sizeof(double[6]));
}

TEST_CASE("geo::point - memcpy-able")
{
    CHECK((std::is_trivially_copyable<point<float, 1>>::value));
    CHECK((std::is_trivially_copyable<point<float, 2>>::value));
    CHECK((std::is_trivially_copyable<point<float, 3>>::value));
    CHECK((std::is_trivially_copyable<point<float, 4>>::value));
    CHECK((std::is_trivially_copyable<point<float, 5>>::value));
    CHECK((std::is_trivially_copyable<point<float, 6>>::value));

    CHECK((std::is_trivially_copyable<point<double, 1>>::value));
    CHECK((std::is_trivially_copyable<point<double, 2>>::value));
    CHECK((std::is_trivially_copyable<point<double, 3>>::value));
    CHECK((std::is_trivially_copyable<point<double, 4>>::value));
    CHECK((std::is_trivially_copyable<point<double, 5>>::value));
    CHECK((std::is_trivially_copyable<point<double, 6>>::value));
}

// Equality --------------------------------------------------------------------

TEST_CASE("geo::point - Equality comparison")
{
    point<double, 1> const p1_a {12};
    point<double, 1> const p1_b {21};
    CHECK(p1_a == p1_a);
    CHECK(p1_a != p1_b);
    CHECK(p1_b != p1_a);
    CHECK(p1_b == p1_b);

    point<double, 2> const p2_a {12, 34};
    point<double, 2> const p2_b {43, 21};
    CHECK(p2_a == p2_a);
    CHECK(p2_a != p2_b);
    CHECK(p2_b != p2_a);
    CHECK(p2_b == p2_b);

    point<double, 3> const p3_a {12, 34, 56};
    point<double, 3> const p3_b {65, 43, 21};
    CHECK(p3_a == p3_a);
    CHECK(p3_a != p3_b);
    CHECK(p3_b != p3_a);
    CHECK(p3_b == p3_b);

    point<double, 4> const p4_a {12, 34, 56, 78};
    point<double, 4> const p4_b {87, 65, 43, 21};
    CHECK(p4_a == p4_a);
    CHECK(p4_a != p4_b);
    CHECK(p4_b != p4_a);
    CHECK(p4_b == p4_b);
}
