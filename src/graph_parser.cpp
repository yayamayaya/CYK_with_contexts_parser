#include "graph_parser.hpp"
#include "parser.hpp"
#include "grammar.hpp"

graph_parser::graph_parser(): _p(new parser) {}

graph_parser::~graph_parser() {}

int graph_parser::add_grammar_rule(const std::string& rule)
{
    (void)rule;
    return 0;
}

int graph_parser::parse_graph(const std::string& linear_graph)
{
    return _p->parse_string(linear_graph);
}

const std::string graph_parser::print_parsing_table()
{
    return _p->print_table();
}

void graph_parser::draw_parsed_graph(const std::string& png_loc)
{
    return _p->print_graph(png_loc);
}