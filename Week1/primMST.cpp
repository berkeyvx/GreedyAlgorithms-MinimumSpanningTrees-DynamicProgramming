#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <utility>
#include <functional>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>

class Graph
{
    
    std::vector<std::vector<std::pair<int, long>>> g;
    int totalVertexNumber;
    std::vector<bool> visited;
    
    
public:

    Graph(int vertexNum):totalVertexNumber{vertexNum},visited(totalVertexNumber,false), g(vertexNum){
        
        for(auto i : visited)
            i = false;
        
    }
    
    Graph(){
        readFile();
    }
    

    // undirected graph
    void addEdge(int src, int dst, long cost){
        g.at(src).push_back(std::make_pair(dst, cost));
        g.at(dst).push_back(std::make_pair(src, cost));
    }

    
    std::vector<std::vector<std::pair<int, long>>> getGraph(){
        return g;
    }
    
    
    long getSize(){
        return totalVertexNumber;
    }
    
    
    int primMST(int initVertex);
    void readFile();
};



int main(int argc, char const *argv[])
{
    Graph g;
    std::cout << g.primMST(1);
    return 0;
}



int Graph::primMST(int initVertex){
    int cost = 0;
    std::vector<std::vector<std::pair<int, long>>> MST(totalVertexNumber);
    MST.reserve(totalVertexNumber);
    
    typedef std::pair<int,int> pair;
    std::priority_queue<pair, std::vector<pair>, std::greater<pair>> minPriorityQueue;
    
    // push first vertex into minPQ, cost,dest
    minPriorityQueue.push(std::make_pair(0, initVertex));
    
    int source = initVertex;
    while (minPriorityQueue.empty() != true) {
        auto minPair = minPriorityQueue.top();
        minPriorityQueue.pop();
        if(visited.at(minPair.second))
            continue;
        visited.at(minPair.second) = true;
        cost += minPair.first;
        
        int dest = minPair.second;
        MST.at(source).push_back(std::make_pair(dest, minPair.first));
        source = minPair.second;
        
        std::vector<std::pair<int,long>> currentVertex = getGraph().at(minPair.second);
        for (auto &neighbour : currentVertex) {
            if (!visited[neighbour.first]) {
                minPriorityQueue.push(std::make_pair(neighbour.second, neighbour.first));
            }

        }
    }
    MST.at(initVertex).erase(MST.at(initVertex).begin());
    for(int i = 1; i < totalVertexNumber; i++){
        for(auto& ii: MST[i]){
            std::cout << i << "->" << ii.first << ":" << ii.second << "\n";
        }
    }
    return cost;
}


void Graph::readFile(){
    std::string line;
    std::ifstream gTxt("mst.txt");
    getline(gTxt, line, '\n');
    int source,dest,cost;
    std::istringstream iss(line);
    int temp;
    iss >> temp;
    totalVertexNumber = temp + 1;
    g.resize(temp+1);
    visited.resize(temp+1);
    iss >> temp;
    while(getline(gTxt, line, '\n')){
        std::istringstream iss2(line);
        iss2 >> source;
        iss2 >> dest;
        iss2 >> cost;
        addEdge(source, dest, cost);
    }
}
