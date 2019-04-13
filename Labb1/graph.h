#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Graph
{
public:
    Graph(int nrOfVertices);
    
    bool DFS();
    bool BFS();

    void shortestPath(int start, int end);

    friend std::istream& operator>>(std::istream& is, Graph& graph);
    friend std::ostream& operator<<(std::ostream& os, const Graph& graph);    

private:  
    void resetVisited();

    bool checkSearch();

    std::vector<int> getNeighbours(int vertex);

    int getSmallest(const std::vector<double>& dist);

    double dist_between(int s_node, int e_node);

    void printPath(int start, int end, std::vector<int> tree);

    std::map<int, std::string> vertices;

    const int nrOfVertices;

    std::vector<std::vector<double>> matrix;
    std::vector<bool> visited;

};

#endif