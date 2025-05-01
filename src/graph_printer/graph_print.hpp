#ifndef GRAPH_PRINTER_INCLUDE_GUARD
#define GRAPH_PRINTER_INCLUDE_GUARD

#include <string>
#include "parser.hpp"

namespace graph_printer
{
    static const std::string GRAPH_CODE_LOCATION = 
    "./graphcode.txt";

    static const std::string DOT_CALL = 
    "dot " + GRAPH_CODE_LOCATION + " -Tpng -o";

    static const std::string GRAPH_CODE_INIT = 
    "digraph G                    \n"
    "{                            \n"
    "\tgraph [dpi = 1000];        \n"
    "\tbgcolor = \"#9F8C76\"    \n\n";

    static const std::string NODE_PROPERTIES = 
    "\tnode                       \n"
    "\t[                          \n"
    "\tshape = \"box\",           \n" 
    "\tstyle = \"rounded,filled\",\n"
    "\theight = 1,                \n"
    "\twidth = 2,                 \n"
    "\tfillcolor = \"#F5F5DC\",   \n"
    "\tfontsize = 17,             \n"
    "\tfontname = \"Courier New\",\n"
    "\tfontcolor = \"#1a1718\",   \n"
    "\tpenwidth = 2,              \n"
    "\tcolor = \"#1a1718\"        \n"
    "\t]                        \n\n";

    static const std::string GRAPH_CODE_END =
    "}                          \n";

    static const std::string NODE_NUM       = 
    "\tnode_num";

    static const std::string NODE_FORMAT    =
    "[shape = \"record\", color=\"#003366\", label = ";

    void print_graph(parsing_table& t);

    void print_node(std::ofstream& graph_code, const unsigned int node_num);

    void dot_call(const std::string& png_loc);
}

#endif