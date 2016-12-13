// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Class for storing coordinate values.
//

#ifndef GEO_INTERNAL_COORDINATES_STORAGE_HPP
#define GEO_INTERNAL_COORDINATES_STORAGE_HPP

#include <istream>
#include <ostream>

namespace geo
{
    template<typename T, unsigned N>
    struct storage_alignment;

    /*
     * Sequence of N values of type T.
     *
     * The size of this class is exactly sizeof(T[N]) without padding and the
     * class is trivially copiable if T is a built-in type.
     */
    template<typename T, unsigned N>
    struct alignas(storage_alignment<T, N>::value) coordinates_storage
    {
        using scalar_type = T;
        using iterator = T*;
        using const_iterator = T const*;

        static constexpr unsigned dimension = N;
        static constexpr char delimiter = ' ';

        /*
         * Initializes coordinates to zeros.
         */
        constexpr
        coordinates_storage() noexcept;

        /*
         * Initializes coordinates to specified values.
         */
        template<typename... Xs>
        constexpr explicit
        coordinates_storage(Xs const&... coords) noexcept;

        /*
         * Range access.
         */
        constexpr iterator begin() noexcept;
        constexpr iterator end() noexcept;
        constexpr const_iterator begin() const noexcept;
        constexpr const_iterator end() const noexcept;
        constexpr const_iterator cbegin() const noexcept;
        constexpr const_iterator cend() const noexcept;

        /*
         * Coordinate access by indexing.
         */
        constexpr
        scalar_type& operator[](unsigned index);

        constexpr
        scalar_type const& operator[](unsigned index) const;

      private:
        scalar_type data_[dimension] {};
    };

    /*
     * Compares for coordinate-wise equality.
     */
    template<typename T, unsigned N>
    constexpr
    bool operator==(coordinates_storage<T, N> const& x,
                    coordinates_storage<T, N> const& y) noexcept;

    template<typename T, unsigned N>
    constexpr
    bool operator!=(coordinates_storage<T, N> const& x,
                    coordinates_storage<T, N> const& y) noexcept;

    /*
     * Input from stream. Expects space-delimited coordinate values.
     */
    template<typename Char, typename CharTraits, typename T, unsigned N>
    auto operator>>(std::basic_istream<Char, CharTraits>& in,
                    coordinates_storage<T, N>& coords)
    -> std::basic_istream<Char, CharTraits>&;

    /*
     * Output to stream. A space is used to delimit coordinate values.
     */
    template<typename Char, typename CharTraits, typename T, unsigned N>
    auto operator<<(std::basic_ostream<Char, CharTraits>& out,
                    coordinates_storage<T, N> const& coords)
    -> std::basic_ostream<Char, CharTraits>&;
}

#include "coordinates_storage.ipp"

#endif
