cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_library(zia-cgi SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Cgi.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

            ${CMAKE_CURRENT_LIST_DIR}/include/Cgi.hpp)
endif (UNIX)

if (WIN32)
    add_library(zia-cgi SHARED
            ${CMAKE_CURRENT_LIST_DIR}/srcs/WinSocket.cpp)
endif (WIN32)


if (UNIX)
    enable_testing()
    target_link_libraries(zia-cgi pthread)

    set (CMAKE_CXX_FLAGS "-std=c++17")

    add_executable(testCompilationBoostCgi
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Cgi.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp

            ${CMAKE_CURRENT_LIST_DIR}/include/Cgi.hpp
            ${CMAKE_CURRENT_LIST_DIR}/tests/tests_cgi.cpp)
    target_link_libraries(testCompilationBoostCgi ${Boost_LIBRARIES})
    add_test(TestBoost testCompilationBoostCgi)

endif(UNIX)


if (WIN32)
    target_link_libraries(zia-cgi Ws2_32)
endif(WIN32)