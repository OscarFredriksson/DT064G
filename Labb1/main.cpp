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
    else            std::cout << "BFS failed: graph is not connected" << std::endl;

    if(graph.DFS()) std::cout << "DFS found all nodes" << std::endl;
    else            std::cout << "DFS failed: Graph is not connected" << std::endl;

    std::cout << "\n";

    std::cout << "Nackstavägen Axvägen 1 till Förrådet:" << "\n";
    graph.shortestPath(24, 37);
    std::cout << "\n";

    std::cout << "L319 till D025:" << "\n";
    graph.shortestPath(46, 47);
    std::cout << "\n";

    std::cout << "Universitetet till Bite Line Västra:" << "\n";
    graph.shortestPath(20, 19);
    std::cout << "\n";

    return 0;
}