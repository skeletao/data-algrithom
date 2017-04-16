#include <iostream>
#include "rbTree.h"

using namespace std;

int main(int agrc, char* argv[])
{
	int array[] = {8, 11, 17, 15, 6, 1, 22, 25, 27};
	int len = sizeof(array) / sizeof(int);
	int i = 0;
	rbRoot* rootTree = (rbRoot *)malloc(sizeof(rbRoot));
	rootTree->node = NULL;
	rbTree node = NULL, root = NULL;
	while (i < len)
	{
		rbInsert(rootTree, array[i]);
		i++;
	}
	
	root = rootTree->node;
	preOrder(root);
	cout << "----pre" << endl;
	midOrder(root);
	cout << "----mid" << endl;
	lastOrder(root);
	cout << "----last" << endl;
	
	rbDelete(rootTree, 15);
	root = rootTree->node;
	preOrder(root);
	cout << "----pre" << endl;
	midOrder(root);
	cout << "----mid" << endl;
	lastOrder(root);
	cout << "----last" << endl;

	//root = deleteAVL(root, 13);
	//root = deleteAVL(root, 5);
	//root = deleteAVL(root, 16);
	//midOrder(root);
	//cout << "----mid" << endl;
	//printAVL(root, 0, 0);
	
	return 0;
}