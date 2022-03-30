#include "MyGLWidget.h"
#include "qmath.h"
MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    fullscreen = false;
    m_Light = false;
    m_Blend = false;
    m_Fog = 0;

    m_xRot = 0.0f;
    m_yRot = 0.0f;
    m_xSpeed = 0.1f;
    m_ySpeed = 0.1f;
    m_Deep = -5.0f;

    m_FileName[0] = "D:/0.jpg";        //应根据实际存放图片的路径进行修改
    m_FileName[1] = "D:/1.png";
    m_FileName[2] = "D:/2.png";
    m_FileName[3] = "D:/3.png";
    m_FileName[4] = "D:/4.jpg";
    m_FileName[5] = "D:/5.jpg";
    QTimer *timer = new QTimer(this);                   //创建一个定时器
    //将定时器的计时信号与updateGL()绑定
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer->start(10);                                   //以10ms为一个计时周期
}
MyGLWidget::~MyGLWidget()
{

}
void MyGLWidget::initializeGL()                         //此处开始对OpenGL进行所以设置
{
    m_Texture[0] = bindTexture(QPixmap(m_FileName[0]));
    m_Texture[1] = bindTexture(QPixmap(m_FileName[1]));
    m_Texture[2] = bindTexture(QPixmap(m_FileName[2]));
    m_Texture[3] = bindTexture(QPixmap(m_FileName[3]));
    m_Texture[4] = bindTexture(QPixmap(m_FileName[4]));
    m_Texture[5] = bindTexture(QPixmap(m_FileName[5]));//载入位图并转换成纹理
    glEnable(GL_TEXTURE_2D);                            //启用纹理映射

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);               //设置背景的颜色为雾气的颜色
    glShadeModel(GL_SMOOTH);                            //启用阴影平滑

    glClearDepth(1.0);                                  //设置深度缓存
    glEnable(GL_DEPTH_TEST);                            //启用深度测试
    glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正

    GLfloat LightAmbient[] = {0.5f, 0.5f, 0.5f, 1.0f};  //环境光参数
    GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  //漫散光参数
    GLfloat LightPosition[] = {0.0f, 0.0f, 2.0f, 1.0f}; //光源位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);     //设置环境光
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);     //设置漫射光
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);   //设置光源位置
    glEnable(GL_LIGHT1);                                //启动一号光源

    //下面是混合部分
    glColor4f(1.0f, 1.0f, 1.0f, 0.5f);                  //全亮度，50%Alpha混合
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);                  //基于源像素alpah通道值得半透明混合函数

    //雾部分
    GLfloat fogColor[] = {0.5f, 0.5f, 0.5f, 1.0f};      //雾的颜色
    glFogi(GL_FOG_MODE, GL_EXP);                        //设置雾气的初始模式
    glFogfv(GL_FOG_COLOR, fogColor);                    //设置雾的颜色
    glFogf(GL_FOG_DENSITY, 0.05);                       //设置雾的密度
    glHint(GL_FOG_HINT, GL_DONT_CARE);                  //设置系统如何计算雾气
    glFogf(GL_FOG_START, 1.0f);                         //雾的开始位置
    glFogf(GL_FOG_END, 5.0f);                           //雾的结束位置
    glEnable(GL_FOG);                                   //启动雾效果


}

void MyGLWidget::paintGL()                              //从这里开始进行所以的绘制
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
    glLoadIdentity();                                   //重置模型观察矩阵
    glTranslatef(0.0f, 0.0f, m_Deep);                   //移入屏幕
    glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);                //绕x轴旋转
    glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);                //绕y轴旋转

    glBindTexture(GL_TEXTURE_2D, m_Texture[0]);            //选择纹理
    glBegin(GL_QUADS);                                  //开始绘制立方体
        glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);                   //右下(顶面)
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_Texture[1]);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);                  //右上(底面)
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);                 //左上(底面)
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(底面)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(底面)
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_Texture[2]);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);                   //右上(前面)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前面)
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_Texture[3]);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);                 //右上(后面)
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);                //左上(后面)
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);                 //左下(后面)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);                  //右下(后面)
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_Texture[4]);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);                  //右上(左面)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(左面)
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左面)
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左面)
    glEnd();

    glBindTexture(GL_TEXTURE_2D, m_Texture[5]);
    glBegin(GL_QUADS);
        glNormal3f(1.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(右面)
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 1.0f);                   //左上(右面)
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右面)
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(右面)
    glEnd();                                            //立方体绘制结束

    m_xRot += m_xSpeed;                                 //x轴旋转
    m_yRot += m_ySpeed;                                 //y轴旋转
}
void MyGLWidget::resizeGL(int width, int height)
{
    if(0 == height)
    {
        height = 1;
    }

    glViewport(0, 0, (GLint)width, (GLint)height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0);

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
void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    static GLuint fogMode[] = {GL_EXP, GL_EXP2, GL_LINEAR};
    switch (event->key())
    {
    //F1为全屏和普通屏的切换键
    case Qt::Key_F1:
        fullscreen = !fullscreen;
        if (fullscreen)
        {
            showFullScreen();
        }
        else
        {
            showNormal();
        }
        updateGL();
        break;
    //ESC为退出键
    case Qt::Key_Escape:
        close();
        break;
    //B为开始关闭混合而对切换键
    case Qt::Key_B:
            m_Blend = !m_Blend;
            if (m_Blend)
            {
                glEnable(GL_BLEND);                         //开启混合
                glDisable(GL_DEPTH_TEST);                   //关闭深度测试
            }
            else
            {
                glDisable(GL_BLEND);                        //关闭混合
                glEnable(GL_DEPTH_TEST);                    //打开深度测试
            }
            break;
     //L为开启关闭光源的切换键
     case Qt::Key_L:
             m_Light = !m_Light;
             if (m_Light)
             {
                 glEnable(GL_LIGHTING);                      //开启光源
             }
             else
             {
                 glDisable(GL_LIGHTING);                     //关闭光源
             }
             break;
    case Qt::Key_G:                                     //G为雾模式的切换键
            m_Fog++;
            if (m_Fog == 3)
            {
                m_Fog = 0;
            }
            glFogi(GL_FOG_MODE, fogMode[m_Fog]);
            break;

            case Qt::Key_PageUp:                                //PageUp按下使木箱移向屏幕内部
                m_Deep -= 0.1f;
                break;
            case Qt::Key_PageDown:                              //PageDown按下使木箱移向观察者
                m_Deep += 0.1f;
                break;
            case Qt::Key_Up:                                    //Up按下减少m_xSpeed
                m_xSpeed -= 0.1f;
                break;
            case Qt::Key_Down:                                  //Down按下增加m_xSpeed
                m_xSpeed += 0.1f;
                break;
            case Qt::Key_Right:                                 //Right按下减少m_ySpeed
                m_ySpeed -= 0.1f;
                break;
            case Qt::Key_Left:                                  //Left按下增加m_ySpeed
                m_ySpeed += 0.1f;
                break;
    }
}
