#include "graph.h"
#include "fstream"

int main()
{
    std::string path = "export.txt";
    std::ifstream file;

    file.open(path.c_str());
    
    Graph graph(48);

    file >> graph;

    if(graph.BFS()) std::cout << "BFS found all nodes" << std::endl;
    else            std::cout << "Graph is not connected" << std::endl;

    if(graph.DFS()) std::cout << "DFS found all nodes" << std::endl;
    else            std::cout << "Graph is not connected" << std::endl;

    return 0;
}