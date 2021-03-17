# common

Implementation of common data structures, classes, etc. that pop up all over the place when building a large system.

This is useful so that any optimizations that we make on common objects like a queue are able to immediately impact
all other components of this system.

## Setup

Requires TBB installed
This can be done if working in common from vcpkg

```shell
./vcpkg/vcpkg install tbb
```

Don't forget to set CMAKE_TOOLCHAIN_FILE to vcpkg/scripts/buildsystems/vcpkg.cmake