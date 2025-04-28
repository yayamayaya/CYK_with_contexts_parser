#ifndef GOOGLE_TESTING_HEADER
#define GOOGLE_TESTING_HEADER

#include <gtest/gtest.h>
#include "parser.hpp"
#include "grammar.hpp"

TEST(context_free_tests, first_test)
{
    // A{0x01} -> BC
    // B{0x02} -> "b"
    // C{0x03} -> "c"

    grammar g = {};
    g.add_terminal_grammar(0x02, {std::make_pair<std::string, std::vector<context_t>>("b", {})});
    g.add_terminal_grammar(0x03, {std::make_pair<std::string, std::vector<context_t>>("c", {})});
    g.add_non_terminal_grammar(0x01, {std::make_pair<grammar_pair_t, std::vector<context_t>>({0x02, 0x03}, {})});

    parser p = {};

    p.set_grammar(g);
    p.parse_string("b c");
}

TEST(context_sensitive_grammar, simple_test)
{
    // S -> AS | SA | BC
    // A -> "a"
    // B -> "b" < A
    // C -> "c" > A

    grammar g = {};
    g.add_non_terminal_grammar(0x01, 
        {
            std::make_pair<grammar_pair_t, std::vector<context_t>>({0x02, 0x01}, {}),
            std::make_pair<grammar_pair_t, std::vector<context_t>>({0x01, 0x02}, {}),
            std::make_pair<grammar_pair_t, std::vector<context_t>>({0x03, 0x04}, {}),
        });

    g.add_terminal_grammar(0x02, {std::make_pair<std::string, std::vector<context_t>>("a", {})});
    g.add_terminal_grammar(0x03, {std::make_pair<std::string, std::vector<context_t>>("b", {{LEFT, 0x02}})});
    g.add_terminal_grammar(0x04, {std::make_pair<std::string, std::vector<context_t>>("c", {{RIGHT, 0x02}})});

    parser p = {};

    p.set_grammar(g);
    p.parse_string("a b c a");
}

#endif
