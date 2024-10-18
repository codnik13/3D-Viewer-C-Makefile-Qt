#include "view.h"
using namespace s21;
#include <QApplication>
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Vision w;
  w.show();
  return a.exec();
}
