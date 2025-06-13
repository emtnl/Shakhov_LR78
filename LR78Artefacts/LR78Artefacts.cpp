// === main.cpp ===
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <locale>
#include "Shakhov_LR7_8_ClassAtrefacts.h"
#include "Methods.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");

    map<int, pair<string, function<void()>>> menu = {
        {1, {"Ввод артефакта", inputArtefact}},
        {2, {"Вывод всех артефактов", printArtefacts}},
        {3, {"Демонстрация конструкторов", demoConstructorsWrapper}},
        {4, {"Демонстрация методов", demoMethodsWrapper}},
        {5, {"Демонстрация операторов", demoOperatorsWrapper}},
        {6, {"Поиск по месту находки", searchByLocationWrapper}},
        {7, {"Фильтрация по историческому периоду", filterByPeriodWrapper}},
        {0, {"Выход", [] { cout << "Завершение программы.\n"; }}}
    };

    int choice = -1;
    while (choice != 0) {
        cout << "\n=== МЕНЮ ===\n";
        for (const auto& item : menu)
            cout << item.first << " - " << item.second.first << '\n';
        choice = inputNumber<int>("Выберите действие: ");
        if (menu.count(choice)) menu[choice].second();
        else cout << "Неверный пункт.\n";
    }

    return 0;
}
