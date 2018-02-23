cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_library(zia-ssl SHARED
            ${CMAKE_CURRENT_LIST_DIR}/include/Ssl.hpp
            ${CMAKE_CURRENT_LIST_DIR}/../Network/include/UnixSocket.hpp

            ${CMAKE_CURRENT_LIST_DIR}/include/SslSocket.hpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/SslSocket.cpp

            ${CMAKE_CURRENT_LIST_DIR}/../Network/srcs/UnixSocket.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Ssl.cpp)
endif (UNIX)

if (WIN32)
    add_library(zia-ssl SHARED
            )
endif (WIN32)

if (UNIX)
    target_link_libraries(zia-ssl pthread crypto ssl)
    set (CMAKE_CXX_FLAGS "-std=c++17")
endif(UNIX)


if (WIN32)
    target_link_libraries(zia-ssl Ws2_32)
endif(WIN32)