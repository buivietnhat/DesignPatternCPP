cmake_minimum_required(VERSION 3.21)
project(Observer)

set(CMAKE_CXX_STANDARD 20)

#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.71.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
#    add_executable(progname file1.cxx file2.cxx)
#    target_link_libraries(progname ${Boost_LIBRARIES})
endif()

add_executable(Observer boost_signal2.cpp)
