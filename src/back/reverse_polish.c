#include "calculator.h"

int workNumber(const char *infix, char *postfix, int *i, int *j) {
  while (isdigit(infix[*i]) || infix[*i] == '.') {
    postfix[*j] = infix[*i];
    (*j)++;
    (*i)++;
  }
  postfix[*j] = ' ';
  (*j)++;
  return OK;
}

int workX(char *infix, int *i, long double X) {
  int err = ERROR;
  if ((*i > 0 && isdigit(infix[*i - 1])) || isdigit(infix[*i + 1]) ||
      infix[*i - 1] == ')' || infix[*i + 1] == '(' || isalpha(infix[*i + 1]))
    err = ERROR;
  else {
    replaceX(infix, X);  // Заменяем 'x' на значение X в выражении
    err = OK;
  }
  return err;
}

int workStr(const char *infix, int *i, struct Stack *stack) {
  int err = ERROR;
  if (*i > 0 && isdigit(infix[*i - 1]) && infix[*i] != 'm') {
    err = ERROR;
  } else {
    push(stack, infix[*i]);
    (*i)++;
    err = OK;
  }
  return err;
}

int workOperator(const char *infix, char *postfix, int *i, int *j,
                 struct Stack *stack) {
  int err = ERROR;
  if (*i == 0) {
    err = ERROR;
  } else {
    if (*i > 0 && isOperator(infix[*i - 1])) {
      err = ERROR;
    } else {
      while (!isEmpty(stack) && (*stack).elements[(*stack).top] != '(' &&
             priority((*stack).elements[(*stack).top]) >= priority(infix[*i])) {
        postfix[*j] = pop(stack);
        (*j)++;
        postfix[*j] = ' ';
        (*j)++;
      }
      push(stack, infix[*i]);
      (*i)++;
      err = OK;
    }
  }
  return err;
}

int workBrackets(const char *infix, char *postfix, int *i, int *j,
                 struct Stack *stack) {
  int err = ERROR;
  if (infix[*i] == '(') {
    if (isdigit(infix[*i - 1]) || infix[*i - 1] == ')')
      err = ERROR;
    else {
      push(stack, infix[*i]);
      (*i)++;
      err = OK;
    }
  } else if (infix[*i] == ')') {
    if (isdigit(infix[*i + 1]) || infix[*i - 1] == '(')
      err = ERROR;
    else {
      while (!isEmpty(stack) && (*stack).elements[(*stack).top] != '(') {
        postfix[*j] = pop(stack);
        (*j)++;
        postfix[*j] = ' ';
        (*j)++;
      }
      pop(stack);  // Извлекаем '(' из стека
      (*i)++;
      err = OK;
    }
  }
  return err;
}

