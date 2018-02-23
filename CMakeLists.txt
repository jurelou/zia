cmake_minimum_required(VERSION 3.9)
project(cpp_zia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (UNIX)
	find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)
endif (UNIX)

include(Modules/CMakeLists.txt)
include(Core/CMakeLists.txt)
if (WIN32)
	include_directories(sza)
endif(WIN32)

if (UNIX)
	enable_testing()
	include_directories(sza ${Boost_INCLUDE_DIR})
	set (CMAKE_CXX_FLAGS "-std=c++17")
endif(UNIX)