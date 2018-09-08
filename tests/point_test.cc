// Copyright snsinfu 2018.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>
#include <type_traits>

#include "catch.hpp"
#include "../include/geo.hpp"


TEST_CASE("point - exposes scalar_type")
{
    CHECK(std::is_same<geo::point<float, 3>::scalar_type, float>::value);
    CHECK(std::is_same<geo::point<double, 3>::scalar_type, double>::value);
}

TEST_CASE("point - exposes vector_type")
{
    CHECK(std::is_same<geo::point<float, 3>::vector_type, geo::vector<float, 3>>::value);
    CHECK(std::is_same<geo::point<double, 3>::vector_type, geo::vector<double, 3>>::value);
}

TEST_CASE("point - exposes constexpr dimension")
{
    constexpr auto dim = geo::point<double, 3>::dimension;
    CHECK(dim == 3);
}

TEST_CASE("point - is default constructible")
{
    geo::point<double, 3> point;
    CHECK(point[0] == 0);
    CHECK(point[1] == 0);
    CHECK(point[2] == 0);
}

TEST_CASE("point - is constructible from coordinate values")
{
    geo::point<double, 3> point = {1.2, 3.4, 5.6};
    CHECK(point[0] == 1.2);
    CHECK(point[1] == 3.4);
    CHECK(point[2] == 5.6);
}

TEST_CASE("point - is copy constructible")
{
    geo::point<double, 3> point = {1.2, 3.4, 5.6};
    geo::point<double, 3> copy = point;
    CHECK(copy[0] == 1.2);
    CHECK(copy[1] == 3.4);
    CHECK(copy[2] == 5.6);
}

TEST_CASE("point::vector - returns coordinate vector")
{
    geo::point<double, 3> const point = {1.2, 3.4, 5.6};
    geo::vector<double, 3> const vector = point.vector();
    CHECK(vector[0] == 1.2);
    CHECK(vector[1] == 3.4);
    CHECK(vector[2] == 5.6);
}

TEST_CASE("point - supports inplace translation by vector")
{
    geo::point<double, 3> point;
    point += geo::vector<double, 3> {1.2, 3.4, 5.6};
    CHECK(point[0] == 1.2);
    CHECK(point[1] == 3.4);
    CHECK(point[2] == 5.6);
}

TEST_CASE("point - supports inplace translation by negated vector")
{
    geo::point<double, 3> point;
    point -= geo::vector<double, 3> {1.2, 3.4, 5.6};
    CHECK(point[0] == -1.2);
    CHECK(point[1] == -3.4);
    CHECK(point[2] == -5.6);
}

TEST_CASE("point::squared_distance - returns the squared Euclidean distance to a point")
{
    geo::point<double, 2> const point = {-2, 3};
    CHECK(point.squared_distance({1, -1}) == Approx(25.0));
}

TEST_CASE("point::distance - returns the Euclidean distance to a point")
{
    geo::point<double, 2> const point = {-2, 3};
    CHECK(point.distance({1, -1}) == Approx(5.0));
}

TEST_CASE("point - supports translation by addition")
{
    geo::point<double, 2> const point = {1, 2};
    geo::vector<double, 2> const vector = {3, 4};
    geo::point<double, 2> const sum = point + vector;
    CHECK(sum[0] == 4);
    CHECK(sum[1] == 6);
}

TEST_CASE("point - supports translation by subtraction")
{
    geo::point<double, 2> const point = {1, 2};
    geo::vector<double, 2> const vector = {4, 3};
    geo::point<double, 2> const diff = point - vector;
    CHECK(diff[0] == -3);
    CHECK(diff[1] == -1);
}

TEST_CASE("point - implements ostream output operator")
{
    geo::point<double, 4> const p1 = {1, 2, 3, 4};
    geo::point<double, 3> const p2 = {5, 6, 7};
    std::stringstream stream;
    stream << p1 << '\n' << p2;
    CHECK(stream.str() == "1 2 3 4\n5 6 7");
}

TEST_CASE("point - implements istream input operator")
{
    geo::point<double, 4> p1;
    geo::point<double, 3> p2;
    std::stringstream stream{"1 2 3 4\n5 6 7"};
    stream >> p1 >> p2;
    CHECK(p1[0] == 1);
    CHECK(p1[1] == 2);
    CHECK(p1[2] == 3);
    CHECK(p1[3] == 4);
    CHECK(p2[0] == 5);
    CHECK(p2[1] == 6);
    CHECK(p2[2] == 7);
}

TEST_CASE("squared_distance - returns the squared Euclidean distance between points")
{
    geo::point<double, 2> const p1 = {-2, 3};
    geo::point<double, 2> const p2 = {1, -1};
    CHECK(squared_distance(p1, p2) == Approx(25.0));
}

TEST_CASE("distance - returns the Euclidean distance between points")
{
    geo::point<double, 2> const p1 = {-2, 3};
    geo::point<double, 2> const p2 = {1, -1};
    CHECK(distance(p1, p2) == Approx(5.0));
}

TEST_CASE("interpolate - returns the dividing point")
{
    geo::point<double, 2> const p1 = {1, 2};
    geo::point<double, 2> const p2 = {3, 4};

    CHECK(distance(interpolate(p1, p2, 0), p1) < 1e-6);
    CHECK(distance(interpolate(p1, p2, 1), p2) < 1e-6);

    CHECK(distance(interpolate(p1, p2, 0.2), {1.4, 2.4}) < 1e-6);
    CHECK(distance(interpolate(p1, p2, 0.5), {2.0, 3.0}) < 1e-6);
    CHECK(distance(interpolate(p1, p2, 0.7), {2.4, 3.4}) < 1e-6);

    CHECK(distance(interpolate(p1, p2, -0.5), {0.0, 1.0}) < 1e-6);
    CHECK(distance(interpolate(p1, p2, 1.5), {4.0, 5.0}) < 1e-6);
}

TEST_CASE("centroid - returns the centroid")
{
    geo::point<double, 2> const points[4] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    geo::point<double, 2> const centroid = geo::centroid(points);
    CHECK(centroid[0] == Approx(4.0));
    CHECK(centroid[1] == Approx(5.0));
}
