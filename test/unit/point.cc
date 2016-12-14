#include <cmath>
#include <cstring>
#include <type_traits>
#include <catch.hpp>

#include <geo/point.hpp>
#include <geo/standard_kernel.hpp>

template<typename T, unsigned N>
using point = geo::point<geo::standard_kernel<T, N>>;

template<typename T, unsigned N>
using vector = geo::vector<geo::standard_kernel<T, N>>;

// Type requirements -----------------------------------------------------------

TEST_CASE("geo::point - No padding")
{
    REQUIRE(sizeof(point<float, 1>) == sizeof(float[1]));
    REQUIRE(sizeof(point<float, 2>) == sizeof(float[2]));
    REQUIRE(sizeof(point<float, 3>) == sizeof(float[3]));
    REQUIRE(sizeof(point<float, 4>) == sizeof(float[4]));
    REQUIRE(sizeof(point<float, 5>) == sizeof(float[5]));
    REQUIRE(sizeof(point<float, 6>) == sizeof(float[6]));

    REQUIRE(sizeof(point<double, 1>) == sizeof(double[1]));
    REQUIRE(sizeof(point<double, 2>) == sizeof(double[2]));
    REQUIRE(sizeof(point<double, 3>) == sizeof(double[3]));
    REQUIRE(sizeof(point<double, 4>) == sizeof(double[4]));
    REQUIRE(sizeof(point<double, 5>) == sizeof(double[5]));
    REQUIRE(sizeof(point<double, 6>) == sizeof(double[6]));
}

TEST_CASE("geo::point - memcpy-able")
{
    REQUIRE((std::is_trivially_copyable<point<float, 1>>::value));
    REQUIRE((std::is_trivially_copyable<point<float, 2>>::value));
    REQUIRE((std::is_trivially_copyable<point<float, 3>>::value));
    REQUIRE((std::is_trivially_copyable<point<float, 4>>::value));
    REQUIRE((std::is_trivially_copyable<point<float, 5>>::value));
    REQUIRE((std::is_trivially_copyable<point<float, 6>>::value));

    REQUIRE((std::is_trivially_copyable<point<double, 1>>::value));
    REQUIRE((std::is_trivially_copyable<point<double, 2>>::value));
    REQUIRE((std::is_trivially_copyable<point<double, 3>>::value));
    REQUIRE((std::is_trivially_copyable<point<double, 4>>::value));
    REQUIRE((std::is_trivially_copyable<point<double, 5>>::value));
    REQUIRE((std::is_trivially_copyable<point<double, 6>>::value));
}

// Creation --------------------------------------------------------------------

TEST_CASE("geo::point - Default construction")
{
    point<double, 1> p1;
    REQUIRE(p1[0] == 0.0);

    point<double, 2> p2;
    REQUIRE(p2[0] == 0.0);
    REQUIRE(p2[1] == 0.0);

    point<double, 3> p3;
    REQUIRE(p3[0] == 0.0);
    REQUIRE(p3[1] == 0.0);
    REQUIRE(p3[2] == 0.0);
}

TEST_CASE("geo::point - Origin")
{
    point<double, 1> p1 = point<double, 1>::origin();
    REQUIRE(p1[0] == 0.0);

    point<double, 2> p2 = point<double, 2>::origin();
    REQUIRE(p2[0] == 0.0);
    REQUIRE(p2[1] == 0.0);

    point<double, 3> p3 = point<double, 3>::origin();
    REQUIRE(p3[0] == 0.0);
    REQUIRE(p3[1] == 0.0);
    REQUIRE(p3[2] == 0.0);
}

TEST_CASE("geo::point - Initialized to specific coordinates")
{
    point<double, 1> p1 {1.2};
    REQUIRE(p1[0] == 1.2);

    point<double, 2> p2 {1.2, 3.4};
    REQUIRE(p2[0] == 1.2);
    REQUIRE(p2[1] == 3.4);

    point<double, 3> p3 {1.2, 3.4, 5.6};
    REQUIRE(p3[0] == 1.2);
    REQUIRE(p3[1] == 3.4);
    REQUIRE(p3[2] == 5.6);

    point<double, 4> p4 {1.2, 3.4, 5.6, 7.8};
    REQUIRE(p4[0] == 1.2);
    REQUIRE(p4[1] == 3.4);
    REQUIRE(p4[2] == 5.6);
    REQUIRE(p4[3] == 7.8);

    point<double, 5> p5 {1.2, 3.4, 5.6, 7.8, 9.0};
    REQUIRE(p5[0] == 1.2);
    REQUIRE(p5[1] == 3.4);
    REQUIRE(p5[2] == 5.6);
    REQUIRE(p5[3] == 7.8);
    REQUIRE(p5[4] == 9.0);
}

TEST_CASE("geo::point - Copy construction")
{
    point<double, 4> p {1.2, 3.4, 5.6, 7.8};
    point<double, 4> q {p};
    REQUIRE(q[0] == 1.2);
    REQUIRE(q[1] == 3.4);
    REQUIRE(q[2] == 5.6);
    REQUIRE(q[3] == 7.8);
}

