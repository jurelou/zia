//
// Created by marmus_a on 16/02/18.
//

#ifndef CPP_ZIA_ISOCKET_HPP
#define CPP_ZIA_ISOCKET_HPP

#include "api/net.h"
namespace  zia::api {
    class ImplSocket {
    public:
        virtual bool bind(const std::string &addr, const std::string &port) = 0;
        virtual bool bind(const std::string &addr, int port) = 0;
        virtual bool listen() = 0;
        virtual bool accept(zia::api::ImplSocket &socket) = 0;
        virtual bool close() = 0;
        virtual int send(const std::string &str) = 0;
        virtual int recv(std::string &buff) = 0;
        virtual int getSocket() const = 0;
        virtual bool isOpen() const = 0;
        virtual const zia::api::NetInfo &getInfo() const = 0;
    };
}
class ISocket : public zia::api::ImplSocket {};
//class zia::api::ImplSocket : public ISocket {};

#endif //CPP_ZIA_ISOCKET_HPP
