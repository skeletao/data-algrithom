#pragma once
#include <iostream>
using namespace std;
typedef int ELEMENT_TYPE;

enum  color
{
	RED,
	BLACK
};

typedef struct redBlackTree {
	ELEMENT_TYPE data;
	unsigned char color;
	struct redBlackTree *leftChild, *rightChild, *parent;
}rbNode, *rbTree;

typedef struct redBlackRoot {
	rbNode *node;
}rbRoot;

static rbNode NIL = { 0, BLACK, 0, 0, 0 };
rbNode *NILP = &NIL;
static void preOrder(rbNode* root)
{
	if (root)
	{
		printf("%d", root->data);
		preOrder(root->leftChild);
		preOrder(root->rightChild);
	}
}

static void midOrder(rbNode* root)
{
	if (root)
	{
		midOrder(root->leftChild);
		printf("%d", root->data);
		midOrder(root->rightChild);
	}
}

static void lastOrder(rbNode* root)
{
	if (root)
	{
		lastOrder(root->leftChild);
		lastOrder(root->rightChild);
		printf("%d", root->data);
	}
}

static rbNode *rbFindNext(rbNode *node, int dir)
{
	rbNode *temp = NULL;
	if (dir)
	{
        temp = node->leftChild;
		if (temp)
		{
			while (temp->rightChild)
			{
				temp = temp->rightChild;
			}
		}
	}
	else
	{
		temp = node->rightChild;
		if (temp)
		{
			while (temp->leftChild)
			{
				temp = temp->leftChild;
			}
		}
	}
	return temp;
}

static void rbLeftRotate(rbRoot *root, rbNode *node) 
{
	rbTree temp = node->rightChild;
	node->rightChild = temp->leftChild;
	if (temp->leftChild)
	{
		temp->leftChild->parent = node;
	}
	temp->parent = node->parent;
	if (!temp->parent)
	{
		root->node = temp;
	}
	else
	{
		if (node == node->parent->leftChild)
		{
			temp->parent->leftChild = temp;
		}
		else
		{
			temp->parent->rightChild = temp;
		}
	}
	temp->leftChild = node;
	node->parent = temp;	
}

static void rbRightRotate(rbRoot *root, rbNode *node)
{
	rbTree temp = node->leftChild;
	node->leftChild = temp->rightChild;
	if (temp->rightChild)
	{
		temp->rightChild->parent = node;
	}
	temp->parent = node->parent;
	if (!temp->parent)
	{
		root->node = temp;
	}
	else
	{
		if (node->parent->leftChild == node)
		{
			temp->parent->leftChild = temp;
		}
		else
		{
			temp->parent->rightChild = temp;
		}
	}
	temp->rightChild = node;
	node->parent = temp;
}

			
static void rbInsertFixup(rbRoot *root, rbNode *node);
static void rbInsert(rbRoot* root, ELEMENT_TYPE data);
static void rbInsertNode(rbRoot* root, rbNode *node)
{
	rbNode *temp = root->node, *target = NULL;
	if (!temp)
	{
		node->color = BLACK;
		root->node = node;
		return;
	}
	while (temp)
	{
		target = temp;
		if (node->data < temp->data)
		{
			temp = temp->leftChild;
		}
		else if (node->data > temp->data)
		{
			temp = temp->rightChild;
		}
		else
		{
			break;
		}
	}
	if (temp)
	{
		printf("%d element alreadt existed!", node->data);
		return;
	}
	if (node->data < target->data)
	{
		target->leftChild = node;
	}
	else
	{
		target->rightChild = node;
	}
	node->parent = target;
	node->color = RED;
	rbInsertFixup(root, node);
}

static void rbInsertFixup(rbRoot *root, rbNode *node)
{
	rbTree father = NULL, grandPa = NULL , uncle = NULL;
	while (node != root->node && node->parent->color == RED)
	{
		father = node->parent;
		grandPa = father->parent;
		if (father == grandPa->leftChild)
		{
			uncle = grandPa->rightChild;
			if (uncle && uncle->color == RED)
			{
				father->color = BLACK;
				uncle->color = BLACK;
				grandPa->color = RED;
				node = grandPa;
			}
			else
			{
				if (node == father->rightChild)
				{
					node->color = BLACK;
					rbLeftRotate(root, father);
				}
				else
				{
					father->color = BLACK;
				}
				rbRightRotate(root, grandPa);
				grandPa->color = RED;
			}
		}
		else
		{
			uncle = grandPa->leftChild;
			if (uncle && uncle->color == RED)
			{
				father->color = BLACK;
				uncle->color = BLACK;
				grandPa->color = RED;
				node = grandPa;
			}
			else
			{
				if (node == father->leftChild)
				{
					node->color = BLACK;
					rbRightRotate(root, father);
				}
				else
				{
					father->color = BLACK;
				}
				rbLeftRotate(root, grandPa);
				grandPa->color = RED;
			}
		}
	}
	root->node->color = BLACK;
}

