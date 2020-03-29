#ifndef TOPOLOGY_HPP
#define TOPOLOGY_HPP

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>

class Graph
{
private:
    int v;
    std::list<int> *adj;
public:
    Graph(int n);
    ~Graph();
    void AddEdge(int s, int d);
    void TopoSortByKahn();
    void TopoSortByStackDfs();
    void TopoSortByRecursiveDfs();
    void Dfs(int s, std::vector<std::list<int>> &inverse_adj, std::vector<bool> &visited);
};

Graph::Graph(int n)
{
    v = n;
    adj = new std::list<int>[v];
}

Graph::~Graph()
{
    v = 0;
    delete[] adj;
}

void Graph::AddEdge(int s, int d)
{
    adj[s].emplace_back(d);
}


void Graph::TopoSortByKahn()
{
    std::vector<int> in_degree(v, 0);
    std::queue<int> candidates;
    for (int i = 0; i < v; i++)
    {
        for (auto &it : adj[i])
        {
            in_degree[it] += 1;
        }
    }

    for (int i = 0; i < in_degree.size(); i++)
    {
        if (in_degree[i] == 0) candidates.push(i);
    }

    while (!candidates.empty())
    {
        int vertex = candidates.front();
        candidates.pop();
        for (auto &it : adj[vertex]) 
        {
            in_degree[it] -= 1;
            if (in_degree[it] == 0) candidates.push(it);
        }
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
}

void Graph::TopoSortByStackDfs()
{
    std::vector<std::list<int>> inverse_adj(v);
    for (int i = 0; i < v; i++)
    {
        for (auto &it: adj[i])
        {
            inverse_adj[it].emplace_back(i);
        }
    } 

    std::vector<bool> visited(v, false);
    std::stack<int> s;
    for (int i = 0; i <v; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;

            // to be finished...
        }
    }
    std::cout << std::endl;
}


void Graph::TopoSortByRecursiveDfs()
{
    std::vector<std::list<int>> inverse_adj(v);
    for (int i = 0; i < v; i++)
    {
        for (auto &it: adj[i])
        {
            inverse_adj[it].emplace_back(i);
        }
    } 

    std::vector<bool> visited(v, false);
    for (int i = 0; i < v; i++)
    {
        Dfs(i, inverse_adj, visited);
    }

    std::cout << std::endl;
}

void Graph::Dfs(int s, std::vector<std::list<int>> &inverse_adj, std::vector<bool> &visited)
{
    if (visited[s]) 
    {
        return;
    } else
    {
        visited[s] = true;
        for (auto &it: inverse_adj[s])
        {
            Dfs(it, inverse_adj, visited);
        }
        std::cout << s << " ";
    }
}

int main(void)
{
    Graph g2(14);
    g2.AddEdge(12, 3);
    g2.AddEdge(3, 13);
    g2.AddEdge(3, 2);
    g2.AddEdge(2, 1);
    g2.AddEdge(1, 0);
    g2.AddEdge(13, 6);
    g2.AddEdge(6, 0);
    g2.AddEdge(12, 4);
    g2.AddEdge(4, 0);
    g2.AddEdge(4, 8);
    g2.AddEdge(8, 9);
    g2.AddEdge(8, 5);
    g2.AddEdge(9, 5);
    g2.AddEdge(6, 7);
    g2.AddEdge(7, 11);
    g2.AddEdge(11, 10);
    g2.AddEdge(10, 9);
    g2.AddEdge(10, 5);
    g2.AddEdge(5, 0);


    g2.TopoSortByKahn();

    g2.TopoSortByRecursiveDfs();
}

#endif 