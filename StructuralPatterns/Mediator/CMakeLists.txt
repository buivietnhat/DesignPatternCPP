cmake_minimum_required(VERSION 3.22)
project(Mediator)

find_package(Boost 1.71.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(Mediator main.cpp)
