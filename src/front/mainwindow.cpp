#include "mainwindow.h"

#include <string>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      process_itog(QRegularExpression(
          "^[(sin|cos|ln|tan|log|mod|asin|atan|acos|sqrt|)0-9^/*-+x.]{255}")) {
  ui->setupUi(this);
  this->setFixedWidth(430);
  this->setFixedHeight(711);
  QLocale locale(QLocale::English);
  process_itog_x.setNotation(QDoubleValidator::StandardNotation);
  process_itog_x.setLocale(locale);
  // ввод только чисел для X
  ui->itog_x->setValidator(&process_itog_x);
  ui->itog->setValidator(&process_itog);
  // ввод только чисел для кредитного
  ui->totalSumCredit->setValidator(&process_itog_x);
  ui->allTime->setValidator(&process_itog_x);
  ui->yearPercent->setValidator(&process_itog_x);
  // ввод только чисел для депозитного
  ui->popoln->setValidator(&process_itog_x);
  ui->snyt->setValidator(&process_itog_x);
  ui->percent_tax->setValidator(&process_itog_x);
  ui->yearPercentDep->setValidator(&process_itog_x);
  ui->PeriodDep->setValidator(&process_itog_x);
  ui->totalSumDep->setValidator(&process_itog_x);
  connect(ui->itog, SIGNAL(textChanged(QString)), this, SLOT(check_x()));
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tochka, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_skobka1, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_skobka2, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_step, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ymnoj, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_delit, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  ui->label_x->setVisible(false);  //видимость полей x
  ui->itog_x->setVisible(false);
  ui->pushButton_graf->setCheckable(true);  //переключаемый режим кнопки
  ui->Graf->xAxis->setLabel("x");
  ui->Graf->yAxis->setLabel("y");
  ui->pushButton_credit->setCheckable(true);
  ui->pushButton_depos->setCheckable(true);
  ui->popoln->setVisible(false);
  ui->snyt->setVisible(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QByteArray button_text = button->text().toLocal8Bit();
  const char *str = button_text.data();
  if (ui->itog->text() == '0' && strpbrk(str, ")^/*")) {
    return;
  }
  if (ui->itog->text() == '0' && !strpbrk(str, ".)^/*")) {
    ui->itog->setText("");
  }
  if (strpbrk(str, "0123456789x+-()^.*/")) {
    ui->itog->setText(ui->itog->text() + button->text());
  } else if (strpbrk(str, "√")) {
    ui->itog->setText(ui->itog->text() + "sqrt(");
  } else {
    ui->itog->setText(ui->itog->text() + button->text() + "(");
  }
}

void MainWindow::on_pushButton_ravn_clicked() {
  std::string str = ui->itog->text().toStdString();
  const char *infix = str.c_str();
  bool error = false;
  bool is_error = false;
  if (ui->pushButton_ravn->text() == "=") {
    char postfix[STACK_SIZE * 2] = {'\0'};
    if ((strchr(infix, 'x')) && (ui->itog_x->text() == ""))
      ui->itog->setText("Add x");
    else
      error = infixToPostfix(infix, postfix,
                             (long double)ui->itog_x->text().toDouble());
    long double result = 0;
    if (error) {
      is_error = evaluateExpression(postfix, &result);
      if (is_error) {
        QString results = QString::number(result, 'g', 10);
        ui->itog->setText(results);
      } else {
        ui->itog->setText("Error");
      }
    } else {
      ui->itog->setText("Error");
    }
  }
}

void MainWindow::on_pushButton_delete_clicked() {
  QString output = ui->itog->text();
  output.chop(1);  //удаление последнего символа
  ui->itog->setText(output);
  if (ui->itog->text() == "") {
    ui->itog->setText("0");
  }
}

void MainWindow::on_pushButton_AC_clicked() { ui->itog->setText("0"); }

void MainWindow::check_x() {
  QByteArray button_text = ui->itog->text().toLocal8Bit();
  const char *str = button_text.data();
  if (strchr(str, 'x')) {
    ui->label_x->setVisible(true);
    ui->itog_x->setVisible(true);
  } else {
    ui->label_x->setVisible(false);
    ui->itog_x->setVisible(false);
  }
}

void MainWindow::on_pushButton_graf_clicked() {
  QPushButton *button = (QPushButton *)sender();  //получить сигнал
  if (button->isChecked()) {
    this->setFixedWidth(942);
    this->setFixedHeight(711);
    button->setChecked(true);
    ui->label_x->setVisible(false);
    ui->itog_x->setVisible(false);

    ui->pushButton_credit->setEnabled(false);
    ui->pushButton_depos->setEnabled(false);

    ui->pushButton_ravn->setEnabled(false);  //кнопка не активна
    ui->xmax_graf->setEnabled(true);
    ui->xmin_graf->setEnabled(true);
    ui->ymax_graf->setEnabled(true);
    ui->ymin_graf->setEnabled(true);
  } else {
    this->setFixedWidth(430);
    button->setChecked(false);
    ui->pushButton_ravn->setEnabled(true);

    ui->pushButton_credit->setEnabled(true);
    ui->pushButton_depos->setEnabled(true);

    ui->xmax_graf->setEnabled(false);
    ui->xmin_graf->setEnabled(false);
    ui->ymax_graf->setEnabled(false);
    ui->ymin_graf->setEnabled(false);
    ui->Graf->replot();
    x.clear();
    y.clear();
    ui->itog->setText("0");
  }
}

void MainWindow::on_pushButton_new_graf_clicked() {
  QString str = ui->itog->text();
  if (str.contains("x") == false) {
    ui->itog->setText("Add x to expression");
  } else {
    ui->label_x->setVisible(false);
    ui->itog_x->setVisible(false);
    double x_min_num = ui->xmin_graf->text().toDouble();
    ;
    double x_max_num = ui->xmax_graf->text().toDouble();
    ;
    double y_min_num = ui->ymin_graf->text().toDouble();
    ;
    double y_max_num = ui->ymax_graf->text().toDouble();
    ;

    double step = 0.001 * (qFabs(x_min_num) + qFabs(x_max_num));
    long double Y = 0;
    double X = x_min_num;
    char postfix[STACK_SIZE * 2] = {'\0'};
    while (X < x_max_num) {
      x.push_back(X);  //вектор X
      QByteArray str_1 =
          str.toLatin1();  //из строки в однобайтовую кодировку ascii
      char *infix = str_1.data();
      infixToPostfix(infix, postfix, X);
      evaluateExpression(postfix, &Y);
      y.push_back(Y);  //вектор Y
      X += step;
    }
    ui->Graf->addGraph();  //отрисовка графика
    ui->Graf->graph(0)->setLineStyle(
        QCPGraph::lsLine);  //линейный стиль графика
    ui->Graf->graph(0)->addData(x,
                                y);  //добавление значений точек x, y на график
    ui->Graf->xAxis->setRange(x_min_num, x_max_num);  //диапазон по X
    ui->Graf->yAxis->setRange(y_min_num, y_max_num);
    ui->Graf->replot();
    x.clear();
    y.clear();
    ui->Graf->graph(0)->data()->clear();
  }
}

void MainWindow::on_pushButton_clear_graf_clicked() {
  ui->Graf->replot();  //обновить график
  x.clear();
  y.clear();
}

void MainWindow::on_pushButton_credit_clicked() {
  QPushButton *button1 = (QPushButton *)sender();  //получить сигнал
  if (button1->isChecked()) {
    this->setFixedHeight(1207);
    this->setFixedWidth(430);
    button1->setChecked(true);
    ui->pushButton_graf->setEnabled(
        false);  // отключить использование кнопки графа
    ui->pushButton_depos->setEnabled(
        false);  // отключить использование кнопки кредита
    ui->label_x->setVisible(false);
    ui->itog_x->setVisible(false);
    no_vid_depos();  //скрыть депозитный
    vid_credit();    //показать кредитный
    ui->itog->setText("0");
  } else {
    ui->pushButton_graf->setEnabled(true);
    ui->pushButton_depos->setEnabled(true);
    this->setFixedWidth(430);
    this->setFixedHeight(711);
    no_vid_credit();  // скрыть кредитный
    vid_depos();
    button1->setChecked(false);
    ui->itog->setText("0");
  }
}

void MainWindow::on_result_clicked() {
  if (ui->totalSumCredit->text().isEmpty() || ui->allTime->text().isEmpty() ||
      ui->yearPercent->text().isEmpty() ||
      (!ui->annuity->isChecked() && !ui->differentiated->isChecked())) {
    ui->itog->setText("Not enough information");
  } else {
    long double sum_credit = ui->totalSumCredit->text().toDouble();
    double time = ui->allTime->text().toDouble();
    long double percent = ui->yearPercent->text().toDouble();
    if (ui->annuity->isChecked()) {
      long double monthlyPaymentAn =
          monthlyPaymentAnn(sum_credit, percent, time);
      long double totalPaymentAn = totalPayment(monthlyPaymentAn, time);
      long double overPaymentAn = overPayment(sum_credit, totalPaymentAn);
      QString monthly_payment = QString::number(monthlyPaymentAn, 'g', 7);
      QString total_payment = QString::number(totalPaymentAn, 'g', 7);
      QString over_payment = QString::number(overPaymentAn, 'g', 7);
      ui->monthlyPayment->setText(monthly_payment);
      ui->totalPayment->setText(total_payment);
      ui->overpayment->setText(over_payment);
    } else {
      long double firstMonthly = 0;
      long double lastMonthly = 0;
      long double totalPaymentDiffer = monthlyPaymentDiff(
          sum_credit, percent, time, &firstMonthly, &lastMonthly);
      long double overPaymentDiffer =
          overPayment(sum_credit, totalPaymentDiffer);
      QString monthly_first_payment_dif = QString::number(firstMonthly, 'g', 7);
      QString monthly_last_payment_dif = QString::number(lastMonthly, 'g', 7);
      QString total_payment_dif = QString::number(totalPaymentDiffer, 'g', 7);
      QString over_payment_dif = QString::number(overPaymentDiffer, 'g', 7);
      ui->monthlyPayment->setText(monthly_first_payment_dif + " - " +
                                  monthly_last_payment_dif);
      ui->totalPayment->setText(total_payment_dif);
      ui->overpayment->setText(over_payment_dif);
    }
  }
}

void MainWindow::on_clear_credit_clicked() {
  ui->totalSumCredit->setText("");
  ui->allTime->setText("");
  ui->yearPercent->setText("");
  ui->monthlyPayment->setText("0");
  ui->overpayment->setText("0");
  ui->totalPayment->setText("0");
  ui->itog->setText("0");
}

void MainWindow::on_result_depos_clicked() {
  if (ui->percent_tax->text().isEmpty() ||
      ui->yearPercentDep->text().isEmpty() || ui->PeriodDep->text().isEmpty() ||
      ui->totalSumDep->text().isEmpty() ||
      (!ui->year->isChecked() && !ui->month->isChecked() &&
       !ui->capitaliz->isChecked())) {
    ui->itog->setText("Not enough information");
  } else {
    long double sum = ui->totalSumDep->text().toDouble();
    double period = ui->PeriodDep->text().toDouble();
    long double percentYear = ui->yearPercentDep->text().toDouble();
    long double popolnen = ui->popoln->text().toDouble();
    long double snytie = ui->snyt->text().toDouble();
    long double percentTax = ui->percent_tax->text().toDouble();

    long double totalPercent = 0;
    long double percentTaxSum_itog = 0;
    long double totalSum_itog = 0;

    if (ui->capitaliz->isChecked()) {
      int capitaliz = 1;
      totalPercent = total_percent_capit_or_month(sum, period, percentYear,
                                                  popolnen, snytie, capitaliz);
    } else if (ui->year->isChecked()) {
      totalPercent =
          total_percent_year(sum, period, percentYear, popolnen, snytie);
    } else if (ui->month->isChecked()) {
      int capitaliz = 0;
      totalPercent = total_percent_capit_or_month(sum, period, percentYear,
                                                  popolnen, snytie, capitaliz);
    }
    percentTaxSum_itog = tax_sum(totalPercent, percentTax);
    totalSum_itog = total_sum(sum, totalPercent, percentTaxSum_itog);
    QString total_payment = QString::number(totalPercent, 'g', 7);
    QString total_sums = QString::number(totalSum_itog, 'g', 7);
    QString percent_tax = QString::number(percentTaxSum_itog, 'g', 7);
    ui->totalPayment_percent->setText(total_payment);
    ui->sum_tax->setText(percent_tax);
    ui->total_sum->setText(total_sums);
  }
}

void MainWindow::on_clear_depos_clicked() {
  ui->popoln->setText("");
  ui->snyt->setText("");
  ui->percent_tax->setText("");
  ui->yearPercentDep->setText("");
  ui->PeriodDep->setText("");
  ui->totalSumDep->setText("");
  ui->totalPayment_percent->setText("0.0");
  ui->total_sum->setText("0.0");
  ui->sum_tax->setText("0.0");
  ui->itog->setText("0");
}

void MainWindow::on_pushButton_depos_clicked() {
  QPushButton *button2 = (QPushButton *)sender();  //получить сигнал
  if (button2->isChecked()) {
    this->setFixedHeight(1207);
    this->setFixedWidth(942);
    button2->setChecked(true);
    ui->pushButton_graf->setEnabled(false);
    ui->pushButton_credit->setEnabled(false);
    ui->label_x->setVisible(false);
    ui->itog_x->setVisible(false);
    vid_depos();      // показать депозитный
    no_vid_graf();    // скрыть граф
    no_vid_credit();  //скрыть кредитный
    ui->itog->setText("0");
  } else {
    this->setFixedWidth(430);
    this->setFixedHeight(711);
    ui->pushButton_graf->setEnabled(true);
    ui->pushButton_credit->setEnabled(true);
    no_vid_depos();  // скрыть все, что связано с депозитом
    vid_graf();  //показать все, что связано с графом
    vid_credit();  // показать кредитный
    button2->setChecked(false);
    ui->itog->setText("0");
  }
}

void MainWindow::on_replenish_clicked() {
  if (ui->replenish->isChecked()) {
    ui->popoln->setVisible(true);
  } else
    ui->popoln->setVisible(false);
}

void MainWindow::on_withdrawals_clicked() {
  if (ui->withdrawals->isChecked()) {
    ui->snyt->setVisible(true);
  } else
    ui->snyt->setVisible(false);
}
void MainWindow::vid_credit() {
  ui->label_sum_credit->setVisible(true);
  ui->label_all_time->setVisible(true);
  ui->label_percent_year->setVisible(true);
  ui->totalSumCredit->setVisible(true);
  ui->allTime->setVisible(true);
  ui->yearPercent->setVisible(true);
  ui->annuity->setVisible(true);
  ui->differentiated->setVisible(true);
  ui->monthlyPayment->setVisible(true);
  ui->label_monthle_payment->setVisible(true);
  ui->overpayment->setVisible(true);
  ui->label_over_payment->setVisible(true);
  ui->label_total_payment->setVisible(true);
  ui->totalPayment->setVisible(true);
  ui->result->setVisible(true);
  ui->clear_credit->setVisible(true);
}

void MainWindow::vid_depos() {
  ui->label_total_payment_percent->setVisible(true);
  ui->totalPayment_percent->setVisible(true);
  ui->total_sum->setVisible(true);
  ui->label_sum_tax->setVisible(true);
  ui->sum_tax->setVisible(true);
  ui->result_depos->setVisible(true);
  ui->capitaliz->setVisible(true);
  ui->withdrawals->setVisible(true);
  ui->replenish->setVisible(true);
  ui->month->setVisible(true);
  ui->year->setVisible(true);
  ui->label_perio_paymen->setVisible(true);
  ui->label_percent_tax->setVisible(true);
  ui->percent_tax->setVisible(true);
  ui->yearPercentDep->setVisible(true);
  ui->label_percent_year_dep->setVisible(true);
  ui->PeriodDep->setVisible(true);
  ui->label_period->setVisible(true);
  ui->label_sum_total_sum->setVisible(true);
  ui->totalSumDep->setVisible(true);
  ui->label_total_sum->setVisible(true);
  ui->clear_depos->setVisible(true);
}

void MainWindow::vid_graf() {
  ui->Graf->setVisible(true);
  ui->label_y_max->setVisible(true);
  ui->label_x_max->setVisible(true);
  ui->label_y_min->setVisible(true);
  ui->label_x_min->setVisible(true);
  ui->xmin_graf->setVisible(true);
  ui->xmax_graf->setVisible(true);
  ui->pushButton_clear_graf->setVisible(true);
  ui->pushButton_new_graf->setVisible(true);
  ui->ymin_graf->setVisible(true);
  ui->ymax_graf->setVisible(true);
}

void MainWindow::no_vid_credit() {
  ui->label_sum_credit->setVisible(false);
  ui->label_all_time->setVisible(false);
  ui->label_percent_year->setVisible(false);
  ui->totalSumCredit->setVisible(false);
  ui->allTime->setVisible(false);
  ui->yearPercent->setVisible(false);
  ui->annuity->setVisible(false);
  ui->differentiated->setVisible(false);
  ui->monthlyPayment->setVisible(false);
  ui->label_monthle_payment->setVisible(false);
  ui->overpayment->setVisible(false);
  ui->label_over_payment->setVisible(false);
  ui->label_total_payment->setVisible(false);
  ui->totalPayment->setVisible(false);
  ui->result->setVisible(false);
  ui->clear_credit->setVisible(false);
}

void MainWindow::no_vid_graf() {
  ui->Graf->setVisible(false);
  ui->label_y_max->setVisible(false);
  ui->label_x_max->setVisible(false);
  ui->label_y_min->setVisible(false);
  ui->label_x_min->setVisible(false);
  ui->xmin_graf->setVisible(false);
  ui->xmax_graf->setVisible(false);
  ui->pushButton_clear_graf->setVisible(false);
  ui->pushButton_new_graf->setVisible(false);
  ui->ymin_graf->setVisible(false);
  ui->ymax_graf->setVisible(false);
}

void MainWindow::no_vid_depos() {
  ui->label_total_payment_percent->setVisible(false);
  ui->totalPayment_percent->setVisible(false);
  ui->total_sum->setVisible(false);
  ui->label_sum_tax->setVisible(false);
  ui->sum_tax->setVisible(false);
  ui->result_depos->setVisible(false);
  ui->capitaliz->setVisible(false);
  ui->withdrawals->setVisible(false);
  ui->snyt->setVisible(false);
  ui->popoln->setVisible(false);
  ui->replenish->setVisible(false);
  ui->month->setVisible(false);
  ui->year->setVisible(false);
  ui->label_perio_paymen->setVisible(false);
  ui->label_percent_tax->setVisible(false);
  ui->percent_tax->setVisible(false);
  ui->yearPercentDep->setVisible(false);
  ui->label_percent_year_dep->setVisible(false);
  ui->PeriodDep->setVisible(false);
  ui->label_period->setVisible(false);
  ui->label_sum_total_sum->setVisible(false);
  ui->totalSumDep->setVisible(false);
  ui->label_total_sum->setVisible(false);
  ui->clear_depos->setVisible(false);
}
