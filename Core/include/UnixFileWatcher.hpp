//
// Created by marmus_a on 08/02/18.
//

#ifndef CPP_ZIA_UNIXFILEWATCHER_HPP
#define CPP_ZIA_UNIXFILEWATCHER_HPP

#include <sys/inotify.h>
#include <limits>
#include <iostream>
#include <zconf.h>
#include "IFileWatcher.hpp"

class UnixFileWatcher : public IFileWatcher {
public:
    const static size_t BUFFLEN = (10 * (sizeof(struct inotify_event) + NAME_MAX + 1));
    UnixFileWatcher(const std::string& fileToWatch);
    virtual ~UnixFileWatcher();
    virtual bool        waitForModification();
private:
    UnixFileWatcher();

    int inotifyDescriptor;
    int watchDescriptor;
};


#endif //CPP_ZIA_UNIXFILEWATCHER_HPP
