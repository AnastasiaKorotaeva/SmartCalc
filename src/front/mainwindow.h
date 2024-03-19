#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <float.h>

#include <QDoubleValidator>
#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QVector>

extern "C" {
#include "../back/calculator.h"
#include "../back/credit.h"
#include "../back/deposit.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  QDoubleValidator process_itog_x;
  QRegularExpressionValidator process_itog;
  QVector<double> x, y;

 private slots:
  void digits_numbers();
  void on_pushButton_ravn_clicked();
  void on_pushButton_delete_clicked();
  void on_pushButton_AC_clicked();
  void check_x();
  void on_pushButton_graf_clicked();
  void on_pushButton_new_graf_clicked();
  void on_pushButton_clear_graf_clicked();
  void on_pushButton_credit_clicked();
  void on_result_clicked();
  void on_clear_credit_clicked();
  void on_result_depos_clicked();
  void on_pushButton_depos_clicked();
  void vid_credit();
  void vid_graf();
  void vid_depos();
  void no_vid_depos();
  void no_vid_credit();
  void no_vid_graf();
  void on_clear_depos_clicked();
  void on_replenish_clicked();
  void on_withdrawals_clicked();
};

#endif  // MAINWINDOW_H
