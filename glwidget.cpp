#include "glwidget.h"
#include "stb_image.h"


float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

double len = 0;
double cf = 15;
double pf = 15;
double wf = 15;

double oc[3] = {0.0, 0.0, 0.0};
double cc[3] = {0.0, 0.0, 3.0};
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

unsigned int VBO, VAO, EBO, cubeVAO, lightVAO;
int shaderProgram;
unsigned int texture;
unsigned int texture1, texture2;
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void Upvector();
void WorldUpVector();

void GLWidget::initializeGL()
{

    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    ourShader.set("C:/Users/CGLAB/Downloads/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/vshader.vert",
                     "C:/Users/CGLAB/Downloads/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/fshader.frag");
    lightingShader.set("C:/Users/CGLAB/Downloads/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/vshader.vert",
                     "C:/Users/CGLAB/Downloads/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/fshader.frag");
    lampShader.set("C:/Users/CGLAB/Downloads/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/vlamp.vert",
                   "C:/Users/CGLAB/Downloads/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/flamp.frag");


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load("C:/Users/CGLAB/Downloads/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load("C:/Users/CGLAB/Downloads/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/qt_structured_light_open_gl-GLSL_Container_And_Smile_Texture_OK/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
}

void GLWidget::paintGL()
{
    initializeOpenGLFunctions();

    double tt = sqrtf(powf(world_look_vector[0],2) + powf(world_look_vector[1],2) + powf(world_look_vector[2],2));

    GLWidget::camera_fov = cf;
    GLWidget::projector_fov = pf;
    GLWidget::world_fov = wf;
    GLWidget::l = le / 150.0;
    GLWidget::u = upp / 150.0;
    GLWidget::length = len;
    int w = GLWidget::width;
    int h = GLWidget::height;
    Upvector();
    WorldUpVector();


    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glViewport(0,h/2,w/2,h/2);

    model = glm::mat4();
    view = glm::mat4();
    projection = glm::mat4();

    qDebug() << GLWidget::camera_fov;
    view  = glm::lookAt(glm::vec3(cc[0],cc[1],cc[2]), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(camera_up_vector[0], camera_up_vector[1], camera_up_vector[2]));
    view = glm::rotate(view, (float)glm::radians(rot_set), glm::vec3(camera_up_vector[0], camera_up_vector[1], camera_up_vector[2]));
    projection = glm::perspective(glm::radians((float)GLWidget::camera_fov), (float)w/ (float)h, 0.1f, 100.0f);
    ourShader.setMat4("model",model);
    ourShader.setMat4("view",view);
    ourShader.setMat4("projection", projection);

    // render box
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glViewport(w/2, h/2, w/2, h/2);
    model = glm::mat4();
    view = glm::mat4();
    projection = glm::mat4();

    glm::vec3 eye_position(cc[0]-v[0] * GLWidget::length, cc[1], cc[2]-v[2] * GLWidget::length);
    glm::vec3 eye_look(-v[0] * GLWidget::length, 0.0, -v[2] * GLWidget::length);

    view = glm::lookAt(eye_position, eye_look, glm::vec3(camera_up_vector[0], camera_up_vector[1], camera_up_vector[2]));
    projection = glm::perspective(glm::radians((float)GLWidget::projector_fov), (float)w/ (float)h, 0.1f, 100.0f);

    ourShader.setMat4("model",model);
    ourShader.setMat4("view",view);
    ourShader.setMat4("projection", projection);

    // render box
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

//    glViewport(0,0,w/2,h/2);
//    eye_position.x =


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);
}




void GLWidget::resizeGL(int w, int h)
{
    GLWidget::width = w;
    GLWidget::height = h;
}

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



GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

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
    setValue(100);
}

FancySlider2::FancySlider2(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider2::sliderChange(QAbstractSlider::SliderChange change)
{
    cf = value()/ (double)99 * 44 + 1;
}


FancySlider3::FancySlider3(QWidget * parent)
    : QSlider(parent)
{
    setValue(100);
}

FancySlider3::FancySlider3(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider3::sliderChange(QAbstractSlider::SliderChange change)
{
    pf = value()/ (double)99 * 44 + 1;
}

FancySlider4::FancySlider4(QWidget * parent)
    : QSlider(parent)
{
    setValue(100);
}

FancySlider4::FancySlider4(Qt::Orientation orientation, QWidget * parent)
    : QSlider(orientation, parent)
{
}

void FancySlider4::sliderChange(QAbstractSlider::SliderChange change)
{
    wf = value()/ (double)99 * 44 + 1;
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
/*

GLfloat MyVertices[8][3] = {{-0.25,-0.25,0.25}, {-0.25,0.25,0.25},{0.25,0.25,0.25},{0.25,-0.25,0.25}
                            ,{-0.25,-0.25,-0.25},{-0.25,0.25,-0.25},{0.25,0.25,-0.25},{0.25,-0.25,-0.25}};

GLfloat MyColors[8][3] = {{0.2,0.2,0.2},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0}
                          ,{0.0,0.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0},{0.0,1.0,1.0}};

GLubyte MyVertexList[24] = {0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4};

float vertices[] = {
    -0.25,-0.25,0.25,  0.2, 0.2, 0.2,
    -0.25,0.25,0.25,   1.0, 0.0, 0.0,
    0.25,0.25,0.25,    1.0, 1.0, 0.0,
    0.25,-0.25,0.25,   0.0, 1.0, 0.0,
    -0.25,-0.25,-0.25, 0.0, 0.0, 1.0,
    -0.25,0.25,-0.25,  1.0, 0.0, 1.0,
    0.25,0.25,-0.25,   1.0, 1.0, 1.0,
    0.25,-0.25,-0.25,  0.0, 1.0, 1.0
};

float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top

};

unsigned int indices[]{
    0,1,3,
    1,2,3,
    2,6,3,
    6,7,3,
    0,4,3,
    4,7,3,
    1,5,2,
    5,6,2,
    4,7,5,
    7,6,5,
    0,4,1,
    4,5,1
};

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
*/
