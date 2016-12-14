#include <cmath>
#include <sstream>
#include <string>
#include <type_traits>

#include <geo/standard_kernel.hpp>
#include <geo/vector.hpp>

#include <catch.hpp>
#define VECTOR_TEST_CASE(...) TEST_CASE("geo::vector - " __VA_ARGS__)

template<typename T, unsigned N>
using vector = geo::vector<geo::standard_kernel<T, N>>;

// Type requirements -----------------------------------------------------------

VECTOR_TEST_CASE("No padding")
{
    REQUIRE(sizeof(vector<float, 1>) == sizeof(float[1]));
    REQUIRE(sizeof(vector<float, 2>) == sizeof(float[2]));
    REQUIRE(sizeof(vector<float, 3>) == sizeof(float[3]));
    REQUIRE(sizeof(vector<float, 4>) == sizeof(float[4]));
    REQUIRE(sizeof(vector<float, 5>) == sizeof(float[5]));
    REQUIRE(sizeof(vector<float, 6>) == sizeof(float[6]));

    REQUIRE(sizeof(vector<double, 1>) == sizeof(double[1]));
    REQUIRE(sizeof(vector<double, 2>) == sizeof(double[2]));
    REQUIRE(sizeof(vector<double, 3>) == sizeof(double[3]));
    REQUIRE(sizeof(vector<double, 4>) == sizeof(double[4]));
    REQUIRE(sizeof(vector<double, 5>) == sizeof(double[5]));
    REQUIRE(sizeof(vector<double, 6>) == sizeof(double[6]));
}

VECTOR_TEST_CASE("Memcpyable")
{
    REQUIRE((std::is_trivially_copyable<vector<float, 1>>::value));
    REQUIRE((std::is_trivially_copyable<vector<float, 2>>::value));
    REQUIRE((std::is_trivially_copyable<vector<float, 3>>::value));
    REQUIRE((std::is_trivially_copyable<vector<float, 4>>::value));
    REQUIRE((std::is_trivially_copyable<vector<float, 5>>::value));
    REQUIRE((std::is_trivially_copyable<vector<float, 6>>::value));

    REQUIRE((std::is_trivially_copyable<vector<double, 1>>::value));
    REQUIRE((std::is_trivially_copyable<vector<double, 2>>::value));
    REQUIRE((std::is_trivially_copyable<vector<double, 3>>::value));
    REQUIRE((std::is_trivially_copyable<vector<double, 4>>::value));
    REQUIRE((std::is_trivially_copyable<vector<double, 5>>::value));
    REQUIRE((std::is_trivially_copyable<vector<double, 6>>::value));
}

// Creation --------------------------------------------------------------------

