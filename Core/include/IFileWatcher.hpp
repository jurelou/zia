//
// Created by marmus_a on 08/02/18.
//

#ifndef CPP_ZIA_IFILEWATCHER_HPP
#define CPP_ZIA_IFILEWATCHER_HPP

#include <string>

class IFileWatcher {
public:
    virtual bool        waitForModification() = 0;
};

#endif //CPP_ZIA_IFILEWATCHER_HPP
