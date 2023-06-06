#include "../../include/http/HttpRequest.hpp"

#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>

std::string getRequest = "GET /TestEndpoint HTTP/1.1\n"
                         "Header1: Value1\n"
                         "Header2: Value2\n";

std::string getRequest2 = "GET /TestEndpoint2 HTTP/1.1\n"
                          "Header1: Value1\n"
                          "Header2: Value2\n";

std::string postRequest = "POST /TestEndpoint HTTP/1.1\n"
                          "Header1: Value1\n"
                          "Header2: Value2\n";

std::string getRequestQuery =
    "GET /TestEndpoint?query1=value1&query2=value2 HTTP/1.1\n"
    "Header1: Value1\n"
    "Header2: Value2\n";

std::string getRequestWithBody = "GET /ServerState HTTP/1.1\n"
                                 "Header1: Value1\n"
                                 "Header2: Value2\n"
                                 "\n"
                                 "TestBody";

TEST_CASE("Request endpoint is correctly parsed.") {
  std::string copy = getRequest;
  std::string copy2 = getRequest2;
  auto object = HttpRequest(std::move(copy));
  auto object2 = HttpRequest(std::move(copy2));

  REQUIRE(object.getEndpoint() == "/TestEndpoint");
  REQUIRE(object2.getEndpoint() == "/TestEndpoint2");
}

TEST_CASE("Request method is correctly parsed.") {
  std::string copy = getRequest;
  std::string copy2 = postRequest;
  auto object = HttpRequest(std::move(copy));
  auto object2 = HttpRequest(std::move(copy2));

  REQUIRE(object.getMethod() == method::GET);
  REQUIRE(object2.getMethod() == method::POST);
}

TEST_CASE("Request query params are parsed.") {
  std::string copy = getRequest;
  std::string copy2 = getRequestQuery;
  auto object = HttpRequest(std::move(copy));
  auto object2 = HttpRequest(std::move(copy2));

  REQUIRE(object.queryParams.empty() == true);
  REQUIRE(object2.queryParams.empty() == false);
}

TEST_CASE("Can get query params values.") {
  std::string copy = getRequestQuery;
  auto object = HttpRequest(std::move(copy));

  REQUIRE(object.queryParams.empty() == false);
  REQUIRE(object.queryParams.at("query1") == "value1");
  REQUIRE(object.queryParams.at("query2") == "value2");
}

TEST_CASE("Invalid query param returns empty string.") {
  std::string copy = getRequestQuery;
  auto object = HttpRequest(std::move(copy));

  REQUIRE(object.queryParams["query3"] == "");
}