VECTOR_TEST_CASE("Construction by specifying components")
{
    SECTION("one-dimensional vector")
    {
        vector<double, 1> v {1.23};
        REQUIRE(v[0] == 1.23);
    }

    SECTION("two-dimensional vector")
    {
        vector<double, 2> v {1.2, 3.4};
        REQUIRE(v[0] == 1.2);
        REQUIRE(v[1] == 3.4);
    }

    SECTION("three-dimensional vector")
    {
        vector<double, 3> v {1.2, 3.4, 5.6};
        REQUIRE(v[0] == 1.2);
        REQUIRE(v[1] == 3.4);
        REQUIRE(v[2] == 5.6);
    }

    SECTION("four-dimensional vector")
    {
        vector<double, 4> v {1.2, 3.4, 5.6, 7.8};
        REQUIRE(v[0] == 1.2);
        REQUIRE(v[1] == 3.4);
        REQUIRE(v[2] == 5.6);
        REQUIRE(v[3] == 7.8);
    }

    SECTION("high-dimensional vector")
    {
        vector<double, 7> v7 {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
        vector<double, 8> v8 {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
        vector<double, 9> v9 {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
        (void) v7;
        (void) v8;
        (void) v9;
    }

    SECTION("copy-list-initialization")
    {
        vector<double, 3> v = {1.2, 3.4, 5.6};
        REQUIRE(v[0] == 1.2);
        REQUIRE(v[1] == 3.4);
        REQUIRE(v[2] == 5.6);
    }

    SECTION("constexpr")
    {
        constexpr vector<double, 3> v {1.2, 3.4, 5.6};
        REQUIRE(v[0] == 1.2);
        REQUIRE(v[1] == 3.4);
        REQUIRE(v[2] == 5.6);
    }
}

VECTOR_TEST_CASE("Zero")
{
    vector<double, 3> zero = vector<double, 3>::zero();
    REQUIRE(zero[0] == 0);
    REQUIRE(zero[1] == 0);
    REQUIRE(zero[2] == 0);
}

// Regularity ------------------------------------------------------------------

VECTOR_TEST_CASE("Default construction")
{
    SECTION("value is zero")
    {
        vector<double, 3> v;
        REQUIRE(v == (vector<double, 3>::zero()));
    }

    SECTION("constexpr")
    {
        constexpr vector<double, 3> v;
        REQUIRE(v == (vector<double, 3>::zero()));
    }
}

VECTOR_TEST_CASE("Copy construction")
{
    SECTION("copy holds the same value as the source")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> const v {u};
        REQUIRE(v[0] == 1.2);
        REQUIRE(v[1] == 3.4);
        REQUIRE(v[2] == 5.6);
    }
}

VECTOR_TEST_CASE("Copy assignment")
{
    SECTION("copy holds the same value as the source")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> v;
        v = u;
        REQUIRE(v[0] == 1.2);
        REQUIRE(v[1] == 3.4);
        REQUIRE(v[2] == 5.6);
    }

    SECTION("copy-list-assignment")
    {
        vector<double, 3> v;
        v = {1.2, 3.4, 5.6};
        REQUIRE(v[0] == 1.2);
        REQUIRE(v[1] == 3.4);
        REQUIRE(v[2] == 5.6);
    }
}

VECTOR_TEST_CASE("Equality comparison")
{
    SECTION("basic test")
    {
        vector<double, 3> const u {1, 2, 3};
        vector<double, 3> const v {4, 5, 6};
        REQUIRE(u == u);
        REQUIRE(u != v);
        REQUIRE(v != u);
        REQUIRE(v == v);
    }
}

// Element access --------------------------------------------------------------

VECTOR_TEST_CASE("Index operator")
{
    SECTION("mutable reference")
    {
        vector<double, 3> v {1.2, 3.4, 5.6};
        v[0] = 2.1;
        v[1] = 4.3;
        v[2] = 6.5;
        REQUIRE(v == (vector<double, 3> {2.1, 4.3, 6.5}));
    }

    SECTION("const reference")
    {
        vector<double, 3> const v {1.2, 3.4, 5.6};
        REQUIRE((std::is_same<decltype(v[0]), double const&>::value));
    }
}

VECTOR_TEST_CASE("Range access")
{
    SECTION("non-const iterator")
    {
        vector<double, 3> v {1.1, 2.2, 3.3};
        vector<double, 3>::iterator i = v.begin();
        vector<double, 3>::iterator j = v.end();
        // Manual iteration
        REQUIRE(i != j);
        REQUIRE(*i == 1.1);
        ++i;
        REQUIRE(i != j);
        REQUIRE(*i == 2.2);
        ++i;
        REQUIRE(i != j);
        REQUIRE(*i == 3.3);
        ++i;
        REQUIRE(i == j);
    }

    SECTION("const iterator")
    {
        vector<double, 3> const v {1.1, 2.2, 3.3};
        vector<double, 3>::const_iterator i = v.begin();
        vector<double, 3>::const_iterator j = v.end();
        REQUIRE(i == v.cbegin());
        REQUIRE(j == v.cend());
        // Manual iteration
        REQUIRE(i != j);
        REQUIRE(*i == 1.1);
        ++i;
        REQUIRE(i != j);
        REQUIRE(*i == 2.2);
        ++i;
        REQUIRE(i != j);
        REQUIRE(*i == 3.3);
        ++i;
        REQUIRE(i == j);
    }

    SECTION("iterator-to-const_iterator conversion")
    {
        vector<double, 3> v {1.1, 2.2, 3.3};
        vector<double, 3>::iterator i = v.begin();
        vector<double, 3>::const_iterator c = i;
        REQUIRE(c == v.cbegin());
    }

    SECTION("loop over mutable references")
    {
        vector<double, 3> v {1.1, 2.2, 3.3};
        for (double& e : v) {
            e *= 2;
        }
        REQUIRE(v[0] == Approx(2.2));
        REQUIRE(v[1] == Approx(4.4));
        REQUIRE(v[2] == Approx(6.6));
    }

    SECTION("loop over const references")
    {
        vector<double, 3> const v {1.1, 2.2, 3.3};
        for (double const& e : v) {
            (void) e;
        }
    }
}

// Linear operations -----------------------------------------------------------

VECTOR_TEST_CASE("Unary plus")
{
    SECTION("results in the same value")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> const v = +u;
        REQUIRE(u == v);
    }

    SECTION("returned value is a copy")
    {
        vector<double, 3> const v {1.2, 3.4, 5.6};
        [](auto const& a, auto const& b) {
            REQUIRE(&a != &b);
        }(+v, v);
    }
}

