// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "vector.hpp"

namespace geo
{
    // Constructors ------------------------------------------------------------

    template<typename K>
    constexpr
    vector<K> vector<K>::zero() noexcept
    {
        return vector<K>();
    }

    // Basic operations --------------------------------------------------------

    template<typename K>
    constexpr
    typename K::metric inner_product(vector<K> const& u,
                                     vector<K> const& v) noexcept
    {
        typename K::scalar sum = 0;
        for (unsigned i = 0; i < K::dimension; ++i) {
            sum += u[i] * v[i];
        }
        return sum;
    }

    template<typename K>
    constexpr
    typename K::metric squared_norm(vector<K> const& v) noexcept
    {
        return inner_product(v, v);
    }

    template<typename K>
    constexpr
    typename K::metric norm(vector<K> const& v) noexcept
    {
        return K::sqrt(squared_norm(v));
    }

    template<typename K>
    constexpr
    vector<K> normalize(vector<K> const& v)
    {
        return v / norm(v);
    }
}
