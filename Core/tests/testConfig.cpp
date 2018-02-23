//
// Created by fumery_a on 07/02/18.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestConfig

#include "ConfParser.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TestBoostCompilation) {
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE(ClassParse)
    BOOST_AUTO_TEST_CASE(execution) {
		BOOST_TEST_MESSAGE("TEST PARSER : ");
		BOOST_TEST_MESSAGE("TEST LONG");
		zia::api::ConfObject trueObj;
		zia::api::ConfArray array;

		std::unique_ptr<zia::api::ConfObject> conf;
		conf.reset(ConfParser("../../Core/tests/conf.json").parse());

		trueObj = std::get<zia::api::ConfObject>(conf->at("Core").v);
		BOOST_CHECK(std::get<long long>(trueObj.at("threads").v) == 4);
		BOOST_TEST_MESSAGE("TEST STRING");
		BOOST_CHECK(std::get<std::string>(trueObj.at("project").v) == "Zia");

		BOOST_TEST_MESSAGE("TEST JSONARRAY");

		array = std::get<zia::api::ConfArray>(trueObj.at("Array").v);
		trueObj = std::get<zia::api::ConfObject>(array.at(0).v);
		std::cout << std::get<std::string>(trueObj.at("testarray").v) << std::endl;

		BOOST_CHECK(std::get<std::string>(trueObj.at("testarray").v) == "itworks");
    }
 BOOST_AUTO_TEST_SUITE_END()
