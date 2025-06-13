// Artefact.cpp
#include "Shakhov_LR7_8_ClassAtrefacts.h"

// === Artefact ===
template <typename AgeType, typename LocationType>
Artefact<AgeType, LocationType>::Artefact() : name(""), age(), locations(), historicalPeriod("") {}

template <typename AgeType, typename LocationType>
Artefact<AgeType, LocationType>::Artefact(string n, AgeType a, LocationType locs, string period)
    : name(move(n)), age(a), locations(move(locs)), historicalPeriod(move(period)) {
}

template <typename AgeType, typename LocationType>
Artefact<AgeType, LocationType>::Artefact(const Artefact& other)
    : name(other.name), age(other.age), locations(other.locations), historicalPeriod(other.historicalPeriod) {
}

template <typename AgeType, typename LocationType>
Artefact<AgeType, LocationType>::Artefact(Artefact&& other) noexcept
    : name(move(other.name)), age(move(other.age)), locations(move(other.locations)), historicalPeriod(move(other.historicalPeriod)) {
}

template <typename AgeType, typename LocationType>
Artefact<AgeType, LocationType>& Artefact<AgeType, LocationType>::operator=(const Artefact& other) {
    if (this != &other) {
        name = other.name;
        age = other.age;
        locations = other.locations;
        historicalPeriod = other.historicalPeriod;
    }
    return *this;
}

template <typename AgeType, typename LocationType>
Artefact<AgeType, LocationType>& Artefact<AgeType, LocationType>::operator=(Artefact&& other) noexcept {
    if (this != &other) {
        name = move(other.name);
        age = move(other.age);
        locations = move(other.locations);
        historicalPeriod = move(other.historicalPeriod);
    }
    return *this;
}

template <typename AgeType, typename LocationType>
string Artefact<AgeType, LocationType>::getName() const { return name; }

template <typename AgeType, typename LocationType>
AgeType Artefact<AgeType, LocationType>::getAge() const { return age; }

template <typename AgeType, typename LocationType>
LocationType Artefact<AgeType, LocationType>::getLocations() const { return locations; }

template <typename AgeType, typename LocationType>
string Artefact<AgeType, LocationType>::getPeriod() const { return historicalPeriod; }

template <typename AgeType, typename LocationType>
void Artefact<AgeType, LocationType>::setName(string n) { name = move(n); }

template <typename AgeType, typename LocationType>
void Artefact<AgeType, LocationType>::setAge(AgeType a) {
    if (a < 0) {
        throw std::invalid_argument("Age некорректен");
    }
    age = a;
}

template <typename AgeType, typename LocationType>
void Artefact<AgeType, LocationType>::setLocations(LocationType locs) { locations = move(locs); }

template <typename AgeType, typename LocationType>
void Artefact<AgeType, LocationType>::setPeriod(string p) { historicalPeriod = move(p); }

template <typename AgeType, typename LocationType>
void Artefact<AgeType, LocationType>::addLocation(const string& newLoc) {
    if constexpr (is_same<LocationType, vector<string>>::value) {
        locations.push_back(newLoc);
    }
}
// Добавьте после всех других методов класса Artefact
template <typename AgeType, typename LocationType>
Artefact<AgeType, LocationType>& Artefact<AgeType, LocationType>::operator++() {
    ++age;
    return *this;
}

template <typename AgeType, typename LocationType>
Artefact<AgeType, LocationType> Artefact<AgeType, LocationType>::operator+(const Artefact& other) const {
    Artefact<AgeType, LocationType> result(*this);
    result.name = name + " + " + other.name;
    result.age += other.age;
    if constexpr (is_same<LocationType, vector<string>>::value) {
        for (const auto& loc : other.locations) {
            result.locations.push_back(loc);
        }
    }
    return result;
}




template <typename AgeType, typename LocationType>
bool Artefact<AgeType, LocationType>::operator==(const Artefact& other) const {
    return name == other.name && age == other.age && locations == other.locations && historicalPeriod == other.historicalPeriod;
}

// ==== Вспомогательные методы ====
template <typename AgeType, typename LocationType>
void Artefact<AgeType, LocationType>::printInfo() const {
    cout << "Name: " << name << "\nAge: " << age << "\nPeriod: " << historicalPeriod << "\nLocations: ";
    if constexpr (is_same<LocationType, vector<string>>::value) {
        for (const auto& loc : locations) cout << loc << ", ";
    }
    else {
        cout << locations;
    }
    cout << "\n";
}

template <typename AgeType, typename LocationType>
bool Artefact<AgeType, LocationType>::isAncient() const {
    return age > 1000;
}

template <typename AgeType, typename LocationType>
string Artefact<AgeType, LocationType>::getHistoricalPeriod() const {
    return historicalPeriod;
}

template <typename AgeType, typename LocationType>
int Artefact<AgeType, LocationType>::countLocations() const {
    if constexpr (is_same<LocationType, vector<string>>::value) {
        return static_cast<int>(locations.size());
    }
    return 1;
}

template <typename AgeType, typename LocationType>
bool Artefact<AgeType, LocationType>::isPrehistoric() const {
    return false;
}

template <typename AgeType, typename LocationType>
string Artefact<AgeType, LocationType>::getPrehistoricEra() const {
    return "";
}

template <typename AgeType, typename LocationType>
bool Artefact<AgeType, LocationType>::isMultilayer() const {
    return false;
}

template <typename AgeType, typename LocationType>
int Artefact<AgeType, LocationType>::countArchaeologicalLayers() const {
    return 0;
}

// === Операторы ввода/вывода ===
template <typename A, typename B>
ostream& operator<<(ostream& os, const Artefact<A, B>& a) {
    os << a.getName() << " " << a.getAge() << " " << a.getPeriod() << " ";
    if constexpr (is_same<B, vector<string>>::value) {
        for (const auto& loc : a.getLocations()) os << loc << ";";
    }
    else {
        os << a.getLocations();
    }
    return os;
}

template <typename A, typename B>
istream& operator>>(istream& is, Artefact<A, B>& a) {
    string name, period;
    A age; B locs;
    is >> name >> age >> period;
    a.setName(name);
    a.setAge(age);
    a.setPeriod(period);
    a.setLocations(locs);
    return is;
}

// === Явные инстанциации ===
template class Artefact<int, string>;
template class Artefact<int, vector<string>>;
template ostream& operator<<<int, string>(ostream&, const Artefact<int, string>&);
template ostream& operator<<<int, vector<string>>(ostream&, const Artefact<int, vector<string>>&);
template istream& operator>><int, string>(istream&, Artefact<int, string>&);
template istream& operator>><int, vector<string>>(istream&, Artefact<int, vector<string>>&);
