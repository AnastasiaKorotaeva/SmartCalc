#include "calculator.h"

void newOrClear(struct Stack *stack) {
  (*stack).top = -1;  // Вершина стека пустая
}

int isEmpty(struct Stack *stack) { return (*stack).top == -1 ? OK : ERROR; }

void push(struct Stack *stack, long double element) {
  if ((*stack).top < STACK_SIZE) {
    (*stack).top++;
    (*stack).elements[(*stack).top] = element;
  }
}

long double pop(struct Stack *stack) {
  long double element = 0;
  element = (*stack).elements[(*stack).top];
  (*stack).top--;
  return element;
}
