// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// CRTP for implementing multiplicative operator overloads.
//

#ifndef GEO_INTERNAL_MULTIPLICATIVE_OPERATIONS_HPP
#define GEO_INTERNAL_MULTIPLICATIVE_OPERATIONS_HPP

namespace geo
{
    /**
     * CRTP mixin for implementing multiplications on D.
     *
     * This class implements multiplication and division on class D.
     */
    template<typename D, typename K>
    struct multiplicative_operations
    {
        using derived_type = D;
        static constexpr unsigned dimension = K::dimension;

        constexpr
        derived_type& operator*=(derived_type const& other) noexcept;

        constexpr
        derived_type& operator/=(derived_type const& other);

        constexpr
        derived_type& derived() noexcept;

        constexpr
        derived_type const& derived() const noexcept;
    };

    template<typename D, typename K>
    constexpr
    D operator*(multiplicative_operations<D, K> const& a,
                multiplicative_operations<D, K> const& b) noexcept;

    template<typename D, typename K>
    constexpr
    D operator/(multiplicative_operations<D, K> const& a,
                multiplicative_operations<D, K> const& b);
}

#include "multiplicative_operations.ipp"

#endif
