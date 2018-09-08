// Copyright snsinfu 2018.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>
#include <type_traits>

#include "catch.hpp"
#include "../include/geo.hpp"


TEST_CASE("vector - exposes scalar_type")
{
    CHECK(std::is_same<geo::vector<float, 3>::scalar_type, float>::value);
    CHECK(std::is_same<geo::vector<double, 3>::scalar_type, double>::value);
}

TEST_CASE("vector - exposes constexpr dimension")
{
    constexpr auto dim = geo::vector<double, 3>::dimension;
    CHECK(dim == 3);
}

TEST_CASE("vector - is default constructible")
{
    geo::vector<double, 3> vector;
    CHECK(vector[0] == 0);
    CHECK(vector[1] == 0);
    CHECK(vector[2] == 0);
}

TEST_CASE("vector - is constructible from coordinate values")
{
    geo::vector<double, 3> vector = {1.2, 3.4, 5.6};
    CHECK(vector[0] == 1.2);
    CHECK(vector[1] == 3.4);
    CHECK(vector[2] == 5.6);
}

TEST_CASE("vector - is copy constructible")
{
    geo::vector<double, 3> vector = {1.2, 3.4, 5.6};
    geo::vector<double, 3> copy = vector;
    CHECK(copy[0] == 1.2);
    CHECK(copy[1] == 3.4);
    CHECK(copy[2] == 5.6);
}

TEST_CASE("vector - supports inplace component-wise addition")
{
    geo::vector<double, 2> vector;
    vector += {1.2, 3.4};
    CHECK(vector[0] == Approx(1.2));
    CHECK(vector[1] == Approx(3.4));
}

TEST_CASE("vector - supports inplace component-wise subtraction")
{
    geo::vector<double, 2> vector;
    vector -= {1.2, 3.4};
    CHECK(vector[0] == Approx(-1.2));
    CHECK(vector[1] == Approx(-3.4));
}

TEST_CASE("vector - supports inplace broadcasting multiplication")
{
    geo::vector<double, 2> vector = {1, 2};
    vector *= 2;
    CHECK(vector[0] == Approx(2.0));
    CHECK(vector[1] == Approx(4.0));
}

TEST_CASE("vector - supports inplace broadcasting division")
{
    geo::vector<double, 2> vector = {9, 6};
    vector /= 3;
    CHECK(vector[0] == Approx(3.0));
    CHECK(vector[1] == Approx(2.0));
}

TEST_CASE("vector::dot - computes dot product")
{
    geo::vector<double, 2> const vector = {1, 2};
    CHECK(vector.dot({3, -4}) == Approx(-5.0));
}

TEST_CASE("vector::squared_norm - returns the squared Euclidean norm")
{
    geo::vector<double, 2> const vector = {3, 4};
    CHECK(vector.squared_norm() == Approx(25.0));
}

TEST_CASE("vector::norm - returns the Euclidean norm")
{
    geo::vector<double, 2> const vector = {3, 4};
    CHECK(vector.norm() == Approx(5.0));
}

TEST_CASE("vector::cross - computes cross product")
{
    geo::vector<double, 3> const vector = {1, 2, 3};
    geo::vector<double, 3> const cross = vector.cross({3, 2, 1});
    CHECK(cross[0] == Approx(-4.0));
    CHECK(cross[1] == Approx(8.0));
    CHECK(cross[2] == Approx(-4.0));
}

TEST_CASE("vector::normalize - returns the normalized vector")
{
    geo::vector<double, 2> const vector = {3, -4};
    geo::vector<double, 2> const norm = vector.normalize();
    CHECK(norm[0] == Approx(0.6));
    CHECK(norm[1] == Approx(-0.8));
}

TEST_CASE("vector - unary + returns a copy")
{
    geo::vector<double, 2> vector = {1, 2};
    geo::vector<double, 2> const& copy = +vector;
    vector[0] = 3;
    CHECK(copy[0] == 1);
    CHECK(copy[1] == 2);
}

