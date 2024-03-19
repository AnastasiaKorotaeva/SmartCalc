#include <check.h>

#include "back/calculator.h"
#include "back/credit.h"
#include "back/deposit.h"

START_TEST(fun_s21_calc_test1) {
  long double result = 0.0;
  char *infix = "111-2^(4^3)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_str_eq(postfix, "111 2 4 3 ^ ^ - ");
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_ldouble_eq(result, -18446744073709551505.0);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test2) {
  long double result = 0.0;
  char *infix = "364*12-323+50/0.235+17*(123-23)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_str_eq(postfix, "364 12 * 323 - 50 0.235 / + 17 123 23 - * + ");
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_ldouble_eq_tol(result, 5957.7659574, 1e-1);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test3) {
  long double result = 0.0;
  char *infix =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_str_eq(
      postfix,
      "15 7 1 1 + - / 3 * 2 1 1 + + 15 * 7 200 1 + - / 3 * - 2 1 1 + + 15 7 1 "
      "1 + - / 3 * 2 1 1 + + - 15 7 1 1 + - / 3 * + 2 1 1 + + - * - ");
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_ldouble_eq_tol(result, -30.0721649, 1e-1);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test4) {
  long double result = 0.0;
  char *infix = "15/0";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_str_eq(postfix, "15 0 / ");
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_ldouble_infinite(result);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test5) {
  char *infix = "(9+2)-(2*(21)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test6) {
  char *infix = "(9+2)(2*(21))";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test7) {
  long double result = 0.0;
  char *infix = "-(9+2)+(2*(21-(-23)))";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_ldouble_eq(result, 77.0);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test8) {
  long double result = 0.0;
  char *infix = "sin(0.12)+cos(3)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_ldouble_eq_tol(result, -0.87028, 1e-6);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test9) {
  long double result = 0.0;
  char *infix = "atan(0.32)*12-(234.234+89)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_ldouble_eq_tol(result, -319.51756, 1e-5);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test10) {
  long double result = 0.0;
  char *infix = "atan(0.32)*12-(234.234+89)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_ldouble_eq_tol(result, -319.51756, 1e-5);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test11) {
  long double result = 0.0;
  char *infix = "sin(0.25)-cos(22.5)+tan(0.5)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_double_eq_tol(result, sin(0.25) - cos(22.5) + tan(0.5), 1e-7);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test12) {
  long double result = 0.0;
  char *infix = "sin(0.....25)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_int_eq(err_2, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test13) {
  long double result = 0.0;
  char *infix = "17.6.8+234";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_int_eq(err_2, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test14) {
  char *infix = "*17.6.8+234";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test15) {
  long double result = 0.0;
  char *infix = "x+23";
  long double X = -2.12;
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, X);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_double_eq_tol(result, 20.88, 1e-7);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test16) {
  char *infix = "2x+23";
  long double X = -2.12;
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, X);
  ck_assert_int_eq(err, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test17) {
  char *infix = "5sin(1)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test18) {
  char *infix = "5+++7";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test19) {
  char *infix = "(20.12+2)17";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test20) {
  long double result = 0.0;
  char *infix = "5mod2+34*2.603";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_double_eq_tol(result, 89.502, 1e-7);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test21) {
  long double result = 0.0;
  char *infix = "+37-15mod2+34^0.12";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_double_eq_tol(result, 37.5267835, 1e-7);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test22) {
  char *infix = "456-2.002*sim(1)";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test23) {
  long double result = 0.0;
  char *infix = "456-2.002\n";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_double_eq_tol(result, 453.998, 1e-7);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test24) {
  long double result = 0.0;
  char *infix = "13 + 17-2.78+2\n";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_double_eq_tol(result, 29.22, 1e-7);
  ck_assert_int_eq(err_2, OK);
}
END_TEST

