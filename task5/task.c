/*
* Copyright (c) 2025, Diniyar Ismailov <idiniyar2006@mail.ru>.
*/

#include <stdio.h>
#include <stdlib.h>

struct Queue
{
    int data;
    struct Queue *next;
    struct Queue *prev;
};

void input(struct Queue *queue)
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

void add_start(struct Queue *queue)
{
    
}

void add_end(struct Queue *queue)
{
    
}

void remove_start(struct Queue *queue)
{
    
}

void remove_end(struct Queue *queue)
{
    
}

void main()
{
    struct Queue *queue;
    input(queue);
}