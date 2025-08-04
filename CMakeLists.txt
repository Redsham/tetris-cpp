cmake_minimum_required(VERSION 3.31)
project(tetris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Init NCurses
set(CURSES_INCLUDE_PATH /opt/homebrew/opt/ncurses/include)
set(CURSES_LIBRARY /opt/homebrew/opt/ncurses/lib)

include_directories(${CURSES_INCLUDE_PATH})
link_directories(/opt/homebrew/opt/ncurses/lib)

# Set debug flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

# Include source files
include_directories(include)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Include tests
add_subdirectory(tests)

add_executable(tetris ${SOURCES})
target_link_libraries(tetris ncursesw)