#include "transform.h"
#include "fstream"
std::vector<coords> fileLoaderVerts(std::string filename, long *verts) {
  std::vector<coords> vect;
  std::ifstream file;
  file.open(filename);
  char c = '\0', str[2000];
  int k = -1;
  str[0] = '\0';
  if (file.is_open()) {
    while (file.get(c)) {
      if (k == -1 && c != 'v')
        for (; !file.eof() && c != '\n'; file.get(c))
          ;
      else if (k == 0 && c != ' ')
        for (str[0] = '\0', k = -1; !file.eof() && c != '\n'; file.get(c))
          ;
      else if (!file.eof() && c != '\n')
        str[++k] = c, str[k + 1] = '\0';
      else {
        coords curr;
        curr.x = curr.y = curr.z = 0;
        long i = 1;
        int num = 0;
        while (num < 3) {
          int sign = 0, point = 0;
          double integ = 0, fract = 0, total = 0;
          while (str[++i] != ' ' && str[i] != '\0') {
            if (str[i] != '.') {
              if (point == 0) {
                if (str[i] == '-')
                  sign = 1;
                else
                  integ = integ * 10 + str[i] - 48;
              } else
                fract = fract * 10 + str[i] - 48;
            } else
              point = 1;
          }
          while ((fract /= 10.0) >= 1.0)
            ;
          total = sign ? (-integ - fract) : (integ + fract);
          if (++num == 1)
            curr.x = total;
          else if (num == 2)
            curr.y = total;
          else if (num == 3)
            curr.z = total;
        }
        vect.push_back(curr);
        ++(*verts);
        str[0] = '\0', k = -1;
      }
    }
    file.close();
  }
  return vect;
}
std::vector<double> fileLoaderFaces(std::string filename, long *edges) {
  std::vector<double> arr;
  std::ifstream file;
  file.open(filename);
  char c = '\0', str[2000];
  int k = -1;
  str[0] = '\0';
  if (file.is_open()) {
    while (file.get(c)) {
      if (k == -1 && c != 'f')
        for (; !file.eof() && c != '\n'; file.get(c))
          ;
      else if (k == 0 && c != ' ')
        for (str[0] = '\0', k = -1; !file.eof() && c != '\n'; file.get(c))
          ;
      else if (!file.eof() && c != '\n')
        str[++k] = c, str[k + 1] = '\0';
      else {
        long i = 2;
        while (str[++i] != '/' && str[i] != ' ')
          ;
        if (str[i] == '/') {
          for (i = 1;
               str[i] != '\0' && !(str[i] == ' ' && str[i + 1] == '\0');) {
            long integ = 0;
            int sign = 0;
            while (str[++i] != '/') {
              if (str[i] == '-')
                sign = 1;
              else
                integ = integ * 10 + str[i] - 48;
            }
            arr.push_back(sign ? -integ : integ);
            ++(*edges);
            while (str[++i] != ' ' && str[i] != '\0')
              ;
          }
        } else {
          for (i = 1;
               str[i] != '\0' && !(str[i] == ' ' && str[i + 1] == '\0');) {
            long integ = 0;
            int sign = 0;
            while (str[++i] != ' ' && str[i] != '\0') {
              if (str[i] == '-')
                sign = 1;
              else
                integ = integ * 10 + str[i] - 48;
            }
            arr.push_back(sign ? -integ : integ);
            ++(*edges);
          }
        }

        str[0] = '\0', k = -1;
      }
    }
    file.close();
  }
  return arr;
}

double ratioDef(std::vector<coords> vect, std::vector<double> arr, long verts,
                long edges) {
  double x, y, xmin = 100000, ymin = 100000, xmax = -100000, ymax = -100000;
  for (long i = 0; i < edges; ++i) {
    if (arr[i] - 1 >= 0 && arr[i] - 1 < verts) {
      x = vect[arr[i] - 1].x;
      if (x < xmin)
        xmin = x;
      else if (x > xmax)
        xmax = x;
      y = vect[arr[i] - 1].y;
      if (y < ymin)
        ymin = y;
      else if (y > ymax)
        ymax = y;
    }
  }
  double ratio = 1 / (ymax - ymin + xmax - xmin);
  if ((ymax - ymin) / (xmax - xmin) > 4.3 ||
      (xmax - xmin) / (ymax - ymin) > 4.3)
    ratio /= 2;
  return ratio;
}
