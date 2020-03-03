#ifndef GRAPH_ADJACENCY_MATRIX_HPP
#define GRAPH_ADJACENCY_MATRIX_HPP

#include <iostream>

class Graph
{
private:
    int **array;
    int size;
    bool directed;
public:
    Graph(int, bool);
    ~Graph();
    void AddEdge(int, int, int);
    void RemoveEdge(int, int);
    void Display();
};

Graph::Graph(int n, bool dir = false):size(n), directed(dir)
{
    array = new int*[n];
    for (int i = 0; i < n; i++)
    {
        array[i] = new int[n]();
    }
}

Graph::~Graph()
{
    for (int i = 0; i < size; i++)
    {
        delete[] array[i];
    }
    delete[] array;
}


void Graph::AddEdge(int i, int j, int w = 1)
{
    if (i < 0 || i >= size || j < 0 || j >= size) return;

    array[i][j] = w;
    if (!directed) array[j][i] = w;
}


void Graph::RemoveEdge(int i, int j)
{
    if (i < 0 || i >= size || j < 0 || j >= size) return;

    array[i][j] = 0;
    if (!directed) array[j][i] = 0;
}


void Graph::Display()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int main(void)
{
    Graph g(5,false);
    
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(0, 4);
    g.AddEdge(3, 1);
    g.AddEdge(3, 2);
    g.AddEdge(4, 1);
    g.AddEdge(4, 3);
    g.RemoveEdge(3, 4);
    g.Display();
    
    return 0;
}

#endif