#pragma once
#include "Shakhov_LR7_8_ClassAtrefacts.h"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <sstream>

using namespace std;

// Универсальный ввод
template <typename T>
T inputNumber(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Повторите ввод.\n";
    }
}

inline string inputNumber() {
    string value;
    getline(cin, value);
    return value;
}

vector<Artefact<int, vector<string>>> artefacts;

void demoConstructors() {
    cout << "\nДемонстрация конструкторов:\n";
    Artefact<int, vector<string>> a1;
    cout << "По умолчанию: "; a1.printInfo();

    Artefact<int, vector<string>> a2("Меч", 500, vector<string>{"Египет"}, "Средневековье");
    cout << "Параметризованный: "; a2.printInfo();

    Artefact<int, vector<string>> a3 = a2;
    cout << "Копирование: "; a3.printInfo();

    Artefact<int, vector<string>> a4 = move(a2);
    cout << "Перемещение: "; a4.printInfo();
}

void demoMethods(vector<Artefact<int, vector<string>>>& artefacts) {
    cout << "\n=== Демонстрация методов ===\n";

    try {
        // Проверка наличия артефактов
        if (artefacts.empty()) {
            throw runtime_error("Нет доступных артефактов для демонстрации");
        }

        cout << "Список артефактов:\n";
        for (size_t i = 0; i < artefacts.size(); ++i) {
            cout << i + 1 << ") ";
            artefacts[i].printInfo();
        }

        // Ввод и проверка индекса
        int index = inputNumber<int>("Выберите номер артефакта для демонстрации: ") - 1;
        if (index < 0 || index >= static_cast<int>(artefacts.size())) {
            throw out_of_range("Выбран неверный номер артефакта");
        }

        auto& a = artefacts[index];

        // Демонстрация методов с обработкой возможных исключений
        cout << "\n--- printInfo() ---\n";
        a.printInfo();

        cout << "\n--- addLocation(\"НОВОЕ МЕСТО\") ---\n";
        try {
            a.addLocation("НОВОЕ МЕСТО");
            cout << "После добавления:\n";
            a.printInfo();
        }
        catch (const invalid_argument& e) {
            cerr << "Ошибка добавления места: " << e.what() << endl;
        }

        cout << "\n--- isAncient() ---\n";
        try {
            cout << (a.isAncient() ? "Артефакт древний (> 1000 лет)."
                : "Артефакт не древний.") << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка проверки древности: " << e.what() << endl;
        }

        cout << "\n--- getHistoricalPeriod() ---\n";
        try {
            cout << "Исторический период: " << a.getHistoricalPeriod() << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка получения периода: " << e.what() << endl;
        }

        cout << "\n--- countLocations() ---\n";
        try {
            cout << "Количество мест: " << a.countLocations() << endl;
        }
        catch (const runtime_error& e) {
            cerr << "Ошибка подсчета мест: " << e.what() << endl;
        }

    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Произошла неизвестная ошибка при демонстрации методов" << endl;
    }
}

void searchByLocation(const vector<Artefact<int, vector<string>>>& artefacts) {
    cout << "Введите место для поиска: ";
    string loc = inputNumber();
    bool found = false;
    for (const auto& a : artefacts)
        for (const auto& l : a.getLocations())
            if (l == loc) {
                a.printInfo();
                found = true;
            }
    if (!found) cout << "Совпадений не найдено.\n";
}

void filterByPeriod(const vector<Artefact<int, vector<string>>>& artefacts) {
    cout << "Введите исторический период (например: Античность, Средневековье): ";
    string period = inputNumber();
    bool found = false;
    for (const auto& a : artefacts)
        if (a.getHistoricalPeriod() == period) {
            a.printInfo();
            found = true;
        }
    if (!found) cout << "Нет артефактов этого периода.\n";
}

