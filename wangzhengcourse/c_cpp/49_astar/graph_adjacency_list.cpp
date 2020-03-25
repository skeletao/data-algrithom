#ifndef GRAPH_ADJACENCY_LIST_HPP
#define GRAPH_ADJACENCY_LIST_HPP

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include "min_heap.hpp"

class Graph
{
private:
    int v;
    bool directed;
    std::list<Edge> *adj;
    Vertex *vertexts;
public:
    Graph(int n, bool dir = false);
    ~Graph();
    void AddEdge(int s, int d, int w = 1);
    void AddVertex(int s, int x, int y);
    void RemoveEdge(int s, int d);
    void Bfs(int s, int d);
    void Dfs(int s, int d);
    void Dfs2(int s, int d); // recursive method
    bool RecurDfs(int s, int d, std::vector<int>& prev, std::vector<bool>& visited);
    void AStar(int s, int d);
    void Display();
};

Graph::Graph(int n, bool dir)
{
    v = n;
    directed = dir;
    adj = new std::list<Edge>[v];
    vertexts = new Vertex[v];
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

void Graph::AddVertex(int s, int x, int y)
{
    vertexts[s] = Vertex(s, x, y);
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


void Graph::AStar(int s, int d)
{
    std::vector<bool> visited(v);
    std::vector<int> prev(v);
    MinHeap heap = MinHeap(v);

    visited[s] = true;
    vertexts[s].dis_s = 0;
    heap.Push(vertexts[s]);

    while (!heap.IsEmpty())
    {
        Vertex cur = heap.Pop();
        int i = cur.node;
        
        for (auto it = adj[i].begin(); it != adj[i].end(); it++)
        {
            int j = (*it).dest;
            int w = (*it).weight;

            if (vertexts[j].dis_s > vertexts[i].dis_s + w)
            {
                vertexts[j].dis_s = vertexts[i].dis_s + w;
                vertexts[j].dis_d = vertexts[j].dis_s + abs(vertexts[j].x - vertexts[d].y) + abs(vertexts[j].y - vertexts[d].y);
                prev[j] = i;

                if (visited[j])
                {
                    heap.Update(vertexts[j]);
                }
                else
                {
                    heap.Push(vertexts[j]);
                    visited[j] = true;
                }
            }

            if (j == d)
            {
                heap.Clears();
                break;
            }
        }
    }

    int tmp = d;

    while (tmp != s)
    {
        std::cout << tmp << "<--";
        tmp = prev[tmp];
    }
    std::cout << s << ": " << vertexts[d].dis_d << std::endl;
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

    int xs[] = {320, 300, 280, 270, 320, 360, 320, 370, 350, 390, 400, 400, 260, 270};
    int ys[] = {630, 630, 625, 630, 700, 620, 590, 580, 730, 690, 620, 580, 700, 600};

    for (int i = 0; i < sizeof(xs)/sizeof(int); i++)
    {
        g2.AddVertex(i, xs[i], ys[i]);
    }

    g2.AStar(0, 11);

    return 0;
}

#endif