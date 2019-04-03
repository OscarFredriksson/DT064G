#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct vertex
{
    int id;
    std::string name;
};

struct edge
{
    vertex v1, v2;
    double length;
    std::string descr;
};

int main()
{
    std::vector<vertex> v;

    std::ifstream file;
    file.open("export.txt");

    while(!file.eof())
    {
        std::string line;
        std::getline(file, line);

        if(line.substr(0,1) == "M")
        {
            line.erase(0, 2);

            vertex temp;

            temp.id = stoi(line.substr(0, line.find(" ")));
            temp.name = line.substr(line.find(" ")+1);

            v.push_back(temp);
        }
    }

    for(auto e: v)  std::cout << e.id << " " << e.name << "\n";

    return 0;
}