//
// Created by marmus_a on 29/01/18.
//

#pragma once
#ifndef CPP_ZIA_WINMODULELOADER_HPP
#define CPP_ZIA_WINMODULELOADER_HPP

#include <memory>
#include <Windows.h>
#include "IModuleLoader.hpp"

class WinModuleLoader : public IModuleLoader {
public:
	WinModuleLoader();
	~WinModuleLoader();
	virtual bool                                    loadLibrary(const std::string& path, const std::string& file);
	virtual zia::api::Module*                       loadModule();
	virtual zia::api::Net*                          loadNetwork();
	virtual bool                                    unloadLibrary();

private:
	HMODULE	                                        handler;
};

#endif //CPP_ZIA_WINMODULELOADER_HPP
