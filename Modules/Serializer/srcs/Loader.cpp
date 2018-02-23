//
// Created by marmus_a on 29/01/18.
//

#include "Serializer.hpp"

#ifdef __unix__

extern "C" {
	zia::api::Module* create() {
		return (new Serializer);
	}
}

#endif // __unix__

#ifdef WIN32

extern "C" {
	__declspec(dllexport) zia::api::Module* __cdecl create() {
		return (new Serializer);
	}
}

#endif //WIN32
