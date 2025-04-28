#include "parser.hpp"
#include <sstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <map>

words_t parser::string_to_words(const std::string& str)
{
    words_t words = {};
    
    std::string buf;
    std::stringstream ss(str);

    while (ss >> buf)
        words.push_back(buf);
    
    return words;
}

ret_t parser::parse_string(const std::string& str)
{
    if (!str.size())
    {
        std::cout << "> You can't parse an empty string!!" << std::endl;
        return EMPTY_STRING;
    }

    words_t tokens = string_to_words(str);

    return run_CYK(tokens);
}

ret_t parser::run_CYK(const words_t& w)
{
    size_t length = w.size();

    while (keep_running)
        for (index_t j = 0; j < length; j++)
        {
            keep_running = false;

            _t[j][j].merge(detect_terminal(w[j], j));

            for (index_t i = j; static_cast<int>(i) >= 0; i--)
                for (index_t k = i; k < j; k++)
                    _t[i][j].merge(detect_non_terminal(_t[i][k], _t[k + 1][j], i, j));
        }

    print_table();

    return 0;
}

std::set<non_terminal_t> parser::detect_terminal(const std::string& str, const index_t ind)
{
    std::set<non_terminal_t> non_terminals;
    
    for (auto rule : _gr.terminal_grammar)
        for (auto it : rule.second)
            if (it.first == str)
                if (find_contexts(it.second, ind, ind))
                    non_terminals.insert(rule.first);
    
    if (non_terminals.size())
        keep_running = true;

    return non_terminals;
}

std::set<non_terminal_t> parser::detect_non_terminal(const std::set<non_terminal_t>& values_f, const std::set<non_terminal_t>& values_s, const index_t ir, const index_t ic)
{
    std::set<non_terminal_t> non_terminals;

    for (auto rule : _gr.non_terminal_grammar)
        for (auto it : rule.second)
            if (find_element(values_f, it.first.first) && find_element(values_s, it.first.second))
                if (find_contexts(it.second, ir, ic))
                    non_terminals.insert(rule.first);

    if (non_terminals.size())
        keep_running = true;

    return non_terminals;
}

bool parser::find_contexts(const std::vector<context_t>& contexts, const index_t index_row, const index_t index_col)
{
    bool contexts_found = true;

    for (auto cnt : contexts)
    {
        auto i = detect_context_type(cnt.first, index_row, index_col);

        contexts_found &= find_element(_t[i.first][i.second], cnt.second);
        if (!contexts_found)
            return false;
    }

    return contexts_found;
}

std::pair<index_t, index_t> parser::detect_context_type(const Context_type type, const index_t ind_row, const index_t ind_col)
{
    switch (type)
    {
    case LEFT:      return {0, ind_row};

    case EXT_LEFT:  return {0, ind_col};
    
    case RIGHT:     return {ind_row, _t.size() - 1};

    case EXT_RIGHT: return {ind_col, _t.size() - 1};

    default:        break;
    }
    
    throw std::runtime_error("> Fatal error in programm");
}

bool parser::find_element(const std::set<non_terminal_t>& elems, const non_terminal_t val)
{
    return std::find(elems.begin(), elems.end(), val) != elems.end();
}

void parser::print_table()
{
    for (auto row : _t)
    {
        for (size_t i = 0; i < _t.size() - row.second.size(); i++)
            std::cout << std::setw(section_print_width)<<  " { } ";

        for (auto col : row.second)
        {
            std::stringstream os = {};

            os << "{ ";
            for (auto it : col.second)
                os << it << " ";
            os << "} ";

            std::cout << std::setw(section_print_width) << os.str();
        }

        std::cout << std::endl;
    }
}

void parser::set_grammar(const grammar& gr)
{
    _gr = gr;   
}