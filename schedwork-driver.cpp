#ifndef RECCHECK
#include <iostream>
#include "schedwork.h"
using namespace std;
void printSchedule(const DailySchedule& s){
  for(size_t d=0; d<s.size(); ++d){
    cout<<"Day "<<d<<": ";
    for(auto w: s[d]) cout<<w<<" ";
    cout<<"\n";
  }
}
int main(){
  AvailabilityMatrix avail={
    {1,1,1,1},
    {1,0,1,0},
    {1,1,0,1},
    {1,0,0,1}
  };
  DailySchedule sched;
  if(schedule(avail,2,2,sched)) printSchedule(sched);
  else cout<<"No solution\n";
  return 0;
}
#endif  // RECCHECK
