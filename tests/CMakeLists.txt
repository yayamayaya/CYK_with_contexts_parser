add_executable(tests tests.cpp tests.hpp)

target_link_libraries(
    tests
    parser
    grammar
    ${GTEST_LIBRARIES}
    pthread
)

target_include_directories(
    tests
    PRIVATE
    ./../src/parser/
    ./../src/grammar/
)