VECTOR_TEST_CASE("Unary minus")
{
    SECTION("results in the negated vector")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> const v = -u;
        REQUIRE(v[0] == -1.2);
        REQUIRE(v[1] == -3.4);
        REQUIRE(v[2] == -5.6);
    }
}

VECTOR_TEST_CASE("In-place addition")
{
    SECTION("results in the element-wise sum")
    {
        vector<double, 3> u {1.2, 3.4, 5.6};
        vector<double, 3> const v {0.1, 0.2, 0.3};
        u += v;
        REQUIRE(u[0] == Approx(1.3));
        REQUIRE(u[1] == Approx(3.6));
        REQUIRE(u[2] == Approx(5.9));
    }
}

VECTOR_TEST_CASE("In-place subtraction")
{
    SECTION("results in the element-wise difference")
    {
        vector<double, 3> u {1.2, 3.4, 5.6};
        vector<double, 3> const v {0.1, 0.2, 0.3};
        u -= v;
        REQUIRE(u[0] == Approx(1.1));
        REQUIRE(u[1] == Approx(3.2));
        REQUIRE(u[2] == Approx(5.3));
    }
}

VECTOR_TEST_CASE("In-place multiplication by scalar")
{
    SECTION("results in the element-wise product")
    {
        vector<double, 3> u {1.2, 3.4, 5.6};
        u *= 1.5;
        REQUIRE(u[0] == Approx(1.2 * 1.5));
        REQUIRE(u[1] == Approx(3.4 * 1.5));
        REQUIRE(u[2] == Approx(5.6 * 1.5));
    }
}

VECTOR_TEST_CASE("In-place division by scalar")
{
    SECTION("results in the element-wise quotient")
    {
        vector<double, 3> u {1.2, 3.4, 5.6};
        u /= 1.5;
        REQUIRE(u[0] == Approx(1.2 / 1.5));
        REQUIRE(u[1] == Approx(3.4 / 1.5));
        REQUIRE(u[2] == Approx(5.6 / 1.5));
    }
}

VECTOR_TEST_CASE("Addition")
{
    SECTION("results in the element-wise sum")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> const v {0.1, 0.2, 0.3};
        vector<double, 3> const w = u + v;
        REQUIRE(w[0] == Approx(1.3));
        REQUIRE(w[1] == Approx(3.6));
        REQUIRE(w[2] == Approx(5.9));
    }
}

VECTOR_TEST_CASE("Subtraction")
{
    SECTION("results in the element-wise difference")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> const v {0.1, 0.2, 0.3};
        vector<double, 3> const w = u - v;
        REQUIRE(w[0] == Approx(1.1));
        REQUIRE(w[1] == Approx(3.2));
        REQUIRE(w[2] == Approx(5.3));
    }
}

VECTOR_TEST_CASE("Multiplication by scalar")
{
    SECTION("from left -- results in the element-wise product")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> const v = 1.5 * u;
        REQUIRE(v[0] == Approx(1.2 * 1.5));
        REQUIRE(v[1] == Approx(3.4 * 1.5));
        REQUIRE(v[2] == Approx(5.6 * 1.5));
    }

    SECTION("from right -- results in the element-wise product")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> const v = u * 1.5;
        REQUIRE(v[0] == Approx(1.2 * 1.5));
        REQUIRE(v[1] == Approx(3.4 * 1.5));
        REQUIRE(v[2] == Approx(5.6 * 1.5));
    }
}

