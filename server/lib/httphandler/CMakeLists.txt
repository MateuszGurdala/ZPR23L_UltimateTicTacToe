set(REQUESTSRC "HttpRequest.cpp" "${INCLUDE}/HttpRequest.hpp")
set(RESPONSESRC "HttpResponse.cpp" "${INCLUDE}/HttpResponse.hpp")
set(HEADERSSRC "HttpHeaders.cpp" "${INCLUDE}/HttpHeaders.hpp")
set(HANDLERSRC "HttpHandler.cpp" "${INCLUDE}/HttpHandler.hpp")

add_library(Http "${REQUESTSRC}" "${RESPONSESRC}" "${HEADERSSRC}" "${HANDLERSRC}")