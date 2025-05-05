#include "grammar.hpp"
#include <iostream>

// Для удобства
std::string context_type_to_string(Context_type type) {
    switch (type) {
        case EXT_RIGHT: return "EXT_RIGHT";
        case RIGHT:     return "RIGHT";
        case EXT_LEFT:  return "EXT_LEFT";
        case LEFT:      return "LEFT";
        default:        return "UNKNOWN";
    }
}

void print_grammar(const grammar& gr) {
    std::cout << "--- Terminal Grammar ---\n";
    for (const auto& [lhs, rules] : gr.terminal_grammar) {
        std::cout << "LHS (non-terminal) ID: " << lhs << "\n";
        for (const auto& [terminal, contexts] : rules) {
            std::cout << "  -> '" << terminal << "' with contexts: ";
            for (const auto& [ctx_type, ctx_nt] : contexts) {
                std::cout << "[" << context_type_to_string(ctx_type) << " " << ctx_nt << "] ";
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n--- Non-Terminal Grammar ---\n";
    for (const auto& [lhs, rules] : gr.non_terminal_grammar) {
        std::cout << "LHS (non-terminal) ID: " << lhs << "\n";
        for (const auto& [pair, contexts] : rules) {
            std::cout << "  -> " << pair.first << " " << pair.second << " with contxts: ";
            for (const auto& [ctx_type, ctx_nt] : contexts) {
                std::cout << "[" << context_type_to_string(ctx_type) << " " << ctx_nt << "] ";
            }
            std::cout << "\n";
        }
    }
}

int main(){
    grammar gr;
    gr.add_grammar("A -> B C < D >= E");
    gr.add_grammar("C -> 'foo' > D");
    gr.add_grammar("A -> B R < E");

    std::cout << "Грамматики успешно добавлены.\n";
    print_grammar(gr);
    return 0;
}