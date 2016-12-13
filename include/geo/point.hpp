// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Point class.
//

#ifndef GEO_POINT_HPP
#define GEO_POINT_HPP

#include "internal/basic_coordinates.hpp"
#include "vector.hpp"

namespace geo
{
    /**
     * Cartesian representation of a point.
     *
     * Coordinates can be accessed as range given by begin() and end() member
     * functions or directly via indexing operator.
     */
    template<typename K>
    struct point : basic_coordinates<point<K>, K>
    {
        using mixin = basic_coordinates<point<K>, K>;

        /**
         * Alias to the template parameter K.
         */
        using kernel = K;

        /**
         * Type for scalars of the underlying Euclidean space.
         */
        using scalar_type = typename K::scalar;

        /**
         * Type for vectors associated to the underlying Euclidean space.
         */
        using vector_type = vector<K>;

        /**
         * Type of iterator for accessing coordinates by mutable references.
         */
        using iterator = typename mixin::iterator;

        /**
         * Type of iterator for accessing coordinates by const references.
         */
        using const_iterator = typename mixin::const_iterator;

        /**
         * Dimension of the underlying Euclidean space.
         */
        static constexpr unsigned dimension = K::dimension;

        // Creation ------------------------------------------------------------

        using mixin::mixin;

        /**
         * Returns a point representing the origin.
         *
         * The coordinates of the origin is all zero. Default-constructed point
         * object also has all-zero coordinates, but using this function may
         * express the intent more clearly.
         */
        static constexpr point origin() noexcept;

        // Translation ---------------------------------------------------------

        /**
         * Translates point by a vector.
         */
        constexpr
        point& operator+=(vector_type const& v) noexcept;

        /**
         * Translates point by a vector.
         */
        constexpr
        point& operator-=(vector_type const& v) noexcept;
    };

    /**
     * Translates point by a vector.
     */
    template<typename K>
    constexpr
    point<K> operator+(point<K> const& p, vector<K> const& v) noexcept;

    /**
     * Translates point by a vector.
     */
    template<typename K>
    constexpr
    point<K> operator-(point<K> const& p, vector<K> const& v) noexcept;

    /**
     * Computes displacement vector from one point to another.
     */
    template<typename K>
    constexpr
    vector<K> operator-(point<K> const& p, point<K> const& q) noexcept;

    // Basic operations --------------------------------------------------------

    /**
     * Computes the squared Euclidean distance between points.
     */
    template<typename K>
    constexpr
    typename K::metric squared_distance(point<K> const& p,
                                        point<K> const& q) noexcept;

    /**
     * Computes the Euclidean distance between points.
     *
     * This function computes the squared root of squared_distance(p, q) using
     * K::sqrt() function. So compilation would fail if the kernel does not
     * provide sqrt() function.
     */
    template<typename K>
    constexpr
    typename K::metric distance(point<K> const& p,
                                point<K> const& q) noexcept;
}

#include "point.ipp"

#endif
