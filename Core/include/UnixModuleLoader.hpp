//
// Created by marmus_a on 29/01/18.
//

#ifndef CPP_ZIA_UNIXMODULELOADER_HPP
#define CPP_ZIA_UNIXMODULELOADER_HPP


#include <memory>
#include <dlfcn.h>
#include "IModuleLoader.hpp"

class UnixModuleLoader : public IModuleLoader {
public:
    UnixModuleLoader();
    ~UnixModuleLoader();
    virtual bool                                    loadLibrary(const std::string& path, const std::string& file);
    virtual zia::api::Module*                       loadModule();
    virtual zia::api::Net*                          loadNetwork();
    virtual bool                                    unloadLibrary();

private:
    void*                                       handler;
};


#endif //CPP_ZIA_UNIXMODULELOADER_HPP
