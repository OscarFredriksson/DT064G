#include "graph.h"
#include <stack>
#include <list>

Graph::Graph(int nrOfVertices):
    visited(nrOfVertices, false),
    matrix(nrOfVertices, std::vector<double>(nrOfVertices, -1))
{}

void Graph::BFS()
{
    resetVisited();

    std::stack<int> neighbours;
    
    const int start = 0;

    neighbours.push(start);
    visited[start] = true;

    while(!neighbours.empty())
    {
        int i = neighbours.top();
        neighbours.pop();

        for(int j = 0; j < matrix[i].size(); j++)
        {
            if(!visited[j] && matrix[j][i] != -1)
            {
                visited[j] = true;
                neighbours.push(j);
            }
        }
    }
}

void Graph::DFS()
{
    resetVisited();

    std::list<int> neighbours;
    
    const int start = 0;

    neighbours.push_back(start);
    visited[start] = true;

    while(!neighbours.empty())
    {
        int i = neighbours.front();
        neighbours.pop_front();

        for(int j = 0; j < matrix[i].size(); j++)
        {
            if(!visited[j] && matrix[j][i] != -1)
            {
                visited[j] = true;
                neighbours.push_back(j);
            }
        }
    }
}

bool Graph::checkSearch()
{
    for(auto v: visited)    
        if(!v)  
            return false;

    return true;
}

void Graph::resetVisited()
{
    for(auto v: visited)    v = false;
}

std::istream& operator>>(std::istream& is, Graph & graph)
{
    while(!is.eof())
    {
        std::string line;
        std::getline(is, line);

        if(isdigit(line[0]))
        {
            int id1 = stoi(line.substr(0, line.find(" ")));      

            line.erase(0, line.find(" ")+1);

            int id2 = stoi(line.substr(0, line.find(" ")));

            line.erase(0, line.find(" ")+1);

            graph.matrix[id1][id2] = stod(line.substr(0, line.find(" ")));
        }
    }  

    return is; 
}

std::ostream& operator<<(std::ostream& os, const Graph & graph)
{
    for(auto v1: graph.matrix)
    {
        for(auto length: v1)  os << length << "\t";
        
        os << "\n";
    }

    return os;
}