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
#include <fstream>


void sortByRatio(std::vector<std::pair<std::pair<int,int>, double>> &schedule);
void sortByDifference(std::vector<std::pair<std::pair<int,int>, double>> &sch);
long long sumOfWeightedCompletionTimes(std::vector<std::pair<std::pair<int,int>, double>> &schedule);
void readJobFilesToVector(std::vector<std::pair<std::pair<int,int>, double>> &schedule);


int main(int argc, char const *argv[])
{
    // pair.first.first = weight, pair.first.second = length, pair.second = Ratio
    std::vector<std::pair<std::pair<int, int>, double>> schedule;
    
    readJobFilesToVector(schedule);

    sortByDifference(schedule);
    std::cout << "Completion Times Weighted Sum using Difference: " << sumOfWeightedCompletionTimes(schedule) << "\n";

    sortByRatio(schedule);
    std::cout << "Completion Time Weighted Sum using Ratio: " << sumOfWeightedCompletionTimes(schedule);
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



void sortByDifference(std::vector<std::pair<std::pair<int,int>, double>> &schedule){
    std::sort(schedule.begin(), schedule.end(), [](std::pair<std::pair<int, int>, double> &l,
                                                   std::pair<std::pair<int,int>, double> &r){
        double lRatio = static_cast<double>(l.first.first)-l.first.second;
        l.second = lRatio;
        double rRatio = static_cast<double>(r.first.first)-r.first.second;
        r.second = rRatio;

        if(lRatio == rRatio){
            return l.first.first > r.first.first;
        }

        return lRatio > rRatio;
    });
}


long long sumOfWeightedCompletionTimes(std::vector<std::pair<std::pair<int,int>, double>> &schedule){
    int timePassed = 0;
    long long weightedCompletionTime = 0;

    for(auto &iii: schedule){
        timePassed += iii.first.second;
        weightedCompletionTime += timePassed * iii.first.first;
        // how many time passed
        //timePassed += iii.first.second;
    }

    return weightedCompletionTime;
}



void readJobFilesToVector(std::vector<std::pair<std::pair<int,int>, double>> &schedule){
    std::ifstream file("jobs.txt");
    std::string line;
    getline(file,line);
    schedule.reserve(std::stoi(line));


    int strIndex = 0;
    int weight = 0;
    int length = 0;
    while(getline(file, line, '\n')){
        // Split index by ' ' and push jobs in vector

        // Find weight
        weight = std::stoi(line);

        // Find length
        while(line[strIndex] != ' '){
            strIndex++;
        }
        strIndex++;

        length = line[strIndex] - '0';
        strIndex++;
        while(line[strIndex] >= '0' && line[strIndex] <= '9'){
            length *= 10;
            length += line[strIndex] - '0';
            strIndex++;
        }
        schedule.push_back(std::make_pair(std::make_pair(weight, length),INT_MIN));
        
        strIndex = 0;
        weight = 0;
        length = 0;
    }
}

