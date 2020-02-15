#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <vector>
#include <random>

template <typename T>
class Skip_list
{
private:
    struct Node{
        int key;
        T value;
        std::vector<Node*> forward;
        Node(int k, int level);
    };
    Node *head;
    int MAX_LEVEL;
    int maxlevel;
    float probability;
    int random_levle();
    Node* make_node(int key, T &value, int level);
public:
    Skip_list();
    Skip_list(int level, float p);
    ~Skip_list();
    void insert(int key, T &value);
    void erase(int key);
    T find(int key);
    void display();
};

#endif