// Comparison operators --------------------------------------------------------

TEST_CASE("geo::point - Equality comparison")
{
    point<double, 1> const p1_a {12};
    point<double, 1> const p1_b {21};
    REQUIRE(p1_a == p1_a);
    REQUIRE(p1_a != p1_b);
    REQUIRE(p1_b != p1_a);
    REQUIRE(p1_b == p1_b);

    point<double, 2> const p2_a {12, 34};
    point<double, 2> const p2_b {43, 21};
    REQUIRE(p2_a == p2_a);
    REQUIRE(p2_a != p2_b);
    REQUIRE(p2_b != p2_a);
    REQUIRE(p2_b == p2_b);

    point<double, 3> const p3_a {12, 34, 56};
    point<double, 3> const p3_b {65, 43, 21};
    REQUIRE(p3_a == p3_a);
    REQUIRE(p3_a != p3_b);
    REQUIRE(p3_b != p3_a);
    REQUIRE(p3_b == p3_b);

    point<double, 4> const p4_a {12, 34, 56, 78};
    point<double, 4> const p4_b {87, 65, 43, 21};
    REQUIRE(p4_a == p4_a);
    REQUIRE(p4_a != p4_b);
    REQUIRE(p4_b != p4_a);
    REQUIRE(p4_b == p4_b);
}

// Assignment ------------------------------------------------------------------

TEST_CASE("geo::point - Copy assignment")
{
    point<double, 4> p {1.2, 3.4, 5.6, 7.8};
    point<double, 4> q;

    q = p;
    REQUIRE(q[0] == 1.2);
    REQUIRE(q[1] == 3.4);
    REQUIRE(q[2] == 5.6);
    REQUIRE(q[3] == 7.8);
}

TEST_CASE("geo::point - Assignment with list syntax")
{
    point<double, 1> p1;
    point<double, 2> p2;
    point<double, 3> p3;
    point<double, 4> p4;
    point<double, 7> p7;
    point<double, 9> p9;

    p1 = 1.2;
    REQUIRE(p1[0] == 1.2);

    p2 = {1.2, 3.4};
    REQUIRE(p2[0] == 1.2);
    REQUIRE(p2[1] == 3.4);

    p3 = {1.2, 3.4, 5.6};
    REQUIRE(p3[0] == 1.2);
    REQUIRE(p3[1] == 3.4);
    REQUIRE(p3[2] == 5.6);

    p4 = {1.2, 3.4, 5.6, 7.8};
    REQUIRE(p4[0] == 1.2);
    REQUIRE(p4[1] == 3.4);
    REQUIRE(p4[2] == 5.6);
    REQUIRE(p4[3] == 7.8);

    p7 = {1.2, 3.4, 5.6, 7.8, 9.0, 9.8, 7.6};
    REQUIRE(p7[0] == 1.2);
    REQUIRE(p7[1] == 3.4);
    REQUIRE(p7[2] == 5.6);
    REQUIRE(p7[3] == 7.8);
    REQUIRE(p7[4] == 9.0);
    REQUIRE(p7[5] == 9.8);
    REQUIRE(p7[6] == 7.6);

    p9 = {1.2, 3.4, 5.6, 7.8, 9.0, 9.8, 7.6, 5.4, 3.2};
    REQUIRE(p9[0] == 1.2);
    REQUIRE(p9[1] == 3.4);
    REQUIRE(p9[2] == 5.6);
    REQUIRE(p9[3] == 7.8);
    REQUIRE(p9[4] == 9.0);
    REQUIRE(p9[5] == 9.8);
    REQUIRE(p9[6] == 7.6);
    REQUIRE(p9[7] == 5.4);
    REQUIRE(p9[8] == 3.2);
}

// Element access --------------------------------------------------------------

TEST_CASE("geo::point - Element modification")
{
    point<double, 3> p {1.2, 3.4, 5.6};

    p[1] = 4.3;
    REQUIRE(p[0] == 1.2);
    REQUIRE(p[1] == 4.3);
    REQUIRE(p[2] == 5.6);
}

TEST_CASE("geo::point - Range access")
{
    point<double, 3> p {1.2, 3.4, 5.6};

    SECTION("iteration")
    {
        auto it = p.cbegin();
        REQUIRE(*it == 1.2);
        ++it;
        REQUIRE(*it == 3.4);
        ++it;
        REQUIRE(*it == 5.6);
        ++it;
        REQUIRE(it == p.cend());
    }

    SECTION("modification")
    {
        for (double& c : p) {
            c *= 2;
        }
        REQUIRE(p[0] == Approx(2.4));
        REQUIRE(p[1] == Approx(6.8));
        REQUIRE(p[2] == Approx(11.2));
    }
}

// Translation -----------------------------------------------------------------

