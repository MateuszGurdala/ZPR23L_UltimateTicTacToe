#include "../../include/http/HttpResponse.hpp"

#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <sstream>
#include <string>

std::string defaultGetResponse = "HTTP/1.1 200 OK\n"
                                 "Access-Control-Allow-Credentials: true\n"
                                 "Access-Control-Allow-Headers: Content-Type\n"
                                 "Access-Control-Allow-Methods: GET\n"
                                 "Access-Control-Allow-Origin: *\n"
                                 "Allow: GET\n"
                                 "Connection: closed\n"
                                 "Content-Length: 0\n";

std::string defaultGetBodyResponse = "HTTP/1.1 200 OK\n"
                                 "Access-Control-Allow-Credentials: true\n"
                                 "Access-Control-Allow-Headers: Content-Type\n"
                                 "Access-Control-Allow-Methods: GET\n"
                                 "Access-Control-Allow-Origin: *\n"
                                 "Allow: GET\n"
                                 "Connection: closed\n";

std::string getDateTime() {
  auto now = std::chrono::system_clock::now();
  auto time = std::chrono::system_clock::to_time_t(now);
  auto timeStr = std::string(ctime(&time));
  std::string ret = "Date: " + timeStr.substr(0, timeStr.length() - 1) + "\n";
  return ret;
}

TEST_CASE("Default GET response is as expected.") {
  auto object = HttpResponse::GETResponse("");

  std::stringstream ss;
  ss << defaultGetResponse;
  ss << getDateTime();
  ss << "\n";

  REQUIRE(object.toString() == ss.str());
}

TEST_CASE("Default OPTIONS response is as expected.") {
  auto object = HttpResponse::OPTIONSResponse();

  std::stringstream ss;
  ss << defaultGetResponse;
  ss << getDateTime();
  ss << "\n";

  REQUIRE(object.toString() == ss.str());
}

TEST_CASE("Response with options is as expected.") {
    std::string body = "SomeBody";
  auto object = HttpResponse::GETResponse(body);

  std::stringstream ss;
  ss << defaultGetBodyResponse;
  ss << "Content-Length: " << body.length() << "\n";
  ss << getDateTime();
  ss << "\n";
  ss << body << "\n";

  REQUIRE(object.toString() == ss.str());
}