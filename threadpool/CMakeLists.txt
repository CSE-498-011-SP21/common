project(Threadpool)

find_package(TBB CONFIG REQUIRED)

enable_testing()
set(CMAKE_CXX_STANDARD 17)

add_library(threadpool SHARED src/threadpool.cc)
target_link_libraries(threadpool PUBLIC pthread)
target_link_libraries(threadpool PUBLIC TBB::tbb)
target_include_directories(threadpool PUBLIC include)

add_executable(threadpool_test test/threadpool_test.cc)
target_link_libraries(threadpool_test PRIVATE threadpool)

add_test(threadpool_test threadpool_test)