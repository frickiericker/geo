// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Vector class.
//

#ifndef GEO_VECTOR_HPP
#define GEO_VECTOR_HPP

#include <istream>
#include <ostream>

#include "internal/basic_coordinates.hpp"
#include "internal/linear_operations.hpp"

namespace geo
{
    /**
     * Cartesian representation of a vector.
     *
     * Components can be accessed as range given by begin() and end() member
     * functions or directly via indexing operator.
     */
    template<typename K>
    struct vector
        : basic_coordinates<vector<K>, K>
        , linear_operations<vector<K>, K>
    {
        using mixin = basic_coordinates<vector<K>, K>;

        /**
         * Alias to the template parameter K.
         */
        using kernel = K;

        /**
         * Type for scalars of the underlying Euclidean space.
         */
        using scalar_type = typename K::scalar;

        /**
         * Type of iterator for accessing components by mutable references.
         */
        using iterator = typename mixin::iterator;

        /**
         * Type of iterator for accessing components by const references.
         */
        using const_iterator = typename mixin::const_iterator;

        /**
         * Dimension of the underlying Euclidean space.
         */
        static constexpr unsigned dimension = K::dimension;

        // Creation ------------------------------------------------------------

        using mixin::mixin;

        /**
         * Creates a zero vector.
         *
         * Components of zero vector is all zero. Default-constructed vector
         * object also has all-zero components, but using this function may
         * express the intent more clearly.
         */
        static constexpr vector zero() noexcept;
    };

    // Basic operations --------------------------------------------------------

    /**
     * Computes the inner product of two vectors.
     */
    template<typename K>
    constexpr
    typename K::metric inner_product(vector<K> const& u,
                                     vector<K> const& v) noexcept;

    /**
     * Computes the squared Euclidean norm of vector.
     *
     * This function is equivalent to inner_product(v, v).
     */
    template<typename K>
    constexpr
    typename K::metric squared_norm(vector<K> const& v) noexcept;

    /**
     * Computes the Euclidean norm of vector.
     *
     * This function computes the squared root of squared_length(v) using
     * K::sqrt() function. So compilation would fail if the kernel does not
     * provide sqrt() function.
     */
    template<typename K>
    constexpr
    typename K::metric norm(vector<K> const& v) noexcept;

    /**
     * Normalizes a vector.
     *
     * This function is equivalent to v / norm(v). Thus, passing zero vector
     * causes division of zero by zero. In such case, the behavior of this
     * function follows that of the underlying scalar type.
     */
    template<typename K>
    constexpr
    vector<K> normalize(vector<K> const& v);
}

#include "vector.ipp"

#endif
