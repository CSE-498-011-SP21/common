project(Rand)

add_library(rand_static STATIC src/zipf.cc)
target_include_directories(rand_static PUBLIC include)

add_library(rand SHARED src/zipf.cc)
target_include_directories(rand PUBLIC include)

add_executable(zipf_test test/zipf_test.cc)
target_link_libraries(zipf_test PRIVATE rand)