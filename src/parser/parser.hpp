#ifndef PARSER_HEADER
#define PARSER_HEADER

#include <set>
#include <map>
#include <string>
#include <vector>
#include "grammar.hpp"

using ret_t         = int;

using index_t       = unsigned int;

using parsing_table = std::map<index_t, std::map<index_t, std::set<non_terminal_t>>>;

using words_t       = std::vector<std::string>;

class parser
{
    parsing_table _t;

    parser(): _t() {}

    ~parser() {}

    words_t string_to_words(const std::string str);

public:

    ret_t parse_string(const grammar& gr, const std::string str);
};

#endif