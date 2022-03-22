#include "openglwidget.h"
#include "qmath.h"
OpenglWidget::OpenglWidget(QWidget* parent)
    :QGLWidget(parent)
{
    initWidget();
    initializeGL();
    QTimer *timer = new QTimer(this);                   //创建一个定时器
        //将定时器的计时信号与updateGL()绑定
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
        timer->start(10);
}
void OpenglWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OpenglWidget::initWidget()
{
    setGeometry( 400, 200, 640, 480 );
    setWindowTitle(tr("opengl demo"));
}

void OpenglWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef( -1.5,  0.0, -6.0 );
    glRotatef( m_rotateRectangle,  0.0,  1.0,  0.0 );

    glBegin( GL_QUADS );
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(  -1.0,  1.0,  0.0 );
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(  1.0,  1.0,  0.0 );
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(  1.0, -1.0,  0.0 );
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f( -1.0, -1.0,  0.0 );
    glEnd();

    glLoadIdentity();

    glTranslatef(  1.5,  0.0, -6.0 );
    glRotatef( m_rotateTriangle,  1.0,  0.0,  0.0 );

    glColor3f((GLfloat)0.3, (GLfloat)0.2, (GLfloat)0.5);
    glBegin( GL_TRIANGLES );
    glVertex3f(  0.0,  1.0,  0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glEnd();

    m_rotateRectangle += 1;
    m_rotateTriangle += 1;
}
void OpenglWidget::resizeGL(int width, int height)
{
    if(0 == height) {
        height = 1;
    }

    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

  //  gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);

    GLdouble aspectRatio = (GLfloat)width/(GLfloat)height;
    GLdouble zNear = 0.1;
    GLdouble zFar = 100.0;

    GLdouble rFov = 45.0 * 3.14159265 / 180.0;
     glFrustum( -zNear * tan( rFov / 2.0 ) * aspectRatio,
               zNear * tan( rFov / 2.0 ) * aspectRatio,
               -zNear * tan( rFov / 2.0 ),
               zNear * tan( rFov / 2.0 ),
               zNear, zFar );

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}
