//
// Created by fumery on 02/02/18.
//

#ifndef CPP_ZIA_CONFPARSER_HPP
#define CPP_ZIA_CONFPARSER_HPP

#include	<string>
#include	<fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include "api/conf.h"
#include "ParserUtils.hpp"

class ConfParser {

public:
	ConfParser(const std::string&);
	~ConfParser();
	zia::api::ConfObject *parse();
	zia::api::ConfObject toConfObj(std::string All);
	zia::api::ConfArray toConfArray(std::string All);
	std::pair<std::string, zia::api::ConfValue> ParseFirstBloc();
	std::pair<std::string, zia::api::ConfValue> getPair(std::string elem);
	std::string getKey(std::string elem);
	std::pair<std::string, zia::api::ConfValue> getValueType(std::pair<std::string, zia::api::ConfValue> elemConf, std::string elem);

private:
    std::string FileName;
	std::string Content = "";
	ParserUtils utils;
};


#endif //CPP_ZIA_CONFPARSER_HPP
