// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "algorithm.hpp"
#include "assert.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace geo
{
    template<typename K, typename Iterator>
    point<K> centroid(Iterator first, Iterator last)
    {
        GEO_ASSERT(first != last);

        point<K> const local_origin = *first;
        vector<K> mean;
        long num = 1;

        while (++first != last) {
            mean += *first - local_origin;
            num += 1;
        }
        mean /= static_cast<typename K::scalar>(num);

        return local_origin + mean;
    }
}
