#ifndef PARSING_TABLE_H
#define PARSING_TABLE_H

#include <set>
#include <unordered_map>
#include "grammar.hpp"

using ret_t         = int;

using index_t       = unsigned int;

using nt_set        = std::set<non_terminal_t>;

using table         = std::unordered_map<std::pair<index_t, index_t>, nt_set>;

//Нетерминалы будут обозначаться уникальным набором символов (unsigned int)
//В таблице будут представлены в виде std::set
//Таблица будет иметь вид std::unordered_map<int, std::unordered_map<int, std::set<unsigned_int>>>
// Грамматика будет обозначаться в обратном?? виде
// A -> BC ====> <B{0x01}, C{0x02}> , A{0x03}
//Парсинг грамматик будет иметь unordered_map<char, unsigned int>
// Как будет задаваться контекст?
// Можно создать ещё одну таблицу для конекстов соответствующих грамматик
// A -> BC & < D =====> <B{0x01}, C{0x02}>, A{0x03} ; A{0x03}, std::vector <std::pair<LEFT, D{0x04}>>
// 

class parsing_table
{
    table _t;

public:

    parsing_table() =delete;

    parsing_table(const index_t height, const index_t width);    

    const nt_set& at(const index_t r, const index_t c);

    void insert(const index_t r, const index_t c, const non_terminal_t data);
}


#endif