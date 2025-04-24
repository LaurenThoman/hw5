#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#endif

#include "schedwork.h"
using namespace std;

// INVALID_ID sentinel
static const Worker_T INVALID_ID = (Worker_T)-1;

// prototype for the backtracking helper
bool scheduleHelper(const AvailabilityMatrix& avail,
                    size_t dailyNeed,
                    size_t maxShifts,
                    DailySchedule& sched,
                    vector<size_t>& used,
                    size_t day,
                    size_t slot);

bool schedule(const AvailabilityMatrix& avail,
              const size_t dailyNeed,
              const size_t maxShifts,
              DailySchedule& sched)
{
    if (avail.empty()) return false;
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();
    // initialize with INVALID_ID
    sched.assign(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> used(numWorkers, 0);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, used, 0, 0);
}

bool scheduleHelper(const AvailabilityMatrix& avail,
                    size_t dailyNeed,
                    size_t maxShifts,
                    DailySchedule& sched,
                    vector<size_t>& used,
                    size_t day,
                    size_t slot)
{
    if (day == avail.size()) return true;
    if (slot == dailyNeed)
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, used, day+1, 0);

    // try each worker
    for (Worker_T w = 0; w < avail[0].size(); ++w) {
        if (!avail[day][w] || used[w] >= maxShifts)
            continue;
        // ensure no duplicate on this day
        bool dup = false;
        for (size_t i = 0; i < slot; ++i) {
            if (sched[day][i] == w) { dup = true; break; }
        }
        if (dup) continue;

        sched[day][slot] = w;
        ++used[w];
        if (scheduleHelper(avail, dailyNeed, maxShifts, sched, used, day, slot+1))
            return true;
        --used[w];
        sched[day][slot] = INVALID_ID;
    }
    return false;
}
