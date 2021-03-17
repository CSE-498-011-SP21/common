find_package(TBB CONFIG REQUIRED)

add_library(threadpool SHARED src/threadpool.cc)
target_link_libraries(threadpool PUBLIC pthread)
target_link_libraries(threadpool PUBLIC TBB::tbb)
target_include_directories(threadpool PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" "$<INSTALL_INTERFACE:include>")

add_executable(threadpool_test test/threadpool_test.cc)
target_link_libraries(threadpool_test PRIVATE threadpool)

add_test(threadpool_test threadpool_test)

install(DIRECTORY include/ DESTINATION include)