#ifndef VIEW_H
#define VIEW_H
//#include <QOpenGLWidget>
#include <QBrush>
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QRect>
#include <QSettings>
#include <QSlider>
#include <QTextStream>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>
#include <iostream>
#include <string>
#include <vector>
#include "transform.h"
namespace s21 {
class Vision : public QOpenGLWidget {
  Q_OBJECT;

 public:
  Vision(QWidget *parent = nullptr);
  ~Vision();
  QRect rect;
  std::vector<coords> vect;
  std::vector<double> arr;
  QPainter painter;
  double red, green, blue, r, g, b, scaleX, scaleY, scaleZ, ratio;
  double xPos, yPos, zPos, xAngle, yAngle, zAngle, prevX, prevY, prevZ,
      prevScaler;
  int vertexSize, lineWidth, pointType, lineType, pic;
  long verts, edges;
  QPushButton *select, *pickerBtn, *saving, *recovery, *img;
  QLabel *mX, *mY, *mZ, *rX, *rY, *rZ, *translate, *rotate, *scale, *title,
      *vertNum, *faceNum;
  QLabel *rF, *gF, *bF, *rB, *gB, *bB, *color, *shape, *lineConf, *thick, *settings, *picture;
  QSlider *moveX, *moveY, *moveZ, *rotateX, *rotateY, *rotateZ, *scaler;
  QSlider *rFront, *gFront, *bFront, *rBack, *gBack, *bBack, *thicking, *point;
  QCheckBox *circle, *square, *dashed, *solid, *bmp, *jpeg;
  // protected:
  void circleShape();
  void squareShape();
  void vertSizing();
  void lineSizing();
  void dashedLine();
  void solidLine();
  void declarating();
  void labeling(QLabel *);
  void openFile();
  void scalingZ();
  void rotating();
  void translating();
  void scaling();
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  void frontPickerRed();
  void frontPickerGreen();
  void frontPickerBlue();
  void backPickerRed();
  void backPickerGreen();
  void backPickerBlue();
  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void save();
  void load();
  void bmpImg();
  void jpegImg();
  void saveImage();
};
}  // namespace s21
#endif
