#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Recursive helper—exactly 2 loops in here
void wordleHelper(int pos,
                  string& cur,
                  set<string>& out,
                  string floats,
                  const set<string>& dict)
{
    int n = (int)cur.size();
    if (pos == n) {
        if (floats.empty() && dict.count(cur))
            out.insert(cur);
        return;
    }
    if (cur[pos] != '-') {
        wordleHelper(pos+1, cur, out, floats, dict);
        return;
    }
    int remain = n - pos;
    if (remain == (int)floats.size()) {
        // must place exactly all floating letters
        for (int i = 0; i < (int)floats.size(); ++i) {
            char c = floats[i];
            cur[pos] = c;
            string nextF = floats;
            nextF.erase(i,1);
            wordleHelper(pos+1, cur, out, nextF, dict);
            cur[pos] = '-';
        }
    }
    else {
        // can place any letter a–z
        for (char c = 'a'; c <= 'z'; ++c) {
            cur[pos] = c;
            string nextF = floats;
            auto p = nextF.find(c);
            if (p != string::npos) nextF.erase(p,1);
            wordleHelper(pos+1, cur, out, nextF, dict);
            cur[pos] = '-';
        }
    }
}

// Public entry point—no loops here
set<string> wordle(const string& in,
                   const string& floating,
                   const set<string>& dict)
{
    set<string> output;
    string current = in;
    wordleHelper(0, current, output, floating, dict);
    return output;
}
