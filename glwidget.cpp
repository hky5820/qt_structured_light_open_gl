#include "glwidget.h"
#include <QTextStream>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}
GLfloat MyVertices[8][3] = {{-0.25,-0.25,0.25}, {-0.25,0.25,0.25},{0.25,0.25,0.25},{0.25,-0.25,0.25}
                            ,{-0.25,-0.25,-0.25},{-0.25,0.25,-0.25},{0.25,0.25,-0.25},{0.25,-0.25,-0.25}};

GLfloat MyColors[8][3] = {{0.2,0.2,0.2},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0}
                          ,{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0}};

GLubyte MyVertexList[24] = {0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4};

double len = 0;
double cf = 15;
double pf = 15;
double wf = 15;

double oc[3] = {0.0, 0.0, 0.0};
double cc[3] = {5.0, 3.0, 0.0};
double wc[3] = {5.0, 3.0, 0.0};

double camera_look_vector[3] = {oc[0]-cc[0], oc[1]-cc[1], oc[2]-cc[2]};
double camera_up_vector[3] = {0.0, 0.0, 0.0};

double world_look_vector[3] = {oc[0]-wc[0], oc[1]-wc[1], oc[2]-wc[2]};
double world_up_vector[3] = {0.0, 0.0, 0.0};

double v[3] = {0, 0, 0};
double wv[3] = {0, 0, 0};

double le = 0;
double upp = 0;

bool p_look_reset = false;

double rot = 0;
double rot_set = 0;

bool fix_or_reset = false;


void Upvector(){

    if(abs(camera_look_vector[0]) < eps){
        v[0] = 1; v[1] = 0; v[2] = 0;
    }
    else if(abs(camera_look_vector[2]) < eps){
        v[0] = 0; v[1] = 0; v[2] = 1;
    }
    else if(abs(camera_look_vector[0]) < eps && abs(camera_look_vector[2]) < eps){
        v[0] = 0; v[1] = 0; v[2] = 0;
    }
    else{
         double z = camera_look_vector[0]/camera_look_vector[2] * -camera_look_vector[0] - camera_look_vector[2];
         v[0] = 0 - cc[0]; v[1] = 0; v[2] = z - cc[2];
    }

    camera_up_vector[0] = camera_look_vector[1] * v[2] - camera_look_vector[2] * v[1];
    camera_up_vector[1] = camera_look_vector[2] * v[0] - camera_look_vector[0] * v[2];
    camera_up_vector[2] = camera_look_vector[0] * v[1] - camera_look_vector[1] * v[0];

    double t = sqrtf(powf(v[0],2) + powf(v[1],2) + powf(v[2],2));
    v[0] = v[0] / t;
    v[1] = v[1] / t;
    v[2] = v[2] / t;
}

void WorldUpVector()
{
    if(abs(world_look_vector[0]) < eps){
        wv[0] = 1; wv[1] = 0; wv[2] = 0;
    }
    else if(abs(world_look_vector[2]) < eps){
        wv[0] = 0; wv[1] = 0; wv[2] = 1;
    }
    else if(abs(world_look_vector[0]) < eps && abs(world_look_vector[2]) < eps){
        wv[0] = 0; wv[1] = 0; wv[2] = 0;
    }
    else{
         double zz = world_look_vector[0]/world_look_vector[2] * -world_look_vector[0] - world_look_vector[2];
         wv[0] = 0 - wc[0]; wv[1] = 0; wv[2] = zz - wc[2];
    }

    world_up_vector[0] = world_look_vector[1] * v[2] - world_look_vector[2] * v[1];
    world_up_vector[1] = world_look_vector[2] * v[0] - world_look_vector[0] * v[2];
    world_up_vector[2] = world_look_vector[0] * v[1] - world_look_vector[1] * v[0];

    double ttt = sqrtf(powf(wv[0],2) + powf(wv[1],2) + powf(wv[2],2));
    wv[0] = wv[0] / ttt;
    wv[1] = wv[1] / ttt;
    wv[2] = wv[2] / ttt;
}

void DrawScene(){

    glRotatef(rot_set, 0.0, 1.0, 0.0);
    for(GLint i = 0; i< 6; i++){
        glDrawElements(GL_POLYGON,4,GL_UNSIGNED_BYTE,&MyVertexList[4*i]);
    }

    glFlush();
}

void DrawWorldScene(){

    glRotatef(rot, 0.0, 1.0, 0.0);
    for(GLint i = 0; i< 6; i++){
        glDrawElements(GL_POLYGON,4,GL_UNSIGNED_BYTE,&MyVertexList[4*i]);
    }

    glFlush();
}



