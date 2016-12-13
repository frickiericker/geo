// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Anisotropic scaling of vector.
//

#ifndef GEO_SCALING_TRANSFORMATION_HPP
#define GEO_SCALING_TRANSFORMATION_HPP

#include "internal/basic_coordinates.hpp"
#include "internal/linear_operations.hpp"
#include "internal/multiplicative_operations.hpp"
#include "vector.hpp"

namespace geo
{
    /**
     * Function-like class for scaling vector by fixed factor.
     *
     * This class supports anisotropic scaling along the Cartesian axes. The
     * scaling factors can be accessed as range given by begin() and end()
     * member functions or directly via indexing operator.
     *
     * Linear operations and multiplications follow the usual semantics of
     * linear operator.
     */
    template<typename K>
    struct scaling_transformation
        : basic_coordinates<scaling_transformation<K>, K>
        , linear_operations<scaling_transformation<K>, K>
        , multiplicative_operations<scaling_transformation<K>, K>
    {
        using mixin = basic_coordinates<scaling_transformation<K>, K>;

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
         * Dimension of the underlying Euclidean space.
         */
        static constexpr unsigned dimension = K::dimension;

        // Creation ------------------------------------------------------------

        using mixin::mixin;

        /**
         * Default constructor creates an identity transformation.
         */
        constexpr
        scaling_transformation() noexcept;

        /**
         * Creates an isotropic scaling.
         */
        constexpr
        scaling_transformation(scalar_type k) noexcept;

        // Operation -----------------------------------------------------------

        /**
         * Transforms a vector.
         */
        constexpr
        vector_type operator()(vector_type const& v) const noexcept;
    };
}

#include "scaling_transformation.ipp"

#endif
