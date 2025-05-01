#include "graph_print.hpp"
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
    _table_size = static_cast<index_t>(w.size());

    while (_keep_running)
        for (index_t j = 0; j < _table_size; j++)
        {
            _keep_running = false;

            if (insert_set_into_set(detect_terminal(w[j], j), _t[j][j]))
                _keep_running = true;

            for (index_t i = j; static_cast<int>(i) >= 0; i--)
                for (index_t k = i; k < j; k++)
                    if (insert_set_into_set(detect_non_terminal(_t[i][k], _t[k + 1][j], i, j), _t[i][j]))
                        _keep_running = true;
        }

    if (_t[0][_table_size - 1].size())
        return 0;

    std::cout << "Expression does not check with the grammar! Check your input" << std::endl;
    return NOT_PARSED;
}

std::set<non_terminal_t> parser::detect_terminal(const std::string& str, const index_t ind)
{
    std::set<non_terminal_t> non_terminals;

    for (auto rule : _gr.terminal_grammar)
        for (auto it : rule.second)
            if (it.first == str)
                if (find_contexts(it.second, ind, ind))
                    non_terminals.insert(rule.first);

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

    return non_terminals;
}

bool parser::insert_set_into_set(const std::set<non_terminal_t>& insert, std::set<non_terminal_t>& to)
{
    bool inserted = 0;

    for (auto it : insert)
        inserted |= to.insert(it).second; 
    
    return inserted;
}

bool parser::find_contexts(const std::vector<context_t>& contexts, const index_t index_row, const index_t index_col)
{
    bool contexts_found = true;

    for (auto cnt : contexts)
    {
        try
        {            
            auto i = detect_context_type(cnt.first, index_row, index_col);
        
            contexts_found &= find_element(_t[i.first][i.second], cnt.second);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << '\n';
            return false;
        }
    }

    return contexts_found;
}

std::pair<index_t, index_t> parser::detect_context_type(const Context_type type, const index_t ind_row, const index_t ind_col)
{
    switch (type)
    {
    case LEFT:
        
        if (!ind_row)
            throw std::logic_error("Attempt to find left context on first symbol was made.");

        return {0, ind_row - 1};

    case EXT_LEFT:  return {0, ind_col};
    
    case RIGHT:     
    
        if (ind_row + 1 == _table_size)
            throw std::logic_error("Attempt to find right context on last symbol was made.");

        return {ind_row + 1, _table_size - 1};

    case EXT_RIGHT: return {ind_col, _table_size - 1};

    default:        break;
    }
    
    throw std::runtime_error("> Fatal error in programm");
}

bool parser::find_element(const std::set<non_terminal_t>& elems, const non_terminal_t val)
{
    return std::find(elems.begin(), elems.end(), val) != elems.end();
}

const std::string parser::print_table()
{
    std::stringstream os = {};

    for (auto row : _t)
    {
        for (size_t i = 0; i < _table_size - row.second.size(); i++)
            os << std::setw(section_print_width)<<  " { } ";

        for (auto col : row.second)
        {
            std::stringstream section = {};

            section << "{ ";
            for (auto it : col.second)
                section << it << " ";
            section << "} ";

            os << std::setw(section_print_width) << section.str();
        }

        os << std::endl;
    }

    return os.str();
}

void parser::set_grammar(const grammar& gr)
{
    _gr = gr;   
}

void parser::print_graph(const std::string& png_loc)
{
    graph_printer::print_graph(_t);

    graph_printer::dot_call(png_loc);
}