Artefact<int, vector<string>> inputArtefactSafe() {
    Artefact<int, vector<string>> a;
    string temp;
    int age;
    int count;
    vector<string> places;

    cout << "Введите название: ";
    getline(cin, temp);
    a.setName(temp);

    age = inputNumber<int>("Введите возраст: ");
    a.setAge(age);

    count = inputNumber<int>("Сколько мест находки: ");
    for (int i = 0; i < count; ++i) {
        cout << "Место #" << i + 1 << ": ";
        getline(cin, temp);
        a.addLocation(temp);
    }

    cout << "Введите период: ";
    getline(cin, temp);
    a.setPeriod(temp);

    return a;
}

void inputArtefact() {
    cout << "\n=== Ввод артефакта ===\n";
    Artefact<int, vector<string>> a = inputArtefactSafe();
    artefacts.push_back(a);
    cout << "Артефакт добавлен.\n";
}

void printArtefacts() {
    cout << "\n=== Список артефактов ===\n";
    if (artefacts.empty()) {
        cout << "Список пуст.\n";
        return;
    }
    for (size_t i = 0; i < artefacts.size(); ++i) {
        cout << i + 1 << ") ";
        artefacts[i].printInfo();
    }
}

void demoConstructorsWrapper() {
    demoConstructors();
}

void demoMethodsWrapper() {
    demoMethods(artefacts);
}

void demoOperatorsWrapper() {
    if (artefacts.size() < 1) {
        cout << "Недостаточно артефактов.\n";
        return;
    }
    printArtefacts();
    int i1 = inputNumber<int>("Выберите номер первого артефакта: ") - 1;
    if (i1 < 0 || i1 >= static_cast<int>(artefacts.size())) return;

    cout << "\n--- Оператор ++ ---\n";
    cout << "До: "; artefacts[i1].printInfo();
    ++artefacts[i1];
    cout << "После ++: "; artefacts[i1].printInfo();

    cout << "\n--- Оператор == (с самим собой) ---\n";
    cout << (artefacts[i1] == artefacts[i1] ? "Равны" : "Не равны") << endl;

    cout << "\n--- Оператор присваивания ---\n";
    Artefact<int, vector<string>> assigned;
    assigned = artefacts[i1];
    cout << "Присвоенный артефакт: "; assigned.printInfo();

    cout << "\n--- Оператор перемещающего присваивания ---\n";
    Artefact<int, vector<string>> moved;
    moved = move(assigned);
    cout << "Результат перемещения: "; moved.printInfo();

    if (artefacts.size() < 2) {
        cout << "\nНедостаточно артефактов для демонстрации оператора +.\n";
        return;
    }

    int i2 = inputNumber<int>("Выберите номер второго артефакта для сложения: ") - 1;
    if (i2 < 0 || i2 >= static_cast<int>(artefacts.size()) || i1 == i2) return;

    cout << "\n--- Оператор + ---\n";
    Artefact<int, vector<string>> sum = artefacts[i1] + artefacts[i2];
    cout << "Сумма: "; sum.printInfo();
}

void searchByLocationWrapper() {
    searchByLocation(artefacts);
}

void filterByPeriodWrapper() {
    filterByPeriod(artefacts);
}

// Операторы ввода/вывода

template <typename A, typename L>
ostream& operator<<(ostream& os, const Artefact<A, vector<L>>& a) {
    os << a.getName() << endl;
    os << a.getAge() << endl;
    for (const auto& loc : a.getLocations())
        os << loc << ",";
    os << endl;
    os << a.getHistoricalPeriod() << endl;
    return os;
}

template <typename A, typename L>
istream& operator>>(istream& is, Artefact<A, vector<L>>& a) {
    string name, line, period;
    A age;
    vector<L> locations;

    getline(is, name);
    is >> age;
    is.ignore();

    getline(is, line);
    stringstream ss(line);
    string loc;
    while (getline(ss, loc, ','))
        locations.push_back(loc);

    getline(is, period);

    a.setName(name);
    a.setAge(age);
    a.setLocations(locations);
    a.setPeriod(period);
    return is;
}

template ostream& operator<< <int, string>(ostream&, const Artefact<int, vector<string>>&);
template istream& operator>> <int, string>(istream&, Artefact<int, vector<string>>&);
