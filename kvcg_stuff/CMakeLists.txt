set(CMAKE_CXX_STANDARD 17)

add_library(kvcg_stuff INTERFACE)
target_include_directories(kvcg_stuff INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>" "$<INSTALL_INTERFACE:include>")

add_library(kvcg_stuff_cuda INTERFACE)
target_include_directories(kvcg_stuff_cuda INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includeCUDA>" "$<INSTALL_INTERFACE:include>")

add_executable(kvcg_logging_test test/kvcg_logging_test.cc)
target_link_libraries(kvcg_logging_test PRIVATE kvcg_stuff)
target_compile_definitions(kvcg_logging_test PRIVATE COMPILE_LOG=DEBUG)

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY includeCUDA/ DESTINATION include)