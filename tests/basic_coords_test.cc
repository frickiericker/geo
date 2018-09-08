// Copyright snsinfu 2018.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iomanip>
#include <sstream>
#include <type_traits>

#include "catch.hpp"
#include "../include/geo.hpp"


TEST_CASE("basic_coords - is default constructible and default coords are zeros")
{
    geo::basic_coords<double, 3> coords;
    CHECK(coords[0] == 0);
    CHECK(coords[1] == 0);
    CHECK(coords[2] == 0);
}

TEST_CASE("basic_coords - is constructible from coordinate values")
{
    geo::basic_coords<double, 3> coords = {1.2, 3.4, 5.6};
    CHECK(coords[0] == 1.2);
    CHECK(coords[1] == 3.4);
    CHECK(coords[2] == 5.6);
}

TEST_CASE("basic_coords - supports float")
{
    geo::basic_coords<float, 3> coords = {1.2F, 3.4F, 5.6F};
    CHECK(coords[0] == 1.2F);
    CHECK(coords[1] == 3.4F);
    CHECK(coords[2] == 5.6F);
}

TEST_CASE("basic_coords - supports range-based for loop with mutable access")
{
    geo::basic_coords<int, 3> coords = {1, 2, 3};
    for (int& coord : coords) {
        coord++;
    }
    CHECK(coords[0] == 2);
    CHECK(coords[1] == 3);
    CHECK(coords[2] == 4);
}

TEST_CASE("basic_coords - supports range-based for loop with const access")
{
    geo::basic_coords<int, 3> const coords = {1, 2, 3};
    int sum = 0;
    for (int const& coord : coords) {
        sum += coord;
    }
    CHECK(sum == 6);
}

TEST_CASE("basic_coords - implements equality comparison operator")
{
    geo::basic_coords<int, 2> coords_a = {1, 2};
    geo::basic_coords<int, 2> coords_b = {1, 2};
    geo::basic_coords<int, 2> coords_c = {3, 4};
    CHECK(coords_a == coords_b);
    CHECK(coords_a != coords_c);
    CHECK(coords_b != coords_c);
}

TEST_CASE("basic_coords - implements ostream output operator")
{
    geo::basic_coords<int, 4> coords = {1, 2, 3, 4};
    std::stringstream stream;
    stream << coords;
    CHECK(stream.str() == "1 2 3 4");
}

TEST_CASE("basic_coords - implements istream input operator")
{
    geo::basic_coords<int, 4> coords;
    std::stringstream stream{"1 2 3 4"};
    stream >> coords;
    CHECK(coords == geo::basic_coords<int, 4>{1, 2, 3, 4});
}

TEST_CASE("basic_coords - supports setprecision manipulator")
{
    geo::basic_coords<double, 2> coords = {1.23456, 7.89012};
    std::stringstream stream;
    stream << std::setprecision(3) << coords;
    CHECK(stream.str() == "1.23 7.89");
}
