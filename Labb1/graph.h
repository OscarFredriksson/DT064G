#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>

class Graph
{
public:
    Graph(int nrOfVertices);
    
    void BFS();

    void DFS();

    bool checkSearch();

    friend std::istream& operator>>(std::istream& is, Graph & graph);

    friend std::ostream& operator<<(std::ostream& os, const Graph & graph);    

private:  
    void resetVisited();


    std::vector<std::vector<double>> matrix;
    std::vector<bool> visited;


};

#endif