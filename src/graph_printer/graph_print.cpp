#include "graph_print.hpp"
#include <fstream>
#include <cstdlib>

void graph_printer::print_graph(parsing_table& table)
{
    std::ofstream graph_code = {};

    graph_code.open(GRAPH_CODE_LOCATION);

    graph_code << GRAPH_CODE_INIT << NODE_PROPERTIES;

    for (index_t i = 0; i < table.size() + 1; i++)
        print_node(graph_code, i);

    for (index_t i = 0; i < table.size(); i++)
        for (index_t j = 0; j < table[i].size(); j++)
            if (table[i][j].size())
                graph_code << "\tnode_num" << i << "->" << "node_num" << j + 1 << std::endl;

    graph_code << GRAPH_CODE_END;

    graph_code.close();
}

void graph_printer::print_node(std::ofstream& graph_code, const unsigned int node_num)
{
    graph_code << NODE_NUM << node_num << NODE_FORMAT << "\"" << node_num << "\"]" << std::endl;
}

void graph_printer::dot_call(const std::string& png_loc)
{
    std::system((DOT_CALL + png_loc).c_str());
}