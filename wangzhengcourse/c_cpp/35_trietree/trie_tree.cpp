#ifndef TRIE_TREE_HPP
#define TRIE_TREE_HPP

// Assume vocabulary table size is 26

#define VOCA_SIZE 26

#include <iostream>
#include <string>

struct Node {
    char letter;
    Node *(children[VOCA_SIZE]); 
    Node(char c): letter(c) {
        for (int i = 0; i < VOCA_SIZE; i++)
        {
            children[i] = nullptr;
        }
    }
};


class TireTree
{
private:
    Node *root;
public:
    TireTree();
    ~TireTree();
    void Insert(const char *s);
    bool Find(const char *s);
    void Display();
};

TireTree::TireTree()
{
    root = new Node('\0');
}

TireTree::~TireTree()
{
    delete root;
}

void TireTree::Insert(const char *s)
{
    Node *child = root;
    while (*s != '\0')
    {
        if (child->children[*s-'a'] == nullptr)
        {
            child->children[*s-'a'] = new Node(*s);
        }
        child = child->children[*s-'a'];
        s++;
    }
}


bool TireTree::Find(const char *s)
{
    Node *child = root;
    while (*s != '\0')
    {
        if (child->children[*s-'a'] == nullptr) return false;

        child = child->children[*s-'a'];
        s++;
    }
    return true;
}

void TireTree::Display()
{
    //to be finished...
}

int main(void)
{
    TireTree t;
    t.Insert("how");
    t.Insert("he");
    t.Insert("hi");
    t.Insert("hello");
    t.Insert("so");
    t.Insert("see");

    char word1[] = "hollw";
    char word2[] = "se";


    std::cout << t.Find(word1) <<" and "<< t.Find(word2) << std::endl;
    
    return 0;
}


#endif