#include "../../include/http/HttpHeaders.hpp"

#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <string>

std::string allowOrigin = "*";

TEST_CASE("Empty HttpHeaders object can be created.") {
  auto object = HttpHeaders();

  REQUIRE(object.toString() == "");
}

TEST_CASE("Headers are successfully parsed and can be accessed.") {
  std::string testHeaders = "Header1: Data1\nHeader2: Data2\n";
  auto object = HttpHeaders(testHeaders);

  REQUIRE(object["Header1"] == "Data1");
  REQUIRE(object["Header2"] == "Data2");
}

TEST_CASE("toString method returns same result as raw headers data.") {
  std::string testHeaders = "Header1: Data1\nHeader2: Data2\n";
  auto object = HttpHeaders(testHeaders);

  REQUIRE(object.toString() == "Header1: Data1\nHeader2: Data2\n");
}

TEST_CASE("toString returns expected headers format.") {
  std::string testHeaders = "Header1: Data1\nHeader2: Data2\n";
  auto object = HttpHeaders();

  object.addHeader("Header1", "Data1");
  object.addHeader("Header2", "Data2");

  REQUIRE(object.toString() == testHeaders);
}

TEST_CASE("All methods of adding a header work.") {
  auto object = HttpHeaders();

  std::string key1 = "Header1";
  std::string value1 = "Data1";

  std::string key2 = "Header2";
  std::string value2 = "Data2";

  std::string key3 = "Header3";
  std::string value3 = "Data3";

  REQUIRE(object.addHeader(key1, value1) == 0);
  REQUIRE(object.addHeader("Header2", value2) == 0);
  REQUIRE(object.addHeader("Header3", "Data3") == 0);

  REQUIRE(object[key1] == value1);
  REQUIRE(object[key2] == value2);
  REQUIRE(object[key3] == value3);
}

TEST_CASE("Can't add same header twice.") {
  auto object = HttpHeaders();

  std::string key1 = "Header1";
  std::string value1 = "Data1";

  object.addHeader(key1, value1);

  REQUIRE(object[key1] == value1);
  REQUIRE(object.addHeader(key1, value1) == 1);
}

TEST_CASE("Content length header works.") {
  auto object = HttpHeaders();

  object.addContentLengthHeader(15);

  REQUIRE(object["Content-Length"] == "15");
}

TEST_CASE("CORS headers work.") {
  auto object = HttpHeaders();

  object.addCORSHeaders();

  std::string expected =
      "Access-Control-Allow-Credentials: true\n"
      "Access-Control-Allow-Headers: Content-Type\n"
      "Access-Control-Allow-Methods: GET\n"
      "Access-Control-Allow-Origin: *\n";

  REQUIRE(object.toString() == expected);
}

TEST_CASE("Copy operator works.") {
  std::string testHeaders = "Header1: Data1\nHeader2: Data2\n";
  auto object = HttpHeaders(testHeaders);
  HttpHeaders copy = object;

  REQUIRE(copy.toString() == object.toString());
}