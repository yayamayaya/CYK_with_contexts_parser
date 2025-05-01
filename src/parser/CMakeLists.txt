
add_library(parser parser.cpp parser.hpp)

target_include_directories(
    parser
    PRIVATE
    ./../grammar/
    ./../graph_printer/
)

target_link_libraries(
        parser
        PRIVATE
        printer
    )
