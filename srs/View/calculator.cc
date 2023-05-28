#include "calculator.h"

#include <QVector>

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
}

Calculator::~Calculator() { delete ui; }

void Calculator::PrintSymbols() {
  QPushButton* button = (QPushButton*)sender();
  if (result_pressed_) ui->label->setText("");
  ui->label->setText(ui->label->text() + button->text());
  result_pressed_ = false;
}

void Calculator::PrintOperators()
{
    QPushButton* button = (QPushButton*)sender();
    ui->label->setText(ui->label->text() + button->text());
    result_pressed_ = false;
}

void Calculator::Result() {
  std::string text = ui->label->text().toStdString();
  if (cont_.IsValid(text))
    ui->label->setText(QString::fromUtf8(cont_.Result(text)));
  else
    ui->label->setText("ERROR");
  result_pressed_ = true;
}

void Calculator::Clear() { ui->label->setText(""); }

}  // namespace s21
