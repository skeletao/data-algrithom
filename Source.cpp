#include <iostream>
#include "stl.cpp"

using namespace std;

int main(int argc, char* argv[])
{
	int array[] = { 8, 9, 3 };
	char string[] = "string";

	stack* stack = stack_init(array);
	stack_push(array + 1, stack);
	int a1 = *(int *)stack_pop(stack);
	int a2 = *(int *)stack_peek(stack);
	a2 = *(int *)stack_pop(stack);
	stack_destory(stack);

	stack = stack_init(string);
	stack_push(string + 1, stack);
	char s1 = *(char *)stack_pop(stack);
	char s2 = *(char *)stack_peek(stack);
	s2 = *(char *)stack_pop(stack);
	stack_destory(stack);

	return 0;
}

/*
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
*/