# GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Include source files for tests
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(tetris-tests ${TEST_SOURCES})

target_link_libraries(tetris-tests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(tetris-tests)