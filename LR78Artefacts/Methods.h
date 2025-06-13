#pragma once
#include "Shakhov_LR7_8_ClassAtrefacts.h"
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <sstream>

using namespace std;

// ������������� ����
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
        cout << "������! ��������� ����.\n";
    }
}

inline string inputNumber() {
    string value;
    getline(cin, value);
    return value;
}

vector<Artefact<int, vector<string>>> artefacts;

void demoConstructors() {
    cout << "\n������������ �������������:\n";
    Artefact<int, vector<string>> a1;
    cout << "�� ���������: "; a1.printInfo();

    Artefact<int, vector<string>> a2("���", 500, vector<string>{"������"}, "�������������");
    cout << "�����������������: "; a2.printInfo();

    Artefact<int, vector<string>> a3 = a2;
    cout << "�����������: "; a3.printInfo();

    Artefact<int, vector<string>> a4 = move(a2);
    cout << "�����������: "; a4.printInfo();
}

void demoMethods(vector<Artefact<int, vector<string>>>& artefacts) {
    cout << "\n=== ������������ ������� ===\n";

    try {
        // �������� ������� ����������
        if (artefacts.empty()) {
            throw runtime_error("��� ��������� ���������� ��� ������������");
        }

        cout << "������ ����������:\n";
        for (size_t i = 0; i < artefacts.size(); ++i) {
            cout << i + 1 << ") ";
            artefacts[i].printInfo();
        }

        // ���� � �������� �������
        int index = inputNumber<int>("�������� ����� ��������� ��� ������������: ") - 1;
        if (index < 0 || index >= static_cast<int>(artefacts.size())) {
            throw out_of_range("������ �������� ����� ���������");
        }

        auto& a = artefacts[index];

        // ������������ ������� � ���������� ��������� ����������
        cout << "\n--- printInfo() ---\n";
        a.printInfo();

        cout << "\n--- addLocation(\"����� �����\") ---\n";
        try {
            a.addLocation("����� �����");
            cout << "����� ����������:\n";
            a.printInfo();
        }
        catch (const invalid_argument& e) {
            cerr << "������ ���������� �����: " << e.what() << endl;
        }

        cout << "\n--- isAncient() ---\n";
        try {
            cout << (a.isAncient() ? "�������� ������� (> 1000 ���)."
                : "�������� �� �������.") << endl;
        }
        catch (const exception& e) {
            cerr << "������ �������� ���������: " << e.what() << endl;
        }

        cout << "\n--- getHistoricalPeriod() ---\n";
        try {
            cout << "������������ ������: " << a.getHistoricalPeriod() << endl;
        }
        catch (const exception& e) {
            cerr << "������ ��������� �������: " << e.what() << endl;
        }

        cout << "\n--- countLocations() ---\n";
        try {
            cout << "���������� ����: " << a.countLocations() << endl;
        }
        catch (const runtime_error& e) {
            cerr << "������ �������� ����: " << e.what() << endl;
        }

    }
    catch (const out_of_range& e) {
        cerr << "������: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cerr << "������: " << e.what() << endl;
    }
    catch (...) {
        cerr << "��������� ����������� ������ ��� ������������ �������" << endl;
    }
}

void searchByLocation(const vector<Artefact<int, vector<string>>>& artefacts) {
    cout << "������� ����� ��� ������: ";
    string loc = inputNumber();
    bool found = false;
    for (const auto& a : artefacts)
        for (const auto& l : a.getLocations())
            if (l == loc) {
                a.printInfo();
                found = true;
            }
    if (!found) cout << "���������� �� �������.\n";
}

void filterByPeriod(const vector<Artefact<int, vector<string>>>& artefacts) {
    cout << "������� ������������ ������ (��������: ����������, �������������): ";
    string period = inputNumber();
    bool found = false;
    for (const auto& a : artefacts)
        if (a.getHistoricalPeriod() == period) {
            a.printInfo();
            found = true;
        }
    if (!found) cout << "��� ���������� ����� �������.\n";
}

Artefact<int, vector<string>> inputArtefactSafe() {
    Artefact<int, vector<string>> a;
    string temp;
    int age;
    int count;
    vector<string> places;

    cout << "������� ��������: ";
    getline(cin, temp);
    a.setName(temp);

    age = inputNumber<int>("������� �������: ");
    a.setAge(age);

    count = inputNumber<int>("������� ���� �������: ");
    for (int i = 0; i < count; ++i) {
        cout << "����� #" << i + 1 << ": ";
        getline(cin, temp);
        a.addLocation(temp);
    }

    cout << "������� ������: ";
    getline(cin, temp);
    a.setPeriod(temp);

    return a;
}

void inputArtefact() {
    cout << "\n=== ���� ��������� ===\n";
    Artefact<int, vector<string>> a = inputArtefactSafe();
    artefacts.push_back(a);
    cout << "�������� ��������.\n";
}

void printArtefacts() {
    cout << "\n=== ������ ���������� ===\n";
    if (artefacts.empty()) {
        cout << "������ ����.\n";
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
        cout << "������������ ����������.\n";
        return;
    }
    printArtefacts();
    int i1 = inputNumber<int>("�������� ����� ������� ���������: ") - 1;
    if (i1 < 0 || i1 >= static_cast<int>(artefacts.size())) return;

    cout << "\n--- �������� ++ ---\n";
    cout << "��: "; artefacts[i1].printInfo();
    ++artefacts[i1];
    cout << "����� ++: "; artefacts[i1].printInfo();

    cout << "\n--- �������� == (� ����� �����) ---\n";
    cout << (artefacts[i1] == artefacts[i1] ? "�����" : "�� �����") << endl;

    cout << "\n--- �������� ������������ ---\n";
    Artefact<int, vector<string>> assigned;
    assigned = artefacts[i1];
    cout << "����������� ��������: "; assigned.printInfo();

    cout << "\n--- �������� ������������� ������������ ---\n";
    Artefact<int, vector<string>> moved;
    moved = move(assigned);
    cout << "��������� �����������: "; moved.printInfo();

    if (artefacts.size() < 2) {
        cout << "\n������������ ���������� ��� ������������ ��������� +.\n";
        return;
    }

    int i2 = inputNumber<int>("�������� ����� ������� ��������� ��� ��������: ") - 1;
    if (i2 < 0 || i2 >= static_cast<int>(artefacts.size()) || i1 == i2) return;

    cout << "\n--- �������� + ---\n";
    Artefact<int, vector<string>> sum = artefacts[i1] + artefacts[i2];
    cout << "�����: "; sum.printInfo();
}

void searchByLocationWrapper() {
    searchByLocation(artefacts);
}

void filterByPeriodWrapper() {
    filterByPeriod(artefacts);
}

// ��������� �����/������

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
