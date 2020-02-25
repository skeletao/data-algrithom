#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <queue>

/*
 * Simple binary search tree
 * 1. Do not support case which has same value
 * 2. Do not consinder banlance
 */

struct node {
    int data;
    node *left;
    node *right;
    node(int a): data(a), left(nullptr), right(nullptr) {}
};


node* serach(node *root, int val)
{
    while (root != nullptr)
    {
        if (val == root->data) 
        {
            break;
        } 
        else if (val < root->data)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }   
    }

    return root;
}

void insert(node **root, int val)
{
    if (*root == nullptr) *root = new node(val);

    node *tmp = *root;

    while (1)
    {
        if (val < tmp->data)
        {
            if (tmp->left) 
            {
                tmp = tmp->left;
            } 
            else
            {
                tmp->left = new node(val);
                return;
            }
            
        } 
        else if (val > tmp->data)
        {
            if (tmp->right) 
            {
                tmp = tmp->right;
            } 
            else
            {
                tmp->right = new node(val);
                return;
            }
        }
        else
        {
            return;
        }
    }

}


void delete2(node **root, int val)
{
    node *p = *root;
    node *pp = nullptr;
    node *child = nullptr;

    while (p != nullptr)
    {
        if (val == p->data) 
        {
            break;
        } 
        else if (val < p->data)
        {
            pp = p;
            p = p->left;
        }
        else
        {
            pp = p;
            p = p->right;
        }   
    }

    if (p == nullptr) return;

    if (p->left != nullptr && p->right != nullptr)
    {
        node *min = p->right;
        pp = p;
        while (min->left != nullptr)
        {
            pp = min;
            min = min->left;
        }
        p->data = min->data;
        p = min;
    }

    if (p->left != nullptr)
    {
        child = p->left;
    } 
    else if (p->right != nullptr)
    {
        child = p->right;
    } 
    else
    {
        child = nullptr;
    }

    if (pp == nullptr)
    {
        *root = child;
    } else
    {
        if (pp->left == p)
        {
            pp->left = child;
        } else
        {
            pp->right = child;
        }
    }
    delete p;
}


void level_order(node *root)
{
    if (root == nullptr) return;

    std::queue<node *> q;
    q.push(root);
    node *tmp = nullptr;

    while (!q.empty())
    {
        tmp = q.front();
        q.pop();
        std::cout << tmp->data << " ";
        if (tmp->left) q.push(tmp->left);
        if (tmp->right) q.push(tmp->right);
    }
    std::cout << std::endl;
}


#endif



int main(void)
{
    node *root = nullptr;

    int a[] = {33, 16, 50, 13, 18, 34, 58, 15, 17, 25, 51, 66, 19, 27, 55};
    int n = sizeof(a)/sizeof(a[0]);
    for (int i = 0; i < n; i++)
    {
        insert(&root, a[i]);
    }
    level_order(root);

    delete2(&root, 13);
    level_order(root);

    delete2(&root, 18);
    level_order(root);

    delete2(&root, 55);
    level_order(root);  

    delete2(&root, 33);
    level_order(root);  

    return 0;
}