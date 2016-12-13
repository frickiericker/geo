// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Ellipsoid shape.
//

#ifndef GEO_ELLIPSOID_HPP
#define GEO_ELLIPSOID_HPP

#include "box.hpp"
#include "scaling_transformation.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace geo
{
    /**
     * Ellipsoid.
     */
    template<typename K>
    struct ellipsoid
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
         * Type of scaling transformation.
         */
        using scaling_type = scaling_transformation<K>;

        /**
         * Dimension of the underlying Euclidean space.
         */
        static constexpr unsigned dimension = K::dimension;

        // Creation ------------------------------------------------------------

        /**
         * Creates a unit sphere (ellipsoid) centered at the origin.
         */
        constexpr
        ellipsoid() noexcept = default;

        /**
         * Creates an ellipsoid of given center and semiaxes.
         */
        constexpr
        ellipsoid(point_type const& center, scaling_type const& semiaxes);

        // Attributes ----------------------------------------------------------

        /**
         * Returns the center.
         */
        constexpr
        point_type center() const noexcept;

        /**
         * Returns the scaling transformation of semiaxes.
         */
        constexpr
        scaling_type semiaxes() const noexcept;

        // Analytic query ------------------------------------------------------

        /**
         * Evaluates the implicit function.
         *
         * The implicit function is negative inside the ellipsoid, zero at the
         * boundary and positive outside the ellipsoid.
         */
        constexpr
        metric_type potential(point_type const& p) const noexcept;

        /**
         * Evaluates the gradient of implicit function.
         */
        constexpr
        vector_type gradient(point_type const& p) const noexcept;

        /**
         * Returns an estimate of shortest distance from point to the surface.
         *
         * The distance is oriented so that it has the same sign as the
         * implicit function. That is, negative inside and positive outside.
         * The absolute value gives usual distance.
         *
         * The returned distance is estimation and it gets inaccurate as the
         * point gets apart from the boundary.
         */
        constexpr
        metric_type oriented_distance(point_type const& p) const noexcept;

        /**
         * Returns a transformation that approximately maps centric position
         * vector to surface position vector.
         *
         * The returned transformation is linear approximation and it gets
         * inaccurate as the point gets apart from the boundary.
         *
         * The transformation is undefined for the center of ellipsoid, so
         * assertion fails if the argument is the same as center().
         */
        constexpr
        scaling_type skin_map(point_type const& p) const noexcept;

      private:
        point_type center_ {};
        scaling_type scaling_ {};
        scaling_type quadratic_map_ {};
    };

    /**
     * Returns the axis-aligned bounding box of ellipsoid.
     */
    template<typename K>
    box<K> bounding_box(ellipsoid<K> const& e) noexcept;
}

#include "ellipsoid.ipp"

#endif
