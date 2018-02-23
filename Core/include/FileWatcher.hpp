//
// Created by marmus_a on 08/02/18.
//

#ifndef CPP_ZIA_FILEWATCHER_HPP
#define CPP_ZIA_FILEWATCHER_HPP

#ifdef __unix__

#include "UnixFileWatcher.hpp"
using FileWatcher = UnixFileWatcher;

#endif // __unix__

#ifdef _WIN32

#include "WinFileWatcher.hpp"
using FileWatcher = WinFileWatcher;

#endif //WIN32


#endif //CPP_ZIA_FILEWATCHER_HPP
