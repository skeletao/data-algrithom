#pragma once
#include <iostream>
using namespace std;
typedef int ELEMENTTYPE;
typedef struct binaryTree {
	ELEMENTTYPE data;
	struct binaryTree *leftChild;
	struct binaryTree *rightChild;
}btNode, *btNodePtr;

void preOrder(btNodePtr root)
{
	if (root)
	{
		printf("%d", root->data);
		preOrder(root->leftChild);
		preOrder(root->rightChild);
	}
}

void midOrder(btNodePtr root)
{
	if (root)
	{
		midOrder(root->leftChild);
		printf("%d", root->data);
		midOrder(root->rightChild);
	}
}

void lastOrder(btNodePtr root)
{
	if (root)
	{
		lastOrder(root->leftChild);
		lastOrder(root->rightChild);
		printf("%d", root->data);
	}
}

bool searchBST(btNodePtr root, btNodePtr pre, ELEMENTTYPE key, btNodePtr& node)
{
	if (root == NULL)
	{
		node = pre;
		return false;
	}
	if (key == root->data)
	{
		node = root;
		return true;
	}
	else if (key < root->data)
	{
		return searchBST(root->leftChild, root, key, node);
	}
	else
	{
		return searchBST(root->rightChild, root, key, node);
	}
}

bool insertBST(btNodePtr& root, ELEMENTTYPE key)
{
	btNodePtr temp = NULL;
	btNodePtr node = (btNodePtr)malloc(sizeof(btNode));
	node->data = key;
	node->leftChild = NULL;
	node->rightChild = NULL;
	if (root == NULL)
	{
		root = node;
		return true;
	}
	if (searchBST(root, NULL, key, temp))
	{
		return false;
	}
	if (key < temp->data)
	{
		temp->leftChild = node;
	}
	else
	{
		temp->rightChild = node;
	}
	return true;
}


bool deleteBTS(btNodePtr& root, ELEMENTTYPE key)
{
	btNodePtr parent = NULL, target = root, midR = NULL, mrParent = NULL, replace = NULL;
	while (target && target->data != key)
	{
		parent = target;
		if (target->data > key)
		{
			target = target->leftChild;
		}
		else
		{
			target = target->rightChild;
		}
	}

	if (!target)
	{
		return false;
	}

	if (!target->leftChild)
	{
		replace = target->rightChild;
	}
	else if (!target->rightChild)
	{
		replace = target->leftChild;
	}
	else
	{
		midR = target->rightChild;
		while (midR->leftChild)
		{
			mrParent = midR;
			midR = midR->leftChild;
		}

		if (!mrParent)
		{
			target->rightChild = midR->rightChild;
		}
		else
		{
			mrParent->leftChild = midR->rightChild;
		}

		midR->leftChild = target->leftChild;
		midR->rightChild = target->rightChild;
		replace = midR;
	}
	
	if (parent) {
		if (target == parent->leftChild)
		{
			parent->leftChild = replace;
		}
		else
		{
			parent->rightChild = replace;
		}
	}
	else
	{
		root = replace;
	}
	free(target);
	return true;
}
