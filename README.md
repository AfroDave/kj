# kj

`kj` is a small collection of [stb](https://github.com/nothings/stb) inspired libs.

library             | category
--------------------|----------
**kj.h**            | misc
**kj_math.h**       | maths
**kj_sse.h**        | simd
**kj_threading.h**  | multithreading
**kj_networking.h** | sockets

All the libraries target C/C++ for both win32 and linux.

*Warning: Still very early in development.*

## Usage

All the libraries follow the same pattern:

```
#define KJ(_MATH|_THREADING|...)_IMPL
#include "kj(_math|_threading|...).h"
```

The implementation part is only required *once* in a C/C++ file that includes
the header. Otherwise include only the header:

```
#include "kj(_math|_threading|...).h"
```

## License

These libraries are in the public domain (or the equivalent where that is not
possible). You can do anything you want with them. You have no legal obligation
to do anything else, although I appreciate attribution.
