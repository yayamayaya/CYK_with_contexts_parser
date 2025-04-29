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

    index_t       _table_size;

    grammar       _gr;

    bool volatile _keep_running;
    
    words_t string_to_words(const std::string& str);

    ret_t   run_CYK(const words_t& w);

    bool insert_set_into_set(const std::set<non_terminal_t>& insert, std::set<non_terminal_t>& to);

    std::set<non_terminal_t> detect_terminal(const std::string& str, const index_t ind);

    std::set<non_terminal_t> detect_non_terminal(const std::set<non_terminal_t>& values_f, const std::set<non_terminal_t>& values_s, const index_t ir, const index_t ic);

    bool find_element(const std::set<non_terminal_t>& elems, const non_terminal_t val);

    bool find_contexts(const std::vector<context_t>& contexts, const index_t index_row, const index_t index_col);

    std::pair<index_t, index_t> detect_context_type(const Context_type type, const index_t ind_row, const index_t ind_col);

    static constexpr int section_print_width = 20;

public:

    parser(): _t(), _table_size(0), _gr(), _keep_running(true) {}

    ~parser() {}

    static constexpr ret_t EMPTY_STRING = 0x11;

    static constexpr ret_t NOT_PARSED   = 0x12;

    ret_t parse_string(const std::string& str);

    //Временно
    void set_grammar(const grammar& gr);

    void print_table();
};

#endif