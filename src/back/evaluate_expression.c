#include "calculator.h"

int processNumber(const char *postfix, struct Stack *stack, int *index,
                  long double *result) {
  int err = OK;
  long double num = 0.0;
  long double fraction = 0.1;  // Десятичная часть числа
  int decimal = 0;  // Флаг для отслеживания десятичной части

  if (postfix == NULL || stack == NULL || index == NULL || result == NULL)
    err = ERROR;
  while ((isdigit(postfix[*index]) || postfix[*index] == '.') && (err == OK)) {
    if (postfix[*index] == '.') {
      if (decimal) err = ERROR;  // Ошибка при второй десятичной точке
      decimal = 1;  // Установим флаг десятичной части
    } else {
      if (decimal) {
        num += (postfix[*index] - '0') * fraction;
        fraction *= 0.1;
      } else
        num = num * 10 + (postfix[*index] - '0');
    }
    (*index)++;
  }
  if (decimal && fraction == 0.1)
    err = ERROR;  // Ошибка при отсутствии цифр после десятичной точки
  if (err == OK) {
    push(stack, num);
    *result = num;
  }
  return err;
}

int processFunction(char token, struct Stack *stack, long double *result) {
  int err = OK;
  double operand = 0;
  if (stack == NULL || result == NULL) err = ERROR;
  if (!isEmpty(stack))
    operand = pop(stack);
  else
    err = ERROR;
  if (err == OK) {
    switch (token) {
      case 's':
        push(stack, sin(operand));
        break;
      case 'c':
        push(stack, cos(operand));
        break;
      case 't':
        push(stack, tan(operand));
        break;
      case 'C':
        push(stack, acos(operand));
        break;
      case 'S':
        push(stack, asin(operand));
        break;
      case 'T':
        push(stack, atan(operand));
        break;
      case 'q':
        push(stack, sqrt(operand));
        break;
      case 'l':
        push(stack, log10(operand));
        break;
      case 'L':
        push(stack, log(operand));
        break;
      case 'U':
        push(stack, -(operand));
        break;
      case 'Y':
        push(stack, +(operand));
        break;
    }
  }
  *result = (*stack).elements[(*stack).top];
  return err;
}

int processOperator(char token, struct Stack *stack) {
  int err = OK;
  if (stack == NULL) err = ERROR;
  double operand1 = 0;
  double operand2 = pop(stack);
  if (!isEmpty(stack))
    operand1 = pop(stack);
  else
    err = ERROR;
  if (err == OK) {
    switch (token) {
      case '+':
        push(stack, operand1 + operand2);
        break;
      case '-':
        push(stack, operand1 - operand2);
        break;
      case '*':
        push(stack, operand1 * operand2);
        break;
      case '/':
        push(stack, operand1 / operand2);
        break;
      case '^':
        push(stack, pow(operand1, operand2));
        break;
      case 'm':
        push(stack, fmod(operand1, operand2));
        break;
    }
  }
  return err;
}

int evaluateExpression(char *postfix, long double *result) {
  int err = OK;
  if (postfix == NULL || result == NULL) err = ERROR;
  struct Stack stack = {0};
  newOrClear(&stack);
  int index = 0;
  while (postfix[index] != '\0' && (err == OK)) {
    char token = postfix[index];

    if (isdigit(token) || token == '.') {
      err = processNumber(postfix, &stack, &index, result);
    } else if (token == ' ' || token == '\t')
      index++;
    else if (token == 's' || token == 'c' || token == 't' || token == 'C' ||
             token == 'S' || token == 'T' || token == 'l' || token == 'L' ||
             token == 'q' || token == 'U' || token == 'Y') {
      err = processFunction(token, &stack, result);
      index++;
    } else if (token == '+' || token == '-' || token == '*' || token == '/' ||
               token == '^' || token == 'm') {
      err = processOperator(token, &stack);
      index++;
    } else
      err = ERROR;
  }
  if (err == ERROR)
    *result = 0;
  else
    *result = pop(&stack);
  newOrClear(&stack);
  return err;
}
