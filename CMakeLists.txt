cmake_minimum_required(VERSION 3.16)
project(NSI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(nsi
    main.cpp
    logo.cpp
    port.cpp
    website.cpp
    check_website.cpp
)

target_compile_options(nsi PRIVATE -Wall -Wextra -Wpedantic)
