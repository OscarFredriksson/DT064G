#include "graph.h"

int main()
{
    std::string path = "export.txt";
    Graph graph(path);

    graph.printMatrix();

    return 0;
}