add_library(parsing_table table.cpp table.hpp)

target_include_directories(
    parsing_table
    PRIVATE
    ./../grammar/
)