void GLWidget::initializeGL()
{
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, MyColors);
    glVertexPointer(3, GL_FLOAT, 0, MyVertices);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::paintGL()
{
    double tt = sqrtf(powf(world_look_vector[0],2) + powf(world_look_vector[1],2) + powf(world_look_vector[2],2));

    GLWidget::camera_fov = cf;
    GLWidget::projector_fov = pf;
    GLWidget::world_fov = wf;
    GLWidget::l = le / 150.0;
    GLWidget::u = upp / 150.0;
    GLWidget::length = len;
    int w = GLWidget::widht;
    int h = GLWidget::height;

    Upvector();
    WorldUpVector();

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(GLWidget::camera_fov, 1.0, 0.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, h/2, w/2, h/2);
    glPushMatrix();
        gluLookAt(cc[0], cc[1], cc[2],   0.0, 0.0, 0.0,   camera_up_vector[0], camera_up_vector[1], camera_up_vector[2]);
        DrawScene();
    glPopMatrix();


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(GLWidget::projector_fov, 1.0, 0.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(w/2, h/2, w/2, h/2);
    glPushMatrix();
        gluLookAt(cc[0]-v[0] * GLWidget::length, cc[1], cc[2]-v[2] * GLWidget::length,
                 -v[0] * GLWidget::length, 0.0, -v[2] * GLWidget::length,
                camera_up_vector[0], camera_up_vector[1], camera_up_vector[2]);
        DrawScene();
    glPopMatrix();


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(GLWidget::world_fov, 1.0, 0.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w/2, h/2);
    glPushMatrix();
        gluLookAt(wc[0] + wv[0] * GLWidget::l + world_look_vector[0]/tt * GLWidget::u,
                wc[1]+ wv[1] * GLWidget::l + world_look_vector[1]/tt * GLWidget::u,
                wc[2] + wv[2] * GLWidget::l + world_look_vector[2]/tt * GLWidget::u,
                0.0 + wv[0] * GLWidget::l, 0.0 + wv[1] * GLWidget::l, 0.0 + wv[2] * GLWidget::l ,
                world_up_vector[0], world_up_vector[1], world_up_vector[2]);
        DrawWorldScene();
    glPopMatrix();




    glViewport(0, 0, w, h);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(-1, 0, 0);
        glVertex3f(1, 0, 0);
    glEnd();
    glBegin(GL_LINES);
        glVertex3f(0, -1, 0);
        glVertex3f(0, 1, 0);
    glEnd();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);
}

void GLWidget::resizeGL(int w, int h)
{
    GLWidget::widht = w;
    GLWidget::height = h;
}


FancySlider::FancySlider(QWidget * parent)
    : QSlider(parent)
{
    setValue(50);
}
FancySlider::FancySlider(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider::sliderChange(QAbstractSlider::SliderChange change)
{
    len = (double)value()/ (double)50;
}



FancySlider2::FancySlider2(QWidget * parent)
    : QSlider(parent)
{
}

FancySlider2::FancySlider2(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider2::sliderChange(QAbstractSlider::SliderChange change)
{
    cf = value()/ (double)99 * 25 + 15;
}


FancySlider3::FancySlider3(QWidget * parent)
    : QSlider(parent)
{
}

FancySlider3::FancySlider3(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider3::sliderChange(QAbstractSlider::SliderChange change)
{
    pf = value()/ (double)99 * 25 + 15;
}

FancySlider4::FancySlider4(QWidget * parent)
    : QSlider(parent)
{
}

FancySlider4::FancySlider4(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider4::sliderChange(QAbstractSlider::SliderChange change)
{
    wf = value()/ (double)99 * 25 + 15;
}


FancySlider5::FancySlider5(QWidget * parent)
    : QSlider(parent)
{
    setValue(50);
}

FancySlider5::FancySlider5(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider5::sliderChange(QAbstractSlider::SliderChange change)
{
     le = (value() - 50) * 3.0;
}


FancySlider6::FancySlider6(QWidget * parent)
    : QSlider(parent)
{
    setValue(50);
}

FancySlider6::FancySlider6(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider6::sliderChange(QAbstractSlider::SliderChange change)
{
    upp = (value() - 50) * 5.0;
}


FancySlider7::FancySlider7(QWidget * parent)
    : QSlider(parent)
{
    setValue(0);
}

FancySlider7::FancySlider7(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider7::sliderChange(QAbstractSlider::SliderChange change)
{

    rot = value() / 99.0 * 360.0;
}




SetPandC::SetPandC(QWidget * parent) : QPushButton( parent)
{
}

void SetPandC::mousePressEvent(QMouseEvent *event){
    double tt = sqrtf(powf(world_look_vector[0],2) + powf(world_look_vector[1],2) + powf(world_look_vector[2],2));
    cc[0] = wc[0] + wv[0] * le/150.0 + world_look_vector[0]/tt * upp/150.0;
    cc[1] = wc[1] + wv[1] * le/150.0 + world_look_vector[1]/tt * upp/150.0;
    cc[2] = wc[2] + wv[2] * le/150.0 + world_look_vector[2]/tt * upp/150.0;

    rot_set = rot;
}

PLookFix::PLookFix(QWidget * parent) : QPushButton( parent)
{
    
}

void PLookFix::mousePressEvent(QMouseEvent *event){

}

PLookReset::PLookReset(QWidget * parent) : QPushButton( parent)
{
}

void PLookReset::mousePressEvent(QMouseEvent *event){

}


//PushRight::PushRight(QWidget * parent) : QPushButton( parent)
//{
//}

//void PushRight::mousePressEvent(QMouseEvent *event){
//    le++;
//    qDebug() << "left = "<< le;
//}

//PushDown::PushDown(QWidget * parent) : QPushButton( parent)
//{
//}

//void PushDown::mousePressEvent(QMouseEvent *event){
//    upp--;

//   // qDebug() << "down = "<< d;
//}


