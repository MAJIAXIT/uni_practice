#include "json.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;
using json = nlohmann::json;

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: ./shuffler <filename.json>" << endl;
        exit(EXIT_SUCCESS);
    }

    if (strstr(*++argv, ".json") == nullptr) {
        cout << "File must be .json type. Exiting..." << endl;
        exit(EXIT_SUCCESS);
    }

    ifstream in(*argv);
    if (!in) {
        cout << "Error while opening file \"" << *argv << "\". Exiting..."
             << endl;
        exit(EXIT_FAILURE);
    }

    // Parse file contents
    json data = json::parse(in);

    random_device rd;
    mt19937 g(rd());

    // Shuffle file
    shuffle(data.begin(), data.end(), g);
    cout << data.dump(4) << endl;

    exit(EXIT_SUCCESS);
}