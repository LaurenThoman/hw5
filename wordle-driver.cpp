#ifndef RECCHECK
#include <iostream>
#include <set>
#include <string>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;
int main(int argc, char* argv[]){
  if(argc<2){
    cout<<"Usage: wordle pattern [floating]\n";
    return 1;
  }
  auto const & dict = readDictWords("dict-eng.txt");
  string pat = argv[1];
  string floats = (argc>2?argv[2]:"");
  auto res = wordle(pat, floats, dict);
  for(auto &w: res) cout<<w<<"\n";
  return 0;
}
#endif  // RECCHECK
