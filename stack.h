//
// Created by Noam pnueli on 27/10/2016.
//

#ifndef INFIXEVAL_STACK_H
#define INFIXEVAL_STACK_H

#endif //INFIXEVAL_STACK_H

#define STACK_MAX 100

void stack_init(struct stack* stack);
void push(struct stack* stack, char* data);
char* pop(struct stack* stack);
char* peek(struct stack* stack);

typedef struct stack
{
    char* data[STACK_MAX];
    int size;
} stack;