//
// Created by marmus_a on 29/01/18.
//

#include "Network.hpp"

#ifdef __unix__

extern "C" {
	zia::api::Net* create() {
		return (new Network);
	}
}

#endif // __unix__

#ifdef WIN32

extern "C" {
	__declspec(dllexport) zia::api::Net* __cdecl create() {
		return (new Network);
	}
}

#endif //WIN32