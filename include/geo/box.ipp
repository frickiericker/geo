// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <algorithm>

#include "box.hpp"

namespace geo
{
    // Creation ----------------------------------------------------------------

    template<typename K>
    constexpr
    box<K>::box() noexcept
    {
        for (scalar_type& coord : highest_vertex_) {
            coord = scalar_type(1);
        }
    }

    template<typename K>
    constexpr
    box<K>::box(point_type const& p, point_type const& q)
    {
        point_type lowest;
        point_type highest;

        for (unsigned i = 0; i < dimension; ++i) {
            lowest[i] = std::min(p[i], q[i]);
            highest[i] = std::max(p[i], q[i]);
        }

        lowest_vertex_ = lowest;
        highest_vertex_ = highest;
    }

    // Attributes --------------------------------------------------------------

    template<typename K>
    constexpr
    auto box<K>::lowest_vertex() const noexcept -> point_type
    {
        return lowest_vertex_;
    }

    template<typename K>
    constexpr
    auto box<K>::highest_vertex() const noexcept -> point_type
    {
        return highest_vertex_;
    }

    template<typename K>
    constexpr
    auto box<K>::diagonal_span() const noexcept -> vector_type
    {
        return highest_vertex() - lowest_vertex();
    }

    template<typename K>
    constexpr
    auto box<K>::center() const noexcept -> point_type
    {
        return lowest_vertex() + diagonal_span() / scalar_type(2);
    }

    template<typename K>
    constexpr
    auto box<K>::volume() const noexcept -> metric_type
    {
        metric_type vol = 1;
        for (scalar_type side : diagonal_span()) {
            vol *= side;
        }
        return vol;
    }
}
