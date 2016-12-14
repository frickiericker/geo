// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <istream>
#include <iterator>
#include <ostream>

#include "coordinates_storage.hpp"
#include "../assert.hpp"

namespace geo
{
    // Storage alignment -------------------------------------------------------

    namespace detail
    {
        inline constexpr
        bool is_power_of_two(unsigned n) noexcept
        {
            return n && !(n & (n - 1));
        }
    }

    // Align array as a big scalar if its size is a power of two. This way
    // the compiler may fit the array into a SIMD register.
    template<typename T, unsigned N>
    struct storage_alignment
    {
        static constexpr auto value =
            detail::is_power_of_two(alignof(T) * N) ? alignof(T) * N
                                                    : alignof(T);
    };

    // Creation ----------------------------------------------------------------

    template<typename T, unsigned N>
    constexpr
    coordinates_storage<T, N>::coordinates_storage() noexcept = default;

    template<typename T, unsigned N>
    template<typename... Xs>
    constexpr
    coordinates_storage<T, N>::coordinates_storage(Xs const&... coords) noexcept
        : data_ {coords...}
    {
    }

    // Element access ----------------------------------------------------------

    template<typename T, unsigned N>
    constexpr
    auto coordinates_storage<T, N>::begin() noexcept -> iterator
    {
        return std::begin(data_);
    }

    template<typename T, unsigned N>
    constexpr
    auto coordinates_storage<T, N>::end() noexcept -> iterator
    {
        return std::end(data_);
    }

    template<typename T, unsigned N>
    constexpr
    auto coordinates_storage<T, N>::begin() const noexcept -> const_iterator
    {
        return std::begin(data_);
    }

    template<typename T, unsigned N>
    constexpr
    auto coordinates_storage<T, N>::end() const noexcept -> const_iterator
    {
        return std::end(data_);
    }

    template<typename T, unsigned N>
    constexpr
    auto coordinates_storage<T, N>::cbegin() const noexcept -> const_iterator
    {
        return std::begin(data_);
    }

    template<typename T, unsigned N>
    constexpr
    auto coordinates_storage<T, N>::cend() const noexcept -> const_iterator
    {
        return std::end(data_);
    }

    template<typename T, unsigned N>
    constexpr
    T& coordinates_storage<T, N>::operator[](unsigned index)
    {
        GEO_EXTRA_ASSERT(index < dimension);
        return data_[index];
    }

    template<typename T, unsigned N>
    constexpr
    T const& coordinates_storage<T, N>::operator[](unsigned index) const
    {
        GEO_EXTRA_ASSERT(index < dimension);
        return data_[index];
    }

    // Regular operators -------------------------------------------------------

    template<typename T, unsigned N>
    constexpr
    bool operator==(coordinates_storage<T, N> const& x,
                    coordinates_storage<T, N> const& y) noexcept
    {
        for (unsigned i = 0; i < N; ++i) {
            if (x[i] != y[i]) {
                return false;
            }
        }
        return true;
    }

    template<typename T, unsigned N>
    constexpr
    bool operator!=(coordinates_storage<T, N> const& x,
                    coordinates_storage<T, N> const& y) noexcept
    {
        return !(x == y);
    }

    // Input/output ------------------------------------------------------------

    template<typename Char, typename CharTraits,
             typename T, unsigned N>
    auto operator>>(std::basic_istream<Char, CharTraits>& in,
                    coordinates_storage<T, N>& coords)
    -> std::basic_istream<Char, CharTraits>&
    {
        using stream_type = std::basic_istream<Char, CharTraits>;
        using sentry_type = typename stream_type::sentry;

        if (sentry_type sentry {in}) {
            for (T& coord : coords) {
                in >> std::ws >> coord;
            }
        }
        return in;
    }

    template<typename Char, typename CharTraits,
             typename T, unsigned N>
    auto operator<<(std::basic_ostream<Char, CharTraits>& out,
               coordinates_storage<T, N> const& coords)
    -> std::basic_ostream<Char, CharTraits>&
    {
        using stream_type = std::basic_ostream<Char, CharTraits>;
        using sentry_type = typename stream_type::sentry;

        if (sentry_type sentry {out}) {
            Char const delim = out.widen(coords.delimiter);
            bool need_delim = false;
            for (T const& coord : coords) {
                if (need_delim) {
                    out << delim;
                }
                out << coord;
                need_delim = true;
            }
        }
        return out;
    }
}
