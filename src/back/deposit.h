#ifndef _DEPOSIT_H_
#define _DEPOSIT_H_

#include <math.h>
#include <stdio.h>

long double total_percent_capit_or_month(long double sum, double period,
                                         long double percent,
                                         long double replenishments,
                                         long double withdraws, int capitaliz);
long double total_percent_year(long double sum, double period,
                               long double percent, long double replenishments,
                               long double withdraws);
long double tax_sum(long double total_percent, long double tax);
long double total_sum(long double sum, long double total_percent,
                      long double tax_sum);

#endif