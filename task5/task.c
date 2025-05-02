/*
* Copyright (c) 2025, Diniyar Ismailov <idiniyar2006@mail.ru>.
*/

#include <stdio.h>
#include <stdlib.h>

#define METHOD_NO_ARGS(type, name) _method_##type##_##name(struct type *object)
#define METHOD(type, name, ...) _method_##type##_##name(struct type *object, __VA_ARGS__)
#define CONSTRUCTOR_NO_ARGS(type) _constructor_##type(struct type *object)
#define CONSTRUCTOR(type, ...) _constructor_##type(struct type *object, __VA_ARGS__)

struct Dequeue
{
    struct DoubleLinkedElement *first;
    struct DoubleLinkedElement *last;
};

struct DoubleLinkedElement
{
    int data;
    struct DoubleLinkedElement *next;
    struct DoubleLinkedElement *prev;
};

void METHOD_NO_ARGS(Dequeue, input)
{
    char c;
    while (1)
    {
        scanf("%c", &c);
        if (c == ' ') {
            continue;
        }
        if (c == '.') {
            break;
        }
    }
}

void CONSTRUCTOR_NO_ARGS(Dequeue)
{
    object->first = NULL;
    object->last = NULL;
}

struct DoubleLinkedElement *_constructor_DoubleLinkedElement(int data, struct DoubleLinkedElement *next, struct DoubleLinkedElement *prev)
{
    struct DoubleLinkedElement *element = malloc(sizeof(struct DoubleLinkedElement));
    element->data = data;
    element->next = next;
    element->prev = prev;
    return element;
}

// -1 object is NULL
int METHOD(Dequeue, add_start, int data)
{
    if (object == NULL)
    {
        return -1;
    }
    if (object->first == NULL)
    {
        object->first = _constructor_DoubleLinkedElement(data, NULL, NULL);
        object->last = object->first;
        return 0;
    }
    struct DoubleLinkedElement *element = _constructor_DoubleLinkedElement(data, object->first, NULL);
    object->first = element;
    return 0;
}

void METHOD_NO_ARGS(Dequeue, print)
{
    struct DoubleLinkedElement *element = object->first;
    while (element != NULL)
    {
        printf("%d ", element->data);
        element = element->next;
    }
}

void main()
{
    struct Dequeue dequeue;
    _constructor_Dequeue(&dequeue);
    _method_Dequeue_add_start(&dequeue, 1);
    _method_Dequeue_add_start(&dequeue, 2);
    _method_Dequeue_print(&dequeue);
}