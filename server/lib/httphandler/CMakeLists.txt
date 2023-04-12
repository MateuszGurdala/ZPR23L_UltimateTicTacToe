set(REQUESTSRC "HttpRequest.cpp" "${INCLUDE}/HttpRequest.hpp")
set(RESPONSESRC "HttpResponse.cpp" "${INCLUDE}/HttpResponse.hpp")

add_library(Http "${REQUESTSRC}" "${RESPONSESRC}")