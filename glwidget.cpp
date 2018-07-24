#include "glwidget.h"
#include "square.h"
#include <QTextStream>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
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
    glClearColor(1.0, 1.0, 1.0, 1.0);

//    glEnableClientState(GL_COLOR_ARRAY);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glColorPointer(3, GL_FLOAT, 0, MyColors);
//    glVertexPointer(3, GL_FLOAT, 0, MyVertices);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile("C:/Users/CGLAB/Desktop/test/OpenGL/vshader.glsl");

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile("C:/Users/CGLAB/Desktop/test/OpenGL/fshader.glsl");

    m_program.addShader(&vShader);
    m_program.addShader(&fShader);

    if(!m_program.link()){
        qWarning( " Error : unable to link a shader program.");
        return;
    }

    m_vertexAttr = m_program.attributeLocation( "vertexAttr");
    m_colorAttr = m_program.attributeLocation("colorAttr");
    m_matrixUniform = m_program.uniformLocation("matrix");

    m_square = new Square(&m_program, m_vertexAttr, m_colorAttr);
}

void GLWidget::paintGL()
{
    if(!m_program.bind()){
        qWarning( " Bind Error.");
        return;
    }

    int w = GLWidget::widht;
    int h = GLWidget::height;
    GLWidget::camera_fov = cf;
    GLWidget::projector_fov = pf;
    GLWidget::world_fov = wf;
    GLWidget::l = le / 150.0;
    GLWidget::u = upp / 150.0;
    GLWidget::length = len;
    double tt = sqrtf(powf(world_look_vector[0],2) + powf(world_look_vector[1],2) + powf(world_look_vector[2],2));
    Upvector();
    WorldUpVector();


    glClear(GL_COLOR_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.perspective(GLWidget::camera_fov, 1.0, 0.0, 10.0);
    glViewport(0, h/2, w/2, h/2);

    QVector3D eye(cc[0],cc[1],cc[2]);
    QVector3D center(0.0,0.0,0.0);
    QVector3D up(camera_up_vector[0],camera_up_vector[1],camera_up_vector[2]);
    matrix.lookAt(eye,center,up);

    matrix.rotate(rot_set, 0,1,0);
    m_program.setUniformValue(m_matrixUniform, matrix);
    m_square->draw();

    matrix.setToIdentity();
    if(!matrix.isIdentity()){
        qWarning("1st matrix is not identity");
    }



    matrix.perspective(GLWidget::projector_fov, 1.0, 0.0, 10.0);
    glViewport(w/2, h/2, w/2, h/2);
    eye.setX(cc[0]-v[0] * GLWidget::length); eye.setY(cc[1]); eye.setZ(cc[2]-v[2] * GLWidget::length);
    center.setX(-v[0] * GLWidget::length); center.setY(0.0); center.setZ(-v[2] * GLWidget::length);

    matrix.lookAt(eye,center,up);
    matrix.rotate(rot_set, 0,1,0);
    m_program.setUniformValue(m_matrixUniform, matrix);
    m_square->draw();


    matrix.setToIdentity();
    if(!matrix.isIdentity()){
        qWarning("2nd matrix is not identity");
    }



    matrix.perspective(GLWidget::world_fov, 1.0, 0.0, 10.0);
    glViewport(0, 0, w/2, h/2);
    eye.setX(wc[0] + wv[0] * GLWidget::l + world_look_vector[0]/tt * GLWidget::u);
    eye.setY(wc[1]+ wv[1] * GLWidget::l + world_look_vector[1]/tt * GLWidget::u);
    eye.setZ(wc[2] + wv[2] * GLWidget::l + world_look_vector[2]/tt * GLWidget::u);
    center.setX(0.0 + wv[0] * GLWidget::l);
    center.setY(0.0 + wv[1] * GLWidget::l);
    center.setZ(0.0 + wv[2] * GLWidget::l);
    up.setX(world_up_vector[0]);
    up.setY(world_up_vector[1]);
    up.setZ(world_up_vector[2]);
    matrix.lookAt(eye,center,up);

    matrix.rotate(rot,0,1,0);
    m_program.setUniformValue(m_matrixUniform, matrix);
    m_square->draw();


    m_program.release();


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

Square::Square(QOpenGLShaderProgram *program,
               int vertexAttr, int colorAttr) :
m_program( program ),
m_vertexAttr( vertexAttr ),
m_colorAttr( colorAttr )
{
   initVertices();
   initColors();
   initList();
}

void Square::draw(){
    m_program->setAttributeArray( m_vertexAttr, m_vertices.data(), 3 );
    m_program->setAttributeArray( m_colorAttr, m_colors.data(), 3 );

    m_program->enableAttributeArray( m_vertexAttr );
    m_program->enableAttributeArray( m_colorAttr );

    for(GLint i = 0; i< 6; i++){
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &m_vertex_list[4*i]);
    }

    m_program->disableAttributeArray( m_vertexAttr );
    m_program->disableAttributeArray( m_colorAttr );
}

void Square::initVertices(){

    m_vertices.resize(24);

    m_vertices[0] = -0.25;
    m_vertices[1] = -0.25;
    m_vertices[2] = 0.25;

    m_vertices[3] = -0.25;
    m_vertices[4] = 0.25;
    m_vertices[5] = 0.25;

    m_vertices[6] = 0.25;
    m_vertices[7] = 0.25;
    m_vertices[8] = 0.25;

    m_vertices[9] = 0.25;
    m_vertices[10] = -0.25;
    m_vertices[11] = 0.25;

    m_vertices[12] = -0.25;
    m_vertices[13] = -0.25;
    m_vertices[14] = -0.25;

    m_vertices[15] = -0.25;
    m_vertices[16] = 0.25;
    m_vertices[17] = -0.25;

    m_vertices[18] = 0.25;
    m_vertices[19] = 0.25;
    m_vertices[20] = -0.25;

    m_vertices[21] = 0.25;
    m_vertices[22] = -0.25;
    m_vertices[23] = -0.25;
}

void Square::initColors(){

    m_colors.resize(24);

    m_colors[0] = 0.2;
    m_colors[1] = 0.2;
    m_colors[2] = 0.2;

    m_colors[3] = 1.0;
    m_colors[4] = 0.0;
    m_colors[5] = 0.0;

    m_colors[6] = 1.0;
    m_colors[7] = 1.0;
    m_colors[8] = 0.0;

    m_colors[9]   = 0.0;
    m_colors[10]  = 1.0;
    m_colors[11]  = 0.0;

    m_colors[12]  = 0.0;
    m_colors[13]  = 0.0;
    m_colors[14]  = 1.0;

    m_colors[15]  = 1.0;
    m_colors[16]  = 0.0;
    m_colors[17]  = 1.0;

    m_colors[18]  = 1.0;
    m_colors[19]  = 1.0;
    m_colors[20]  = 1.0;

    m_colors[21]  = 0.0;
    m_colors[22]  = 1.0;
    m_colors[23]  = 1.0;
}

void Square::initList(){

    m_vertex_list.resize(24);

    m_vertex_list[0] = 0;
    m_vertex_list[1] = 3;
    m_vertex_list[2] = 2;
    m_vertex_list[3] = 1;

    m_vertex_list[4] = 2;
    m_vertex_list[5] = 3;
    m_vertex_list[6] = 7;
    m_vertex_list[7] = 6;

    m_vertex_list[8] = 0;
    m_vertex_list[9] = 4;
    m_vertex_list[10] = 7;
    m_vertex_list[11] = 3;

    m_vertex_list[12] = 1;
    m_vertex_list[13] = 2;
    m_vertex_list[14] = 6;
    m_vertex_list[15] = 5;

    m_vertex_list[16] = 4;
    m_vertex_list[17] = 5;
    m_vertex_list[18] = 6;
    m_vertex_list[19] = 7;

    m_vertex_list[20] = 0;
    m_vertex_list[21] = 1;
    m_vertex_list[22] = 5;
    m_vertex_list[23] = 4;
}











FancySlider::FancySlider(QWidget * parent)
    : QSlider(parent)
{
    setValue(50);
}
void FancySlider::sliderChange(QAbstractSlider::SliderChange change)
{
    len = (double)value()/ (double)50;
}


FancySlider2::FancySlider2(QWidget * parent)
    : QSlider(parent)
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
void FancySlider3::sliderChange(QAbstractSlider::SliderChange change)
{
    pf = value()/ (double)99 * 25 + 15;
}


FancySlider4::FancySlider4(QWidget * parent)
    : QSlider(parent)
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
void FancySlider5::sliderChange(QAbstractSlider::SliderChange change)
{
     le = (value() - 50) * 3.0;
}


FancySlider6::FancySlider6(QWidget * parent)
    : QSlider(parent)
{
    setValue(50);
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
void FancySlider7::sliderChange(QAbstractSlider::SliderChange change)
{

    rot = value() / 99.0 * 360.0;
}


void SetPandC::mousePressEvent(QMouseEvent *event){
    double tt = sqrtf(powf(world_look_vector[0],2) + powf(world_look_vector[1],2) + powf(world_look_vector[2],2));
    cc[0] = wc[0] + wv[0] * le/150.0 + world_look_vector[0]/tt * upp/150.0;
    cc[1] = wc[1] + wv[1] * le/150.0 + world_look_vector[1]/tt * upp/150.0;
    cc[2] = wc[2] + wv[2] * le/150.0 + world_look_vector[2]/tt * upp/150.0;

    rot_set = rot;
}

void PLookFix::mousePressEvent(QMouseEvent *event){

}

void PLookReset::mousePressEvent(QMouseEvent *event){

}
