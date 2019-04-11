#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>

class Graph
{
public:
    Graph(int nrOfVertices);
    
    bool BFS();

    bool DFS();

    friend std::istream& operator>>(std::istream& is, Graph & graph);

    friend std::ostream& operator<<(std::ostream& os, const Graph & graph);    

private:  
    void resetVisited();

    bool checkSearch();



    std::vector<std::vector<double>> matrix;
    std::vector<bool> visited;


};

#endif