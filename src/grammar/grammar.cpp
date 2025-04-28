#include "grammar.hpp"

void grammar::add_non_terminal_grammar(const non_terminal_t gr, const std::vector<std::pair<grammar_pair_t, std::vector<context_t>>>& val)
{
    non_terminal_grammar[gr] = val;
}

void grammar::add_terminal_grammar(const non_terminal_t gr, const std::vector<std::pair<std::string, std::vector<context_t>>>& val)
{
    terminal_grammar[gr] = val;
}