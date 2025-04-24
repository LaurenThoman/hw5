#include <iostream>
#include <string>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: wordle pattern [floating]\n";
        return 1;
    }
    const auto& dict = readDictWords("dict-eng.txt");
    string pattern = argv[1];
    string floats = (argc > 2 ? argv[2] : "");
    auto answers = wordle(pattern, floats, dict);
    for (auto& w : answers) cout << w << "\n";
    return 0;
}
