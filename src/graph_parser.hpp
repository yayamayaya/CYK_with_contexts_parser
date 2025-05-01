#ifndef GRAPH_PARSER_HEADER
#define GRAPH_PARSER_HEADER

#include <string>

class parser;

class graph_parser
{
    parser *_p;

public:

    graph_parser();

    ~graph_parser();

    int add_grammar_rule(const std::string& rule);

    int parse_graph(const std::string& linear_graph);

    const std::string print_parsing_table();

    void draw_parsed_graph(const std::string& png_loc);

    graph_parser(const graph_parser& ref) =delete;

    graph_parser& operator =(const graph_parser& ref) =delete;
};

#endif