static void rbInsert(rbRoot* root, ELEMENT_TYPE data)
{
		rbNode *node = (rbTree)(malloc(sizeof(rbNode)));
		node->color = RED;
		node->data = data;
		node->leftChild = NULL;
		node->rightChild = NULL;
		node->parent = NULL;
		rbInsertNode(root, node);
}



static void rbDeleteFixup(rbRoot* root, rbNode* node, rbNode* father);
static void rbDelete(rbRoot* root, ELEMENT_TYPE data);
static rbNode* rbSearch(rbRoot* root, ELEMENT_TYPE data)
{
	rbNode* target = root->node;
	
	while (target)
	{
		if (data == target->data)
		{
			break;
		}
		else if(data < target->data)
		{
			target = target->leftChild;
		}
		else
		{
			target = target->rightChild;
		}
	}
	return target;
}

static void rbDeleteNode(rbRoot* root, rbNode *node)
{
	rbNode *target = NULL, *temp = NULL;
	if (!root->node || !node)
	{
		return;
	}
	if (node == root->node)
	{
		free(node);
		root->node = NULL;
		return;
	}
	rbNode *father = node->parent;
	if (!node->leftChild || !node->rightChild)
	{
		target = node;
	}
	else
	{
		target = rbFindNext(node, 0);
		node->data = target->data;
	}
	temp = (target->leftChild) ? target->leftChild : target->rightChild;
	if (node == father->leftChild)
	{
		father->leftChild = temp;
	}
	else
	{
		father->rightChild = temp;
	}
	if (temp)
	{
		temp->parent = father;
	}
	if (target->color == BLACK)
	{
		rbDeleteFixup(root, temp, father);
	}
	free(target);
}

static void rbDeleteFixup(rbRoot* root, rbNode* node, rbNode *father)
{
	rbTree grandPa = NULL , brother = NULL;
	while (node != root->node && (!node || node->color == BLACK ))
	{
		if (node == father->leftChild)
		{
			brother = father->rightChild;
			if (brother->color == RED)
			{
				father->color = BLACK;
				brother->color = RED;
				rbLeftRotate(root, father);
			}
			else
			{
				if ((!brother->leftChild || brother->leftChild->color == BLACK) && (!brother->rightChild || brother->rightChild->color == BLACK))
				{
					brother->color = RED;
					node = father;
				}
				else
				{
					if ((brother->leftChild && brother->leftChild->color == RED) && (!brother->rightChild || brother->rightChild->color == BLACK))
					{
						brother->color = RED;
						brother->leftChild->color = BLACK;
						rbRightRotate(root, brother);
						brother = brother->leftChild;
					}
					brother->color = father->color;
					father->color = BLACK;
					brother->rightChild->color = BLACK;
					rbLeftRotate(root, father);
					node = brother;
				}
			}
		}
		else
		{
			brother = father->leftChild;
			if (brother->color == RED)
			{
				father->color = BLACK;
				brother->color = RED;
				rbRightRotate(root, father);
			}
			else
			{
				if ((!brother->leftChild || brother->leftChild->color == BLACK) && (!brother->rightChild || brother->rightChild->color == BLACK))
				{
					brother->color = RED;
					node = father;
				}
				else
				{
				
					if ((brother->leftChild && brother->leftChild->color == RED) && (!brother->rightChild || brother->rightChild->color == BLACK))
					{
						brother->color = RED;
						brother->leftChild->color = BLACK;
						rbLeftRotate(root, brother);
					}
					brother->color = father->color;
					father->color = BLACK;
					brother->rightChild->color = BLACK;
					rbRightRotate(root, father);
					node = brother;
				}
			}
		}
	}
	root->node->color = BLACK;
}

static void rbDelete(rbRoot* root, ELEMENT_TYPE data)
{
	 rbNode *node = rbSearch(root, data);
	 rbDeleteNode(root, node);
}