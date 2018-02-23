//
// Created by marmus_a on 08/02/18.
//

#include <iostream>
#include "WinFileWatcher.hpp"

WinFileWatcher::WinFileWatcher(const std::string & fileToWatch)
{
	this->fileToWatch = fileToWatch;
	char	buff[4096];

	GetCurrentDirectory(4096, buff);
	if ((this->handle = FindFirstChangeNotification((std::string(buff) + "\\").c_str(), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE)) == INVALID_HANDLE_VALUE) {
		std::cerr << "WinFileWatcher Error " << buff << "\\" << fileToWatch << ": " << GetLastError() << std::endl;
	}
}

WinFileWatcher::~WinFileWatcher()
{
}

bool WinFileWatcher::waitForModification()
{
	char	buff[4096];

	GetCurrentDirectory(4096, buff);
	while (WaitForSingleObject(this->handle, INFINITE) != WAIT_OBJECT_0) {
		if ((this->handle = FindFirstChangeNotification((std::string(buff) + "\\").c_str(), FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE)) == INVALID_HANDLE_VALUE) {
			std::cerr << "WinFileWatcher Error " << buff << "\\" << this->fileToWatch << ": " << GetLastError() << std::endl;
			return (false);
		}
	}
	return (true);
}
