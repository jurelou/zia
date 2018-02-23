//
// Created by marmus_a on 28/01/18.
//

#ifndef CPP_ZIA_IMODULELOADER_HPP
#define CPP_ZIA_IMODULELOADER_HPP

#include <memory>
#include <string>
#include <api/module.h>
#include <api/net.h>

class IModuleLoader {
public:
    virtual bool                                    loadLibrary(const std::string& path, const std::string& file) = 0;
    virtual zia::api::Module*                       loadModule() = 0;
    virtual zia::api::Net*                          loadNetwork() = 0;
    virtual bool                                    unloadLibrary() = 0;
};

#endif //CPP_ZIA_IMODULELOADER_HPP
