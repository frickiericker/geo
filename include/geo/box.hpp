// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Box shape.
//

#ifndef GEO_BOX_HPP
#define GEO_BOX_HPP

#include "point.hpp"
#include "vector.hpp"

namespace geo
{
    /**
     * Axis-aligned box.
     */
    template<typename K>
    struct box
    {
        /**
         * Alias to the template parameter K.
         */
        using kernel = K;

        /**
         * Type for scalars of the underlying Euclidean space.
         */
        using scalar_type = typename K::scalar;

        /**
         * Type for distance measured in the underlying Euclidean space.
         */
        using metric_type = typename K::metric;

        /**
         * Type for points in the underlying Euclidean space.
         */
        using point_type = point<K>;

        /**
         * Type for vectors associated to the underlying Euclidean space.
         */
        using vector_type = vector<K>;

        /**
         * Dimension of the underlying Euclidean space.
         */
        static constexpr unsigned dimension = K::dimension;

        // Creation ------------------------------------------------------------

        /**
         * Creates a unit box.
         *
         * The lowest vertex of the created box is at the origin, and the
         * highest vertex is the point whose coordinates are all ones.
         */
        constexpr
        box() noexcept;

        /**
         * Creates an axis-aligned bounding box of segment connecting two given
         * points.
         */
        constexpr
        box(point_type const& p, point_type const& q);

        // Attributes ----------------------------------------------------------

        /**
         * Returns the vertex with lowest coordinate values.
         */
        constexpr
        point_type lowest_vertex() const noexcept;

        /**
         * Returns the vertex with highest coordinate values.
         */
        constexpr
        point_type highest_vertex() const noexcept;

        /**
         * Returns the vector connecting the lowest to the highest vertices.
         */
        constexpr
        vector_type diagonal_span() const noexcept;

        /**
         * Returns the center of the volume.
         */
        constexpr
        point_type center() const noexcept;

        /**
         * Returns the volume.
         */
        constexpr
        metric_type volume() const noexcept;

      private:
        point_type lowest_vertex_ {};
        point_type highest_vertex_ {};
    };
}

#include "box.ipp"

#endif
