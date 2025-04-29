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
/*
Работа читалки:

Добавляем грамматики по одной, нетерминалы разделяются пробелами:
    А -> B C < D >= E
    Читалка смотрит на то, что стоит после "->", и распределяет грамматики:

    Если там пара нетерминалов - кидает в табличку нетерминалов с соответствующими контекстами
    Если стоит строка (пусть будет обозначаться через '')         - кидает в табличку терминалов

    Для простоты пусть контексты обозначаются только нетерминалами
    контексты идут с соответствующим типом:
    < - LEFT
    > - RIGHT
    <= - EXT_LEFT
    >= - EXT_RIGHT

    Каждый нетерминал обозначается уникальным числом. Можно сделать вектор, где индекс как раз будет соответствующим нетерминалом

    В нашем парсере не будет конъюкций, ибо нафиг надо

    вот пример грамматики:

    grammar gr = {};
    gr.add_grammar("A -> B C < D >= E")
    Результат:

                                                     1  2  3  4  5
    std::vector<std::string> unique_non_terminals = {A, B, C, D, E}

    non_terminal_grammar[1] ==
    {
        vector<>{pair<>{pair<>{2, 3}, vector<>{pair<>{LEFT, D}, pair<>{EXT_RIGHT, E}}}}
    }

    gr.add_grammar("C -> 'foo' > D")
    Результат:

    terminal_grammar[3] == 
    {
        vector<>{pair<>{string(foo), vector<>{pair<>{RIGHT, D}}}}}
    }

    Если у нас уже есть грамматика к данному нетерминалу, мы просто добавляем ещё одну:

    gr.add_grammar("A -> D E")
    Результат:

    non_terminal_grammar[1] ==
    {
        vector<>{pair<>{pair<>{2, 3}, vector<>{pair<>{LEFT, D}, pair<>{EXT_RIGHT, E}}}, pair<>{pair<>{4, 5}, vector<>{}} <- Просто добавили ещё одну}
    }
*/

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