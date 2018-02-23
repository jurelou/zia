//
// Created by marmus_a on 08/02/18.
//

#ifndef CPP_ZIA_WINFILEWATCHER_HPP
#define CPP_ZIA_WINFILEWATCHER_HPP

#include <Windows.h>
#include "IFileWatcher.hpp"

class WinFileWatcher : public IFileWatcher {
public:
	WinFileWatcher(const std::string& fileToWatch);
	virtual ~WinFileWatcher();
	virtual bool        waitForModification();
private:
	WinFileWatcher();

	HANDLE WINAPI handle;
	std::string			fileToWatch;
};

#endif //CPP_ZIA_WINFILEWATCHER_HPP
