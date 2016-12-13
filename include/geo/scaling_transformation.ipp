// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "scaling_transformation.hpp"

namespace geo
{
    // Creation ----------------------------------------------------------------

    template<typename K>
    constexpr
    scaling_transformation<K>::scaling_transformation() noexcept
        : scaling_transformation(scalar_type(1))
    {
    }

    template<typename K>
    constexpr
    scaling_transformation<K>::scaling_transformation(scalar_type k) noexcept
    {
        for (scalar_type& scale : *this) {
            scale = k;
        }
    }

    // Operation ---------------------------------------------------------------

    template<typename K>
    constexpr
    auto scaling_transformation<K>::operator()(vector_type const& v) const noexcept
    -> vector_type
    {
        vector_type result = v;
        for (unsigned i = 0; i < dimension; ++i) {
            result[i] *= (*this)[i];
        }
        return result;
    }
}
