#include "view.h"
using namespace s21;
void Vision::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, 0, 0);
  if (pic)
    bmp->setChecked(false);
  else jpeg->setChecked(false);
  painter.begin(this);
  painter.setOpacity(0.3);
  painter.fillRect(width() - 180, 0, 180, height(), Qt::darkGray);
  painter.end();
  glScalef(scaleX, scaleY, scaleZ);
  glTranslatef(xPos, yPos, zPos);
  glRotatef(xAngle, 1, 0, 0);
  glRotatef(yAngle, 0, 1, 0);
  glRotatef(zAngle, 0, 0, 1);
  double x, y, z;
  if (dashed->isChecked() || solid->isChecked()) {
    glLineWidth(lineWidth);
    glClearColor(r, g, b, 0);
    glColor3f(red, green, blue);
    if (lineType==2) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(10, 10);
    } else
      glDisable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_STRIP);
    if (!vect.empty() && !arr.empty())
      for (long i = 0; i < edges; ++i) {
        if (arr[i] - 1 >= 0 && arr[i] - 1 < verts) {
          x = vect[arr[i] - 1].x;
          y = vect[arr[i] - 1].y;
          z = vect[arr[i] - 1].z;
          glVertex3f(x, y, z);
        }
      }
    glEnd();
  }
  else{
      thicking->setValue(0);
      lineWidth=1, lineType=0;
  }
  if(circle->isChecked() || square->isChecked()) {
    glPointSize(vertexSize);
    glClearColor(r, g, b, 0);
    glColor3f(red, green, blue);
    if (pointType==1) {
      glDisable(GL_POINT_SPRITE);
      glEnable(GL_POINT_SMOOTH);
    } else {
      glEnable(GL_POINT_SPRITE);
      glDisable(GL_POINT_SMOOTH);
    }
    glBegin(GL_POINTS);
    if (!vect.empty() && !arr.empty())
      for (long i = 0; i < edges; ++i) {
        if (arr[i] - 1 >= 0 && arr[i] - 1 < verts) {
          x = vect[arr[i] - 1].x;
          y = vect[arr[i] - 1].y;
          z = vect[arr[i] - 1].z;
          glVertex3f(x, y, z);
        }
      }
    glEnd();
  } else {
    point->setValue(0);
    vertexSize=1, pointType=0;
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_POINT_SPRITE);
  }
  update();
}
