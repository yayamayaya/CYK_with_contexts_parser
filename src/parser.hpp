#ifndef PARSER_HEADER
#define PARSER_HEADER

#include <set>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include "graph.h"
#include "grammar.hpp"

using ret_t         = int;

using index_t       = unsigned int;

using parsing_table = std::map<index_t, std::map<index_t, std::set<non_terminal_t>>>;

using words_t       = std::vector<std::string>;

// using graph         = std::unordered_map<index_t, std::unordered_map<index_t, char>>;

class parser
{
public:

    static constexpr ret_t EMPTY_STRING     = 0x11;

    static constexpr ret_t NOT_PARSED       = 0x12;

    static constexpr ret_t GRAMMAR_ADD_ERR  = 0x13;

private:
    
    parsing_table _t;

    index_t       _table_size;

    grammar       _gr;

    std::vector<std::tuple<index_t, std::pair<index_t, index_t>, non_terminal_t>> _right_contexts;

    std::vector<unsigned int> _current_path;

    bool volatile _keep_running;
    
    // bool volatile _going_back_counter;/

    words_t string_to_words(const std::string& str);

    ret_t   run_CYK(const words_t& w);

    bool insert_set_into_set(const std::set<non_terminal_t>& insert, std::set<non_terminal_t>& to);

    std::set<non_terminal_t> detect_terminal(const std::string& str, const index_t ind);

    bool check_right_contexts();

    void print_path();

    void fill_table_col(const index_t col_ind, const std::string& new_term);

    std::set<non_terminal_t> detect_non_terminal(const std::set<non_terminal_t>& values_f, const std::set<non_terminal_t>& values_s, const index_t ir, const index_t ic);

    bool find_element(const std::set<non_terminal_t>& elems, const non_terminal_t val);
    
    void clear_col();

    bool find_contexts(const std::vector<context_t>& contexts, const index_t index_row, const index_t index_col);

    std::pair<index_t, index_t> detect_context_type(const Context_type type, const index_t ind_row, const index_t ind_col);

    static constexpr int section_print_width = 20;

    static constexpr char no_connection      = '0';

public:

    parser(): _t(), _table_size(0), _gr(), _keep_running(true) {}

    ~parser() {}

    //Задать уже существующую грамматику
    void set_grammar(const grammar &gr);

    //Добавить правило к грамматике
    ret_t add_grammar_rule(const std::string &rule);

    //Запустить парсер для строк    
    ret_t parse_graph(const Graph& g, const index_t lhs);

    //Запустить парсер
    ret_t parse_string(const std::string& str);

    //Напечатать табличку парсинга
    const std::string print_table();

    //Напечатать граф
    void print_graph(const std::string& png_name);
};

#endif