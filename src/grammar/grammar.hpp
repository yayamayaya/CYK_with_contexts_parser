#ifndef GRAMMAR_READER_H
#define GRAMMAR_READER_H

#include <map>
#include <vector>
#include <string>
#include <iostream>

using non_terminal_t = unsigned int;
using grammar_pair_t = std::pair<non_terminal_t, non_terminal_t>;

enum Context_type
{
    EXT_RIGHT = 0x01,
    RIGHT     = 0x02,
    EXT_LEFT  = 0x04,
    LEFT      = 0x08
};

using context_t = std::pair<Context_type, non_terminal_t>;

/*
Описание работы читалки:

Добавляем грамматики по одной, пример:
    A -> B C < D >= E

Если в правой части:
- два нетерминала — это правило в `non_terminal_grammar`
- один терминал в кавычках — это правило в `terminal_grammar`
Контексты обозначаются < > <= >= и идут после пары.

Все нетерминалы — это уникальные строки, которым присваиваются уникальные ID.
*/

class grammar
{
public:
    // Таблица терминальных правил: нетерминал → список {строка-терминал, контексты}
    std::map<non_terminal_t, std::vector<std::pair<std::string, std::vector<context_t> > > > terminal_grammar;

    // Таблица нетерминальных правил: нетерминал → список {{нетерминал, нетерминал}, контексты}
    std::map<non_terminal_t, std::vector<std::pair<grammar_pair_t, std::vector<context_t> > > > non_terminal_grammar;

    grammar() = default;
    ~grammar() = default;

    // Добавить терминальное правило напрямую
    void add_terminal_grammar(const non_terminal_t gr, const std::vector<std::pair<std::string, std::vector<context_t> > > & val);

    // Добавить нетерминальное правило напрямую
    void add_non_terminal_grammar(const non_terminal_t gr, const std::vector<std::pair<grammar_pair_t, std::vector<context_t> > > & val);

    // Основной метод: парсит строку правила и добавляет её
    void add_grammar(const std::string& line);
};

#endif 
