#ifndef RECCHECK
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

//  checks if start with pref
bool prefixExists(const set<string>& dict, const string& pref) {
  auto it = dict.lower_bound(pref);
  return it != dict.end()
    && it->compare(0, pref.size(), pref) == 0;
}

//  helper function with recursion
void wordleHelper(int pos,
                  string& cur,
                  set<string>& out,
                  string floats,
                  const set<string>& dict)
{
  int n = (int)cur.size();

  //  base case
  if(pos == n) {
    if(floats.empty() && dict.count(cur))
      out.insert(cur);
    return;
  }

  if (cur[pos] != '-') {
    string pref = cur.substr(0, pos+1);
    if(!prefixExists(dict, pref)){
      return;
    }

    wordleHelper(pos+1, cur, out, floats, dict);
    return;
  }

  int remaining = n-pos;
  if(remaining == (int)floats.size()){
    
    //  place all floating letter
    for(int i = 0; i < (int)floats.size(); ++i){
      char c = floats[i];
      cur[pos] = c;
      string pref = cur.substr(0, pos+1);

      if(!prefixExists(dict, pref)){
        cur[pos] = '-';
        continue;
      }
      string nextF = floats;
      nextF.erase(i,1);
      wordleHelper(pos+1, cur, out, nextF, dict);
      cur[pos] = '-';
    }
  }

  else{
    //  places any letters a to z
    for (char c = 'a'; c <= 'z'; ++c) {

      cur[pos] = c;
      string pref = cur.substr(0, pos+1);

      if(!prefixExists(dict, pref)) {
        cur[pos] = '-';
        continue;

      }
      string nextF = floats;
      auto p = nextF.find(c);
      
      if(p != string::npos){
        nextF.erase(p,1);
      } 

      //  recursive step
      wordleHelper(pos+1, cur, out, nextF, dict);
      cur[pos] = '-';
    }
  }
}

//  entry point
set<string> wordle(const string& in,
                   const string& floating,
                   const set<string>& dict)
{
  set<string> output;
  string current = in;
  wordleHelper(0, current, output, floating, dict);
  return output;
}
