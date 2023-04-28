find_package(Catch2 3 REQUIRED)

set(HTTPHEADERSTESTS "http/HttpHeadersTest.cpp" "${INCLUDE}/http/HttpHeaders.hpp" "${LIB}/httphandler/HttpHeaders.cpp")

add_executable(TESTS ${HTTPHEADERSTESTS})
target_link_libraries(TESTS PRIVATE Catch2::Catch2WithMain)