int isOperator(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int priority(char c) {
  int prior = 0;
  if (c == '+' || c == '-')
    prior = 0;
  else if (c == '*' || c == '/')
    prior = 1;
  else if (c == 's' || c == 'c' || c == 't' || c == 'C' || c == 'S' ||
           c == 'T' || c == 'l' || c == 'L' || c == '^' || c == 'q')
    prior = 2;
  else if (c == 'm')
    prior = 3;
  else if (c == 'U' || c == 'Y')
    prior = 4;
  return prior;
}

int checkBrackets(const char *infix) {
  int countOpen = 0;
  int countClose = 0;
  int count = 0;
  int i = 0;
  while (infix[i] != '\0') {
    if (infix[i] == '(')
      countOpen++;
    else if (infix[i] == ')')
      countClose++;
    i++;
  }
  if (countOpen == countClose)
    count = 1;  // Количество скобок совпадает
  else
    count = 0;  // Количество скобок не совпадает
  return count;
}

void replaceStr(char *string, size_t *i, size_t *j, const char *long_str,
                char new_str, size_t length_str) {
  if (strncmp(&string[*i], long_str, length_str) == 0) {
    string[*j] = new_str;
    *i += length_str;
    (*j)++;
  }
}

int remakeStr(char *string) {
  int err = ERROR;
  int exit = 0;
  size_t i = 0;
  size_t j = 0;
  size_t len = strlen(string);
  while (i < len && string[i] != '\0' && string != NULL && !exit) {
    err = OK;
    replaceStr(string, &i, &j, "cos", 'c', 3);
    replaceStr(string, &i, &j, "sin", 's', 3);
    replaceStr(string, &i, &j, "tan", 't', 3);
    replaceStr(string, &i, &j, "mod", 'm', 3);
    replaceStr(string, &i, &j, "log", 'l', 3);
    replaceStr(string, &i, &j, "ln", 'L', 2);
    replaceStr(string, &i, &j, "sqrt", 'q', 4);
    replaceStr(string, &i, &j, "asin", 'S', 4);
    replaceStr(string, &i, &j, "acos", 'C', 4);
    replaceStr(string, &i, &j, "atan", 'T', 4);
    if (string[i] == '-' && (i == 0 || string[i - 1] == '(')) {
      string[j] = 'U';
    } else if (string[i] == '+' && (i == 0 || string[i - 1] == '(')) {
      string[j] = 'Y';
    } else if (isdigit(string[i]) || isOperator(string[i]) ||
               string[i] == ' ' || string[i] == 'x' || string[i] == '.' ||
               string[i] == ')' || string[i] == '(')
      string[j] = string[i];
    else if (string[i] == '\n' || string[i] == '\0')
      string[j] = '\0';
    else {
      exit = 1;
      err = ERROR;
    }
    i++;
    j++;
  }
  string[j] = '\0';
  return err;
}

int replaceX(char *string, long double X) {
  int err = ERROR;
  size_t lengthStart = strlen(string);
  int lengthOstatok = STACK_SIZE - lengthStart;
  char expressionX[256] = {'\0'};
  char *replaceStr = string;
  snprintf(
      expressionX, STACK_SIZE, "%Lf",
      fabsl(
          X));  // два оператора подряд нельзя, поэтому x обязательно без знака
  size_t lengthX = strlen(expressionX);
  if (X < 0) {
    memmove(expressionX + 1, expressionX, lengthX + 1);
    expressionX[0] = 'U';  // Сдвигаем вправо и вместо минуса добавляем 'U'
  }
  for (; *replaceStr != '\0' && (lengthOstatok - lengthX) > 0; replaceStr++) {
    if (*replaceStr == 'x') {
      if (lengthOstatok) {
        memmove(replaceStr + lengthX - 1, replaceStr,
                strlen(replaceStr));  // добавляем место для expressionX
        memmove(replaceStr, expressionX, lengthX);
        lengthOstatok -= lengthX;
      }
    }
  }
  err = OK;
  return err;
}

int infixToPostfix(const char *infix, char *postfix, long double X) {
  struct Stack stack = {0};
  newOrClear(&stack);
  int i = 0;
  int j = 0;
  int err = ERROR;

  char infix_2[STACK_SIZE + 1] = {'\0'};
  strncpy(infix_2, infix, STACK_SIZE);
  err = remakeStr(infix_2);
  if (!checkBrackets(infix)) err = ERROR;
  if (err == OK) {
    while (infix_2[i] != '\0' && err == OK) {
      if (isdigit(infix_2[i]) || infix_2[i] == '.')
        err = workNumber(infix_2, postfix, &i, &j);
      else if (infix_2[i] == 'x')
        err = workX(infix_2, &i, X);
      else if (isalpha(infix_2[i]))
        err = workStr(infix_2, &i, &stack);
      else if (infix_2[i] == '(' || infix_2[i] == ')')
        err = workBrackets(infix_2, postfix, &i, &j, &stack);
      else if (isOperator(infix_2[i]))
        err = workOperator(infix_2, postfix, &i, &j, &stack);
      else if (infix_2[i] == ' ')
        i++;
    }
    while (!isEmpty(&stack) && err == OK) {
      postfix[j] = pop(&stack);
      j++;
      postfix[j] = ' ';
      j++;
    }
    postfix[j] = '\0';
  }
  if (err == ERROR) {
    *postfix = 0;
    newOrClear(&stack);
  }
  return err;
}
