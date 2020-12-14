// maximum-weight independent set of a path graph

/*

task in this problem is to run the dynamic programming algorithm 
(and the reconstruction procedure) from lecture on this data set. 
The question is: of the vertices 1, 2, 3, 4, 17, 117, 517, and 997, 
which ones belong to the maximum-weight independent set? 
(By "vertex 1" we mean the first vertex of the graph---there is no vertex 0.) 
In the box below, enter a 8-bit string, where the ith bit should be 1 if the ith 
of these 8 vertices is in the maximum-weight independent set, and 0 otherwise. 

*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <set>
#include <array>

std::vector<long> readFile();
std::vector<long> mwis(std::vector<long> path);
std::string inArray(const std::array<int, 8> arr);


int main(int argc, char const *argv[])
{
    const std::array<int, 8> test {1, 2, 3, 4, 17, 117, 517, 997};
    std::cout << inArray(test);
    return 0;
}



std::string inArray(const std::array<int, 8> arr)
{
    std::string result {""};
    auto v = readFile();
    auto mwisVec = mwis(v);

    std::set<long> s;


    // obtain the which vertices are in M-W independent set
    // Reconstruction algorithm
    long i = v.size() + 1;
    while (i >= 1)
    {
        if (mwisVec[i-1] >= (mwisVec[i-2] + v[i-1]))
            i--;
        else
        {
            s.insert(i);
            i -= 2;
        }
    }
    
    // Construct a string for task
    for (auto &&i : arr)
    {
        if(s.find(i) != s.end())
        {
            result.append("1");
        }
        else
        {
            result.append("0");
        }
        
    }
    
    return result;
    
}

// linear time algorithm for finding maximum weight independent set of path graph
// maximum weight is equal to *(result.end() - 1)
// we return vector because of reconstruction algorithm
std::vector<long> mwis(std::vector<long> path)
{
    std::vector<long> result;
    result.push_back(0);
    result.push_back(path[0]);

    for(size_t i = 2; i < path.size() + 1; i++)
    {
        result.push_back(0);
    }


    for (size_t i = 2; i < path.size() + 1; i++)
    {
        result[i] = std::max(result[i-1], result[i-2] + path[i-1]);
    }
    
    return result;
}

std::vector<long> readFile()
{
    std::string line;
    std::fstream file("mwis.txt");
    // read first line for number of vertex
    std::getline(file, line, '\n');
    auto n = std::stoi(line);
    
    // return variable
    std::vector<long> result;

    long temp;
    while(getline(file, line, '\n')){
        temp = std::stol(line);
        result.push_back(temp);
    }

    return result;
}