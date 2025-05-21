
add_library(printer graph_print.cpp graph_print.hpp)

target_include_directories(
    printer
    PUBLIC
    ./../grammar/
    ./../
    ./../graph/
)