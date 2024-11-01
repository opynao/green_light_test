include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB TEST_FILES *.cpp)

add_executable(tests ${TEST_FILES})

target_link_libraries(tests gtest gtest_main ${PROJECT_NAME}_lib)

include(GoogleTest)
gtest_discover_tests(tests)
