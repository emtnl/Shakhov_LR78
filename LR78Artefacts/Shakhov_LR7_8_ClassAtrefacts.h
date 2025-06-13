#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include < stdexcept >
using namespace std;

template <typename AgeType, typename LocationType>
class Artefact {
protected:
    string name;
    AgeType age;
    LocationType locations;
    string historicalPeriod;

public:
    Artefact();
    Artefact(string n, AgeType a, LocationType locs, string period);
    Artefact(const Artefact& other);
    Artefact(Artefact&& other) noexcept;
    Artefact& operator=(const Artefact& other);
    Artefact& operator=(Artefact&& other) noexcept;

    string getName() const;
    AgeType getAge() const;
    LocationType getLocations() const;
    string getPeriod() const;

    void setName(string n);
    void setAge(AgeType a);
    void setLocations(LocationType locs);
    void setPeriod(string p);

    void addLocation(const string& newLoc);
    bool operator==(const Artefact& other) const;

    void printInfo() const;
    bool isAncient() const;
    string getHistoricalPeriod() const;
    int countLocations() const;

    bool isPrehistoric() const;
    string getPrehistoricEra() const;
    bool isMultilayer() const;
    int countArchaeologicalLayers() const;

    template <typename A, typename B>
    friend ostream& operator<<(ostream& os, const Artefact<A, B>& a);
    // Добавьте в public секцию класса Artefact
    Artefact& operator++(); // Префиксный инкремент
    Artefact operator+(const Artefact& other) const; // Оператор сложения
    template <typename A, typename B>
    friend istream& operator>>(istream& is, Artefact<A, B>& a);

    virtual ~Artefact() = default;
};

// Специализация Age<int, LocationType>
template <typename LocationType>
class Age : public Artefact<int, LocationType> {
public:
    Age();
    Age(const string& name, int age, const vector<LocationType>& locations, const string& period);
    Age(const Age& other);
    Age(Age&& other) noexcept;
    Age& operator=(const Age& other);
    Age& operator=(Age&& other) noexcept;

    using Artefact<int, LocationType>::getName;
    using Artefact<int, LocationType>::getAge;
    using Artefact<int, LocationType>::getLocations;
    using Artefact<int, LocationType>::getPeriod;

    using Artefact<int, LocationType>::setName;
    using Artefact<int, LocationType>::setAge;
    using Artefact<int, LocationType>::setLocations;
    using Artefact<int, LocationType>::setPeriod;

    void printInfo() const;
    bool isPrehistoric() const;
    string getPrehistoricEra() const;
    bool isMultilayer() const;
    int countArchaeologicalLayers() const;
};

// Специализация Locate<AgeType>
template <typename AgeType>
class Locate : public Artefact<AgeType, vector<string>> {
public:
    Locate();
    Locate(const string& name, AgeType age, const vector<string>& locations, const string& period);
    Locate(const Locate& other);
    Locate(Locate&& other) noexcept;
    Locate& operator=(const Locate& other);
    Locate& operator=(Locate&& other) noexcept;

    void printInfo() const;
    void addLocation(const string& loc);
    bool isMultilayer() const;
    int countArchaeologicalLayers() const;
    bool isAncient() const;
};

// Адаптер
template <typename Container>
class ArtefactAdapter {
private:
    Container artefacts;

public:
    void add(const Artefact<int, vector<string>>& a) {
        artefacts.insert(artefacts.end(), a);
    }

    void showAll() const {
        for (const auto& a : artefacts)
            a.printInfo();
    }

    set<string> getUniqueLocations() const {
        set<string> result;
        for (const auto& a : artefacts)
            for (const auto& loc : a.getLocations())
                result.insert(loc);
        return result;
    }

    map<string, vector<Artefact<int, vector<string>>>> groupByPeriod() const {
        map<string, vector<Artefact<int, vector<string>>>> groups;
        for (const auto& a : artefacts)
            groups[a.getPeriod()].push_back(a);
        return groups;
    }
};