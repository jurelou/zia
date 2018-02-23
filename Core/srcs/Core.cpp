//
// Created by marmus_a on 09/02/18.
//

#include "Core.hpp"

Core::Core() {
    this->net = nullptr;
    this->pipeline = nullptr;
}


Core::~Core() {
    delete this->net;
    delete this->pipeline;
}

bool Core::run(const zia::api::Conf& config) {
    if (!this->config(config) || !this->pipeline) {
        return (false);
    }
    return (this->net->run(this->pipeline->getCallback(*this->net)));
}

bool Core::loadCoreModule(const std::string& lib, const std::string& path){

   if (!this->moduleLoader.loadLibrary(path, lib)) {
        std::cerr << "Error: Unable to load Library " << path << lib << std::endl;
        return (false);
    }
    if (zia::api::Module *loadedModule = this->moduleLoader.loadModule()) {
        this->pipeline->push_back(std::shared_ptr<zia::api::Module>(loadedModule));
    } else {
        std::cerr << "Error: can't load module from library " << path <<lib << std::endl;
        return (false);
    }
    return (true);
}

bool Core::config(const zia::api::Conf& config) {
    try {
        if (config.find("Core") != config.end()) {
            if (auto CoreConfig = std::get_if<zia::api::Conf>(&config.at("Core").v)) {
                if (CoreConfig->find("workers") != CoreConfig->end()) {
                    if (auto workers = std::get_if<long long>(&CoreConfig->at("workers").v)) {
                        this->pipeline = new Pipeline(static_cast<int>(*workers));
                    }
                } else {
                    this->pipeline = new Pipeline(4);
                }
            } else {
                std::cerr << "Error: Bad type for core config" << std::endl;
                return (false);
            }
        } else {
            std::cerr << "Error: Missing core config" << std::endl;
            return (false);
        }
        if (auto netConfig = std::get_if<zia::api::Conf>(&config.at("Net").v)) {
            std::string netpath;
            if (netConfig->find("path") == netConfig->end()) {
                netpath = "";
            } else {
                if (auto tmpNetPath = std::get_if<std::string>(&netConfig->at("path").v)) {
                    netpath = *tmpNetPath;
                }
            }
            if (auto libname = std::get_if<std::string>(&netConfig->at("lib").v)) {
                if (!this->moduleLoader.loadLibrary(netpath, *libname)) {
                    std::cerr << "Error: Failed to load " << netpath << *libname << std::endl;
                    return (false);
                }
            }

            if (!(this->net = this->moduleLoader.loadNetwork())) {
                std::cerr << "Error: Failed to instanciate module Net" << std::endl;
                return (false);
            }

            if (auto netInternConfig = std::get_if<zia::api::Conf>(&netConfig->at("config").v)) {
                if (!this->net->config(*netInternConfig)) {
                    return (false);
                }
            } else {
                std::cerr << "Error: Missing config in Module Net" << std::endl;
                return (false);
            }
        } else {
            std::cerr << "Error: Missing module Net in configuration file" << std::endl;
            return (false);
        }

        //TODO Load Pipeline's Modules
        if (auto moduleList = std::get_if<zia::api::ConfArray>(&config.at("Modules").v)) {
            if (!this->loadCoreModule("zia-serializer", "./")){
                return (false);
            }
            for (auto item : *moduleList) {
                const zia::api::Conf *moduleConf;
                const zia::api::Conf *moduleInternConfig;
                std::string path;
                const std::string *name;
                const std::string *lib;
                if (!(moduleConf = std::get_if<zia::api::Conf>(&item.v))) {
                    std::cerr << "Error: bad Module conf type" << std::endl;
                    return (false);
                }
                if (moduleConf->find("path") != moduleConf->end()) {
                    if (auto tmpPath = std::get_if<std::string>(&moduleConf->at("path").v)) {
                        path = *tmpPath;
                    }
                } else {
                    path = "";
                }
                if (!(name = std::get_if<std::string>(&moduleConf->at("name").v))) {
                    std::cerr << "Error: Missing field name in a Module" << std::endl;
                    return (false);
                }
                if (!(lib = std::get_if<std::string>(&moduleConf->at("lib").v))) {
                    std::cerr << "Error: Missing field lib in Module " << *name << std::endl;
                    return (false);
                }
                if (!(moduleInternConfig = std::get_if<zia::api::Conf>(&moduleConf->at("config").v))) {
                    std::cerr << "Error: Missing config of Module " << *name << std::endl;
                    return (false);
                }
                if (!this->moduleLoader.loadLibrary(path, *lib)) {
                    std::cerr << "Error: Unable to load Library " << path << *lib << std::endl;
                    return (false);
                }
                if (zia::api::Module *loadedModule = this->moduleLoader.loadModule()) {
                    if (!loadedModule->config(*moduleInternConfig)) {
                        std::cerr << "Error: Configuration of module " << *name << " failed" << std::endl;
                        return (false);
                    }
                    this->pipeline->push_back(std::shared_ptr<zia::api::Module>(loadedModule));
                } else {
                    std::cerr << "Error: can't load module from library " << path << *lib << std::endl;
                    return (false);
                }
            }
            if (!this->loadCoreModule("zia-unserializer", "./")){
                return (false);
            }
            return (true);
        } else {
            std::cerr << "Error: Missing field Modules in configuration" << std::endl;
            return (false);
        }
    } catch(std::exception& err) {
        std::cerr << err.what() << std::endl;
        return (false);
    }
}

bool Core::stop() {
    if (this->net) {
        return (this->net->stop());
    }
    std::cerr << "No running Server" << std::endl;
    return (false);
}
