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

struct SingleLinkedCyclicList
{
    struct SingleLinkedElement *head;
};

void CONSTRUCTOR(SingleLinkedCyclicList)
{
    object->head = NULL;
}

int METHOD_NO_ARGS(SingleLinkedCyclicList, get_length)
{
    int length = 1;
    if (object->head == NULL)
    {
        return 0;
    }
    struct SingleLinkedElement *element = object->head;
    while (element->next != object->head)
    {
        element = element->next;
        length++;
    }
    return length;
}

void METHOD_NO_ARGS(SingleLinkedCyclicList, free)
{
    if (object == NULL)
    {
        return;
    }
    struct SingleLinkedElement *element = object->head;
    if (element == NULL)
    {
        return;
    }
    struct SingleLinkedElement *next = element->next;
    if (next == NULL)
    {
        return;
    }
    int length = _method_SingleLinkedCyclicList_get_length(object);
    for (int i = 0; i < length; i++)
    {
        free(element);
        if (i == length - 1)
        {
            break;
        }
        element = next;
        next = element->next;
    }
}

void METHOD(SingleLinkedCyclicList, append, int value)
{
    struct SingleLinkedElement *element = object->head;
    if (element == NULL)
    {
        element = malloc(sizeof(struct SingleLinkedElement));
        element->data = value;
        element->next = element;
        object->head = element;
        return;
    }
    while (element->next != object->head)
    {
        element = element->next;
    }
    struct SingleLinkedElement *newElement = malloc(sizeof(struct SingleLinkedElement));
    newElement->data = value;
    newElement->next = object->head;
    element->next = newElement;
}

struct SingleLinkedElement *METHOD(SingleLinkedCyclicList, first_by_value, int value)
{
    struct SingleLinkedElement *element = object->head;
    while (element != NULL)
    {
        if (element->data == value)
        {
            return element;
        }
        element = element->next;
    }
}

int main()
{
    struct SingleLinkedCyclicList list;
    _constructor_SingleLinkedCyclicList(&list);
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
        _method_SingleLinkedCyclicList_append(&list, c - '0');
    }
    int k, n;
    scanf("%d\n%d", &k, &n);
    
}