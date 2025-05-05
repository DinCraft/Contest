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

void CONSTRUCTOR_NO_ARGS(Dequeue)
{
    object->first = NULL;
    object->last = NULL;
}

struct DoubleLinkedElement *_constructor_DoubleLinkedElement(int data, struct DoubleLinkedElement *prev, struct DoubleLinkedElement *next) 
{
    struct DoubleLinkedElement *element = malloc(sizeof(struct DoubleLinkedElement));
    element->data = data;
    element->prev = prev;
    element->next = next;

    if (prev != NULL)
    {
        prev->next = element;
    }
    if (next != NULL)
    {
        next->prev = element;
    }
    return element;
}

// 1 - object is NULL
int METHOD(Dequeue, add_start, int data)
{
    if (object == NULL)
    {
        return 1;
    }
    if (object->first == NULL)
    {
        object->first = _constructor_DoubleLinkedElement(data, NULL, NULL);
        object->last = object->first;
        return 0;
    }
    struct DoubleLinkedElement *element = _constructor_DoubleLinkedElement(data, NULL, object->first);
    object->first = element;
    return 0;
}

// 1 - object is NULL
int METHOD(Dequeue, add_end, int data)
{
    if (object == NULL)
    {
        return 1;
    }
    if (object->first == NULL)
    {
        object->first = _constructor_DoubleLinkedElement(data, NULL, NULL);
        object->last = object->first;
        return 0;
    }
    struct DoubleLinkedElement *element = _constructor_DoubleLinkedElement(data, object->last, NULL);
    object->last = element;
    return 0;
}

// 1 - object is NULL
// 2 - dequeue is empty
// 3 - dequeue has exactly one element (elements count: 1 -> 0)
int METHOD_NO_ARGS(Dequeue, remove_start)
{
    if (object == NULL)
    {
        return 1;
    }
    if (object->first == NULL)
    {
        return 2;
    }
    if (object->first->next == NULL)
    {
        free(object->first);
        object->first = NULL;
        object->last = NULL;
        return 3;
    }
    struct DoubleLinkedElement *newFirst = object->first->next;
    newFirst->prev = NULL;
    free(object->first);
    object->first = newFirst;
    return 0;
}

// 1 - object is NULL
// 2 - dequeue is empty
// 3 - dequeue has exactly one element (elements count: 1 -> 0)
int METHOD_NO_ARGS(Dequeue, remove_end)
{
    if (object == NULL)
    {
        return 1;
    }
    if (object->first == NULL)
    {
        return 2;
    }
    if (object->first->next == NULL)
    {
        free(object->first);
        object->first = NULL;
        object->last = NULL;
        return 3;
    }
    struct DoubleLinkedElement *newLast = object->last->prev;
    newLast->next = NULL;
    free(object->last);
    object->last = newLast;
    return 0;
}

void METHOD_NO_ARGS(Dequeue, print)
{
    struct DoubleLinkedElement *element = object->first;
    if (element == NULL)
    {
        printf("0");
        return;
    }
    while (element != NULL)
    {
        printf("%d ", element->data);
        element = element->next;
    }
}

void METHOD_NO_ARGS(Dequeue, input)
{
    int n;
    while (1)
    {
        int success = scanf("%d", &n);
        if (success == 0) {
            break;
        }
        if (n == 0)
        {
            continue;
        }
        if (n > 0)
        {
            if (n % 2 == 0)
            {
                for (int i = 1; i <= n; i++)
                {
                    _method_Dequeue_add_start(object, i);
                }
            }
            else
            {
                for (int i = 1; i <= n; i++)
                {
                    _method_Dequeue_add_end(object, i);
                }
            }
        }
        else if (n < 0)
        {
            if (n % 2 == 0)
            {
                for (int i = 0; i < -n; i++)
                {
                    if (_method_Dequeue_remove_end(object) >= 2)
                    {
                        break;
                    }
                }
            }
            else
            {
                for (int i = 0; i < -n; i++)
                {
                    if (_method_Dequeue_remove_start(object) >= 2)
                    {
                        break;
                    }
                }
            }
        }
        _method_Dequeue_print(object);
        printf("\n\n");
    }
}

void main()
{
    struct Dequeue dequeue;
    _constructor_Dequeue(&dequeue);
    _method_Dequeue_input(&dequeue);
}