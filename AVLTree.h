#pragma once
#include <iostream>
using namespace std;
typedef int	ELEMENT_TYPE;
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define HEIGHT(a) ((!a) ? 0 : ((avlNodePtr)(a))->height)

typedef struct avlTreeNode {
	ELEMENT_TYPE data;
	struct avlTreeNode* leftChild;
	struct avlTreeNode* rightChild;
	int height;
}avlNode, *avlNodePtr;

void preOrder(avlNodePtr root)
{
	if (root)
	{
		printf("%d", root->data);
		preOrder(root->leftChild);
		preOrder(root->rightChild);
	}
}

void midOrder(avlNodePtr root)
{
	if (root)
	{
		midOrder(root->leftChild);
		printf("%d", root->data);
		midOrder(root->rightChild);
	}
}

void lastOrder(avlNodePtr root)
{
	if (root)
	{
		lastOrder(root->leftChild);
		lastOrder(root->rightChild);
		printf("%d", root->data);
	}
}




avlNodePtr searchAVL( avlNodePtr root, ELEMENT_TYPE key)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->data == key)
	{
		return root;
	}
	else if (root->data > key)
	{
		return searchAVL(root->leftChild, key);
	}
	else
	{
		return searchAVL(root->rightChild, key);
	}
}

avlNodePtr llRotate(avlNodePtr root)
{
	avlNodePtr newRoot = root->leftChild;
	root->leftChild = newRoot->rightChild;
	newRoot->rightChild = root;
	root->height = MAX(HEIGHT(root->leftChild), HEIGHT(root->rightChild)) + 1;
	newRoot->height = MAX(HEIGHT(newRoot->leftChild), root->height) + 1;
	return newRoot;
}


avlNodePtr rrRotate(avlNodePtr root)
{
	avlNodePtr newRoot = root->rightChild;
	root->rightChild = newRoot->leftChild;
	newRoot->leftChild = root;
	root->height = MAX(HEIGHT(root->leftChild), HEIGHT(root->rightChild)) + 1;
	newRoot->height = MAX(HEIGHT(newRoot->rightChild), root->height) + 1;
	return newRoot;
}

avlNodePtr lrRotate(avlNodePtr root)
{
	root->leftChild = rrRotate(root->leftChild);
	return llRotate(root);
}

avlNodePtr rlRotate(avlNodePtr root)
{
	root->rightChild = llRotate(root->rightChild);
	return rrRotate(root);
}

void printAVL(avlNodePtr root, ELEMENT_TYPE data, int direction)
{
	if (root)
	{
		if (direction == 1)
		{
			printf("%d is %d left child, and height is %d\n", root->data, data, root->height);
		}
		else if(direction == -1)
		{
			printf("%d is %d right child, and height is %d\n", root->data, data, root->height);
		}
		else
		{
			printf("%d is root and height is %d\n", root->data, root->height);
		}
		printAVL(root->leftChild, root->data, 1);
		printAVL(root->rightChild, root->data, -1);
	}
	
}

avlNodePtr insertAVL(avlNodePtr root, ELEMENT_TYPE key)
{
	if (!root)
	{
	    root = (avlNodePtr)malloc(sizeof(avlNode));
		root->data = key;
		root->leftChild = NULL;
		root->rightChild = NULL;
		root->height = 1;
	}
	else if (root->data > key)
	{
		root->leftChild = insertAVL(root->leftChild, key);
		if (HEIGHT(root->leftChild) - HEIGHT(root->rightChild) == 2)
		{
			if (key < root->leftChild->data)
			{
				root = llRotate(root);
			}
			else
			{
				root = lrRotate(root);
			}
		}
	}
	else if(root->data < key)
	{
		root->rightChild = insertAVL(root->rightChild, key);
		if (HEIGHT(root->rightChild) - HEIGHT(root->leftChild) == 2)
		{
			if (key > root->rightChild->data)
			{
				root = rrRotate(root);
			}
			else
			{
				root = rlRotate(root);
			}
		}
	}
	else
	{
		printf("vlaue already existed!!!");
	}
	root->height = MAX(HEIGHT(root->leftChild), HEIGHT(root->rightChild)) + 1;
	return root;
}

avlNodePtr deleteAVL(avlNodePtr root, ELEMENT_TYPE key)
{
	avlNodePtr target = NULL, newRoot = NULL, next = NULL;
	ELEMENT_TYPE replace;
	if (!root)
	{
		return NULL;
	}

	if (root->data > key)
	{
		root->leftChild = deleteAVL(root->leftChild, key);
		if (HEIGHT(root->rightChild) - HEIGHT(root->leftChild) == 2)
		{
			next = root->rightChild;
			if (HEIGHT(next->rightChild) < HEIGHT(next->leftChild))
			{
				root = rlRotate(root);
			}
			else
			{
				root = rrRotate(root);
			}
		}
		else
		{
			root->height = MAX(HEIGHT(root->leftChild), HEIGHT(root->rightChild)) + 1;
		}
	}
	else if(root->data < key)
	{
		root->rightChild = deleteAVL(root->rightChild, key);
		if (HEIGHT(root->leftChild) - HEIGHT(root->rightChild) == 2)
		{
			next = root->leftChild;
			if (HEIGHT(next->leftChild) < HEIGHT(next->rightChild))
			{
				root = lrRotate(root);
			}
			else
			{
				root = llRotate(root);
			}
		}
		else
		{
			root->height = MAX(HEIGHT(root->leftChild), HEIGHT(root->rightChild)) + 1;
		}
	}
	else
	{
		if (root->leftChild && root->rightChild)
		{
			if (root->leftChild->height > root->rightChild->height)
			{
				next = root->leftChild;
				while (next->rightChild)
				{
					next = next->rightChild;
				}
				replace = root->data;
				root->data = next->data;
				next->data = replace;
				root->leftChild = deleteAVL(root->leftChild, replace);
			}
			else
			{
				next = root->rightChild;
				while (next->leftChild)
				{
					next = next->leftChild;
				}
				replace = root->data;
				root->data = next->data;
				next->data = replace;
				root->rightChild = deleteAVL(root->rightChild, replace);
			}
		}
		else
		{
			next = root;
			root = (!root->leftChild) ? root->rightChild : root->leftChild;
			free(next);
		}
	}
	return root;
}