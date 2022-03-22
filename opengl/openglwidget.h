#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H
#include <QtOpenGL/QGL>
#include <QTimer>
class OpenglWidget : public QGLWidget
{
public:
    OpenglWidget(QWidget* parent = 0);

protected:
  void initializeGL();
  void initWidget();
  void paintGL();
  void resizeGL(int width, int height);
  int m_rotateTriangle=0,m_rotateRectangle =0;
};

#endif // OPENGLWIDGET_H
