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
 
struct Queue
{
    struct SingleLinkedElement *start;
    struct SingleLinkedElement *end;
};

void CONSTRUCTOR(Queue)
{
    object->start = NULL;
    object->end = NULL;
}

void METHOD(Queue, append, int value)
{
	struct SingleLinkedElement *element;
	element = malloc(sizeof(struct SingleLinkedElement));
	element->data = value;
	element->next = NULL;
	if (object->start == NULL)
	{
		object->start = element;
		object->end = element;
		return;
	}
	object->end->next = element;
	object->end = element;
}

void METHOD_NO_ARGS(Queue, print)
{
	struct SingleLinkedElement *element = object->start;
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

void METHOD_NO_ARGS(Queue, remove)
{
	if (object->start == NULL)
	{
		return;
	}
	struct SingleLinkedElement *start = object->start;
	object->start = start->next;
	free(start);
}

int handle(struct Queue *queue, int n, int value)
{
	int result = value;
	if (n == 0)
	{
		return result;
	}
	if (n < 0)
	{
		for (int i = 0; i < -n; i++)
		{
			if (queue->start == NULL)
			{
				return result;
			}
			_method_Queue_remove(queue);
		}
	}
	else
	{
		result += n;
		for (int i = 0; i < n; i++)
		{
			_method_Queue_append(queue, value + i);
		}
	}
	return result;
}

int main()
{
    struct Queue queue;
    _constructor_Queue(&queue);
	int n;
	int value = 1;
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
        value = handle(&queue, n, value);
		if (n != 0)
		{
			zeros_only = 0;
		}
		first = 0;
		if (n != 0)
		{
			_method_Queue_print(&queue);
			if (queue.start != NULL)
			{
				printf("\n");
			}
		}
		if (queue.start == NULL && n  != 0)
		{
			printf("0\n");	
		}
    }
	
}