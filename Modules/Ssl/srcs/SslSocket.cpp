//
// Created by louis on 22/02/18.
//

#include "SslSocket.hpp"



SslSocket::SslSocket() {
    this->ctx = nullptr;
}

SslSocket::~SslSocket() {}


int                     SslSocket::send(const std::string& str) {
    int err;
    if (!ctx){
        return (0);
    }
    err = SSL_write(ctx, str.c_str(), strlen(str.c_str()));
    return (err);
}


bool SslSocket::accept(zia::api::ImplSocket &socket) {
    socklen_t addrLen;
    auto unixSocket = dynamic_cast<SslSocket *>(&socket);
    if (unixSocket) {
        if ((unixSocket->socket = ::accept(this->socket, (struct sockaddr *)&unixSocket->addr, &addrLen)) < 0) {
            std::cerr << "Fail to accept " << inet_ntoa(unixSocket->addr.sin_addr) << std::endl;
            return (false);
        }
        unixSocket->netInfo.ip.i = unixSocket->addr.sin_addr.s_addr;
        unixSocket->netInfo.ip.str = ::inet_ntoa(unixSocket->addr.sin_addr);
        unixSocket->netInfo.port = this->netInfo.port;
        unixSocket->netInfo.time = std::chrono::system_clock::now();
        unixSocket->opened = true;
        return (true);
    }
    return (false);
}

int                     SslSocket::recv(std::string& buff) {
    char   buffer[4096];
    int    res;

    if (!ctx){
        return (0);
    }
    res = SSL_read(ctx, buffer, sizeof(buffer)-1);
    buffer[res] = 0;
    buff = buffer;
    return (res);
}

void                SslSocket::setCtx(SSL *ctx){
    this->ctx = ctx;
}