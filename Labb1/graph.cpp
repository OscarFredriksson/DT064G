#include "graph.h"
#include <stack>
#include <list>

Graph::Graph(int nrOfVertices):
    nrOfVertices(nrOfVertices),
    visited(nrOfVertices, false),
    matrix(nrOfVertices, std::vector<double>(nrOfVertices, -1))
{}

bool Graph::DFS()
{
    resetVisited();

    std::stack<int> nodes;
    
    const int start = 0;

    nodes.push(start);
    visited[start] = true;

    while(!nodes.empty())
    {
        int i = nodes.top();
        nodes.pop();

        for(auto n: getNeighbours(i))
        {
            visited[n] = true;
            nodes.push(n);
        }
    }

    return checkSearch();
}

bool Graph::BFS()
{
    resetVisited();

    std::list<int> nodes;
    
    const int start = 0;

    nodes.push_back(start);
    visited[start] = true;

    while(!nodes.empty())
    {
        int i = nodes.front();
        nodes.pop_front();

        for(auto n: getNeighbours(i))
        {
            visited[n] = true;
            nodes.push_back(n);
        }
    }

    return checkSearch();
}

std::vector<int> Graph::getNeighbours(int vertex)
{
    std::vector<int> neighbours;
    
    for(int j = 0; j < matrix[vertex].size(); j++)
    {
        if(!visited[j] && matrix[j][vertex] != -1)
        {
            neighbours.push_back(j);
        }
    }

    return neighbours;
}

bool Graph::checkSearch()
{
    for(auto v: visited)    if(!v)  return false;
    return true;
}

void Graph::shortestPath(int start, int end)
{
    resetVisited();

    std::vector<double> dist(nrOfVertices, 99999.9);
    std::vector<int> tree(nrOfVertices);

    dist[start] = 0;

    for(int i = 0; i < matrix[0].size(); i++)
    {
        int curr_node = getSmallest(dist);
        visited[curr_node] = true;


        for(auto n: getNeighbours(curr_node))
        {
            double new_path = dist[curr_node] + dist_between(curr_node, n);

            if(new_path < dist[n])
            {
                dist[n] = new_path;
                tree[n] = curr_node;
            }
        }
    }

    std::cout << "Längd: " << dist[end] << "\n";

    std::cout << "Väg: ";
    printPath(start, end, tree);
}

double Graph::dist_between(int s_node, int e_node)
{
    return matrix[e_node][s_node];
}

int Graph::getSmallest(const std::vector<double>& dist)
{
    double min = 9999999;
    int min_index;

    for(int i = 0; i < dist.size(); i++)
    {
        //std::cout << dist[i] << " " << min << std::endl;

        if(dist[i] < min && !visited[i]) 
        {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

void Graph::printPath(int start, int end, std::vector<int> tree)
{
    std::vector<int> path;
    int trace = end;
    while(trace != start)
    {
        path.push_back(trace);

        trace = tree[trace];
    }
    path.push_back(start);

    std::for_each(path.rbegin(), path.rend(), [this, &path](int node)
    {
        std::cout << vertices[node];

        if(node != path[0]) std::cout << " -> ";
    });

    std::cout << std::endl;
}

void Graph::resetVisited()
{
    for(auto v: visited)    v = false;
}

std::istream& operator>>(std::istream& is, Graph& graph)
{
    while(!is.eof())
    {
        std::string line;
        std::getline(is, line);
        
        if(line.substr(0, 1) == "M")
        {
            line.erase(0, 2);

            int id = stoi(line.substr(0, line.find(" ")));
            std::string name = line.substr(line.find(" ")+1);
            graph.vertices[id] = name;

            //std::cout << id << " " << graph.vertices[id] << std::endl;
        }
        else if(isdigit(line[0]))
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

std::ostream& operator<<(std::ostream& os, const Graph& graph)
{
    for(auto v1: graph.matrix)
    {
        for(auto length: v1)  os << length << "\t";
        
        os << "\n";
    }

    return os;
}