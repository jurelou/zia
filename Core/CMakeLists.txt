cmake_minimum_required(VERSION 3.9)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

if (UNIX)
    add_executable(zia
            # CLion Project Includes
            ${CMAKE_CURRENT_LIST_DIR}/include/Core.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/Server.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/Pipeline.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ThreadPool.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/IModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/UnixModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/FileWatcher.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/IFileWatcher.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/UnixFileWatcher.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ConfParser.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ParserUtils.hpp

            sza/api/http.h
            sza/api/net.h
            sza/api/conf.h
            sza/api/module.h

            ${CMAKE_CURRENT_LIST_DIR}/srcs/Core.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Server.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Pipeline.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/main.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/UnixModuleLoader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/ThreadPool.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/UnixFileWatcher.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/ConfParser.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/ParserUtils.cpp)
endif (UNIX)

if (WIN32)
    add_executable(zia
            # CLion Project Includes
			${CMAKE_CURRENT_LIST_DIR}/include/Core.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/Server.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/Pipeline.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ThreadPool.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/IModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/WinModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/FileWatcher.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/IFileWatcher.hpp
			${CMAKE_CURRENT_LIST_DIR}/include/WinFileWatcher.hpp

            sza/api/http.h
            sza/api/net.h
            sza/api/conf.h
            sza/api/module.h

			${CMAKE_CURRENT_LIST_DIR}/srcs/Core.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Server.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Pipeline.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/main.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/WinModuleLoader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/ThreadPool.cpp
			${CMAKE_CURRENT_LIST_DIR}/srcs/WinFileWatcher.cpp)
endif (WIN32)

if (UNIX)
    target_link_libraries(zia dl pthread)

    file (GLOB_RECURSE
            src_files_common
            ${CMAKE_CURRENT_LIST_DIR}/include/Core.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/Server.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/Pipeline.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ThreadPool.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/IModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/UnixModuleLoader.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/FileWatcher.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/IFileWatcher.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/UnixFileWatcher.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ConfParser.hpp
            ${CMAKE_CURRENT_LIST_DIR}/include/ParserUtils.hpp

            sza/api/http.h
            sza/api/net.h
            sza/api/conf.h
            sza/api/module.h

            ${CMAKE_CURRENT_LIST_DIR}/srcs/Core.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Server.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/Pipeline.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/UnixModuleLoader.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/ThreadPool.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/UnixFileWatcher.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/ConfParser.cpp
            ${CMAKE_CURRENT_LIST_DIR}/srcs/ParserUtils.cpp
            )

        add_executable(testConfig
                ${CMAKE_CURRENT_LIST_DIR}/tests/testConfig.cpp
                ${src_files_common}
                )

        add_executable(testCore
                ${CMAKE_CURRENT_LIST_DIR}/tests/testCore.cpp
                ${src_files_common}
                )
    target_link_libraries(testConfig ${Boost_LIBRARIES} dl pthread)
    target_link_libraries(testCore ${Boost_LIBRARIES} dl pthread)
    add_test(TestCore testCore TestConfig TestConfig)
endif(UNIX)

if (WIN32)
    target_link_libraries(zia Kernel32)
endif(WIN32)
