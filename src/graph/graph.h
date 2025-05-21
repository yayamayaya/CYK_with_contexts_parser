#include <unordered_map>
#include <set>
#include <string> 
#include <vector>
#include <algorithm>
#include <iostream>

class Graph {
    private: 
        std::unordered_map<unsigned int, std::unordered_map<unsigned int, std::string> > adjacency_map;
        std::set<unsigned int> vertices;
    public:
        void add_edge(unsigned int u, unsigned int v, const std::string& name){
            
            adjacency_map[u][v] = name;
            // adjacency_map[v][u] = name;

            vertices.insert(u);
            vertices.insert(v);
        }

        unsigned int return_str_size(const unsigned int lhs) const
        {
            return static_cast<unsigned int>(adjacency_map.at(lhs).size());
        }

        std::string get_edge_name(unsigned int u, unsigned int v) const{

            auto outer_it = adjacency_map.find(u);
            if (outer_it == adjacency_map.end()) return "0";

            const auto& inner_map = outer_it -> second;
            auto inner_it = inner_map.find(v);
            if (inner_it == inner_map.end()) return "0";

            return inner_it -> second;
        }

        void print_matrix() const{

            std::vector<unsigned int> sorted_vertices(vertices.begin(), vertices.end());
            std::sort(sorted_vertices.begin(), sorted_vertices.end());

            // Вывод заголовков
            std::cout << "    ";
            for (unsigned int v : sorted_vertices) {
                std::cout << v << "      ";
            }
            std::cout << std::endl;

            // Вывод строк матрицы
            for (unsigned int i : sorted_vertices){
                std::cout << i << "   ";
                for (unsigned int j : sorted_vertices){
                    std::string edge = get_edge_name(i, j);
                    std::cout << edge;
                    // Добавляем пробелы для выравнивания
                    size_t len = edge.length();
                    for (size_t k = len; k < 6; ++k) // 6 символов на ячейку
                        std::cout << ' ';
                }
                std::cout << std::endl;
            }
        }

        void clear_graph(){
            adjacency_map.clear();
            vertices.clear();
        }
};
