cmake_minimum_required(VERSION 3.28)
project(rh_go)

set (Boost_USE_STATIC_LIBS OFF)
set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED program_options unit_test_framework)

add_executable(rh_go src/main.cpp
        src/common/model/user.hpp)

target_link_libraries(rh_go Boost::program_options Boost::unit_test_framework)