#include "view.h"
using namespace s21;
void Vision::openFile() {
  this->hide();
  initializeGL();
  QString filename =
      QFileDialog::getOpenFileName(this, nullptr, QDir::currentPath(), "*.obj");
  title->setText((filename.split('/'))[6]);
  vect = fileLoaderVerts(filename.toStdString(), &verts);
  arr = fileLoaderFaces(filename.toStdString(), &edges);
  ratio = ratioDef(vect, arr, verts, edges);
  scaleX = scaleY = (ratio < 1 ? ratio : 1),
  scaler->setValue(ratio < 1 ? ratio : 1);
  QString vert = "vertices: ";
  vertNum->setText(vert.append(QString::fromStdString(std::to_string(verts))));
  QString face = "edges: ";
  faceNum->setText(face.append(QString::fromStdString(std::to_string(edges))));
  this->show();
  this->grab().save("img.bmp");
}
void Vision::initializeGL() {
  vect.clear(), arr.clear();
  glDisable(GL_POINT_SMOOTH);
  glDisable(GL_POINT_SPRITE);
  glDisable(GL_LINE_STIPPLE);
  rFront->setValue(10), gFront->setValue(10), bFront->setValue(10);
  rBack->setValue(0), gBack->setValue(0), bBack->setValue(0);
  moveY->setValue(0), moveX->setValue(0), moveZ->setValue(0), scaleZ = 0;
  rotateY->setValue(0), rotateX->setValue(0), rotateZ->setValue(0);
  thicking->setValue(0), point->setValue(0);
  ratio = red = green = blue = 1;
  r = g = b = 0;
  lineType=vertexSize=pointType=lineWidth = 1;
  pic=0;
  prevX = prevY = prevZ = prevScaler = xPos = yPos = zPos = xAngle = yAngle =
      zAngle = verts = edges = scaleZ = 0;
  circle->setChecked(true);
  square->setChecked(false);
  solid->setChecked(true);
  dashed->setChecked(false);
  bmp->setChecked(true);
  jpeg->setChecked(false);
}
