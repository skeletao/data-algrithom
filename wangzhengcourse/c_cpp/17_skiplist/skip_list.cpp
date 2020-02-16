#include <iostream>
#include <limits>
#include <ctime>
#include <string>
#include "skip_list.hpp"

template<typename T>
Skip_list<T>::Node::Node(int k, int level): key(k), value(), forward(level+1, nullptr)
{
}


template<typename T>
Skip_list<T>::Skip_list(): MAX_LEVEL(15), probability(0.6)
{
    level = 0;
    int head_key = std::numeric_limits<int>::min();
    head = new Node(head_key, MAX_LEVEL);
}

template<typename T>
Skip_list<T>::Skip_list(int level, float p): MAX_LEVEL(level), probability(p)
{
    level = 0;
    int head_key = std::numeric_limits<int>::min();
    head = new Node(head_key, MAX_LEVEL);
}

template<typename T>
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

template<typename T>
int Skip_list<T>::random_levle()
{
    static bool seeded = false;
    if (!seeded) 
    {
        std::srand(std::time(0));
        seeded = true;
    }
    int lvl = 0;
    while (((float)std::rand()/RAND_MAX < probability) && lvl < MAX_LEVEL) lvl++;

    return lvl;
}

template<typename T>
typename Skip_list<T>::Node *Skip_list<T>::make_node(int k, T &val, int level)
{
    Node *node = new Node(k, level);
    node->value = val;
    return node; 
}

template<typename T>
typename Skip_list<T>::Node *Skip_list<T>::find(int k)
{
    Node *node = head;
    for (int i = level; i >= 0; i--)
    {
        while (node->forward[i] && node->forward[i]->key < k) node = node->forward[i];
    }
    node = node->forward[0];
    if (node && node->key == k)
    {
        return node;
    } else
    {
        return NULL;
    }
}

template<typename T>
void Skip_list<T>::insert(int k, T v)
{
    Node *node = head;

    typename std::vector<Node *> update(head->forward);

    for (int i = level; i >= 0; i--)
    {
        while (node->forward[i] && node->forward[i]->key < k) node = node->forward[i];
        update[i] = node;
    }
    node = node->forward[0];

    if (!node || node->key!= k)
    {
        int new_level = random_levle();
        Node *new_node = make_node(k, v, new_level);
        if (new_level > level)
        {
            for (int i = new_level; i > level; i--) update[i] = head;
            level = new_level;
        }

        for (int i = 0; i <= new_level; i++)
        {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }

    } else
    {
        if (node->value != v) node->value = v;
    }
    
}

template<typename T>
void Skip_list<T>::erase(int k)
{
    Node *node = head;
    typename std::vector<Node *> update(head->forward);

    for (int i = level; i >= 0; i--)
    {
        while (node->forward[i] && node->forward[i]->key < k) node = node->forward[i];
        update[i] = node;
    }

    node = node->forward[0];

    if (node && node->key == k)
    {
        for (int i = node->forward.size()-1; i >= 0 ; i--)
        {
            update[i]->forward[i] = node->forward[i];
        }
        delete node;
    }

    while (level > 0 && !head->forward[level]) level--;
}

template<typename T>
void Skip_list<T>::display()
{
    Node *node;
    for (int i = level; i >= 0; i--)
    {
        node = head->forward[i];
        std::cout << "Level " << i << ": ";
        while (node)
        {
            std::cout << node->key << "[" << node->value << "] ";
            node = node->forward[i];
        }
        std::cout << std::endl;
    }
}



int main(void)
{
    Skip_list<std::string> sl(3, 0.5);

    sl.insert(1, "one");
    sl.insert(2, "two");
    sl.insert(3, "three");
    sl.insert(4, "four");
    sl.insert(5, "five");
    sl.insert(6, "six");
    sl.insert(7, "seven");
    sl.insert(8, "eight");
    sl.insert(9, "nine");
    sl.insert(10, "ten");
    std::cout << "********Insert 1~10, MAX_LEVEL:3, Probability:0.5********" << std::endl;
    sl.display();

    sl.erase(6);
    sl.erase(8);
    std::cout << "********Delete 6 and 8********" << std::endl;
    sl.display();

    return 0;
}