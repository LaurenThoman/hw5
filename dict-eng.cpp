#include "dict-eng.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <set>
#include <string>

#ifndef RECCHECK
const std::set<std::string>& readDictWords(std::string fn){
  static std::set<std::string> dict;
  if(dict.empty()){
    std::ifstream f(fn);
    if(!f) throw std::logic_error("Cannot open dict");
    std::string w;
    while(f>>w){
      bool ok=true;
      for(char c:w) if(!std::isalpha(c)||std::isupper(c)) ok=false;
      if(ok) dict.insert(w);
    }
    std::cerr<<"Read "<<dict.size()<<" words\n";
  }
  return dict;
}
#endif  // RECCHECK
