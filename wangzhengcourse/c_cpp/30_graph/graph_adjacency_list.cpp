#ifndef GRAPH_ADJACENCY_LIST_HPP
#define GRAPH_ADJACENCY_LIST_HPP

#include <iostream>
#include <list>

struct Edge
{
    int start;
    int dest;
    int weight;
    Edge(int s, int d, int w): start(s), dest(d), weight(w){}  
};

class Graph
{
private:
    int v;
    bool directed;
    std::list<Edge> *adj;
public:
    Graph(int n, bool dir = false);
    ~Graph();
    void AddEdge(int s, int d, int w = 1);
    void RemoveEdge(int s, int d);
    void Display();
};

Graph::Graph(int n, bool dir)
{
    v = n;
    directed = dir;
    adj = new std::list<Edge>[v];
}

Graph::~Graph()
{
    delete[] adj;
}

void Graph::AddEdge(int s, int d, int w)
{
    adj[s].emplace_back(s, d, w);
    if (!directed) adj[d].emplace_back(d, s, w);
}

void Graph::RemoveEdge(int s, int d)
{
    for (auto it=adj[s].begin(); it != adj[s].end(); it++)
    {
        if ((*it).dest == d) 
        {
            adj[s].erase(it);
            break;
        }
    }

    if (directed) return;

    for (auto it=adj[d].begin(); it != adj[d].end(); it++)
    {
        if ((*it).dest == s) 
        {
            adj[d].erase(it);
            break;
        }
    }
}


void Graph::Display()
{
    for (int i = 0; i < v; i++)
    {
        std::cout << i << ": ";
        for (auto it = adj[i].begin(); it != adj[i].end(); it++)
        {
            std::cout << (*it).dest << "(" << (*it).weight << ") ";
        }
        std::cout << std::endl;
    }
}


int main(void)
{
    Graph g1(6, true);
    g1.AddEdge(0, 1, 10);
    g1.AddEdge(0, 4, 15);
    g1.AddEdge(1, 2, 15);
    g1.AddEdge(1, 3, 2);
    g1.AddEdge(2, 5, 5);
    g1.AddEdge(3, 2, 1);
    g1.AddEdge(3, 5, 12);
    g1.AddEdge(4, 5, 10);
    g1.Display();

    Graph g2(14, false);
    g2.AddEdge(0, 1, 20);
    g2.AddEdge(0, 4, 60);
    g2.AddEdge(0, 5, 60);
    g2.AddEdge(0, 6, 60);
    g2.AddEdge(1, 2, 20);
    g2.AddEdge(2, 3, 10);
    g2.AddEdge(3, 12, 40);
    g2.AddEdge(3, 13, 30);
    g2.AddEdge(4, 8, 50);
    g2.AddEdge(4, 12, 40);
    g2.AddEdge(5, 8, 70);
    g2.AddEdge(5, 9, 80);
    g2.AddEdge(5, 10, 50);
    g2.AddEdge(6, 7, 70);
    g2.AddEdge(6, 13, 50);
    g2.AddEdge(7, 11, 50);
    g2.AddEdge(8, 9, 50);
    g2.AddEdge(9, 10, 60);
    g2.AddEdge(10, 11, 60);
    g2.Display();

    return 0;
}

#endif