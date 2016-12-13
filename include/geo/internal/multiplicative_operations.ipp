// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "multiplicative_operations.hpp"

namespace geo
{
    // Internals ---------------------------------------------------------------

    template<typename D, typename K>
    constexpr
    auto multiplicative_operations<D, K>::derived() noexcept -> derived_type&
    {
        return static_cast<derived_type&>(*this);
    }

    template<typename D, typename K>
    constexpr
    auto multiplicative_operations<D, K>::derived() const noexcept -> derived_type const&
    {
        return static_cast<derived_type const&>(*this);
    }

    // Operations --------------------------------------------------------------

    template<typename D, typename K>
    constexpr
    auto multiplicative_operations<D, K>::operator*=(derived_type const& other) noexcept
    -> derived_type&
    {
        derived_type& self = derived();
        for (unsigned i = 0; i < dimension; ++i) {
            self[i] *= other[i];
        }
        return self;
    }

    template<typename D, typename K>
    constexpr
    auto multiplicative_operations<D, K>::operator/=(derived_type const& other)
    -> derived_type&
    {
        derived_type& self = derived();
        for (unsigned i = 0; i < dimension; ++i) {
            self[i] /= other[i];
        }
        return self;
    }

    template<typename D, typename K>
    constexpr
    D operator*(multiplicative_operations<D, K> const& a,
                multiplicative_operations<D, K> const& b) noexcept
    {
        return D(a.derived()) *= b.derived();
    }

    template<typename D, typename K>
    constexpr
    D operator/(multiplicative_operations<D, K> const& a,
                multiplicative_operations<D, K> const& b)
    {
        return D(a.derived()) /= b.derived();
    }
}
