#ifndef _STACK_H_
#define _STACK_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 255

#define OK 1
#define ERROR 0

struct Stack {
  int top;
  long double elements[STACK_SIZE];
};

void newOrClear(struct Stack *stack);
int isEmpty(struct Stack *stack);
void push(struct Stack *stack, long double element);
long double pop(struct Stack *stack);

int workNumber(const char *infix, char *postfix, int *i, int *j);
int workX(char *infix, int *i, long double X);
int workStr(const char *infix, int *i, struct Stack *stack);
int workOperator(const char *infix, char *postfix, int *i, int *j,
                 struct Stack *stack);
int workBrackets(const char *infix, char *postfix, int *i, int *j,
                 struct Stack *stack);
int isOperator(char c);
int priority(char c);
int checkBrackets(const char *infix);
void replaceStr(char *string, size_t *i, size_t *j, const char *long_str,
                char new_str, size_t length_str);
int remakeStr(char *string);
int replaceX(char *string, long double X);
int infixToPostfix(const char *infix, char *postfix, long double X);

int processNumber(const char *postfix, struct Stack *stack, int *index,
                  long double *result);
int processFunction(char token, struct Stack *stack, long double *result);
int processOperator(char token, struct Stack *stack);
int evaluateExpression(char *postfix, long double *result);

#endif
