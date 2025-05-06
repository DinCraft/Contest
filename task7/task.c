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

void METHOD_NO_ARGS(TreeElement, createTree)
{
	int n;
	scanf("%d", &n);
	if (n == 1)
	{
		struct TreeElement *element = malloc(sizeof(struct TreeElement));
		_constructor_TreeElement(element);
		object->L = element;
		_method_TreeElement_createTree(object->L);
	}
	scanf("%d", &n);
	if (n == 1)
	{
		struct TreeElement *element = malloc(sizeof(struct TreeElement));
		_constructor_TreeElement(element);
		object->R = element;
		_method_TreeElement_createTree(object->R);
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

int METHOD_NO_ARGS(TreeElement, count_verticies)
{
	int result = 0;
	if (object->R)
	{
		result +=_method_TreeElement_count_verticies(object->R);
	}
	result++;
	if (object->L)
	{
		result += _method_TreeElement_count_verticies(object->L);
	}
	return result;
}

int METHOD_NO_ARGS(TreeElement, count_leaves)
{
	int result = 0;
	if (object->R)
	{
		result +=_method_TreeElement_count_leaves(object->R);
	}
	if (object->L)
	{
		result += _method_TreeElement_count_leaves(object->L);
	}
	if (!object->L & !object->R)
	{
		result++;
	}
	return result;
}

int METHOD(TreeElement, max_depth, int d, int md)
{
	if (object->R)
	{
		md = _method_TreeElement_max_depth(object->R, d + 1, md > d + 1 ? md : d + 1);
	}
	if (object->L)
	{
		md = _method_TreeElement_max_depth(object->L, d + 1, md > d + 1 ? md : d + 1);
	}
	return md;
}

int METHOD(TreeElement, count_left_child_nodes, int counter)
{
	if (object->R)
	{
		counter = _method_TreeElement_count_left_child_nodes(object->R, counter);
	}
	if (object->L)
	{
		counter = _method_TreeElement_count_left_child_nodes(object->L, counter + 1);
	}
	return counter;
}

int main()
{
	struct BinaryTree tree;
	int n;
	_constructor_BinaryTree(&tree);
	scanf("%d", &n);
	_method_TreeElement_createTree(tree.root);
	int verticies = _method_TreeElement_count_verticies(tree.root);
	int leaves = _method_TreeElement_count_leaves(tree.root);
	int max_depth = _method_TreeElement_max_depth(tree.root, 0, 0);
	int left_child_nodes = _method_TreeElement_count_left_child_nodes(tree.root, 0);
	printf("%d\n", verticies);
	printf("%d\n", leaves);
	printf("%d\n", max_depth);
	printf("%d", left_child_nodes);
	return 0;
}