// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Geometric algorithms for range of points.
//

#ifndef GEO_ALGORITHM_HPP
#define GEO_ALGORITHM_HPP

#include "point.hpp"

namespace geo
{
    /**
     * Computes the centroid of points in given range.
     *
     * The range must contain at least one point. Assertion fails if the range
     * is empty (that is, first == last).
     */
    template<typename K, typename Iterator>
    point<K> centroid(Iterator first, Iterator last);
}

#include "algorithm.ipp"

#endif
