find_package(Catch2 3 REQUIRED)
add_executable(TESTS test.cpp)
target_link_libraries(TESTS PRIVATE Catch2::Catch2WithMain)