#ifndef GRAPH_ADJACENCY_LIST_HPP
#define GRAPH_ADJACENCY_LIST_HPP

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>

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
    void Bfs(int s, int d);
    void Dfs(int s, int d);
    void Dfs2(int s, int d); // recursive method
    bool RecurDfs(int s, int d, std::vector<int>& prev, std::vector<bool>& visited);
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
    if (s > v || d > v || s==d) return;
    
    adj[s].emplace_back(s, d, w);
    if (!directed) adj[d].emplace_back(d, s, w);
}

void Graph::RemoveEdge(int s, int d)
{
    if (s > v || d > v || s==d) return;

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


void Graph::Bfs(int s, int d)
{
    if (s > v || d > v || s==d) return;

    std::queue<int> queue;
    std::vector<int> prev(v);
    std::vector<bool> visited(v);

    queue.push(s);
    visited[s] = true;
    int i = 0;

    while(!queue.empty())
    {
        int s1 = queue.front();
        int d1 = s1;
        queue.pop();
        for (auto it=adj[s1].begin(); it != adj[s1].end(); it++)
        {
            d1 = (*it).dest;
            if (!visited[d1])
            {
                prev[d1] = s1;
                if (d1 == d)
                {
                    break;
                }
                visited[d1] = true;
                queue.push(d1);
            }
        }
        if (d1 == d)
        {
            while (d1 != s)
            {
                std::cout << d1 << "<--";
                d1 = prev[d1];
            }
            std::cout << s << std::endl;
            return;  
        }
    }
}

void Graph::Dfs(int s, int d)
{
    if (s>v || d>v || s==d) return;

    std::stack<int> stack;
    std::vector<bool> visited(v);
    std::vector<int> prev(v);

    stack.push(s);
    visited[s] = true;

    while (!stack.empty())
    {
        int s1 = stack.top();
        int d1 = s1;
        stack.pop();
        
        for (auto it = adj[s1].begin(); it != adj[s1].end(); it++)
        {
            d1 = (*it).dest;

            if (!visited[d1])
            {
                prev[d1] = s1;
                if (d1 == d)
                {
                    break;
                }
                visited[d1] = true;
                stack.push(d1);
            }
        }
        if (d1 == d)
        {
            while (d1 != s)
            {
                std::cout << d1 << "<--";
                d1 = prev[d1];
            }
            std::cout << s << std::endl;
            return;
        }
    }
}

void Graph::Dfs2(int s, int d)
{
    if (s>v || d>v || s==d) return;

    std::vector<bool> visited(v);
    std::vector<int> prev(v);
    visited[s] = true;
    bool res = RecurDfs(s, d, prev, visited);

    if (res)
    {
        int tmp = d;
        while (tmp != s)
        {
            std::cout << tmp << "<--";
            tmp = prev[tmp];
        }
        std::cout << s << std::endl;
        return;
    }
}

bool Graph::RecurDfs(int s, int d, std::vector<int>& prev, std::vector<bool>& visited)
{
    bool res = false;
    for (auto it = adj[s].begin(); it != adj[s].end(); it++)
    {
        int d1 = (*it).dest;
        if (!visited[d1])
        {
            prev[d1] = s;
            if (d1 == d) return true;
            visited[d1] = true;
            res = RecurDfs(d1, d, prev, visited);
            if (res) return true;
        }
    }
    return res;
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

    Graph g2(15, false);
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


    Graph g3 = Graph(9,false);
    g3.AddEdge(0, 1, 20);
    g3.AddEdge(0, 3, 20);
    g3.AddEdge(1, 2, 60);
    g3.AddEdge(1, 4, 60);
    g3.AddEdge(2, 5, 60);
    g3.AddEdge(3, 4, 20);
    g3.AddEdge(4, 5, 10);
    g3.AddEdge(4, 6, 10);
    g3.AddEdge(5, 7, 10);
    g3.AddEdge(6, 7, 10);
    g3.Display();


    g3.Bfs(0, 6);
    g3.Dfs(0, 6);
    g3.Dfs2(0, 6);

    return 0;
}

#endif