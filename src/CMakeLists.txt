add_library(graph_parser graph_parser.cpp graph_parser.hpp)

target_link_libraries(graph_parser PRIVATE parser grammar printer)

target_include_directories(
    graph_parser
    PRIVATE
    ./parser/
    ./grammar/
    ./graph_printer/
)

add_subdirectory(parser)
add_subdirectory(grammar)
add_subdirectory(graph_printer)