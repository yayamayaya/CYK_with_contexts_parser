add_executable(tests tests.cpp tests.hpp)

target_link_libraries(
    tests
    context_parsing
    ${GTEST_LIBRARIES}
    pthread
)

