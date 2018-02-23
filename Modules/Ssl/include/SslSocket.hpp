//
// Created by louis on 22/02/18.
//

#ifndef CPP_ZIA_SSLSOCKET_HPP
#define CPP_ZIA_SSLSOCKET_HPP

#include "Socket.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>


class   SslSocket : public Socket
{
public:
    SslSocket();
    ~SslSocket();

    virtual int         send(const std::string& str);
    virtual int         recv(std::string& buff);
    void                setCtx(SSL *ctx);
    virtual bool        accept(zia::api::ImplSocket &socket);

private:
    SSL                 *ctx;
};

#endif //CPP_ZIA_SSLSOCKET_HPP
