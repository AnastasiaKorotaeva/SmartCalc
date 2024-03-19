#include "credit.h"

// Функция для расчета ежемесячного платежа в аннуитетном кредите
long double monthlyPaymentAnn(long double sumCredit, long double percent,
                              double time) {
  double monthlyPercent = (percent / 100) / 12;
  return (sumCredit * monthlyPercent) / (1 - pow(1 + monthlyPercent, -time));
}

// Общая выплата в аннуитетном кредите
long double totalPayment(long double monthlyPayment, double time) {
  long double totalPayment = monthlyPayment * time;
  return totalPayment;
}

// Переплата по кредиту
long double overPayment(long double sumCredit, long double totalPayment) {
  return totalPayment - sumCredit;
}

// Функция для расчета ежемесячного платежа и общей выплаты в дифференцированном
// кредите
long double monthlyPaymentDiff(long double sumCredit, long double percent,
                               double time, long double *firstMonthly,
                               long double *lastMonthly) {
  long double totalPayment = 0;
  long double osnovnPayment = sumCredit / time;
  for (int month = 0; month < time; month++) {
    long double monthlyPercent =
        osnovnPayment +
        (sumCredit - osnovnPayment * month) * (percent / 100) / 12;
    if (month == 0) {
      *firstMonthly = monthlyPercent;
    }
    if (month == time - 1) {
      *lastMonthly = monthlyPercent;
    }
    totalPayment += monthlyPercent;
  }
  return totalPayment;
}
