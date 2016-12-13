// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// Assertion macros.
//
// This header has no inline implementation file (*.ipp).
//

#ifndef GEO_ASSERT_HPP
#define GEO_ASSERT_HPP

#include <cassert>

#if (GEO_ASSERT_LEVEL + 0) >= 1
# define GEO_ASSERT(cond) assert(cond)
#else
# define GEO_ASSERT(cond)
#endif

#if (GEO_ASSERT_LEVEL + 0) >= 2
# define GEO_EXTRA_ASSERT(cond) assert(cond)
#else
# define GEO_EXTRA_ASSERT(cond)
#endif

#endif
