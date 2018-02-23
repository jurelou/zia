//
// Created by Elias Demnati on 10/02/2018.
//

#define BOOST_TEST_DYN_LINK           // A ajouter dans le cas d'une liaison dynamique à Boost Test
#define BOOST_TEST_MODULE TestUnserializer

#include <boost/test/unit_test.hpp>
#include "Unserializer.hpp"

BOOST_AUTO_TEST_SUITE( requests )

BOOST_AUTO_TEST_CASE(normal_request) {
  Unserializer* unsrzl = new Unserializer();
  zia::api::HttpDuplex http;
  std::string raw_resp = "<html>\r\n<body>\r\n<h1>Hello, World!</h1>\r\n</body>\r\n</html>";

  http.resp.version = zia::api::http::Version::http_1_0;
  http.resp.status = zia::api::http::common_status::ok;
  http.resp.headers["Date"] = "Sun, 18 Oct 2012 10:36:20 GMT";
  http.resp.headers["Server"] = "Apache/2.2.14 (Win32)";
  http.resp.headers["Content-Length"] = "88";
  http.resp.headers["Connection"] = "Closed";
  http.resp.headers["Content-Type"] = "text/html";

  for (auto& it: raw_resp) {
    http.resp.body.push_back(static_cast<std::byte>(it));
  }

  BOOST_CHECK(unsrzl->exec(http));
}

BOOST_AUTO_TEST_CASE(no_body) {
  Unserializer* unsrzl = new Unserializer();
  zia::api::HttpDuplex http;

  http.resp.version = zia::api::http::Version::http_1_0;
  http.resp.status = zia::api::http::common_status::not_found;
  http.resp.headers["Date"] = "Sun, 18 Oct 2012 10:36:20 GMT";
  http.resp.headers["Server"] = "Apache/2.2.14 (Win32)";
  http.resp.headers["Connection"] = "Closed";
  http.resp.headers["Content-Type"] = "text/html";

  BOOST_CHECK(unsrzl->exec(http));
}

BOOST_AUTO_TEST_CASE(no_headers) {
  Unserializer* unsrzl = new Unserializer();
  zia::api::HttpDuplex http;
  std::string raw_resp = "<html>\r\n<body>\r\n<h1>Hello, World!</h1>\r\n</body>\r\n</html>";

  http.resp.version = zia::api::http::Version::http_1_0;
  http.resp.status = zia::api::http::common_status::ok;

  for (auto& it: raw_resp) {
    http.resp.body.push_back(static_cast<std::byte>(it));
  }

  BOOST_CHECK(unsrzl->exec(http));
}

BOOST_AUTO_TEST_SUITE_END()