TEST_CASE("vector - unary - returns a negated vector")
{
    geo::vector<double, 2> const vector = {1, 2};
    geo::vector<double, 2> const negated = -vector;
    CHECK(negated[0] == -1);
    CHECK(negated[1] == -2);
}

TEST_CASE("vector - addition returns component-wise sum")
{
    geo::vector<double, 2> const vec1 = {1, 2};
    geo::vector<double, 2> const vec2 = {3, 4};
    geo::vector<double, 2> const sum = vec1 + vec2;
    CHECK(sum[0] == 4);
    CHECK(sum[1] == 6);
}

TEST_CASE("vector - subtraction returns component-wise difference")
{
    geo::vector<double, 2> const vec1 = {1, 2};
    geo::vector<double, 2> const vec2 = {4, 3};
    geo::vector<double, 2> const diff = vec1 - vec2;
    CHECK(diff[0] == -3);
    CHECK(diff[1] == -1);
}

TEST_CASE("vector - right multiplication by scalar returns a scaled vector")
{
    geo::vector<double, 2> const vec = {1, 2};
    geo::vector<double, 2> const scaled = vec * 3;
    CHECK(scaled[0] == 3);
    CHECK(scaled[1] == 6);
}

TEST_CASE("vector - left multiplication by scalar returns a scaled vector")
{
    geo::vector<double, 2> const vec = {1, 2};
    geo::vector<double, 2> const scaled = 3 * vec;
    CHECK(scaled[0] == 3);
    CHECK(scaled[1] == 6);
}

TEST_CASE("vector - division by scalar returns a scaled vector")
{
    geo::vector<double, 2> const vec = {1, 2};
    geo::vector<double, 2> const scaled = vec / 5;
    CHECK(scaled[0] == Approx(0.2));
    CHECK(scaled[1] == Approx(0.4));
}

TEST_CASE("vector - dot computes dot product")
{
    geo::vector<double, 2> const vec1 = {1, 2};
    geo::vector<double, 2> const vec2 = {3, -4};
    CHECK(dot(vec1, vec2) == Approx(-5.0));
}

TEST_CASE("vector - squared_norm computes the squared Euclidean norm")
{
    geo::vector<double, 2> const vec = {3, 4};
    CHECK(squared_norm(vec) == Approx(25.0));
}

TEST_CASE("vector - norm computes the Euclidean norm")
{
    geo::vector<double, 2> const vec = {3, 4};
    CHECK(norm(vec) == Approx(5.0));
}

TEST_CASE("vector - cross computes cross product")
{
    geo::vector<double, 3> const vec1 = {1, 2, 3};
    geo::vector<double, 3> const vec2 = {3, 2, 1};
    geo::vector<double, 3> const crossvec = cross(vec1, vec2);
    CHECK(crossvec[0] == Approx(-4.0));
    CHECK(crossvec[1] == Approx(8.0));
    CHECK(crossvec[2] == Approx(-4.0));
}

TEST_CASE("vector - normalize returns the normalized vector")
{
    geo::vector<double, 2> const vec = {3, -4};
    geo::vector<double, 2> const norm = normalize(vec);
    CHECK(norm[0] == Approx(0.6));
    CHECK(norm[1] == Approx(-0.8));
}

TEST_CASE("vector - implements ostream output operator")
{
    geo::vector<double, 4> const vec1 = {1, 2, 3, 4};
    geo::vector<double, 3> const vec2 = {5, 6, 7};
    std::stringstream stream;
    stream << vec1 << '\n' << vec2;
    CHECK(stream.str() == "1 2 3 4\n5 6 7");
}

TEST_CASE("vector - implements istream input operator")
{
    geo::vector<double, 4> vec1;
    geo::vector<double, 3> vec2;
    std::stringstream stream{"1 2 3 4\n5 6 7"};
    stream >> vec1 >> vec2;
    CHECK(vec1[0] == 1);
    CHECK(vec1[1] == 2);
    CHECK(vec1[2] == 3);
    CHECK(vec1[3] == 4);
    CHECK(vec2[0] == 5);
    CHECK(vec2[1] == 6);
    CHECK(vec2[2] == 7);
}
