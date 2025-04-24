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

// prototype
void wordleHelper(int idx,
                  string& cur,
                  set<string>& out,
                  string floats,
                  int blanks,
                  const set<string>& dict);

set<string> wordle(const string& in,
                   const string& floating,
                   const set<string>& dict)
{
    set<string> output;
    string current = in;
    int blanks = 0;
    for(int i = 0; i < (int)in.size(); ++i)
        if(in[i]=='-') blanks++;
    wordleHelper(0, current, output, floating, blanks, dict);
    return output;
}

void wordleHelper(int idx,
                  string& cur,
                  set<string>& out,
                  string floats,
                  int blanks,
                  const set<string>& dict)
{
    int n = cur.size();
    if(idx==n) {
        if(floats.empty() && dict.count(cur))
            out.insert(cur);
        return;
    }
    if(cur[idx] != '-') {
        wordleHelper(idx+1, cur, out, floats, blanks, dict);
        return;
    }
    if(blanks == (int)floats.size()) {
        for(int i=0; i<(int)floats.size(); ++i) {
            char c = floats[i];
            cur[idx] = c;
            string nextF = floats;
            nextF.erase(i,1);
            wordleHelper(idx+1, cur, out, nextF, blanks-1, dict);
            cur[idx] = '-';
        }
    }
    else {
        for(char c='a'; c<='z'; ++c){
            string nextF = floats;
            auto p = nextF.find(c);
            if(p!=string::npos) nextF.erase(p,1);
            cur[idx] = c;
            wordleHelper(idx+1, cur, out, nextF, blanks-1, dict);
            cur[idx] = '-';
        }
    }
}
