// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "assert.hpp"
#include "box.hpp"
#include "sphere.hpp"

namespace geo
{
    // Creation ------------------------------------------------------------

    template<typename K>
    constexpr
    sphere<K>::sphere(point_type const& center, metric_type radius)
        : center_ {center}
        , squared_radius_ {radius * radius}
    {
        GEO_ASSERT(radius >= 0);
    }

    // Attributes ----------------------------------------------------------

    template<typename K>
    constexpr
    auto sphere<K>::center() const noexcept -> point_type
    {
        return center_;
    }

    template<typename K>
    constexpr
    auto sphere<K>::squared_radius() const noexcept -> metric_type
    {
        return squared_radius_;
    }

    template<typename K>
    auto sphere<K>::radius() const noexcept -> metric_type
    {
        return K::sqrt(squared_radius_);
    }

    // Analytic query ------------------------------------------------------

    template<typename K>
    constexpr
    auto sphere<K>::potential(point_type const& p) const noexcept -> metric_type
    {
        return squared_distance(p, center()) - squared_radius();
    }

    template<typename K>
    constexpr
    auto sphere<K>::gradient(point_type const& p) const noexcept -> vector_type
    {
        return scalar_type(2) * (p - center());
    }

    template<typename K>
    constexpr
    auto sphere<K>::oriented_distance(point_type const& p) const noexcept -> metric_type
    {
        return distance(p, center()) - radius();
    }

    template<typename K>
    constexpr
    auto sphere<K>::skin_map(point_type const& p) const noexcept -> scaling_type
    {
        return scalar_type(1) - radius() / distance(p, center());
    }

    // Basic algorithms --------------------------------------------------------

    template<typename K>
    box<K> bounding_box(sphere<K> const& s) noexcept
    {
        vector<K> semi_diagonal;
        auto const radius = s.radius();
        for (auto& e : semi_diagonal) {
            e = radius;
        }
        return box<K>{s.center() - semi_diagonal,
                      s.center() + semi_diagonal};
    }
}
