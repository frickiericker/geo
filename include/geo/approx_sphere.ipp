// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <limits>
#include <utility>

#include "approx_sphere.hpp"
#include "assert.hpp"

namespace geo
{
    namespace detail
    {
        template<typename X>
        struct metric_type_for
        {
            using type = decltype(norm(std::declval<X>() - std::declval<X>()));
        };
    }

    // Creation ----------------------------------------------------------------

    namespace detail
    {
        template<typename T>
        struct default_epsilon_for
        {
            static constexpr T get() noexcept;
        };
    }

    template<typename X>
    constexpr
    approx_sphere<X>::approx_sphere(X const& center)
        : center_(center)
    {
        epsilon(detail::default_epsilon_for<metric_type>::get());
    }

    template<typename X>
    constexpr
    approx_sphere<X> approx(X const& center) noexcept
    {
        return approx_sphere<X>(center);
    }

    template<typename X>
    constexpr
    approx_sphere<X> Approx(X const& center) noexcept
    {
        return approx(center);
    }

    // Parameter setter --------------------------------------------------------

    template<typename X>
    constexpr
    approx_sphere<X>& approx_sphere<X>::epsilon(metric_type e)
    {
        GEO_EXTRA_ASSERT(e >= 0);
        squared_radius_ = e * e;
        return *this;
    }

    namespace detail
    {
        template<typename T>
        constexpr
        T default_epsilon_for<T>::get() noexcept
        {
            return T();
        }

        template<>
        constexpr inline
        float default_epsilon_for<float>::get() noexcept
        {
            // Same as Catch
            return std::numeric_limits<float>::epsilon() * 100;
        };

        template<>
        constexpr inline
        double default_epsilon_for<double>::get() noexcept
        {
            // Same as Catch
            return std::numeric_limits<double>::epsilon() * 100;
        };
    }

    // Approximate equality ----------------------------------------------------

    template<typename X>
    constexpr
    bool approx_sphere<X>::contains(object_type const& other) const noexcept
    {
        return squared_norm(other - center_) <= squared_radius_;
    }

    template<typename X>
    constexpr
    bool operator==(approx_sphere<X> const& sphere,
                    typename approx_sphere<X>::object_type const& obj) noexcept
    {
        return sphere.contains(obj);
    }

    template<typename X>
    constexpr
    bool operator==(typename approx_sphere<X>::object_type const& obj,
                    approx_sphere<X> const& sphere) noexcept
    {
        return sphere.contains(obj);
    }

    template<typename X>
    constexpr
    bool operator!=(approx_sphere<X> const& sphere,
                    typename approx_sphere<X>::object_type const& obj) noexcept
    {
        return !sphere.contains(obj);
    }

    template<typename X>
    constexpr
    bool operator!=(typename approx_sphere<X>::object_type const& obj,
                    approx_sphere<X> const& sphere) noexcept
    {
        return !sphere.contains(obj);
    }
}
