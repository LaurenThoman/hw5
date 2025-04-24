#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#endif

#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// prototype for the recursive helper
void wordleHelper(int pos,
                  string& current,
                  set<string>& output,
                  string floats,
                  const set<string>& dict);

set<string> wordle(const string& in,
                   const string& floating,
                   const set<string>& dict)
{
    set<string> output;
    string current = in;
    // kick off recursion (no loop here!)
    wordleHelper(0, current, output, floating, dict);
    return output;
}

void wordleHelper(int pos,
                  string& current,
                  set<string>& output,
                  string floats,
                  const set<string>& dict)
{
    int n = (int)current.size();
    if (pos == n) {
        if (floats.empty() && dict.count(current))
            output.insert(current);
        return;
    }
    if (current[pos] != '-') {
        wordleHelper(pos+1, current, output, floats, dict);
        return;
    }
    int remainingSlots = n - pos;
    if (remainingSlots == (int)floats.size()) {
        // must place all floats
        for (int i = 0; i < (int)floats.size(); ++i) {
            char c = floats[i];
            current[pos] = c;
            string nextFloats = floats;
            nextFloats.erase(i, 1);
            wordleHelper(pos+1, current, output, nextFloats, dict);
            current[pos] = '-';
        }
    }
    else {
        // any letter a–z
        for (char c = 'a'; c <= 'z'; ++c) {
            string nextFloats = floats;
            auto p = nextFloats.find(c);
            if (p != string::npos)
                nextFloats.erase(p,1);
            current[pos] = c;
            wordleHelper(pos+1, current, output, nextFloats, dict);
            current[pos] = '-';
        }
    }
}
