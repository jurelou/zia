//
// Created by louis on 10/02/18.
//

#include "Cgi.hpp"

#ifdef __unix__

extern "C" {
	zia::api::Module* create() {
		return (new Cgi);
	}
}

#endif // __unix__

#ifdef WIN32

extern "C" {
	__declspec(dllexport) zia::api::Module* __cdecl create() {
		return (new Cgi);
	}
}

#endif //WIN32