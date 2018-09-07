Lightweight point geometry for C++11
====================================

![C++11][cxx-badge]
[![Build Status][travis-badge]][travis-url]
[![Boost License][license-badge]][license-url]

This repository contains a single-file, header-only library of points and
vectors in the n-dimensional Euclidean space.

```c++
#include <iostream>
#include <geo.hpp>

int main()
{
    geo::point<double, 3> point = {1.2, 3.4, 5.6};
    point += {2.3, 4.5, 6.7};
    std::cout << point.distance({8.9, 0.1, 2.3}) << '\n';
}
```

[cxx-badge]: https://img.shields.io/badge/C%2B%2B-11-orange.svg
[license-badge]: https://img.shields.io/badge/license-Boost-blue.svg
[license-url]: https://raw.githubusercontent.com/snsinfu/geo/master/LICENSE.txt
[travis-badge]: https://travis-ci.org/snsinfu/geo.svg?branch=master
[travis-url]: https://travis-ci.org/snsinfu/geo

- [Installation](#installation)
- [Testing](#testing)
- [License](#license)
- [Alternatives](#alternatives)

## Installation

The geo library has no dependency and is single header-only. Just download
[geo.hpp][header] into your include directory.

```console
curl -LO https://raw.githubusercontent.com/snsinfu/geo/master/include/geo.hpp
```

[header]: https://raw.githubusercontent.com/snsinfu/geo/master/include/geo.hpp

## Testing

```console
git clone https://github.com/snsinfu/geo
cd geo/tests
make
```
## License

Boost Software License, Version 1.0.

## Alternatives

The geo library targets for small projects and prototypes that just need points
and/or vectors without any overwhelming features. So geo would be unsuited for
larger projects and you may find the following alternatives to be useful:

- [GLM][glm]: Many useful functions for 2D/3D graphics programming. Header-only.
- [CGAL][cgal]: Comprehensive geometric algorithms like Delaunay tesselation.
- [Eigen][eigen]: More of linear algebra than geometry. Header-only.

[glm]: https://glm.g-truc.net/
[cgal]: https://www.cgal.org/
[eigen]: https://eigen.tuxfamily.org/
