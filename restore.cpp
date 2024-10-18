#include "view.h"
using namespace s21;
void Vision::save() {
  QSettings settings("", "3DViewer");
  settings.setValue("back_red", red);
  settings.setValue("back_green", green);
  settings.setValue("back_blue", blue);
  settings.setValue("front_red", r);
  settings.setValue("front_green", g);
  settings.setValue("front_blue", b);
  settings.setValue("line_width", lineWidth);
  settings.setValue("point_size", vertexSize);
  settings.setValue("line_type", lineType);
  settings.setValue("point_type", pointType);
}
void Vision::load() {
  QSettings settings("", "3DViewer");
  red = settings.value("back_red", 1.0).toDouble();
  green = settings.value("back_green", 1.0).toDouble();
  blue = settings.value("back_blue", 1.0).toDouble();
  r = settings.value("front_red", 1.0).toDouble();
  g = settings.value("front_green", 1.0).toDouble();
  b = settings.value("front_blue", 1.0).toDouble();
  lineType = settings.value("line_type", 0).toInt();
  pointType = settings.value("point_type", 0).toInt();
  lineWidth = settings.value("line_width", 1.0).toDouble();
  vertexSize = settings.value("point_size", 1.0).toDouble();
  thicking->setValue(lineWidth), point->setValue(vertexSize);
  if (lineType==2) {
    dashed->setChecked(true);
    solid->setChecked(false);
  } else if(lineType==1){
    dashed->setChecked(false);
    solid->setChecked(true);
  }else {
      dashed->setChecked(false);
      solid->setChecked(false);
    }
  if (pointType == 1) {
    circle->setChecked(true);
    square->setChecked(false);
  } else if (pointType == 2) {
    circle->setChecked(false);
    square->setChecked(true);
  } else {
    circle->setChecked(false);
    square->setChecked(false);
  }
}
