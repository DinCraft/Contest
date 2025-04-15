/*
 * Copyright (c) 2025, Diniyar Ismailov <idiniyar2006@mail.ru>.
 */

 #include <stdio.h>
 #include <stdlib.h>
 
 #define METHOD_NO_ARGS(type, name) _method_##type##_##name(struct type *object)
 #define METHOD(type, name, ...) _method_##type##_##name(struct type *object, __VA_ARGS__)
 #define CONSTRUCTOR(type) _constructor_##type(struct type *object)
 
 struct DoubleLinkedElement
 {
     int data;
     struct DoubleLinkedElement *next;
     struct DoubleLinkedElement *prev;
 };
 
 struct DoubleLinkedCyclicList
 {
     struct DoubleLinkedElement *head;
 };
 
 void CONSTRUCTOR(DoubleLinkedCyclicList)
 {
     object->head = NULL;
 }
 
 int METHOD_NO_ARGS(DoubleLinkedCyclicList, get_length)
 {
     int length = 1;
     if (object->head == NULL)
     {
         return 0;
     }
     struct DoubleLinkedElement *element = object->head;
     while (element->next != object->head)
     {
         element = element->next;
         length++;
     }
     return length;
 }
 
 void METHOD(DoubleLinkedCyclicList, append, int value)
 {
     struct DoubleLinkedElement *element = object->head;
     if (element == NULL)
     {
         element = malloc(sizeof(struct DoubleLinkedElement));
         element->data = value;
         element->next = element;
         element->prev = element;
         object->head = element;
         return;
     }
     while (element->next != object->head)
     {
         element = element->next;
     }
     struct DoubleLinkedElement *newElement = malloc(sizeof(struct DoubleLinkedElement));
     newElement->data = value;
     newElement->prev = element;
     newElement->next = object->head;
     object->head->prev = newElement;
     element->next = newElement;
 }
 
 void METHOD_NO_ARGS(DoubleLinkedCyclicList, free)
 {
     if (object == NULL)
     {
         return;
     }
     struct DoubleLinkedElement *element = object->head;
     if (element == NULL)
     {
         return;
     }
     struct DoubleLinkedElement *next = element->next;
     if (next == NULL)
     {
         return;
     }
     int length = _method_DoubleLinkedCyclicList_get_length(object);
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
 
 // -1 = data not found
 int METHOD(DoubleLinkedCyclicList, print_from, int startElement)
 {
     struct DoubleLinkedElement *e = object->head;
     int length = _method_DoubleLinkedCyclicList_get_length(object);
     int found = 0;
     for (int i = 0; i < length; i++)
     {
         if (e->data == startElement)
         {
             found = 1;
             break;
         }
         e = e->next;
     }
     if (found == 0)
     {
         return -1;
     }
     for (int i = 0; i < length - 1; i++)
     {
         printf("%d ", e->data);
         e = e->next;
     }
     printf("%d", e->data);
     return 0;
 }
 
 // -1 = data not found
 int METHOD(DoubleLinkedCyclicList, print_reversed_from, int data)
 {
     struct DoubleLinkedElement *e = object->head;
     int length = _method_DoubleLinkedCyclicList_get_length(object);
     int found = 0;
     for (int i = 0; i < length; i++)
     {
         if (e->data == data)
         {
             found = 1;
             break;
         }
         e = e->next;
     }
     if (found == 0)
     {
         return -1;
     }
     for (int i = 0; i < length - 1; i++)
     {
         printf("%d ", e->data);
         e = e->prev;
     }
     printf("%d", e->data);
     return 0;
 }
 
 void METHOD_NO_ARGS(DoubleLinkedCyclicList, print)
 {
     int data = object->head->data;
     _method_DoubleLinkedCyclicList_print_from(object, data);
 }
 
 void METHOD_NO_ARGS(DoubleLinkedCyclicList, print_reversed)
 {
     int data = object->head->data;
     _method_DoubleLinkedCyclicList_print_reversed_from(object, data);
 }
 
 int main()
 {
     struct DoubleLinkedCyclicList list;
     _constructor_DoubleLinkedCyclicList(&list);
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
         _method_DoubleLinkedCyclicList_append(&list, c - '0');
     }
     int length = _method_DoubleLinkedCyclicList_get_length(&list);
     if (length == 0)
     {
         printf("0");
         _method_DoubleLinkedCyclicList_free(&list);
         return 0;
     }
     struct DoubleLinkedElement *e = list.head;
     _method_DoubleLinkedCyclicList_print(&list);
     printf("\n");
     _method_DoubleLinkedCyclicList_print_reversed_from(&list, e->prev->data);
     printf("\n");
     int k;
     int found = 0;
     scanf("%d", &k);
     for (int i = 0; i < length; i++)
     {
         if (e->data == k)
         {
             found = 1;
             break;
         }
         e = e->next;
     }
     if (found)
     {
         _method_DoubleLinkedCyclicList_print_from(&list, k);
         printf("\n");
         _method_DoubleLinkedCyclicList_print_reversed_from(&list, k);
     }
     else
     {
         _method_DoubleLinkedCyclicList_print(&list);
         printf("\n");
         _method_DoubleLinkedCyclicList_print_reversed_from(&list, e->prev->data);
     }
     _method_DoubleLinkedCyclicList_free(&list);
     return 0;
 }
 