# kj

`kj` is a small collection of [stb](https://github.com/nothings/stb) inspired libs.

library             | category
--------------------|----------
**kj.h**            | misc
**kj_atomic.h**     | multithreading
**kj_colour.h**     | graphics
**kj_datetime.h**   | date and time
**kj_io.h**         | io
**kj_math.h**       | maths
**kj_sse.h**        | simd
**kj_sync.h**       | multithreading
**kj_thread.h**     | multithreading

All the libraries target C/C++ for both win32 and linux.

*Warning: Still very early in development.*

## Usage

All the libraries follow the same pattern:

```
#define KJ(_MATH|_SYNC|...)_IMPL
#include "kj(_math|_sync|...).h"
```

The implementation part is only required *once* in a C/C++ file that includes
the header. Otherwise include only the header:

```
#include "kj(_math|_sync|...).h"
```

## License

These libraries are in the public domain (or the equivalent where that is not
possible). You can do anything you want with them. You have no legal obligation
to do anything else, although I appreciate attribution.
