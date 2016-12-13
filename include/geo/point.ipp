// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "point.hpp"
#include "vector.hpp"

namespace geo
{
    // Creation ----------------------------------------------------------------

    template<typename K>
    constexpr
    point<K> point<K>::origin() noexcept
    {
        return point<K>();
    }

    // Translation -------------------------------------------------------------

    template<typename K>
    constexpr
    point<K>& point<K>::operator+=(vector_type const& other) noexcept
    {
        for (unsigned i = 0; i < dimension; ++i) {
            (*this)[i] += other[i];
        }
        return *this;
    }

    template<typename K>
    constexpr
    point<K>& point<K>::operator-=(vector_type const& other) noexcept
    {
        for (unsigned i = 0; i < dimension; ++i) {
            (*this)[i] -= other[i];
        }
        return *this;
    }

    template<typename K>
    constexpr
    point<K> operator+(point<K> const& p, vector<K> const& v) noexcept
    {
        return point<K>(p) += v;
    }

    template<typename K>
    constexpr
    point<K> operator-(point<K> const& p, vector<K> const& v) noexcept
    {
        return point<K>(p) -= v;
    }

    namespace detail
    {
        template<typename K>
        constexpr
        vector<K> to_vector(point<K> const& p) noexcept
        {
            vector<K> v;
            for (unsigned i = 0; i < K::dimension; ++i) {
                v[i] = p[i];
            }
            return v;
        }
    }

    template<typename K>
    constexpr
    vector<K> operator-(point<K> const& p, point<K> const& q) noexcept
    {
        return detail::to_vector(p) - detail::to_vector(q);
    }

    // Basic operations --------------------------------------------------------

    template<typename K>
    constexpr
    typename K::metric squared_distance(point<K> const& p,
                                        point<K> const& q) noexcept
    {
        return squared_norm(p - q);
    }

    template<typename K>
    constexpr
    typename K::metric distance(point<K> const& p,
                                point<K> const& q) noexcept
    {
        return K::sqrt(squared_distance(p, q));
    }
}
