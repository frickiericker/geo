// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "linear_operations.hpp"

namespace geo
{
    // Internals ---------------------------------------------------------------

    template<typename D, typename K>
    constexpr
    auto linear_operations<D, K>::derived() noexcept -> derived_type&
    {
        return static_cast<derived_type&>(*this);
    }

    template<typename D, typename K>
    constexpr
    auto linear_operations<D, K>::derived() const noexcept -> derived_type const&
    {
        return static_cast<derived_type const&>(*this);
    }

    // Direction ---------------------------------------------------------------

    template<typename D, typename K>
    constexpr
    D operator+(linear_operations<D, K> const& a) noexcept
    {
        return a.derived();
    }

    template<typename D, typename K>
    constexpr
    D operator-(linear_operations<D, K> const& a) noexcept
    {
        D result = a.derived();
        for (auto& element : result) {
            element = -element;
        }
        return result;
    }

    // Translation -------------------------------------------------------------

    template<typename D, typename K>
    constexpr
    auto linear_operations<D, K>::operator+=(derived_type const& other) noexcept
    -> derived_type&
    {
        derived_type& self = derived();
        for (unsigned i = 0; i < dimension; ++i) {
            self[i] += other[i];
        }
        return self;
    }

    template<typename D, typename K>
    constexpr
    auto linear_operations<D, K>::operator-=(derived_type const& other) noexcept
    -> derived_type&
    {
        derived_type& self = derived();
        for (unsigned i = 0; i < dimension; ++i) {
            self[i] -= other[i];
        }
        return self;
    }

    template<typename D, typename K>
    constexpr
    D operator+(linear_operations<D, K> const& a,
                linear_operations<D, K> const& b) noexcept
    {
        return D(a.derived()) += b.derived();
    }

    template<typename D, typename K>
    constexpr
    D operator-(linear_operations<D, K> const& a,
                linear_operations<D, K> const& b) noexcept
    {
        return D(a.derived()) -= b.derived();
    }

    // Scaling -----------------------------------------------------------------

    template<typename D, typename K>
    constexpr
    auto linear_operations<D, K>::operator*=(scalar_type k) noexcept -> derived_type&
    {
        derived_type& self = derived();
        for (scalar_type& element : self) {
            element *= k;
        }
        return self;
    }

    template<typename D, typename K>
    constexpr
    auto linear_operations<D, K>::operator/=(scalar_type k) -> derived_type&
    {
        derived_type& self = derived();
        for (scalar_type& element : self) {
            element /= k;
        }
        return self;
    }

    template<typename D, typename K>
    constexpr
    D operator*(linear_operations<D, K> const& a,
                typename linear_operations<D, K>::scalar_type k) noexcept
    {
        return D(a.derived()) *= k;
    }

    template<typename D, typename K>
    constexpr
    D operator*(typename linear_operations<D, K>::scalar_type k,
                linear_operations<D, K> const& a) noexcept
    {
        return D(a.derived()) *= k;
    }

    template<typename D, typename K>
    constexpr
    D operator/(linear_operations<D, K> const& a,
                typename linear_operations<D, K>::scalar_type k)
    {
        return D(a.derived()) /= k;
    }
}
