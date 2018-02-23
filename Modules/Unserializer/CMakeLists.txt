cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_library(zia-unserializer SHARED
        ${CMAKE_CURRENT_LIST_DIR}/srcs/Unserializer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

      ${CMAKE_CURRENT_LIST_DIR}/include/Unserializer.hpp)

enable_testing()
target_link_libraries(zia-unserializer pthread)

set (CMAKE_CXX_FLAGS "-std=c++17")

add_executable(testUnserializer
        ${CMAKE_CURRENT_LIST_DIR}/srcs/Unserializer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

        ${CMAKE_CURRENT_LIST_DIR}/include/Unserializer.hpp
      ${CMAKE_CURRENT_LIST_DIR}/tests/UnserializerTests.cpp)
target_link_libraries(testUnserializer ${Boost_LIBRARIES})
add_test(TestBoost testUnserializer)
