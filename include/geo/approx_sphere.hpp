// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Approximate equality testing for points and vectors.
//

#ifndef GEO_APPROX_SPHERE_HPP
#define GEO_APPROX_SPHERE_HPP

#include <utility>

namespace geo
{
    namespace detail
    {
        template<typename X>
        struct metric_type_for;
    }

    /**
     * Helper class for testing for approximate equality.
     *
     * This class wraps point or vector so that equality operator gives
     * approximate comparison within defined error range (distance).
     */
    template<typename X>
    struct approx_sphere
    {
        /**
         * Alias to the template parameter X.
         */
        using object_type = X;

        /**
         * The metric type (kernel::metric) associated to the object X.
         */
        using metric_type = typename detail::metric_type_for<X>::type;

        /**
         * Creates approx_sphere object.
         */
        constexpr explicit
        approx_sphere(object_type const& center);

        /**
         * Sets error range.
         *
         * Assertion fails if e is negative. Zero is permitted.
         */
        constexpr
        approx_sphere& epsilon(metric_type e);

        /**
         * Determines if given object lies within the error range.
         */
        constexpr
        bool contains(object_type const& other) const noexcept;

      private:
        object_type center_ {};
        metric_type squared_radius_ {};
    };

    /**
     * Returns true if obj lies within the error range of sphere.
     */
    template<typename X>
    constexpr
    bool operator==(approx_sphere<X> const& sphere,
                    typename approx_sphere<X>::object_type const& obj) noexcept;

    template<typename X>
    constexpr
    bool operator==(typename approx_sphere<X>::object_type const& obj,
                    approx_sphere<X> const& sphere) noexcept;

    /**
     * Returns true if obj is outside of the error range of sphere.
     */
    template<typename X>
    constexpr
    bool operator!=(approx_sphere<X> const& sphere,
                    typename approx_sphere<X>::object_type const& obj) noexcept;

    template<typename X>
    constexpr
    bool operator!=(typename approx_sphere<X>::object_type const& obj,
                    approx_sphere<X> const& sphere) noexcept;

    /**
     * Creates approx_sphere from given object.
     */
    template<typename X>
    constexpr
    approx_sphere<X> approx(X const& center) noexcept;

    /**
     * Same as approx(center).
     *
     * This function provides basic syntactic compatibility with the Catch test
     * framework (https://github.com/philsquared/Catch).
     */
    template<typename X>
    constexpr
    approx_sphere<X> Approx(X const& center) noexcept;
}

#include "approx_sphere.ipp"

#endif
