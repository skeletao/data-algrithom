#include <iostream>
#include <limits>
#include <ctime>
#include "skip_list.hpp"

using namespace std;

template <typename T>
Skip_list<T>::Node::Node(int k, int level): key(k), value()
{
    for(int i= 0; i < level; i++) forward.emplace_back(nullptr);
}


template <typename T>
Skip_list<T>::Skip_list(): MAX_LEVEL(15), probability(0.6)
{
    maxlevel = 0;
    int head_key = std::numeric_limits<int>::min();
    head = new Node(head_key, MAX_LEVEL);
}

template <typename T>
Skip_list<T>::Skip_list(int level, float p): MAX_LEVEL(level), probability(p)
{
    maxlevel = 0;
    int head_key = std::numeric_limits<int>::min();
    head = new Node(head_key, MAX_LEVEL);
}

template <typename T>
Skip_list<T>::~Skip_list()
{
    Node *node = head, *tmp = head;

    while (node && node->forward[0])
    {
        tmp = node;
        node = node->forward[0];
        delete tmp;
    }
    delete node;
}

template <typename T>
int Skip_list<T>::random_levle()
{
    static bool seeded = false;
    if (!seeded) 
    {
        std::srand(std::time(0));
        seeded = true;
    }
    int lvl = 1;
    while (((float)std::rand()/RAND_MAX < probability) && lvl < MAX_LEVEL) lvl++;

    return lvl;
}

template <typename T>
Skip_list<T>::Node *Skip_list<T>::make_node(int k, T &val, int level)
{
    Node *node = new Node(k, level);
    node->value = val;
    return node; 
}

template <typename T>
T Skip_list<T>::find(int k)
{

}

template <typename T>
void Skip_list<T>::insert(int k, T &v)
{

}

template <typename T>
void Skip_list<T>::erase(int k)
{

}

template <typename T>
void Skip_list<T>::display()
{
    
}