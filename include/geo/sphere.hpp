// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Spherical shape.
//

#ifndef GEO_SPHERE_HPP
#define GEO_SPHERE_HPP

#include "box.hpp"
#include "point.hpp"
#include "scaling_transformation.hpp"
#include "vector.hpp"

namespace geo
{
    /**
     * Sphere.
     */
    template<typename K>
    struct sphere
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
         * Creates a unit sphere.
         */
        constexpr
        sphere() noexcept = default;

        /**
         * Creates a sphere of given center and radius.
         */
        constexpr
        sphere(point_type const& center, metric_type radius);

        // Attributes ----------------------------------------------------------

        /**
         * Returns the center.
         */
        constexpr
        point_type center() const noexcept;

        /**
         * Returns the squared radius.
         */
        constexpr
        metric_type squared_radius() const noexcept;

        /**
         * Returns the radius.
         */
        metric_type radius() const noexcept;

        // Analytic query ------------------------------------------------------

        /**
         * Evaluates the implicit function.
         *
         * The implicit function is negative inside the sphere, zero at the
         * boundary and positive outside the sphere.
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
         */
        constexpr
        metric_type oriented_distance(point_type const& p) const noexcept;

        /**
         * Returns a transformation that maps centric position vector to
         * surface position vector.
         *
         * The transformation is undefined for the center of sphere, so
         * assertion fails if the argument is the same as center().
         */
        constexpr
        scaling_type skin_map(point_type const& p) const noexcept;

      private:
        point_type center_ {};
        metric_type squared_radius_ {scalar_type(1)};
    };

    /**
     * Returns the axis-aligned bounding box of sphere.
     */
    template<typename K>
    box<K> bounding_box(sphere<K> const& s) noexcept;
}

#include "sphere.ipp"

#endif
