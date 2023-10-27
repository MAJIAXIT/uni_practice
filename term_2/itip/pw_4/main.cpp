#include "json.hpp"
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>

#define STRUCT_ARR_SIZE 100

using namespace std;
using json = nlohmann::json;

struct _struct {
    string name;
    int mainP;
    int helpP;
    friend ostream &operator<<(ostream &out, struct _struct &ob) {
        out << "MainP: " << ob.mainP << "\tHelpP: " << ob.helpP
            << "\tName: " << ob.name << endl;
        return out;
    }
};

void to_json(json &j, const _struct &st) {
    j = json{{"helpP", st.helpP}, {"mainP", st.mainP}, {"name", st.name}};
}

bool structCompare(_struct const &lhs, _struct const &rhs) {
    if (lhs.mainP != rhs.mainP)
        return lhs.mainP < rhs.mainP;
    return true;
}

int main() {
    ifstream words("words.txt");
    if (!words) {
        cerr << "Error while opening file \"words.txt\". Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    set<string> _set;
    set<string>::iterator _setIt;
    string word;

    // Fill the set
    while (getline(words, word, '-'))
        _set.insert(word);

    // Out set contents
    // for (auto &el : _set) {
    //     std::cout << el << ' ';
    // }

    // Return to start of file stream
    words.clear();
    words.seekg(0);

    // Fill the map
    map<int, int> _map;
    map<int, int>::iterator _mapIt;
    while (getline(words, word, '-'))
        _map[word.length()]++;

    // Out map contents
    // while (_mapIt != _map.end()) {
    //     cout << _mapIt->first << " : " << _mapIt->second << endl;
    //     ++_mapIt;
    // }

    // Fill structs array
    array<_struct, STRUCT_ARR_SIZE> arr;
    array<_struct, STRUCT_ARR_SIZE>::iterator arrIt;
    for (arrIt = arr.begin(); arrIt != arr.end(); arrIt++) {
        // Randomize name from set
        size_t r = rand() % _set.size();
        _setIt = _set.begin();
        advance(_setIt, r);
        arrIt->name = _setIt->data();

        // Randomize mainP
        arrIt->mainP = 1;
        for (int i = 0; i < 3; i++) {
            r = rand() % _map.size();
            _mapIt = _map.begin();
            advance(_mapIt, r);
            arrIt->mainP *= _mapIt->second;
        }

        // helpP
        arrIt->helpP = _map[arrIt->name.length()];
        arrIt->helpP *= arrIt->helpP;
    }

    sort(arr.begin(), arr.end(), structCompare);

    // Output sorted array
    // for (arrIt = arr.begin(); arrIt != arr.end(); arrIt++)
    //     cout << *arrIt;

    array<_struct, STRUCT_ARR_SIZE> arr2;
    array<_struct, STRUCT_ARR_SIZE>::iterator arr2It = arr2.begin();

    copy_if(arr.begin(), arr.end(), arr2.begin(),
            [](_struct x) { return (x.mainP + x.helpP) % 2 == 1; });

    // Creating json array
    json j;
    for (_struct x : arr2)
        if (x.name.length() != 0)
            j.push_back(x);

    ofstream out("out.json");
    if (!out) {
        cerr << "Error while opening file \"out.json\". Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
    // Write json to file
    out << j.dump(4);

    exit(EXIT_SUCCESS);
}

