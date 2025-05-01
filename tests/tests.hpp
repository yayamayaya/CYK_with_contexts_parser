#ifndef GOOGLE_TESTING_HEADER
#define GOOGLE_TESTING_HEADER

#include <gtest/gtest.h>
#include "parser.hpp"
#include "grammar.hpp"

TEST(context_free_tests, simple_test1)
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
    EXPECT_EQ(p.parse_string("b c"), 0);
}

TEST(context_free_tests, negative_test1)
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
    EXPECT_EQ(p.parse_string("b d"), parser::NOT_PARSED);
}

TEST(context_sensitive_grammar, simple_test1)
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
    EXPECT_EQ(p.parse_string("a b c a"), 0);
}

TEST(context_sensitive_grammar, simple_test2)
{
    // S -> AB
    // A -> "a" > B
    // B -> "b" < C
    // C -> "a"

    grammar g = {};
    g.add_non_terminal_grammar(0x01, {std::make_pair<grammar_pair_t, std::vector<context_t>>({0x02, 0x03}, {})});

    g.add_terminal_grammar(0x02, {std::make_pair<std::string, std::vector<context_t>>("a", {{RIGHT, 0x03}})});
    g.add_terminal_grammar(0x03, {std::make_pair<std::string, std::vector<context_t>>("b", {{LEFT, 0x04}})});
    g.add_terminal_grammar(0x04, {std::make_pair<std::string, std::vector<context_t>>("a", {})});

    parser p = {};

    p.set_grammar(g);
    EXPECT_EQ(p.parse_string("a b"), 0);
}

TEST(context_sensitive_grammar, simple_test3)
{
    //S -> AS | "a"
    //A -> "a" > S

    grammar g = {};
    g.add_non_terminal_grammar(0x01, {std::make_pair<grammar_pair_t, std::vector<context_t>>({0x02, 0x01}, {})});

    g.add_terminal_grammar(0x01, {std::make_pair<std::string, std::vector<context_t>>("a", {})});
    g.add_terminal_grammar(0x02, {std::make_pair<std::string, std::vector<context_t>>("a", {{RIGHT, 0x01}})});

    parser p = {};

    p.set_grammar(g);
    EXPECT_EQ(p.parse_string("a a a a"), 0);
}

TEST(context_sensitive_grammar, negative_test2)
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
    EXPECT_EQ(p.parse_string("b c a"), parser::NOT_PARSED);
}

TEST(graph_print_test, only_test)
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
    EXPECT_EQ(p.parse_string("a b c a"), 0);
    EXPECT_NO_THROW(p.print_graph("./graph.png"));
}

#endif
