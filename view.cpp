#include "view.h"
using namespace s21;
Vision::Vision(QWidget *parent) : QOpenGLWidget(parent) {
  vect.clear(), arr.clear();
  this->resize(1600, 1000);
  declarating();
  connect(scaler, &QSlider::valueChanged, this, &Vision::scaling);
  connect(select, &QPushButton::clicked, this, &Vision::openFile);
  connect(rFront, &QSlider::valueChanged, this, &Vision::frontPickerRed);
  connect(gFront, &QSlider::valueChanged, this, &Vision::frontPickerGreen);
  connect(bFront, &QSlider::valueChanged, this, &Vision::frontPickerBlue);
  connect(rBack, &QSlider::valueChanged, this, &Vision::backPickerRed);
  connect(gBack, &QSlider::valueChanged, this, &Vision::backPickerGreen);
  connect(bBack, &QSlider::valueChanged, this, &Vision::backPickerBlue);
  connect(circle, &QCheckBox::clicked, this, &Vision::circleShape);
  connect(square, &QCheckBox::clicked, this, &Vision::squareShape);
  connect(point, &QSlider::valueChanged, this, &Vision::vertSizing);
  connect(dashed, &QCheckBox::clicked, this, &Vision::dashedLine);
  connect(solid, &QCheckBox::clicked, this, &Vision::solidLine);
  connect(thicking, &QSlider::valueChanged, this, &Vision::lineSizing);
  connect(saving, &QPushButton::clicked, this, &Vision::save);
  connect(recovery, &QPushButton::clicked, this, &Vision::load);
  connect(bmp, &QCheckBox::clicked, this, &Vision::bmpImg);
  connect(jpeg, &QCheckBox::clicked, this, &Vision::jpegImg);
  connect(img, &QPushButton::clicked, this, &Vision::saveImage);
}
Vision::~Vision() {}
void Vision::circleShape() {
  square->setChecked(false);
  pointType = 1;
}
void Vision::squareShape() {
  circle->setChecked(false);
  pointType = 2;
}
void Vision::dashedLine() {
  solid->setChecked(false);
  lineType = 2;
}
void Vision::solidLine() {
  dashed->setChecked(false);
  lineType = 1;
}
void Vision::vertSizing() { vertexSize = point->value(); }
void Vision::lineSizing() { lineWidth = thicking->value(); }
void Vision::frontPickerRed() { red = rFront->value() / 100.0; }
void Vision::frontPickerGreen() { green = gFront->value() / 100.0; }
void Vision::frontPickerBlue() { blue = bFront->value() / 100.0; }
void Vision::backPickerRed() { r = rBack->value() / 100.0; }
void Vision::backPickerGreen() { g = gBack->value() / 100.0; }
void Vision::backPickerBlue() { b = bBack->value() / 100.0; }
void Vision::bmpImg() { pic = 0; }
void Vision::jpegImg() { pic = 1; }
void Vision::labeling(QLabel *label) {
  if (label == vertNum || label == faceNum || label == title)
    label->resize(170, 20);
  else
    label->resize(155, 20);
  label->setAlignment(Qt::AlignCenter);
  if (label != title) label->setStyleSheet("font-style:italic;");
  if (label == translate || label == rotate || label == scale || label == color || label == shape ||
      label == lineConf || label==settings || label==picture)
    label->setStyleSheet("color:lime;font-style:italic;letter-spacing:1px;font-size:16px;");
  else if (label == title)
    label->setStyleSheet("color:lime;");
  else
    label->setStyleSheet("color:lime;font-style:italic;");
}
void Vision::rotating() {
  xAngle = (double)rotateX->value();
  yAngle = (double)rotateY->value();
  zAngle = (double)rotateZ->value();
}
void Vision::translating() {
  xPos += (moveX->value() - prevX) / ratio / 400.0;
  yPos += (moveY->value() - prevY) / ratio / 350.0;
  prevX = moveX->value(), prevY = moveY->value();
}
void Vision::scalingZ() {
  scaleX += (moveZ->value() - prevZ) * ratio / 100.0;
  scaleY += (moveZ->value() - prevZ) * ratio / 100.0;
  prevZ = moveZ->value();
}
void Vision::scaling() {
  scaleX += (scaler->value() - prevScaler) * ratio / 10.0;
  scaleY += (scaler->value() - prevScaler) * ratio / 10.0;
  prevScaler = scaler->value();
}
void Vision::mousePressEvent(QMouseEvent *e) {
  if (e->buttons() == Qt::Key_Left) xPos = e->x(), yPos = e->y();
  update();
}
void Vision::mouseMoveEvent(QMouseEvent *e) {
  xAngle = 180 * (double(e->y()) - yPos) / width();
  yAngle = 180 * (double(e->x()) - xPos) / height();
  update();
}
void Vision::saveImage() {
  QImage image = grabFramebuffer();
  QString defaultFileName = QString("screenshot.%1").arg(pic ? "jpeg" : "bmp");
  QString str = QFileDialog::getSaveFileName(
      this, tr("Save image"), QDir::currentPath() + "/" + defaultFileName,
      tr("Image (*.jpeg *.bmp)"));
  if (!str.isEmpty()) {
    if (image.isNull()) {
      qDebug() << "Failed to capture image.";
    } else {
      if (image.save(str)) {
        qDebug() << "Image saved successfully.";
      } else {
        qDebug() << "Failed to save image. Check the file path and format.";
        qDebug() << "File path:" << str;
        qDebug() << "Supported formats:"
                 << QImageWriter::supportedImageFormats();
      }
    }
  }
}
