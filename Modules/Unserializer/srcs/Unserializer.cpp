//
// Created by Elias Demnati on 10/02/2018.
//

#include    <iostream>
#include    "Unserializer.hpp"

std::map<zia::api::http::Version, std::string> versionMap = {
  {zia::api::http::Version::http_0_9, "HTTP/0.6"},
  {zia::api::http::Version::http_1_0, "HTTP/1.0"},
  {zia::api::http::Version::http_1_1, "HTTP/1.1"},
  {zia::api::http::Version::http_2_0, "HTTP/2.0"}
};

std::map<int, std::string> statusMap = {
  {(int)zia::api::http::common_status::continue_,                       "Continue"},
  {(int)zia::api::http::common_status::switching_protocols,             "Switching Protocols"},
  {(int)zia::api::http::common_status::ok,                              "OK"},
  {(int)zia::api::http::common_status::created,                         "Created"},
  {(int)zia::api::http::common_status::accepted,                        "Accepted"},
  {(int)zia::api::http::common_status::nonauthoritative_information,    "Non-Authorative Information"},
  {(int)zia::api::http::common_status::no_content,                      "No Content"},
  {(int)zia::api::http::common_status::reset_content,                   "Reset Content"},
  {(int)zia::api::http::common_status::partial_content,                 "Partial Content"},
  {(int)zia::api::http::common_status::multiple_choices,                "Multiple Choices"},
  {(int)zia::api::http::common_status::moved_permanently,               "Moved Permanently"},
  {(int)zia::api::http::common_status::found,                           "Found"},
  {(int)zia::api::http::common_status::see_other,                       "See Other"},
  {(int)zia::api::http::common_status::not_modified,                    "Not Modified"},
  {(int)zia::api::http::common_status::use_proxy,                       "Use Proxy"},
  {(int)zia::api::http::common_status::temporary_redirect,              "Temporary Redirect"},
  {(int)zia::api::http::common_status::bad_request,                     "Bad Request"},
  {(int)zia::api::http::common_status::unauthorized,                    "Unauthorized"},
  {(int)zia::api::http::common_status::payment_required,                "Payment Required"},
  {(int)zia::api::http::common_status::forbidden,                       "Forbidden"},
  {(int)zia::api::http::common_status::not_found,                       "Not Found"},
  {(int)zia::api::http::common_status::method_not_allowed,              "Method Not Allowed"},
  {(int)zia::api::http::common_status::not_acceptable,                  "Not Acceptable"},
  {(int)zia::api::http::common_status::proxy_authentication_required,   "Proxy Authentication Required"},
  {(int)zia::api::http::common_status::request_timeout,                 "Request Time-out"},
  {(int)zia::api::http::common_status::conflict,                        "Conflict"},
  {(int)zia::api::http::common_status::gone,                            "Gone"},
  {(int)zia::api::http::common_status::length_required,                 "Length Required"},
  {(int)zia::api::http::common_status::precondition_failed,             "Precondition Failed"},
  {(int)zia::api::http::common_status::request_entity_too_large,        "Request Entity Too Large"},
  {(int)zia::api::http::common_status::request_uri_too_large,           "Request-URI Too Long"},
  {(int)zia::api::http::common_status::unsupported_media_type,          "Unsupported Media Type"},
  {(int)zia::api::http::common_status::requested_range_not_satisfiable, "Requested range unsatisfiable"},
  {(int)zia::api::http::common_status::expectation_failed,              "Expectation failed"},
  {(int)zia::api::http::common_status::im_a_teapot,                     "I'm a teapot"},
  {(int)zia::api::http::common_status::internal_server_error,           "Internal Server Error"},
  {(int)zia::api::http::common_status::not_implemented,                 "Not Implemented"},
  {(int)zia::api::http::common_status::bad_gateway,                     "Bad Gateway"},
  {(int)zia::api::http::common_status::service_unavailable,             "Service Unavailable"},
  {(int)zia::api::http::common_status::gateway_timeout,                 "Gateway Time-out"},
  {(int)zia::api::http::common_status::http_version_not_supported,      "HTTP Version not supported"}
};

bool        Unserializer::config(const zia::api::Conf& conf) {
  return true;
}

bool        Unserializer::setResponse(std::stringstream& ss, zia::api::HttpDuplex& http) {
  ss << versionMap[http.resp.version] << " " << http.resp.status << " " << statusMap[http.resp.status] << "\r\n";

  for (auto& it: http.resp.headers) {
    ss << it.first << ": " << it.second << "\r\n";
  }

  return true;
}

bool        Unserializer::convertToByte(std::stringstream& ss, zia::api::HttpDuplex& http) {
  http.raw_resp.clear();

  for (auto& it: ss.str()) {
    http.raw_resp.push_back(static_cast<std::byte>(it));
  }

  for (auto& it: http.resp.body) {
    http.raw_resp.push_back(it);
  }

  return true;
}

bool        Unserializer::exec(zia::api::HttpDuplex& http) {
  std::stringstream ss;

  return this->setResponse(ss, http) && this->convertToByte(ss, http);
}
