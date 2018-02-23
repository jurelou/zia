//
// Created by louis on 29/01/18.
//

#include "Ssl.hpp"

#ifdef __unix__

extern "C" {
	zia::api::Net* create() {
		return (new Ssl);
	}
}

#endif // __unix__

#ifdef WIN32

extern "C" {
	__declspec(dllexport) zia::api::Net* __cdecl create() {
		return (new Ssl);
	}
}

#endif //WIN32