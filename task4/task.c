/*
* Copyright (c) 2025, Diniyar Ismailov <idiniyar2006@mail.ru>.
*/

#include <stdio.h>
#include <stdlib.h>

#define METHOD_NO_ARGS(type, name) _method_##type##_##name(struct type *object)
#define METHOD(type, name, ...) _method_##type##_##name(struct type *object, __VA_ARGS__)
#define CONSTRUCTOR(type) _constructor_##type(struct type *object)

struct SingleLinkedElement
{
    int data;
    struct SingleLinkedElement *next;
};

struct Stack
{
    struct SingleLinkedElement *top;
};

void CONSTRUCTOR(Stack)
{
    object->top = NULL;
}

int METHOD_NO_ARGS(Stack, get_length)
{
    if (object->top == NULL)
    {
        return 0;
    }
    int length = 1;
    struct SingleLinkedElement *element = object->top;
    while (element->next != NULL)
    {
        element = element->next;
        length++;
    }
    return length;
}

void METHOD(Stack, push, int value)
{
    struct SingleLinkedElement *element = malloc(sizeof(struct SingleLinkedElement));
    element->data = value;
    element->next = NULL;
    if (object->top != NULL)
    {
        element->next = object->top;
    }
    object->top = element;
}

int METHOD_NO_ARGS(Stack, pop)
{
    struct SingleLinkedElement *element = object->top;
    if (element == NULL)
    {
        return 1;
    }
    object->top = element->next;
    free(element);
    return 0;
}

void METHOD_NO_ARGS(Stack, print)
{
	struct SingleLinkedElement *element = object->top;
	if (element == NULL)
	{
		return;
	}
	while (element->next != NULL)
	{
		printf("%d ", element->data);
		element = element->next;
	}
	printf("%d", element->data);
}

void METHOD_NO_ARGS(Stack, free)
{
	while (!_method_Stack_pop(object));
}

void handle(struct Stack *stack, int n)
{
	int length = _method_Stack_get_length(stack);
	if (n == 0)
	{
		return;
	}
	if (n < 0)
	{
		for (int i = 0; i < -n; i++)
		{
			if (stack->top == NULL)
			{
				return;
			}
			_method_Stack_pop(stack);
		}
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			_method_Stack_push(stack, length + i);
		}
	}
}

void main()
{
    struct Stack stack;
    _constructor_Stack(&stack);
	int n;
	int first = 1;
	int zeros_only = 1;
    while (1)
    {
        int result = scanf("%d", &n);
        if (result == 0) {
			if (first | zeros_only)
			{
				printf("0\n");
			}
            break;
        }
        handle(&stack, n);
        first = 0;
		if (n != 0)
		{
			zeros_only = 0;
			_method_Stack_print(&stack);
			if (stack.top != NULL)
			{
				printf("\n");
			}
		}
		if (stack.top == NULL && n  != 0)
		{
			printf("0\n");	
		}
    }
	_method_Stack_free(&stack);
}