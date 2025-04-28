add_library(context_parsing INTERFACE)

target_link_libraries(context_parsing INTERFACE parser grammar)

target_include_directories(
    context_parsing
    INTERFACE
    ./parser/
    ./grammar/
)

add_subdirectory(parser)
add_subdirectory(grammar)