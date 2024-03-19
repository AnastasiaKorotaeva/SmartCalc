#ifndef _CREDIT_H_
#define _CREDIT_H_

#include <math.h>
#include <stdio.h>

// Функция для расчета ежемесячного платежа в аннуитетном кредите
long double monthlyPaymentAnn(long double sumCredit, long double percent,
                              double time);
// Общая выплата в аннуитетном кредите
long double totalPayment(long double monthlyPayment, double time);
// Переплата по кредиту
long double overPayment(long double sumCredit, long double totalPayment);

// Функция для расчета ежемесячного платежа и общей выплаты в дифференцированном
// кредите
long double monthlyPaymentDiff(long double sumCredit, long double percent,
                               double time, long double *firstMonthly,
                               long double *lastMonthly);

#endif
