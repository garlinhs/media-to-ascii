cmake_minimum_required(VERSION 3.0.2)

project(media_to_ascii VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-error=unused-result -pedantic -march=native -O3 -ffast-math -Wno-stringop-overflow")

find_package(OpenCV 4 REQUIRED)
find_package(Curses REQUIRED)

if(OpenCV_FOUND)
    message ("OpenCV package found")
else()
    message (FATAL_ERROR "Cannot find OpenCV package")
endif()

if(Curses_FOUND)
    message ("Curses package found")
else()
    message (FATAL_ERROR "Cannot find Curses package")
endif()

include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
  ${CURSES_INCLUDE_DIRS}
)

add_executable(
    media_to_ascii
    src/main.cpp
    src/menu.cpp
    src/audio.cpp
    src/helper.cpp
)

target_compile_options(media_to_ascii PRIVATE "-std=c++17" "-Werror")

target_link_libraries(
    media_to_ascii
    ${OpenCV_LIBS}
    ${CURSES_LIBRARIES}
    dl
    m
    pthread
)
