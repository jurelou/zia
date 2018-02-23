//
// Created by marmus_a on 09/02/18.
//

#ifndef CPP_ZIA_SERVER_HPP
#define CPP_ZIA_SERVER_HPP


#include <string>
#include "Core.hpp"
#include "ConfParser.hpp"

class Server {
public:
    Server(const std::string& configFile = "./config.json");
    ~Server();

    bool        reloadConfig();
    bool        run();
private:
	Server() {}

    std::unique_ptr<zia::api::Conf>		config;
    std::string                 		configFile;
    std::unique_ptr<Core> 	      		core;
};


#endif //CPP_ZIA_SERVER_HPP
