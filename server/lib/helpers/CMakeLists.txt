set(INDEXCONVERTERSRC "${INCLUDE}/helpers/BoardIndexConverter.hpp" "BoardIndexConverter.cpp")
set(MOVESIMULATORSRC "${INCLUDE}/helpers/MoveSimulator.hpp" "MoveSimulator.cpp")

add_library(BoardIndexConverter ${INDEXCONVERTERSRC})
add_library(MoveSimulator ${MOVESIMULATORSRC})
target_link_libraries(MoveSimulator GameHandler)