START_TEST(fun_s21_calc_test25) {
  long double result = 0.0;
  char *infix = "3.";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_int_eq(err_2, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test26) {
  long double result = 0.0;
  char *infix = "22+";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_int_eq(err_2, ERROR);
}
END_TEST

START_TEST(fun_s21_calc_test27) {
  long double result = 0.0;
  char *infix = "acos(0.01)+asin(0.2)-sqrt(16)+ln1-log2";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_double_eq_tol(result, -2.53888, 1e-5);
  ck_assert_int_eq(err_2, OK);
}

START_TEST(fun_s21_calc_test28) {
  long double result = 0.0;
  char *infix = "sqrt";
  char postfix[STACK_SIZE * 2] = {0};
  int err = 0;
  err = infixToPostfix(infix, postfix, 0);
  ck_assert_int_eq(err, OK);

  int err_2 = 0;
  err_2 = evaluateExpression(postfix, &result);
  ck_assert_int_eq(err_2, ERROR);
}

START_TEST(fun_s21_calc_creditAnn) {
  long double percent = 9;
  long double sum = 40000;
  long double month = 16;
  long double monthly_payment = monthlyPaymentAnn(sum, percent, month);
  long double total_payment = totalPayment(monthly_payment, month);
  long double over_payment = overPayment(sum, total_payment);
  ck_assert_ldouble_eq_tol(2662.35, monthly_payment, 1e-2);
  ck_assert_double_eq_tol(42597.62, total_payment, 1e-2);
  ck_assert_double_eq_tol(2597.62, over_payment, 1e-2);
}

START_TEST(fun_s21_calc_creditDiff) {
  long double percent = 9;
  long double sum = 40000;
  long double month = 16;
  long double firstMonthly = 0;
  long double lastMonthly = 0;
  long double total_payment =
      monthlyPaymentDiff(sum, percent, month, &firstMonthly, &lastMonthly);
  long double over_payment = overPayment(sum, total_payment);
  ck_assert_ldouble_eq_tol(2800.0, firstMonthly, 1e-7);
  ck_assert_ldouble_eq_tol(2518.75, lastMonthly, 1e-7);
  ck_assert_double_eq_tol(42550.0, total_payment, 1e-7);
  ck_assert_double_eq_tol(2550.0, over_payment, 1e-7);
}

START_TEST(fun_s21_calc_deposit1) {
  long double sum = 100000;
  double period = 18;
  long double percentYear = 11;
  long double popolnen = 2500;
  long double snytie = 1000;
  int capitaliz = 1;
  long double percentTax = 3;
  long double result = total_percent_capit_or_month(
      sum, period, percentYear, popolnen, snytie, capitaliz);
  ck_assert_ldouble_eq_tol(result, 20060.9, 1e-1);

  long double result2 = tax_sum(result, percentTax);
  ck_assert_ldouble_eq_tol(result2, 601.8277, 1e-4);

  long double result3 = total_sum(sum, result, result2);
  ck_assert_ldouble_eq_tol(result3, 119459.1, 1e-1);
}

START_TEST(fun_s21_calc_deposit2) {
  long double sum = 23000;
  double period = 23;
  long double percentYear = 9;
  long double popolnen = 3500;
  long double snytie = 550;
  long double percentTax = 3;
  long double result =
      total_percent_year(sum, period, percentYear, popolnen, snytie);
  ck_assert_ldouble_eq_tol(result, 5521.5, 1e-1);

  long double result2 = tax_sum(result, percentTax);
  ck_assert_ldouble_eq_tol(result2, 165.645, 1e-3);

  long double result3 = total_sum(sum, result, result2);
  ck_assert_ldouble_eq_tol(result3, 28355.85, 1e-2);
}

Suite *suite_fun_calc(void) {
  Suite *suite;
  TCase *all_tcase;

  suite = suite_create("fun_calc");
  all_tcase = tcase_create("All_case");

  tcase_add_test(all_tcase, fun_s21_calc_test1);
  tcase_add_test(all_tcase, fun_s21_calc_test2);
  tcase_add_test(all_tcase, fun_s21_calc_test3);
  tcase_add_test(all_tcase, fun_s21_calc_test4);
  tcase_add_test(all_tcase, fun_s21_calc_test5);
  tcase_add_test(all_tcase, fun_s21_calc_test6);
  tcase_add_test(all_tcase, fun_s21_calc_test7);
  tcase_add_test(all_tcase, fun_s21_calc_test8);
  tcase_add_test(all_tcase, fun_s21_calc_test9);
  tcase_add_test(all_tcase, fun_s21_calc_test10);
  tcase_add_test(all_tcase, fun_s21_calc_test11);
  tcase_add_test(all_tcase, fun_s21_calc_test12);
  tcase_add_test(all_tcase, fun_s21_calc_test13);
  tcase_add_test(all_tcase, fun_s21_calc_test14);
  tcase_add_test(all_tcase, fun_s21_calc_test15);
  tcase_add_test(all_tcase, fun_s21_calc_test16);
  tcase_add_test(all_tcase, fun_s21_calc_test17);
  tcase_add_test(all_tcase, fun_s21_calc_test18);
  tcase_add_test(all_tcase, fun_s21_calc_test19);
  tcase_add_test(all_tcase, fun_s21_calc_test20);
  tcase_add_test(all_tcase, fun_s21_calc_test21);
  tcase_add_test(all_tcase, fun_s21_calc_test22);
  tcase_add_test(all_tcase, fun_s21_calc_test23);
  tcase_add_test(all_tcase, fun_s21_calc_test24);
  tcase_add_test(all_tcase, fun_s21_calc_test25);
  tcase_add_test(all_tcase, fun_s21_calc_test26);
  tcase_add_test(all_tcase, fun_s21_calc_test27);
  tcase_add_test(all_tcase, fun_s21_calc_test28);

  tcase_add_test(all_tcase, fun_s21_calc_creditAnn);
  tcase_add_test(all_tcase, fun_s21_calc_creditDiff);

  tcase_add_test(all_tcase, fun_s21_calc_deposit1);
  tcase_add_test(all_tcase, fun_s21_calc_deposit2);

  suite_add_tcase(suite, all_tcase);
  return suite;
}

int main(void) {
  int failed_count;
  Suite *suite;
  SRunner *srunner;

  suite = suite_fun_calc();
  srunner = srunner_create(suite);

  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_NORMAL);
  failed_count = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
