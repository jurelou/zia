cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_library(zia-network SHARED
            ${CMAKE_CURRENT_LIST_DIR}/include/Socket.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ISocket.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/Network.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/UnixSocket.hpp

            ${CMAKE_CURRENT_LIST_DIR}/srcs/UnixSocket.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Network.cpp)
endif (UNIX)

if (WIN32)
    add_library(zia-network SHARED
            ${CMAKE_CURRENT_LIST_DIR}/include/Socket.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ISocket.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/WinSocket.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/Network.hpp

            ${CMAKE_CURRENT_LIST_DIR}/srcs/Loader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Network.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/WinSocket.cpp)
endif (WIN32)

if (UNIX)
    target_link_libraries(zia-network pthread)
    set (CMAKE_CXX_FLAGS "-std=c++17")
endif(UNIX)


if (WIN32)
    target_link_libraries(zia-network Ws2_32)
endif(WIN32)