add_library(parser parser.cpp parser.hpp)

target_include_directories(
    parser
    PUBLIC
    ./grammar/
)

target_include_directories(
    parser
    PRIVATE
    ./graph_printer/
)

target_link_libraries(
    parser
    PRIVATE
    printer
    grammar
)

add_subdirectory(grammar)
add_subdirectory(graph_printer)