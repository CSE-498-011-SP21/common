project(Threadpool)

enable_testing()
set(CMAKE_CXX_STANDARD 17)

add_library(threadpool INTERFACE)
target_link_libraries(threadpool INTERFACE pthread)
target_include_directories(threadpool INTERFACE include)

add_executable(threadpool_test test/threadpool_test.cc)
target_link_libraries(threadpool_test PRIVATE threadpool)

#add_test(threadpool_test threadpool_test)