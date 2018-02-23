cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_library(zia-serializer SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Serializer.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

            ${CMAKE_CURRENT_LIST_DIR}/include/Serializer.hpp)
endif (UNIX)

if (WIN32)
    add_library(zia-serializer SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/WinSocket.cpp)
endif (WIN32)


if (UNIX)
    enable_testing()
    target_link_libraries(zia-serializer pthread)

    set (CMAKE_CXX_FLAGS "-std=c++17")

    add_executable(testCompilationBoostSerializer
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Serializer.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

            ${CMAKE_CURRENT_LIST_DIR}/include/Serializer.hpp
            ${CMAKE_CURRENT_LIST_DIR}/tests/SerializerTests.cpp)
    target_link_libraries(testCompilationBoostSerializer ${Boost_LIBRARIES})
    add_test(TestBoost testCompilationBoostSerializer)
endif(UNIX)


if (WIN32)
    target_link_libraries(zia-serializer Ws2_32)
endif(WIN32)
