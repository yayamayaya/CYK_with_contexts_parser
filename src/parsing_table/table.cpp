#include <iostream>
#include "table.hpp"

parsing_table::parsing_table(const index_t height, const index_t width)
{
    for (index_t i = 0; i < height; i++)
        for (index_t j = 0; j < width; j++)
            _t.insert(std::make_pair(i, j), {});
}

const nt_set& parsing_table::at(const index_t r, const index_t c)
{
    auto it = _t.find(std::make_pair(r, c));
    if (it == _t.end())
        throw std::out_of_range("> Reaching beyond table boundaries!");
    
    return it->second;
}

void parsing_table::insert(const index_t r, const index_t c, const non_terminal_t data)
{
    auto it = _t.find(std::make_pair(r, c));
    if (it == _t.end())
        throw std::out_of_range("> Reaching beyond table boundaries!");

    it->second.insert(data);
}