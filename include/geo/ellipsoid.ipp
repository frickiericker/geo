// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "box.hpp"
#include "ellipsoid.hpp"

namespace geo
{
    // Creation ------------------------------------------------------------

    template<typename K>
    constexpr
    ellipsoid<K>::ellipsoid(point_type const& center, scaling_type const& semiaxes)
        : center_ {center}
        , scaling_ {semiaxes}
        , quadratic_map_ {scaling_type(scalar_type(1)) / semiaxes}
    {
    }

    // Attributes ----------------------------------------------------------

    template<typename K>
    constexpr
    auto ellipsoid<K>::center() const noexcept -> point_type
    {
        return center_;
    }

    template<typename K>
    constexpr
    auto ellipsoid<K>::semiaxes() const noexcept -> scaling_type
    {
        return scaling_;
    }

    // Analytic query ------------------------------------------------------

    template<typename K>
    constexpr
    auto ellipsoid<K>::potential(point_type const& p) const noexcept -> metric_type
    {
        vector_type const r = p - center();
        vector_type const s = quadratic_map_(r);
        return inner_product(r, s) - metric_type(1);
    }

    template<typename K>
    constexpr
    auto ellipsoid<K>::gradient(point_type const& p) const noexcept -> vector_type
    {
        return scalar_type(2) * quadratic_map_(p - center());
    }

    template<typename K>
    constexpr
    auto ellipsoid<K>::oriented_distance(point_type const& p) const noexcept -> metric_type
    {
        return potential(p) / norm(gradient(p));
    }

    template<typename K>
    constexpr
    auto ellipsoid<K>::skin_map(point_type const& p) const noexcept -> scaling_type
    {
        // Formula derived via linear approximation.
        return (scalar_type(2) * potential(p) / squared_norm(gradient(p))) * quadratic_map_;
    }

    // Basic algorithms --------------------------------------------------------

    template<typename K>
    box<K> bounding_box(ellipsoid<K> const& e) noexcept
    {
        vector<K> ones;
        for (auto& component : ones) {
            component = 1;
        }
        auto const scaling = e.semiaxes();
        auto const semi_diagonal = scaling(ones);
        return box<K>{e.center() - semi_diagonal,
                      e.center() + semi_diagonal};
    }
}
