#include <QApplication>

#include "frontend/consoleview.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ConsoleView w;
  w.show();
  return a.exec();
}
