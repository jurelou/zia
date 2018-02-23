//
// Created by louis on 07/02/18.
//

#define BOOST_TEST_DYN_LINK           // A ajouter dans le cas d'une liaison dynamique à Boost Test
#define BOOST_TEST_MODULE tests_cgi

#include <boost/test/unit_test.hpp>
#include "Cgi.hpp"
BOOST_AUTO_TEST_SUITE( requests )


BOOST_AUTO_TEST_CASE(nocgi) {
    Cgi *cgi = new Cgi();
    zia::api::HttpDuplex duplex;
        duplex.req.uri = "https://argos.sh/index.zia";
        duplex.req.method = zia::api::http::Method::post;
        duplex.req.version = zia::api::http::Version::http_1_1;
        duplex.req.headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8";
    BOOST_CHECK(!cgi->exec(duplex));
}

BOOST_AUTO_TEST_CASE(wrong_path) {
        Cgi *cgi = new Cgi();
        zia::api::HttpDuplex duplex;
        duplex.req.uri = "https://argos.sh/cgi-bin/tutu";
        duplex.req.method = zia::api::http::Method::post;
        duplex.req.version = zia::api::http::Version::http_1_1;
        duplex.req.headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8";
        BOOST_CHECK(!cgi->exec(duplex));
}


BOOST_AUTO_TEST_CASE(simple_valid_request) {
        Cgi *cgi = new Cgi();
        zia::api::HttpDuplex duplex;
        duplex.req.uri = "https://argos.sh/cgi-bin/phpInfo.php";
        duplex.req.method = zia::api::http::Method::post;
        duplex.req.version = zia::api::http::Version::http_1_1;
        duplex.req.headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8";
        BOOST_CHECK(cgi->exec(duplex));
}

BOOST_AUTO_TEST_CASE(print_env) {
        Cgi *cgi = new Cgi();
        zia::api::HttpDuplex duplex;
        duplex.req.uri = "https://argos.sh/cgi-bin/env.php?toto=tutu&tutu=tutu&titi=titi";
        duplex.req.method = zia::api::http::Method::post;
        duplex.req.version = zia::api::http::Version::http_1_1;
        duplex.req.headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8";
        BOOST_CHECK(cgi->exec(duplex));
}

BOOST_AUTO_TEST_SUITE_END()
