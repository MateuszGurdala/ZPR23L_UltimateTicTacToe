set(REQUESTSRC "HttpRequest.cpp" "${INCLUDE}/HttpRequest.hpp")
set(RESPONSESRC "HttpResponse.cpp" "${INCLUDE}/HttpResponse.hpp")

add_library(HTTP "${REQUESTSRC}" "${RESPONSESRC}")