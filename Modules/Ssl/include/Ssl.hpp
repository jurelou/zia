//
// Created by louis on 22/02/18.
//

#ifndef CPP_ZIA_SSL_HPP
#define CPP_ZIA_SSL_HPP

#include "SslSocket.hpp"
#include <api/net.h>
#include <list>
#include <memory>
#include <thread>
#include <iostream>
#include <mutex>

#include <openssl/ssl.h>
#include <openssl/err.h>

class Ssl : public zia::api::Net {
public:
    Ssl();
    virtual ~Ssl();

    virtual bool    config(const zia::api::Conf& conf);
    virtual bool    run(zia::api::Net::Callback cb);
    virtual bool    stop();
    virtual bool    send(zia::api::ImplSocket* sock, const Raw& resp);

    friend void     networkRoutine(Ssl* net);
private:
    int                                     setFdsSet();
    fd_set                                  fdsSet;
    zia::api::Net::Callback                 callback;
    std::unique_ptr<ISocket>                listener;
    std::list<std::pair<std::shared_ptr<ISocket>, SSL *>>     sockets;
    std::unique_ptr<std::thread>            thread;
    std::mutex                              locker;

    SSL            *handshake(int sock);
    SSL_CTX         *ctx;


};

void                networkRoutine(Ssl* net);

#endif //CPP_ZIA_SSL_HPP
