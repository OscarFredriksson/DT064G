#include "graph.h"
#include <fstream>

Graph::Graph(std::string path)
{
    fillMatrix();
    loadMatrix(path);
}

void Graph::fillMatrix()
{
    for(int i = 0; i < 48; i++)
    {
        std::vector<double> temp;

        for(int j = 0; j < 48; j++) temp.push_back(0.0); 

        adjacencyMatrix.push_back(temp);
    }
}

void Graph::loadMatrix(std::string path)
{
    std::ifstream file;
    file.open(path);

    while(!file.eof())
    {
        std::string line;
        std::getline(file, line);

        if(isdigit(line[0]))
        {
            int id1 = stoi(line.substr(0, line.find(" ")));      

            line.erase(0, line.find(" ")+1);

            int id2 = stoi(line.substr(0, line.find(" ")));

            line.erase(0, line.find(" ")+1);

            adjacencyMatrix[id1][id2] = stod(line.substr(0, line.find(" ")));
        }
    }   
}

void Graph::printMatrix()
{
    for(auto v1: adjacencyMatrix)
    {
        for(auto length: v1)  std::cout << length << "\t";
        std::cout << std::endl;
    }
}

void Graph::load(std::string path)
{
    std::ifstream file;
    file.open(path);

    while(!file.eof())
    {
        std::string line;
        std::getline(file, line);

        if(line.substr(0, 1) == "M")
        {
            line.erase(0, 2);

            int id = stoi(line.substr(0, line.find(" ")));
            std::string name = line.substr(line.find(" ")+1);

            vertices[id] = name;
        }
        else if(isdigit(line[0]))
        {
            Edge temp;

            int id = stoi(line.substr(0, line.find(" ")));      

            temp.v1 = Vertex(id, vertices[id]);

            line.erase(0, line.find(" ")+1);

            id = stoi(line.substr(0, line.find(" ")));

            temp.v2 = Vertex(id, vertices[id]);

            line.erase(0, line.find(" ")+1);

            temp.length = stod(line.substr(0, line.find(" ")));

            temp.descr = line.substr(line.find("[") + 1, line.find("]") - line.find("[") - 1);

            edges.push_back(temp);

        }
    }
}

void Graph::print()
{
    for(auto e: edges)  std::cout << e.v1.id << " " << e.v2.id << " " << e.length << " " << e.descr << "\n";
}