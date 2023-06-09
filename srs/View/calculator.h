#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

#include "../Controller/controller.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

namespace s21 {
class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();

 private:
  Ui::Calculator *ui;
  s21::Controller cont_;
  bool result_pressed_;

 private slots:
  void PrintSymbols();
  void PrintOperators();
  void Result();
  void Clear();
  void Display();
};
}  // namespace s21
#endif  // VIEW_H
