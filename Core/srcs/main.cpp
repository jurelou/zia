//
// Created by marmus_a on 25/01/18.
//

#include <iostream>
#include <Server.hpp>

int main(int ac, char **av) {
    if (ac > 1) {
        return (Server(std::string(av[1])).run());
    } else {
        std::cout << "usage: " << av[0] << " pathToConfigurationFile" << std::endl;
        return (true);
    }
}
