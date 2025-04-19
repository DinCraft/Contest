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
    for (int i = 0; i < _method_SingleLinkedCyclicList_get_length(object) - 1; i++)
    {
        if (element->data == value)
        {
            return element;
        }
        element = element->next;
    }
    return NULL;
}

struct SingleLinkedElement *METHOD(SingleLinkedCyclicList, get_prev, struct SingleLinkedElement *element)
{
    struct SingleLinkedElement *e = element;
    if (object->head == element)
    {
        for (int i = 0; i < _method_SingleLinkedCyclicList_get_length(object) - 1; i++)
        {
            e = e->next;
        }
        return e;
    }
    while (e->next != element)
    {
        e = e->next;
    }
    return e;
}

void METHOD(SingleLinkedCyclicList, remove, struct SingleLinkedElement *element)
{
    if (_method_SingleLinkedCyclicList_get_length(object) == 1)
    {
        object->head = NULL;
        return;
    }
    struct SingleLinkedElement *prev = _method_SingleLinkedCyclicList_get_prev(object, element);
    // first
    if (object->head == element)
    {
        object->head = element->next;
        prev->next = object->head;
        free(element);
    }
    // otherwise
    else
    {
        prev->next = element->next;
        free(element);
    }
    return;
}

void METHOD_NO_ARGS(SingleLinkedCyclicList, print)
{
    struct SingleLinkedElement *element = object->head;
    if (element == NULL)
    {
        return;
    }
    for (int i = 0; i < _method_SingleLinkedCyclicList_get_length(object) - 1; i++)
    {
        printf("%d ", element->data);
        element = element->next;
    }
    printf("%d", element->data);
}

// <element> must be an element from <object>
void METHOD(SingleLinkedCyclicList, remove_from, struct SingleLinkedElement *element, int amount)
{
    if (_method_SingleLinkedCyclicList_get_length(object) <= amount)
    {
        _method_SingleLinkedCyclicList_free(object);
        return;
    }
    struct SingleLinkedElement *elem = element->next;
    struct SingleLinkedElement *next_elem = NULL;
    for (int i = 0; i < amount; i++)
    {
        if (elem == NULL)
        {
            return;
        }
        next_elem = elem->next;
        _method_SingleLinkedCyclicList_remove(object, elem);
        elem = next_elem;
    }
}

#ifndef TESTS
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
    if (list.head == NULL)
    {
        printf("the list is empty");
        return 0;
    }
    _method_SingleLinkedCyclicList_print(&list);
    struct SingleLinkedElement *element = _method_SingleLinkedCyclicList_first_by_value(&list, k);
    if (element == NULL)
    {
        printf("\n");
        _method_SingleLinkedCyclicList_print(&list);
        return 0;
    }
    
    _method_SingleLinkedCyclicList_remove_from(&list, element, n);
    printf("\n");
    if (_method_SingleLinkedCyclicList_get_length(&list) == 0)
    {
        printf("the list is empty");
        return 0;
    }
    _method_SingleLinkedCyclicList_print(&list);
}
#endif