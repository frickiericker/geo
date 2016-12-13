// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Generic CRTP for implementing linear operator overloads.
//

#ifndef GEO_INTERNAL_LINEAR_OPERATIONS_HPP
#define GEO_INTERNAL_LINEAR_OPERATIONS_HPP

namespace geo
{
    /**
     * CRTP mixin for implementing linear operations on D.
     *
     * This class implements unary +, unary -, addition, subtraction,
     * multiplication by scalar and division by scalar on class D. The type
     * of scalar is K::scalar.
     */
    template<typename D, typename K>
    struct linear_operations
    {
        using derived_type = D;
        using scalar_type = typename K::scalar;
        static constexpr unsigned dimension = K::dimension;

        constexpr
        derived_type& operator+=(derived_type const& other) noexcept;

        constexpr
        derived_type& operator-=(derived_type const& other) noexcept;

        constexpr
        derived_type& operator*=(scalar_type k) noexcept;

        constexpr
        derived_type& operator/=(scalar_type k);

        constexpr
        derived_type& derived() noexcept;

        constexpr
        derived_type const& derived() const noexcept;
    };

    template<typename D, typename K>
    constexpr
    D operator+(linear_operations<D, K> const& a) noexcept;

    template<typename D, typename K>
    constexpr
    D operator-(linear_operations<D, K> const& a) noexcept;

    template<typename D, typename K>
    constexpr
    D operator+(linear_operations<D, K> const& a,
                linear_operations<D, K> const& b) noexcept;

    template<typename D, typename K>
    constexpr
    D operator-(linear_operations<D, K> const& a,
                linear_operations<D, K> const& b) noexcept;

    template<typename D, typename K>
    constexpr
    D operator*(linear_operations<D, K> const& a,
                typename linear_operations<D, K>::scalar_type k) noexcept;

    template<typename D, typename K>
    constexpr
    D operator*(typename linear_operations<D, K>::scalar_type k,
                linear_operations<D, K> const& a) noexcept;

    template<typename D, typename K>
    constexpr
    D operator/(linear_operations<D, K> const& a,
                typename linear_operations<D, K>::scalar_type k);
}

#include "linear_operations.ipp"

#endif
