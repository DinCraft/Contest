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
	struct TreeElement *L;
	struct TreeElement *R;
};

struct BinaryTree
{
	struct TreeElement *root;
};

void CONSTRUCTOR(BinaryTree)
{
	object->root = malloc(sizeof(struct TreeElement));
}

void CONSTRUCTOR(TreeElement)
{
	object->L = NULL;
	object->R = NULL;
}

void METHOD(TreeElement, createTree, int side)
{
	int n;
	scanf("%d", &n);
	if (n == 1)
	{
		struct TreeElement *element = malloc(sizeof(struct TreeElement));
		_constructor_TreeElement(element);
		if (side == -1)
		{
			object->L = element;
			_method_TreeElement_createTree(object->L, -1);
		}
		else
		{
			object->R = element;
			_method_TreeElement_createTree(object->R, -1);
		}
	}
	else
	{
		if (side == -1)
		{
			_method_TreeElement_createTree(object, 1);
		}
	}
}

//     1
//   1
//     1
// 1
//     1
//   1
//     1
//2^3-1
void METHOD(TreeElement, print, int depth)
{
	if (object->R)
	{
		_method_TreeElement_print(object->R, depth + 1);
	}
	for (int i = 0; i < depth; i++)
	{
		printf("  ");
	}
	printf("1\n");
	if (object->L)
	{
		_method_TreeElement_print(object->L, depth + 1);
	}
}

int main()
{
	struct BinaryTree tree;
	_constructor_BinaryTree(&tree);
	_method_TreeElement_createTree(tree.root, -1);
	_method_TreeElement_print(tree.root, 0);
	return 0;
}