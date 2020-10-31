/*
    A Scheduling Application: That is how do you schedule jobs on shared resources in order to accomplish some objective
                              Assume there is just one shared resource. Problem is what order should we sequence these jobs
                              Jobs with heigher weight deserves to be processed earlier than those with lower weight.

        Completion Times: the completion times of Cj of job j = sum of job lengths up to and including j.

        Goal: Minimize the weighted sum of completion times.

                    min ∑ WjCj, j= 1 -> n

    Weight = importance of work
    Length = Completion time of work
    Greedy Algorithm: order by decreasing ratio Wi/Li
*/


#include <iostream>
#include <utility>
#include <climits>
#include <vector>

void sortByRatio(std::vector<std::pair<std::pair<int,int>, double>> &schedule);


int main(int argc, char const *argv[])
{
    // pair.first.first = weight, pair.first.second = length, pair.second = Ratio
    std::vector<std::pair<std::pair<int, int>, double>> schedule;
    
    // Jobs to be scheduled
    schedule.push_back(std::make_pair(std::make_pair(3, 5), INT_MIN));
    schedule.push_back(std::make_pair(std::make_pair(1, 2), INT_MIN));
    schedule.push_back(std::make_pair(std::make_pair(5, 3), INT_MIN));
    
    sortByRatio(schedule);
    
    for (auto &iii : schedule) {
        std::cout << "Weight: " << iii.first.first << "\tLength: " << iii.first.second << "\tRatio: " << iii.second << "\n";
    }
    return 0;
}


void sortByRatio(std::vector<std::pair<std::pair<int,int>, double>> &schedule){
    std::sort(schedule.begin(), schedule.end(), [](std::pair<std::pair<int, int>, double> &l,
                                                   std::pair<std::pair<int,int>, double> &r){
        double lRatio = static_cast<double>(l.first.first)/l.first.second;
        l.second = lRatio;
        double rRatio = static_cast<double>(r.first.first)/r.first.second;
        r.second = rRatio;
        return lRatio > rRatio;
    });
}
