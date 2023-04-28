set(REQUESTSRC "HttpRequest.cpp" "${INCLUDE}/http/HttpRequest.hpp")
set(RESPONSESRC "HttpResponse.cpp" "${INCLUDE}/http/HttpResponse.hpp")
set(HEADERSSRC "HttpHeaders.cpp" "${INCLUDE}/http/HttpHeaders.hpp")
set(HANDLERSRC "HttpHandler.cpp" "${INCLUDE}/http/HttpHandler.hpp")

add_library(Http "${REQUESTSRC}" "${RESPONSESRC}" "${HEADERSSRC}" "${HANDLERSRC}")