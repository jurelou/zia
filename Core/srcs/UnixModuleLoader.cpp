//
// Created by marmus_a on 29/01/18.
//

#include <iostream>
#include "UnixModuleLoader.hpp"


UnixModuleLoader::UnixModuleLoader() {
    this->handler = nullptr;
}

UnixModuleLoader::~UnixModuleLoader() {
    if (this->handler) {
        dlclose(this->handler);
    }
}

bool UnixModuleLoader::loadLibrary(const std::string& path, const std::string &file) {
    std::cout << "Loading: " << "lib" + file + ".so" << std::endl;
    if (this->handler) {
        //TODO ProperLibLoader
        //unloadLibrary();
    }
    return (!!(this->handler = dlopen((path + "lib" + file + ".so").c_str(), RTLD_LAZY)));
}

zia::api::Module* UnixModuleLoader::loadModule() {
    zia::api::Module*   (*ptr)();

    ptr = reinterpret_cast<zia::api::Module*(*)()>(dlsym(this->handler, "create"));
    if (ptr) {
        return (ptr());
    } else {
        return (nullptr);
    }
}

bool UnixModuleLoader::unloadLibrary() {
    if (this->handler) {
        dlclose(this->handler);
        this->handler = nullptr;
        return (true);
    }
    return (false);
}

zia::api::Net* UnixModuleLoader::loadNetwork() {
    zia::api::Net*   (*ptr)();

    ptr = reinterpret_cast<zia::api::Net*(*)()>(dlsym(this->handler, "create"));
    if (ptr) {
        return (ptr());
    } else {
        return (nullptr);
    }
}