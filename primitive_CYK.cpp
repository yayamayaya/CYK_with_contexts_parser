#include <iostream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using std::string;

std::set<string> find_termninal(std::string str);

std::set<string> find_non_terminal(std::set<string> vf, std::set<string> vs);

bool find_elem(const std::set<string>& elems, const string& str);

void print_table(const std::map<int, std::map<int, std::set<string>>>& table);

int cyk(const std::vector<string>& w);

static std::map<string, std::vector<std::pair<string, string>>> rules;

int main()
{
    rules["NP"] ={{"Det", "Nom"}};
    rules["Nom"] = {{"AP", "Nom"}, {"book", ""}, {"orange", ""}, {"man", ""}};
    rules["AP"] = {{"Adv", "A"}, {"heavy", ""}, {"orange", ""}, {"tall", ""}};
    rules["Det"] = {{"a", ""}};
    rules["Adv"] = {{"very", ""}, {"extremely", ""}};
    rules["A"] = {{"heavy", ""}, {"orange", ""}, {"tall", ""}, {"muscular", ""}};

    std::vector<string> w = {"a", "very", "tall", "extremely", "muscular", "man"};

    cyk(w);

    return 0;
}


std::set<string> find_termninal(std::string str)
{
    return find_non_terminal(std::set({str}), std::set<string>({""}));
}

std::set<string> find_non_terminal(std::set<string> vf, std::set<string> vs)
{
    std::set<string> non_terminals;

    for (auto rule : rules)
        for (auto it : rule.second)
            if (find_elem(vf, it.first) && find_elem(vs, it.second))
                non_terminals.insert(rule.first);

    //Добавляем проверку всех контекстов для правила, прежде чем делать insert

    return non_terminals;
}

bool find_elem(const std::set<string>& elems, const string& str)
{
    return std::find(elems.begin(), elems.end(), str) != elems.end();
}

int cyk(const std::vector<string>& w)
{
    size_t l = w.size();

    std::map<int, std::map<int, std::set<string>>> table{};

    //Добавляем флаг состояния, оборачиваем в while
    for (size_t i = 0; i < l; i++)
    {
        //Делаем append, не присваивание.
        table[i][i] = find_termninal(w[i]);

        for (size_t j = i; static_cast<int>(j) >= 0; --j)
            for (size_t k = j; k < i; k++)
                table[j][i].merge(find_non_terminal(table[j][k], table[k + 1][i]));
    }
    
    print_table(table);

    return 0;    
}

void print_table(const std::map<int, std::map<int, std::set<string>>>& table)
{
    for (auto row : table)
    {
        for (size_t i = 0; i < table.size() - row.second.size(); i++)
            std::cout << std::setw(20)<<  " { } ";

        for (auto col : row.second)
        {
            std::stringstream os = {};

            os << "{ ";
            for (auto it : col.second)
                os << it << " ";
            os << "} ";

            std::cout << std::setw(20) << os.str();
        }

        std::cout << std::endl;
    }
}