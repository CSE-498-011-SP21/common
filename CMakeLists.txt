cmake_minimum_required(VERSION 3.0)

project(Common VERSION 0.0.1)

enable_testing()

add_subdirectory(rand)

add_subdirectory(threadpool)

add_subdirectory(kvcg_stuff)

install(TARGETS kvcg_stuff
        EXPORT CommonTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION kvcg_stuff/include
        )

install(EXPORT CommonTargets
        FILE CommonTargets.cmake
        NAMESPACE Common::
        DESTINATION lib/cmake/Common
        )

set(CPACK_PACKAGE_VENDOR "CSE 498")
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "CSE 498")
set(CPACK_SOURCE_GENERATOR "DEB")
set(CPACK_SOURCE_IGNORE_FILES
        /.git
        /dist
        /.*build.*
        /\\\\.DS_Store
        )
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6")

include(CPack)
