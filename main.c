//
// Created by Noam Pnueli on 27/10/2016.
//

#include <string.h>
#include <stdlib.h>
#import <stdio.h>
#import "stack.h"

#define BUFF_SIZE 50

int operate(char** op1, char** op2, char operator, char* buff);
int operator_importance(char* op1, char* op2);

int main()
{
    stack value_stack;
    stack_init(&value_stack);

    stack operator_stack;
    stack_init(&operator_stack);

    char buffer[BUFF_SIZE];
    printf("Please enter an expression:\n");
    fgets(buffer, BUFF_SIZE, stdin);

    for(int i = 0; i < strlen(buffer); i++)
    {
        char token = buffer[i];

        if(token == ' ')
            continue;

        if(token >= '0' && token <= '9')
        {
            char* num = malloc(BUFF_SIZE);
            int len = 0;
            while(buffer[i] >= '0' && buffer[i] <= '9')
            {
                i++;
                len++;
            }
            memcpy(num, &buffer[i - len], len + 1);
            *(num + len) = '\0';
            i--;
            push(&value_stack, num);
        }
        else if(token == '(')
        {
            push(&operator_stack, &buffer[i]);
        }
        else if(token == ')')
        {
            while(*peek(&operator_stack) != '(')
            {
                char operator = *pop(&operator_stack);
                char* operand2 = pop(&value_stack);
                char* operand1 = pop(&value_stack);

                char* result = malloc(BUFF_SIZE);
                operate(&operand1, &operand2, operator, result);
                push(&value_stack, result);
            }
            pop(&operator_stack);
        }
        else if(token == '+' || token == '-' || token == '*' ||token == '/')
        {
            while(operator_stack.size > 0 && operator_importance(peek(&operator_stack), &token) > 0)
            {
                char operator = *pop(&operator_stack);
                char* operand2 = pop(&value_stack);
                char* operand1 = pop(&value_stack);

                char* result = malloc(BUFF_SIZE);
                operate(&operand1, &operand2, operator, result);
                push(&value_stack, result);
            }
            push(&operator_stack, &buffer[i]);
        }
    }

    while(operator_stack.size > 0)
    {
        char operator = *pop(&operator_stack);
        char* operand2 = pop(&value_stack);
        char* operand1 = pop(&value_stack);

        char* result = malloc(BUFF_SIZE);
        operate(&operand1, &operand2, operator, result);
        free(operand2);
        free(operand1);
        push(&value_stack, result);
    }

    char* answer = pop(&value_stack);
    printf("Answer: %s", answer);

    free(answer);

    return 0;
}

int operate(char** op1, char** op2, char operator, char* buff)
{
    int operand1 = atoi(*op1);
    int operand2 = atoi(*op2);

    if(operator == '+')
    {
        sprintf(buff, "%d", operand1 + operand2);
        char ans[BUFF_SIZE];
        sprintf(ans, "%d", operand1 + operand2);
        return (int) strlen(ans);
    }
    else if(operator == '*')
    {
        sprintf(buff, "%d", operand1 * operand2);
        char ans[BUFF_SIZE];
        sprintf(ans, "%d", operand1 + operand2);
        return (int) strlen(ans);
    }
    else if(operator == '/')
    {
        sprintf(buff, "%d", operand1 / operand2);
        char ans[BUFF_SIZE];
        sprintf(ans, "%d", operand1 + operand2);
        return (int) strlen(ans);
    }
    else if(operator == '-')
    {
        sprintf(buff, "%d", operand1 - operand2);
        char ans[BUFF_SIZE];
        sprintf(ans, "%d", operand1 + operand2);
        return (int) strlen(ans);
    }
    else
    {
        fprintf(stderr, "Syntax Error\n");
    }

    return 0;
}

int operator_importance(char* op1, char* op2)
{
    if ((*op1 == '*' || *op1 == '/') && (*op2 == '+' || *op2 == '-'))
        return 1;
    if ((*op1 == '*' || *op1 == '/') && (*op2 == '*' || *op2 == '/'))
        return 1;
    return 0;
}
