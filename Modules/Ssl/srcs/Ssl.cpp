//
// Created by louis on 22/02/18.
//

#include "Ssl.hpp"


Ssl::Ssl() : listener(new SslSocket), sockets(), thread(nullptr) {
    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
}

Ssl::~Ssl() {
    EVP_cleanup();
    for (auto &socket : this->sockets) {
        if (socket.first->isOpen()) {
            socket.first->close();
        }
    }
    if (this->listener->isOpen()) {
        this->listener->close();
    }
}

bool Ssl::config(const zia::api::Conf &conf) {
    const long long *port;
    const std::string *ipBinding;
    const std::string *cert;
    const std::string *key;

    if (!(port = std::get_if<long long>(&conf.at("port").v))) {
        std::cerr << "Error: Missing port field in Net configuration" << std::endl;
        return (false);
    }
    if (!(ipBinding = std::get_if<std::string>(&conf.at("ip_binding").v))) {
        std::cerr << "Error: Missing ip_binding field in Net configuration" << std::endl;
        return (false);
    }

    if (!(cert = std::get_if<std::string>(&conf.at("certificate").v))) {
        std::cerr << "Error: Missing port field in Net configuration" << std::endl;
        return (false);
    }
    if (!(key = std::get_if<std::string>(&conf.at("key").v))) {
        std::cerr << "Error: Missing port field in Net configuration" << std::endl;
        return (false);
    }

    /* create context */
    const SSL_METHOD *method;
    method = SSLv23_server_method();
    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        return false;
    }

    SSL_CTX_set_ecdh_auto(ctx, 1);

    if (SSL_CTX_use_certificate_file(ctx, (*cert).c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return false;
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, (*key).c_str(), SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        return false;
    }
    return (this->listener->bind(*ipBinding, static_cast<int>(*port)));
}

bool Ssl::run(zia::api::Net::Callback cb) {
    this->listener->listen();
    this->callback = cb;
    this->thread = std::make_unique<std::thread>(networkRoutine, this);
    return (true);
}

bool Ssl::stop() {
    {
        std::unique_lock<std::mutex> lock(this->locker);
        this->listener->close();
    }
    if (this->thread) {
        this->thread->join();
        this->thread.reset();
        this->thread = nullptr;
    }
    return (true);
}

bool Ssl::send(zia::api::ImplSocket *sock, const zia::api::Net::Raw &resp) {
    std::string     tmp;
    for (auto c : resp) {tmp += static_cast<char>(c);}
    if (sock) {
        sock->send(tmp);
    }
    return (true);
}

int Ssl::setFdsSet() {
    int         socketMax;
    FD_ZERO(&this->fdsSet);
    FD_SET(this->listener->getSocket(), &this->fdsSet);
    socketMax = this->listener->getSocket();
    for (auto& socket : this->sockets) {
        FD_SET(socket.first->getSocket(), &this->fdsSet);
        socketMax = ((socket.first->getSocket() > socketMax) ? (socket.first->getSocket()) : (socketMax));
    }
    return (socketMax + 1);
}

SSL            *Ssl::handshake(int sock){
    SSL *ssl;

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sock);
    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        return (nullptr);
    }
    else {
        return (ssl);
    }
}

void networkRoutine(Ssl* net) {
    struct timeval time;
    while (net->listener->isOpen()) {
        time = {1, 0};
        if (::select(net->setFdsSet(), &net->fdsSet, nullptr, nullptr, &time) >= 0) {
            std::unique_lock<std::mutex>    lock(net->locker);
            for (auto connexion : net->sockets) {
                if (FD_ISSET(connexion.first->getSocket(), &net->fdsSet)) {
                    std::string msg;
                    SslSocket *derivedPointer = dynamic_cast<SslSocket *>(connexion.first.get());
                    derivedPointer->recv(msg);
                    if (!msg.empty()) {
                        zia::api::Net::Raw raw;
                        for (auto c : msg) {
                            raw.push_back(static_cast<std::byte>(c));
                        }
                        net->callback(raw, connexion.first->getInfo());
                    } else {
                        connexion.first->close();
                    }
                }
            }

            net->sockets.remove_if([](std::pair<std::shared_ptr<ISocket>, SSL*> &socket) {
                return (!socket.first->isOpen());
            });

            if (FD_ISSET(net->listener->getSocket(), &net->fdsSet) && net->listener->isOpen()) {
                std::shared_ptr<SslSocket> connexion = std::make_shared<SslSocket>();
                if (net->listener->accept(*connexion)) {
                    SSL *ssl = net->handshake(connexion->getSocket());
                    if (ssl != nullptr)
                        connexion->setCtx(ssl);
                        net->sockets.push_back(std::make_pair(connexion, ssl));
                }
            }
        } else {
            perror("select");
        }
    }

    net->sockets.erase(net->sockets.begin(), net->sockets.end());
    //net->sockets.remove_if([] (std::shared_ptr<ISocket>& socket) {return (true);});
    return;
}