TEST_CASE("geo::point - In-place translation")
{
    point<double, 3> p {1.2, 3.4, 5.6};

    SECTION("forward")
    {
        p += vector<double, 3> {2.0, -1.0, 3.0};
        REQUIRE(p[0] == Approx(3.2));
        REQUIRE(p[1] == Approx(2.4));
        REQUIRE(p[2] == Approx(8.6));
    }

    SECTION("backward")
    {
        p -= vector<double, 3> {2.0, -1.0, 3.0};
        REQUIRE(p[0] == Approx(-0.8));
        REQUIRE(p[1] == Approx(4.4));
        REQUIRE(p[2] == Approx(2.6));
    }
}

TEST_CASE("geo::point - Algebra")
{
    point<double, 3> const p {1.2, 3.4, 5.6};
    point<double, 3> const q {7.8, 9.0, 9.8};

    SECTION("point-point subtraction gives translation vector")
    {
        vector<double, 3> const u = q - p;
        REQUIRE(u[0] == Approx(6.6));
        REQUIRE(u[1] == Approx(5.6));
        REQUIRE(u[2] == Approx(4.2));
    }

    SECTION("translate point by adding vector")
    {
        vector<double, 3> const u {1.1, 2.2, 3.3};
        point<double, 3> const pu = p + u;
        REQUIRE(pu[0] == Approx(2.3));
        REQUIRE(pu[1] == Approx(5.6));
        REQUIRE(pu[2] == Approx(8.9));
    }

    SECTION("translate point by subtracting vector")
    {
        vector<double, 3> const u {1.1, 2.2, 3.3};
        point<double, 3> const pu = p - u;
        REQUIRE(pu[0] == Approx(0.1));
        REQUIRE(pu[1] == Approx(1.2));
        REQUIRE(pu[2] == Approx(2.3));
    }
}

// Distance calculation --------------------------------------------------------

TEST_CASE("geo::point - Distance calculation")
{
    point<double, 3> const p {1.2, 3.4, 5.6};
    point<double, 3> const q {2.2, 1.1, 3.3};

    SECTION("distinct points")
    {
        double const expect = std::sqrt(1.0 * 1.0
                                      + 2.3 * 2.3
                                      + 2.3 * 2.3);
        REQUIRE(geo::distance(p, q) == Approx(expect));
        REQUIRE(geo::squared_distance(p, q) == Approx(expect * expect));
    }

    SECTION("distance between same points must be zero")
    {
        REQUIRE(geo::distance(p, p) == 0.0);
        REQUIRE(geo::squared_distance(p, p) == 0.0);
    }
}

// Memcpy ----------------------------------------------------------------------

TEST_CASE("geo::point - memcpying single object")
{
    double coords[3] {1.2, 3.4, 5.6};
    point<double, 3> p;
    REQUIRE(sizeof coords == sizeof p);

    SECTION("read in")
    {
        std::memcpy(&p, coords, sizeof p);
        REQUIRE(p[0] == coords[0]);
        REQUIRE(p[1] == coords[1]);
        REQUIRE(p[2] == coords[2]);
    }

    SECTION("write out")
    {
        p = {5.4, 3.2, 1.0};
        std::memcpy(coords, &p, sizeof p);
        REQUIRE(coords[0] == p[0]);
        REQUIRE(coords[1] == p[1]);
        REQUIRE(coords[2] == p[2]);
    }
}

TEST_CASE("geo::point - memcpying array")
{
    double coords[2][3];
    point<double, 3> points[2];
    REQUIRE(sizeof coords == sizeof points);

    SECTION("read in")
    {
        coords[0][0] = 1.2; coords[0][1] = 3.4; coords[0][2] = 5.6;
        coords[1][0] = 7.8; coords[1][1] = 9.0; coords[1][2] = 9.8;
        std::memcpy(points, coords, sizeof points);
        REQUIRE(points[0] == (point<double, 3> {1.2, 3.4, 5.6}));
        REQUIRE(points[1] == (point<double, 3> {7.8, 9.0, 9.8}));
    }

    SECTION("write out")
    {
        points[0] = {0.1, 2.3, 4.5};
        points[1] = {6.7, 8.9, 0.9};
        std::memcpy(coords, points, sizeof points);
        REQUIRE(coords[0][0] == 0.1);
        REQUIRE(coords[0][1] == 2.3);
        REQUIRE(coords[0][2] == 4.5);
        REQUIRE(coords[1][0] == 6.7);
        REQUIRE(coords[1][1] == 8.9);
        REQUIRE(coords[1][2] == 0.9);
    }
}

// Exotic kernel ---------------------------------------------------------------

struct lattice_kernel
{
    static constexpr unsigned dimension = 2;
    using scalar = int;
    using metric = double;
    static metric sqrt(metric x) { return std::sqrt(x); }
};

TEST_CASE("geo::point - Int kernel")
{
    geo::point<lattice_kernel> const p {1, 2};
    geo::point<lattice_kernel> const q {3, 0};

    SECTION("integral displacement")
    {
        REQUIRE(p - q == (geo::vector<lattice_kernel> {-2, 2}));
    }

    SECTION("floating-point distance")
    {
        REQUIRE(squared_distance(p, q) == 8.0);
        REQUIRE(distance(p, q) == Approx(2 * M_SQRT2));
    }
}
