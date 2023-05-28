#include "main.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Calculator w;
  w.show();
  return a.exec();
}
