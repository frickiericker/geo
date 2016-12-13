// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Common base class for point, vector and scaling_transformation.
//
// This header has no inline implementation file (*.ipp).
//

#ifndef GEO_INTERNAL_BASIC_COORDINATES_HPP
#define GEO_INTERNAL_BASIC_COORDINATES_HPP

#include <type_traits>

#include "coordinates_storage.hpp"

namespace geo
{
    /*
     * Implements basic features of coordinate tuple.
     *
     * Directly deriving geo::point and geo::vector from coordinates_storage
     * accidentally makes these two classes implicitly convertible to each
     * other via the copy constructor of coordinates_storage. That's bad. So
     * let us wrap coordinates_storage with a tag type to discriminate point
     * and vector.
     *
     * Also, some convenience constructors are added here.
     */
    template<typename Tag, typename K>
    struct basic_coordinates
        : coordinates_storage<typename K::scalar, K::dimension>
    {
        static constexpr unsigned dimension = K::dimension;
        using scalar_type = typename K::scalar;
        using base_type = coordinates_storage<scalar_type, dimension>;

        constexpr
        basic_coordinates() noexcept = default;

        // Provide nicer interface for low-dimensional cases

        template<unsigned D = dimension, std::enable_if_t<D == 1, int> = 0>
        constexpr
        basic_coordinates(scalar_type x) noexcept
            : base_type(x)
        {
        }

        template<unsigned D = dimension, std::enable_if_t<D == 2, int> = 0>
        constexpr
        basic_coordinates(scalar_type x,
                          scalar_type y) noexcept
            : base_type(x, y)
        {
        }

        template<unsigned D = dimension, std::enable_if_t<D == 3, int> = 0>
        constexpr
        basic_coordinates(scalar_type x,
                          scalar_type y,
                          scalar_type z) noexcept
            : base_type(x, y, z)
        {
        }

        template<unsigned D = dimension, std::enable_if_t<D == 4, int> = 0>
        constexpr
        basic_coordinates(scalar_type x,
                          scalar_type y,
                          scalar_type z,
                          scalar_type w) noexcept
            : base_type(x, y, z, w)
        {
        }

        // Generic case. This is too strict on narrowing conversion.

        template<typename... Xs,
                 std::enable_if_t<(sizeof...(Xs) > 4), int> = 0,
                 std::enable_if_t<(sizeof...(Xs) == dimension), int> = 0>
        constexpr
        basic_coordinates(Xs... init) noexcept
            : base_type(init...)
        {
        }
    };
}

#endif
