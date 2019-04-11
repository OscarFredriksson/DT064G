#include "graph.h"
#include "fstream"

int main()
{
    std::string path = "export.txt";
    std::ifstream file;

    file.open(path.c_str());
    
    Graph graph(48);

    file >> graph;

    graph.BFS();

    if(graph.checkSearch())
        std::cout << "BFS found all nodes" << std::endl;
    else
        std::cout << "Graph is not connected" << std::endl;

    graph.DFS();

    if(graph.checkSearch())
        std::cout << "DFS found all nodes" << std::endl;
    else
        std::cout << "Graph is not connected" << std::endl;

    return 0;
}