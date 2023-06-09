#include "calculator.h"

#include <QVector>
#include <algorithm>
#include <iostream>
#include <utility>

#include "./ui_calculator.h"
namespace s21 {
Calculator::Calculator(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::Calculator), result_pressed_() {
  ui->setupUi(this);
  QVector<QPushButton*>* buttons =
      new QVector<QPushButton*>{ui->pushButton_0,
                                ui->pushButton_1,
                                ui->pushButton_2,
                                ui->pushButton_3,
                                ui->pushButton_4,
                                ui->pushButton_5,
                                ui->pushButton_6,
                                ui->pushButton_7,
                                ui->pushButton_8,
                                ui->pushButton_9,
                                ui->pushButton_x,
                                ui->pushButton_sin,
                                ui->pushButton_cos,
                                ui->pushButton_tan,
                                ui->pushButton_asin,
                                ui->pushButton_acos,
                                ui->pushButton_atan,
                                ui->pushButton_close_bracket,
                                ui->pushButton_open_bracket,
                                ui->pushButton_ln,
                                ui->pushButton_log,
                                ui->pushButton_sqrt,
                                ui->pushButton_dot};
  for (auto it : *buttons) {
    connect(it, SIGNAL(clicked()), this, SLOT(PrintSymbols()));
  }
  *buttons = {ui->pushButton_plus, ui->pushButton_minus, ui->pushButton_mul,
              ui->pushButton_div,  ui->pushButton_mod,   ui->pushButton_pow};
  for (auto it : *buttons) {
    connect(it, SIGNAL(clicked()), this, SLOT(PrintOperators()));
  }
  delete buttons;
  connect(ui->pushButton_result, SIGNAL(clicked()), this, SLOT(Result()));
  connect(ui->pushButton_delete, SIGNAL(clicked()), this, SLOT(Clear()));
  connect(ui->pushButton_graphic, SIGNAL(clicked()), this, SLOT(Display()));
}

Calculator::~Calculator() { delete ui; }

void Calculator::PrintSymbols() {
  QPushButton* button = (QPushButton*)sender();
  if (result_pressed_) ui->label->setText("");
  ui->label->setText(ui->label->text() + button->text());
  result_pressed_ = false;
}

void Calculator::PrintOperators() {
  QPushButton* button = (QPushButton*)sender();
  ui->label->setText(ui->label->text() + button->text());
  result_pressed_ = false;
}

void Calculator::Result() {
  std::string text = ui->label->text().toStdString();
  std::string value = ui->lineEdit_value->text().toStdString();
  if (cont_.IsValid(text, value))
    ui->label->setText(QString::fromUtf8(cont_.Result()));
  else
    ui->label->setText("ERROR");
  result_pressed_ = true;
  ui->lineEdit_value->setText("0");
}

void Calculator::Clear() {
  ui->label->setText("");
  ui->lineEdit_value->setText("0");
}

void Calculator::Display() {
  std::pair<int, int> x_borders{ui->lineEdit_x_start->text().toInt(),
                                ui->lineEdit_x_end->text().toInt()};
  std::pair<int, int> y_borders{ui->lineEdit_y_start->text().toInt(),
                                ui->lineEdit_y_end->text().toInt()};
  std::pair<std::vector<double>, std::vector<double>> dots =
      cont_.CreateDots(ui->label->text().toStdString(), x_borders, y_borders);
  QVector<double> x_dots =
      QVector<double>{dots.first.begin(), dots.first.end()};
  QVector<double> y_dots =
      QVector<double>{dots.second.begin(), dots.second.end()};
  ui->graph->addGraph();
  ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);
  ui->graph->graph(0)->setData(x_dots, y_dots);
  ui->graph->xAxis->setLabel("x");
  ui->graph->yAxis->setLabel("y");
  ui->graph->xAxis->setRange(x_borders.first, x_borders.second);
  ui->graph->yAxis->setRange(y_borders.first, y_borders.second);
  ui->graph->replot();
  Clear();
}

}  // namespace s21
