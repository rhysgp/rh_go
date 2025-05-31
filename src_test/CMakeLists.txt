cmake_minimum_required(VERSION 3.28)
project(rh_go_test CXX)

set (Boost_USE_STATIC_LIBS OFF)
set(CMAKE_CXX_STANDARD 23)

file(
  GLOB rh_go_test_SRC
  "*.cpp"
)

find_package(Boost REQUIRED program_options unit_test_framework)

add_executable(rh_go_test ${rh_go_test_SRC})

target_link_libraries(rh_go Boost::program_options Boost::unit_test_framework)