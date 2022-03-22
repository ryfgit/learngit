### 一、各种几何元素代码

GL_POINTS：点
GL_LINES：线段，二个点确定线段
GL_LINE_STRIP：第一个点依次连接的线段
GL_LINE_LOOP：和GL_LINE_STRIP相同，但首尾连接，形成环状
GL_POLYGON：多边形
GL_QUADS：由四个点组成一个四边形
GL_QUADS_STRIP：四边形带
GL_TRIANGLES：三角形，三个点确定
GL_TRIANGLE_STRIP：共用一个条带上的顶点的一组三角形
GL_TRIANGLE_FAN：以一个原点为中心呈扇形排列，公共相邻顶点的一组三角形

### 二、相关函数

1、在“工程文件”中加入

```
QT += opengl
```

2、QGLWidget类已经内置了对OpenGL的处理，就是通过对initializeGL()、paintGL()和resizeGL()这个三个函数实现的

initializeGL()用来初始化这个OpenGL窗口部件，可以在里面设定一些有关选项。

paintGL()是用来绘制OpenGL的窗口，只要有更新发生，就会调用这个函数

resizeGL()是用来处理窗口大小变化的

```
setGeometry( 0, 0, x, y);
```

设置窗口的位置，即左上角为(0,0)点，大小为x*y。

```
setCaption( "title" );
```

设置窗口标题

```
showFullScreen();
```

全屏显示窗口

**在void NeHeWidget::initializeGL()中**

```
 glClearColor( 0.0, 0.0, 0.0, 0.0 );
```

设置清除屏幕时所用的颜色，0.0代表最黑的情况，1.0就是最亮的情况，第一个参数是红色,第二个是绿色，第三个是蓝色，最后一个参数是Alpha值。

```
 glClearDepth( 1.0 );
```

设置深度缓存。

```
 glEnable( GL_DEPTH_TEST );
```

启用深度测试。

```
glDepthFunc( GL_LEQUAL );
```

所作深度测试的类型。

深度缓存的排序决定那个物体先画。这样就不会将一个圆形后面的正方形画到圆形上来。

**在void NeHeWidget::paintGL()中**

```
glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
```

清楚屏幕和深度缓存。

```
  glLoadIdentity();
```

重置当前的模型观察矩阵。

**在void NeHeWidget::resizeGL( int width, int height )中**

```
glViewport( 0, 0, (GLint)width, (GLint)height );
```

重置当前的视口（Viewport）。

```
  glMatrixMode( GL_PROJECTION );
```

选择投影矩阵。

```
  glLoadIdentity();
```

重置投影矩阵。

```
  gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
```

建立透视投影矩阵。

```
  glMatrixMode( GL_MODELVIEW );
```

选择模型观察矩阵。

```
  glLoadIdentity();
```

重置模型观察矩阵。

### 三、多边形绘制

用GL_TRIANGLES来创建一个三角形，GL_QUADS来创建一个四边形。

只要修改NeHeWidget类中的paintGL()函数就可以了。

```
glTranslatef( -1.5,  0.0, -6.0 );
```

glTranslatef(x, y, z)沿着 X, Y 和 Z 轴移动。在glTranslatef(x, y, z)中移动的时候，并不是相对屏幕中心移动，而是相对与当前所在的屏幕位置。

```
glBegin( GL_TRIANGLES );
```

开始绘制三角形。

```
glVertex3f(  0.0,  1.0,  0.0 );
```

确定三个点的位置

```
glEnd();
```

三角形绘制结束。

```
glBegin( GL_QUADS );
```

绘制四边形。

```
 glVertex3f( -1.0,  1.0,  0.0 );
```

确定四个点的位置

```
glEnd();
```

四边形绘制结束。

### 四、给图形上色

单调着色（Flat coloring）给多边形涂上固定的一种颜色。使用平滑着色（Smooth coloring）将三角形的三个顶点的不同颜色混合在一起，创建漂亮的色彩混合。只要修改NeHeWidget类中的paintGL()函数就可以了。

```
glColor3f( 1.0, 0.0, 0.0 );
```

括号中的三个参数依次是红、绿、蓝三色分量。取值范围可以从0.0到1.0。

我们将颜色设为红色（纯红色，无绿色，无蓝色）。

```
    glVertex3f(  0.0,  1.0,  0.0 );
```

上顶点。

其他两点类似

三角形将被填充。但是因为每个顶点有不同的颜色，因此看起来颜色从每个角喷出，并刚好在三角形的中心汇合，三种颜色相互混合。这就是平滑着色。

```
 glColor3f( 0.5, 0.5, 1.0 );
```

```
glBegin( GL_QUADS );
    glVertex3f( -1.0,  1.0,  0.0 );
    glVertex3f(  1.0,  1.0,  0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
  glEnd();
```

最后的结果是.....全蓝色的正方形。

单调着色（Flat coloring）和单调着色（Flat coloring）取决于

```
glColor3f()
```

相对于

```
glBegin()
```

的位置。

### 五、多边形旋转

在NeHeWidget类中增加两个变量来控制这两个对象的旋转。它们是浮点类型的变量，使得我们能够非常精确地旋转对象。新变量中叫做rTri的用来旋转三角形，rQuad 旋转四边形。

```
GLfloat rTri;
  GLfloat rQuad;
```

在构造函数中给rTri和rQuad赋初值，都是0.0。

**在void NeHeWidget::paintGL()中**

```
glRotatef( rTri,  0.0,  1.0,  0.0 );
```

glRotatef( Angle, Xvector, Yvector, Zvector )负责让对象绕某个轴旋转。Angle 通常是个变量代表对象转过的角度。Xvector，Yvector和Zvector三个参数则共同决定旋转轴的方向。比如( 1, 0, 0 )所描述的矢量经过X坐标轴的1个单位处并且方向向右。( -1, 0, 0 )所描述的矢量经过X坐标轴的1个单位处，但方向向左。

```
glLoadIdentity();
```

增加了另一个glLoadIdentity()调用。目的是为了重置模型观察矩阵。如果没有重置，直接调用glTranslate的话，会出现意料之外的结果。因为坐标轴已经旋转了，很可能没有朝着所希望的方向。所以本来想要左右移动对象的，就可能变成上下移动了，取决于将坐标轴旋转了多少角度。

```
glRotatef( rQuad,  1.0,  0.0,  0.0 );
```

绕X轴旋转四边形。

```
 rTri += 0.2;
  rQuad -= 0.15;
```

在构造函数中已经将rTri和rQuad的值设为0.0，在这里每绘制完一次图像，就修改一下这两个变量。两个变量的变化会使对象的旋转角度发生变化。

### 六、三维图形

三维图形即为多个二维图形所构成，倘若想使之旋转应该注意其旋转中心与图形的相对位置，保证旋转效果

