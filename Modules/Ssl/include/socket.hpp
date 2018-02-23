//
// Created by louis on 22/02/18.
//

#ifndef CPP_ZIA_SOCKET_HPP
#define CPP_ZIA_SOCKET_HPP

#ifdef __unix__

#include "UnixSocket.hpp"
using Socket = UnixSocket;

#endif
#ifdef _WIN32

#include "WinSocket.hpp"
using Socket = WinSocket;

#endif

#endif //CPP_ZIA_SOCKET_HPP
