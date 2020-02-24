#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <random>
#include <stack>
#include <iostream>
#include <queue>

struct node
{
    int data;
    node *left;
    node *right;
    node(int a):data(a),left(nullptr),right(nullptr){}
};



void create_tree(node **root, int n = 5)
{
    int i = 0;

    std::queue<node *> q;

    if (*root == nullptr && i < n) 
    {
        *root = new node(std::rand()%100);
        q.push(*root);
        std::cout << (*root)->data << " ";
        i++;
    }

    while (i < n)
    {
        node *tmp = q.front();
        q.pop();
        tmp->left = new node(std::rand()%100);
        tmp->right = new node(std::rand()%100);
        q.push(tmp->left);
        q.push(tmp->right);
        std::cout << tmp->left->data << " " << tmp->right->data << " ";
        i += 2;
    }
}


void pre_order(node *root)
{
    if (root == nullptr) return;
    printf("%d ", root->data);
    pre_order(root->left);
    pre_order(root->right);
}


void in_order(node *root)
{
    if (root == nullptr) return;
    in_order(root->left);
    printf("%d ", root->data);
    in_order(root->right);
}


void post_order(node *root)
{
    if (root == nullptr) return;
    post_order(root->left);
    post_order(root->right);
    printf("%d ", root->data);
}


void pre_order_stack(node *root)
{
    std::stack<node *> s;

    if (root == nullptr) return;
    s.push(root);
    node *tmp = nullptr;

    while (!s.empty())
    {
        tmp = s.top();
        s.pop();
        std::cout << tmp->data << " ";
        if (tmp->right) s.push(tmp->right);
        if (tmp->left) s.push(tmp->left);
    }   
}


void pre_order2_stack(node *root)
{
    std::stack<node *> s;

    node *tmp = root;

    while (tmp || !s.empty())
    {
        
        if (tmp)
        {
            std::cout << tmp->data << " ";
            s.push(tmp);
            tmp = tmp->left;
        }
        else
        {
            tmp = s.top();
            s.pop();
            tmp = tmp->right;
        }   
    }   
}

void in_order_stack(node *root)
{
    std::stack<node *> s;
  
    node *tmp = root;;

    while (tmp || !s.empty())
    {
        if (tmp)
        {
            s.push(tmp);
            tmp = tmp->left;
        } else
        {
            tmp = s.top();
            s.pop();
            std::cout << tmp->data << " ";
            tmp = tmp->right;
        }
    }       
}

void post_order_stack(node *root)
{
    std::stack<node *> s;

    node *tmp = root;

    while (tmp || !s.empty())
    {
        if (tmp) 
        {
            s.push(tmp);
            s.push(tmp);
            tmp = tmp->left;
        }else
        {
            tmp = s.top();
            s.pop();
            if (!s.empty() && tmp == s.top())
            {   
                tmp = tmp->right; 
            } else
            {
                std::cout << tmp->data << " ";
                tmp = NULL;
            }
        }
    }   
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
}


int get_tree_high(node *root)
{
    if (root == nullptr) return -1;
    int l = get_tree_high(root->left) + 1;
    int r = get_tree_high(root->right) + 1;
    return (l > r)?l : r;
}


int get_leaf_cnt(node *root)
{
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    return get_leaf_cnt(root->left)+get_leaf_cnt(root->right);
}

#endif


int main(void)
{
    node *tree = nullptr;

  
    std::cout << "create tree: ";  
    create_tree(&tree, 10);
    std::cout << std::endl;

    std::cout << "pre order by recursive: ";
    pre_order(tree);
    std::cout << std::endl;

    std::cout << "in order by recursive: ";
    in_order(tree);
    std::cout << std::endl;

    std::cout << "post order by recursive: ";
    post_order(tree);
    std::cout << std::endl;


    std::cout << "pre order by stack: ";
    pre_order_stack(tree);
    std::cout << std::endl;

    std::cout << "in order by stack: ";
    in_order_stack(tree);
    std::cout << std::endl;

    std::cout << "post order by stack: ";
    post_order_stack(tree);
    std::cout << std::endl;

    std::cout << "level order by queue:";
    level_order(tree);
    std::cout << std::endl;

    int cnt = get_leaf_cnt(tree);
    std::cout << "leaf count: " << cnt << std::endl;  

    int high = get_tree_high(tree);
    std::cout << "tree high: " << high << std::endl;  

    return 0;
}