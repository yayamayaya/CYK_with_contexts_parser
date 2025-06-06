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

TEST(context_free_tests, big_grammar_test)
{
    parser p = {};

    p.add_grammar_rule("S -> NP VP");
    p.add_grammar_rule("VP -> VP PP");
    p.add_grammar_rule("VP -> V NP");
    p.add_grammar_rule("VP -> 'eats'");
    p.add_grammar_rule("PP -> P NP");
    p.add_grammar_rule("NP -> Det N");
    p.add_grammar_rule("NP -> 'she'");
    p.add_grammar_rule("V -> 'eats'");
    p.add_grammar_rule("P -> 'with'");
    p.add_grammar_rule("N -> 'fish'");
    p.add_grammar_rule("N -> 'fork'");
    p.add_grammar_rule("Det -> 'a'");

    EXPECT_EQ(p.parse_string("she eats a fish with a fork"), 0);

    std::cout << p.print_table() << std::endl;
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

    // std::cout << p.print_table() << std::endl;
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

    // std::cout << p.print_table() << std::endl;
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

TEST(grammar_reader_test, test1)
{
    grammar g = {};

    EXPECT_NO_THROW(g.add_grammar("A -> B C"));
    EXPECT_NO_THROW(g.add_grammar("A -> 'a'"));
    EXPECT_NO_THROW(g.add_grammar("B -> F D < Z > X <= C >= V"));
    EXPECT_NO_THROW(g.add_grammar("A -> Np Vp"));
}

TEST(grammar_reader_test, negative_test1)
{
    grammar g = {};

    EXPECT_ANY_THROW(g.add_grammar(""));
    EXPECT_ANY_THROW(g.add_grammar("A"));
    EXPECT_ANY_THROW(g.add_grammar("A -> "));
    EXPECT_ANY_THROW(g.add_grammar("A -> B C D"));
}

TEST(full_test, test1)
{
    // S -> AB
    // A -> "a" > B
    // B -> "b" < C
    // C -> "a"

    grammar g = {};

    g.add_grammar("S -> A B");
    g.add_grammar("A -> 'a' > B");
    g.add_grammar("B -> 'b' < C");
    g.add_grammar("C -> 'a'");

    parser p = {};

    p.set_grammar(g);
    EXPECT_EQ(p.parse_string("a b"), 0);

    // std::cout << p.print_table() << std::endl;
}

TEST(full_test, simple_test1)
{
    // S -> AS | SA | BC
    // A -> "a"
    // B -> "b" < A
    // C -> "c" > A

    grammar g = {};

    g.add_grammar("S -> A S");
    g.add_grammar("S -> S A");
    g.add_grammar("S -> B C");
    g.add_grammar("A -> 'a'");
    g.add_grammar("B -> 'b' < A");
    g.add_grammar("C -> 'c' > A");

    parser p = {};

    p.set_grammar(g);
    EXPECT_EQ(p.parse_string("a b c a"), 0);

    // std::cout << p.print_table() << std::endl;
}

TEST(full_test, big_grammar_test)
{
    parser p = {};

    p.add_grammar_rule("S -> A MR");
    p.add_grammar_rule("MR -> M C");
    p.add_grammar_rule("M -> B <= L >= R");
    p.add_grammar_rule("L -> AA LL");
    p.add_grammar_rule("LL -> L BB");
    p.add_grammar_rule("L -> AA BB");
    p.add_grammar_rule("R -> BB RR");
    p.add_grammar_rule("RR -> R CC");
    p.add_grammar_rule("R -> BB CC");
    p.add_grammar_rule("A -> A A");
    p.add_grammar_rule("B -> B B");
    p.add_grammar_rule("C -> C C");
    p.add_grammar_rule("A -> 'a'");
    p.add_grammar_rule("B -> 'b'");
    p.add_grammar_rule("C -> 'c'");
    p.add_grammar_rule("AA -> 'a'");
    p.add_grammar_rule("BB -> 'b'");
    p.add_grammar_rule("CC -> 'c'");

    EXPECT_EQ(p.parse_string("a a b b c c"), 0);
    std::cout << p.print_table() << std::endl;
}

#endif
