#include "deposit.h"

long double total_percent_capit_or_month(long double sum, double period,
                                         long double percent,
                                         long double replenishments,
                                         long double withdraws, int capitaliz) {
  long double percent_month = 0;  //накопенные проценты в тек месяце
  for (int i = 0; (double)i < period; i++) {
    long double percent_month_total = 0;  //совокупный доход по месяцам
    percent_month_total = sum * percent / 100 / 12;
    sum += replenishments;
    sum -= withdraws;
    if (capitaliz) {
      sum += percent_month_total;
    }
    percent_month += percent_month_total;
  }
  return percent_month;
}

long double total_percent_year(long double sum, double period,
                               long double percent, long double replenishments,
                               long double withdraws) {
  long double percent_month = 0;
  for (int i = 0; (double)i < period; i++) {
    sum += replenishments;
    sum -= withdraws;
    if (i >= 12 && i % 12 == 0) {
      long double year_percent = 0;  // Годовые начисления процентов
      year_percent = sum * percent / 100;
      percent_month +=
          year_percent;  // Добавляем годовые начисления к общей сумме
    }
  }
  return percent_month;
}

long double tax_sum(long double total_percent, long double tax) {
  return total_percent * tax /
         100;  //Сумма налога = начисленные проценты * %налога/100
}

long double total_sum(long double sum, long double total_percent,
                      long double tax_sum) {
  return sum + total_percent -
         tax_sum;  // Сумма на вкладе в конце = сумма + начисленные проценты -
                   // налоговая сумма
}
