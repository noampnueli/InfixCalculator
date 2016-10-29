//
// Created by Noam pnueli on 27/10/2016.
//

#import "stdio.h"

#define STACK_MAX 100

typedef struct stack
{
    char* data[STACK_MAX];
    int size;
} stack;

void stack_init(struct stack* stack)
{
    stack->size = 0;
}

void push(struct stack* stack, char* data)
{
    if(stack->size < STACK_MAX)
    {
        stack->size++;
        stack->data[stack->size] = data;
    }
    else
    {
        fprintf(stderr, "Stack Overflow\n");
    }
}

char* pop(struct stack* stack)
{
    if(stack->size > 0)
    {
        char* val = stack->data[stack->size];
        stack->size--;
        return val;
    }
    else
    {
        fprintf(stderr, "Stack Empty\n");
    }
    return NULL;
}

char* peek(struct stack* stack)
{
    return stack->data[stack->size];
}
