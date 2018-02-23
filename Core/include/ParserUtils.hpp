//
// Created by fumery on 02/02/18.
//

#ifndef CPP_ZIA_PARSERUTILS_HPP
#define CPP_ZIA_PARSERUTILS_HPP

#include	<string>
#include	<fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>

class ParserUtils {

public:
	ParserUtils();
	~ParserUtils();

	std::string extract(const std::string& str, const char *beg, const char *end); //utils
	std::string getFragment(std::string all, std::string begin, std::string end);
	int getEnd(std::string all, std::string begin, std::string end);
	bool CheckStr(std::string All);
	std::string ClearIt(std::string str);
	bool CheckFile(std::string All);

	template<typename T, typename P>
	T rmSpc(T start, T end, P p);
};


#endif //CPP_ZIA_CONFPARSER_HPP
