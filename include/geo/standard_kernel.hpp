// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Standard kernel (template parameter K in other files).
//
// This header has no inline implementation file (*.ipp).
//

#ifndef GEO_STANDARD_KERNEL_HPP
#define GEO_STANDARD_KERNEL_HPP

#include <type_traits>
#include <cmath>

namespace geo
{
    /**
     * Kernel that uses builtin floating point type and standard library math.
     */
    template<typename T, unsigned n>
    struct standard_kernel
    {
        static_assert(std::is_floating_point<T>::value, "");
        static_assert(n >= 1, "");

        /**
         * Aliased to T.
         */
        using scalar = T;

        /**
         * Aliased to T.
         */
        using metric = T;

        /**
         * Set to n.
         */
        static constexpr unsigned dimension = n;

        /**
         * Calls std::sqrt(x).
         */
        static metric sqrt(metric x) noexcept
        {
            return std::sqrt(x);
        }
    };
}

#endif
