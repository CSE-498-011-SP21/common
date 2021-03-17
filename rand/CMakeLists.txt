add_library(rand_static STATIC src/zipf.cc)
target_include_directories(rand_static PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" "$<INSTALL_INTERFACE:include>")

add_library(rand SHARED src/zipf.cc)
target_include_directories(rand PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" "$<INSTALL_INTERFACE:include>")

add_executable(zipf_test test/zipf_test.cc)
target_link_libraries(zipf_test PRIVATE rand)
add_test(zipf_test zipf_test)

install(DIRECTORY include/ DESTINATION include)