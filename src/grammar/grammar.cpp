#include "grammar.hpp"
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>

static std::vector<std::string> unique_non_terminals;

static non_terminal_t get_non_terminal_id(const std::string& name) {
    auto it = std::find(unique_non_terminals.begin(), unique_non_terminals.end(), name);
    if (it != unique_non_terminals.end())
        return static_cast<non_terminal_t>(std::distance(unique_non_terminals.begin(), it));

    unique_non_terminals.push_back(name);
    return static_cast<non_terminal_t>(unique_non_terminals.size() - 1);
}

static Context_type parse_context_type(const std::string& token) {
    if (token == "<") return LEFT;
    if (token == ">") return RIGHT;
    if (token == "<=") return EXT_LEFT;
    if (token == ">=") return EXT_RIGHT;
    throw std::runtime_error("Unknown context operator: " + token);
}

void grammar::add_terminal_grammar(const non_terminal_t gr, const std::vector<std::pair<std::string, std::vector<context_t> > > & val) {
    auto& vec = terminal_grammar[gr];
    vec.insert(vec.end(), val.begin(), val.end());
}

void grammar::add_non_terminal_grammar(const non_terminal_t gr, const std::vector<std::pair<grammar_pair_t, std::vector<context_t> > > & val) {
    auto& vec = non_terminal_grammar[gr];
    vec.insert(vec.end(), val.begin(), val.end());
}

void grammar::add_grammar(const std::string& line) {
    std::istringstream iss(line);
    std::string lhs, arrow;
    iss >> lhs >> arrow;
    if (arrow != "->") {
        throw std::runtime_error("Invalid rule format, expected '->'");
    }

    non_terminal_t lhs_id = get_non_terminal_id(lhs);

    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    std::vector<std::string> body;
    std::vector<context_t> contexts;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& tok = tokens[i];

        if (tok == "<" || tok == ">" || tok == "<=" || tok == ">=") {
            if (i + 1 >= tokens.size()) {
                throw std::runtime_error("Context operator without argument");
            }
            Context_type type = parse_context_type(tok);
            non_terminal_t nt = get_non_terminal_id(tokens[i + 1]);
            contexts.emplace_back(type, nt);
            ++i;
        } else {
            body.push_back(tok);
        }
    }

    if (body.size() == 1 && body[0].front() == '\'' && body[0].back() == '\'') {
        std::string terminal = body[0].substr(1, body[0].size() - 2); // strip quotes
        std::vector<std::pair<std::string, std::vector<context_t> > > temp_term;
        temp_term.push_back(std::make_pair(terminal, contexts));
        add_terminal_grammar(lhs_id, temp_term);

    }
    else if (body.size() == 2 && body[0].front() != '\'' && body[1].front() != '\'') {
        non_terminal_t l = get_non_terminal_id(body[0]);
        non_terminal_t r = get_non_terminal_id(body[1]);
        grammar_pair_t pair = std::make_pair(l, r);
        std::vector<std::pair<grammar_pair_t, std::vector<context_t> > > temp_nonterm;
        temp_nonterm.push_back(std::make_pair(pair, contexts));
        add_non_terminal_grammar(lhs_id, temp_nonterm);

    }
    else {
        throw std::runtime_error("Unsupported grammar rule format: " + line);
    }
}
