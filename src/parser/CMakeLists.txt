
add_library(parser parser.cpp parser.hpp)

target_include_directories(
    parser
    PRIVATE
    ./../grammar/
)