//
// Created by marmus_a on 29/01/18.
//

#pragma once
#include <iostream>
#include "WinModuleLoader.hpp"

WinModuleLoader::WinModuleLoader()
{
	this->handler = nullptr;
}

WinModuleLoader::~WinModuleLoader()
{
	if (this->handler) {
		this->unloadLibrary();
	}
}

bool WinModuleLoader::loadLibrary(const std::string & path, const std::string & file)
{
	if (this->handler) {
		this->unloadLibrary();
	}

	return (!!(this->handler = LoadLibrary(TEXT((path + file + ".dll").c_str()))));
}

zia::api::Module * WinModuleLoader::loadModule()
{
	zia::api::Module*		(*ptr)();

	ptr = reinterpret_cast<zia::api::Module*(*)()>(GetProcAddress(this->handler, "create"));
	if (ptr) {
		return (ptr());
	} else {
		return (nullptr);
	}
}

zia::api::Net * WinModuleLoader::loadNetwork()
{
	zia::api::Net*		(*ptr)();

	ptr = reinterpret_cast<zia::api::Net*(*)()>(GetProcAddress(this->handler, "create"));
	if (ptr) {
		return (ptr());
	} else {
		return (nullptr);
	}
}

bool WinModuleLoader::unloadLibrary(){
	this->handler = nullptr;
	return (true);
}