VECTOR_TEST_CASE("Division by scalar")
{
    SECTION("results in the element-wise quotient")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> const v = u / 1.5;
        REQUIRE(v[0] == Approx(1.2 / 1.5));
        REQUIRE(v[1] == Approx(3.4 / 1.5));
        REQUIRE(v[2] == Approx(5.6 / 1.5));
    }
}

// Metric ----------------------------------------------------------------------

VECTOR_TEST_CASE("Inner product")
{
    SECTION("is the sum of element-wise product")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        vector<double, 3> const v {2.1, 4.3, 6.5};
        double const uv = geo::inner_product(u, v);
        REQUIRE(uv == Approx(1.2 * 2.1 + 3.4 * 4.3 + 5.6 * 6.5));
    }

    SECTION("zero vector")
    {
        vector<double, 3> const u {1.2, 3.4, 5.6};
        REQUIRE(geo::inner_product(u, vector<double, 3>::zero()) == 0);
    }
}

VECTOR_TEST_CASE("Squared norm")
{
    SECTION("is inner product with itself")
    {
        vector<double, 3> const v {1.2, 3.4, 5.6};
        REQUIRE(geo::squared_norm(v) == Approx(geo::inner_product(v, v)));
    }
}

VECTOR_TEST_CASE("Norm")
{
    SECTION("is sqrt of inner product with itself")
    {
        vector<double, 3> const v {1.2, 3.4, 5.6};
        REQUIRE(geo::norm(v) == Approx(std::sqrt(geo::inner_product(v, v))));
    }
}

// Misc. operations ------------------------------------------------------------

VECTOR_TEST_CASE("Normalization")
{
    SECTION("norm gets unity")
    {
        vector<double, 3> const v {1.2, 3.4, 5.6};
        vector<double, 3> const n = geo::normalize(v);
        REQUIRE(geo::norm(n) == Approx(1));
    }

    SECTION("parallel to the original vector")
    {
        vector<double, 3> const v {1.2, 3.4, 5.6};
        vector<double, 3> const n = geo::normalize(v);
        vector<double, 3> const w = n * geo::norm(v);
        REQUIRE(w[0] == Approx(v[0]));
        REQUIRE(w[1] == Approx(v[1]));
        REQUIRE(w[2] == Approx(v[2]));
    }
}

// Input/output ----------------------------------------------------------------

VECTOR_TEST_CASE("Input")
{
    SECTION("basic example")
    {
        std::istringstream in {"  1.2  3.4  5.6  abc"};
        vector<double, 3> v;
        in >> v;
        std::string remain;
        std::getline(in, remain);
        REQUIRE(v == (vector<double, 3> {1.2, 3.4, 5.6}));
        REQUIRE(remain == "  abc");
    }
}

VECTOR_TEST_CASE("Output")
{
    SECTION("basic example")
    {
        std::ostringstream out;
        vector<double, 3> const v {1.2, 3.4, 5.6};
        out << v;
        REQUIRE(out.str() == "1.2 3.4 5.6");
    }
}

// Exotic kernel ---------------------------------------------------------------

namespace
{
    struct int_kernel
    {
        static constexpr unsigned dimension = 3;
        using scalar = int;
        using metric = double;
        static metric sqrt(metric x) noexcept { return std::sqrt(x); }
    };
}

VECTOR_TEST_CASE("Int kernel")
{
    SECTION("basic algebra")
    {
        geo::vector<int_kernel> const u {7, 5, 2};
        geo::vector<int_kernel> const v {1, 2, 3};
        geo::vector<int_kernel> const w = u + v;
        REQUIRE(w == (geo::vector<int_kernel> {8, 7, 5}));
    }

    SECTION("components are int, metric is double")
    {
        geo::vector<int_kernel> const v {1, 2, 3};
        int const& v0 = v[0];
        REQUIRE(v0 == 1);
        REQUIRE(geo::norm(v) == Approx(std::sqrt(14.0)));
    }
}
