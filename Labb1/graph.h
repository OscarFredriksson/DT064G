#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Vertex
{
    Vertex() = default;

    Vertex(int id, std::string name)
        :id(id), name(name)
    {}

    int id;
    std::string name;
};

struct Edge
{
    Vertex v1, v2;
    double length;
    std::string descr;
};

class Graph
{
public:
    Graph(std::string path);

    void loadMatrix(std::string path);

    void load(std::string path);

    void fillMatrix();

    void printMatrix();

    void DFS();

    void print();

private:    
    std::map<int, std::string> vertices;
    
    std::vector<Edge> edges;

    std::vector<std::vector<double>> adjacencyMatrix;
};

#endif