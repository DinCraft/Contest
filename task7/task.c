/*
 * Copyright (c) 2025, Diniyar Ismailov <idiniyar2006@mail.ru>.
 */

#include <stdio.h>
#include <stdlib.h>

#define METHOD_NO_ARGS(type, name) _method_##type##_##name(struct type *object)
#define METHOD(type, name, ...) _method_##type##_##name(struct type *object, __VA_ARGS__)
#define CONSTRUCTOR(type) _constructor_##type(struct type *object)

struct TreeElement
{
	int data;
	struct TreeElement *L;
	struct TreeElement *R;
};

struct BinaryTree
{
	struct TreeElement *root;
};

void CONSTRUCTOR(BinaryTree)
{
	object->root = NULL;
}

void METHOD_NO_ARGS(TreeElement, createTree)
{
	
}

void METHOD_NO_ARGS(BinaryTree, print)
{
    printf("%d\n", object->root->data);
}

int main()
{
	struct BinaryTree tree;
	_constructor_BinaryTree(&tree);
	_method_TreeElement_createTree(tree.root);
    _method_BinaryTree_print(&tree);
	return 0;
}