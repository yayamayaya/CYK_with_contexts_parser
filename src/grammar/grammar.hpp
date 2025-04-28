#ifndef GRAMMAR_READER_H
#define GRAMMAR_READER_H

#include <map>
#include <vector>
#include <string>

using non_terminal_t = unsigned int;

using grammar_pair_t = std::pair<non_terminal_t, non_terminal_t>;

enum Context_type
{
    EXT_RIGHT = 0x01,
    RIGHT     = 0x02,
    EXT_LEFT  = 0x04,
    LEFT      = 0x08
};

using context_t      = std::pair<Context_type, non_terminal_t>;

//Класс grammar имеет две таблицы
//Первая таблица отвечает за грамматики нетерминал -> нетерминал {std::map<non_terminal_t, std::pair<std::string, std::vector<contexts>>>}
//Вторая таблица отвечает за грамматики нетерминал -> терминал   {std::map<non_terminal_t, std::pair<grammar_pair_t, std::vector<context_t>>>>}

class grammar
{
public:
    //Такие таблички должны быть
    std::map<non_terminal_t, std::vector<std::pair<std::string, std::vector<context_t>>>> terminal_grammar;
    
    std::map<non_terminal_t, std::vector<std::pair<grammar_pair_t, std::vector<context_t>>>> non_terminal_grammar;

    //Временные функции, чтобы я мог тестировать парсер
    grammar(): terminal_grammar(), non_terminal_grammar() {};

    ~grammar() {};

    void add_terminal_grammar(const non_terminal_t gr, const std::vector<std::pair<std::string, std::vector<context_t>>>& val);

    void add_non_terminal_grammar(const non_terminal_t gr, const std::vector<std::pair<grammar_pair_t, std::vector<context_t>>>& val);
};

#endif