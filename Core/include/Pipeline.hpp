//
// Created by marmus_a on 27/01/18.
//

#ifndef CPP_ZIA_PIPELINE_HPP
#define CPP_ZIA_PIPELINE_HPP

#include <iostream>
#include <memory>
#include <vector>
#include "api/module.h"
#include "ThreadPool.hpp"
#include "ISocket.hpp"

class Pipeline : public std::vector<std::shared_ptr<zia::api::Module>>{
public:
    Pipeline(int nbWorker = 4);
    ~Pipeline();

    void                                    run(zia::api::Net::Raw, zia::api::NetInfo, zia::api::Net& network) const;
    zia::api::Net::Callback                 getCallback(zia::api::Net& network) const;
private:
    ThreadPool*     pool;
};

#endif //CPP_ZIA_PIPELINE_HPP
