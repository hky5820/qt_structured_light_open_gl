#ifndef GLWIDGET_H
#define GLWIDGET_H

#define eps 1e-6

#include <QObject>
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <QSlider>
#include <QTimer>
#include <QWidget>
#include <QtWidgets>
//#include <QPushButton>
#include "fancyslider5.h"
#include "fancyslider6.h"
#include "fancyslider7.h"
#include <QOpenGLShaderProgram>
#include "square.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    int widht, height;

    double length; // Length Between Camera and Projector

    double camera_fov;
    double projector_fov;
    double world_fov;

    double l, u;

    Square *m_square;
    QOpenGLShaderProgram m_program;

    int m_vertexAttr;
    int m_colorAttr;
    int m_matrixUniform;
};

class FancySlider : public QSlider
{
    Q_OBJECT
public:
    explicit FancySlider(QWidget *parent = 0);
    explicit FancySlider(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    virtual void sliderChange(SliderChange change);
};

class FancySlider2 : public QSlider
{
    Q_OBJECT
public:
    explicit FancySlider2(QWidget *parent = 0);
    explicit FancySlider2(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    virtual void sliderChange(SliderChange change);
};

class FancySlider3 : public QSlider
{
    Q_OBJECT
public:
    explicit FancySlider3(QWidget *parent = 0);
    explicit FancySlider3(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    virtual void sliderChange(SliderChange change);
};

class FancySlider4 : public QSlider
{
    Q_OBJECT
public:
    explicit FancySlider4(QWidget *parent = 0);
    explicit FancySlider4(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    virtual void sliderChange(SliderChange change);
};

class FancySlider5 : public QSlider
{
    Q_OBJECT
public:
    explicit FancySlider5(QWidget *parent = 0);
    explicit FancySlider5(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    virtual void sliderChange(SliderChange change);
};


class FancySlider6 : public QSlider
{
    Q_OBJECT
public:
    explicit FancySlider6(QWidget *parent = 0);
    explicit FancySlider6(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    virtual void sliderChange(SliderChange change);
};


class FancySlider7 : public QSlider
{
    Q_OBJECT
public:
    explicit FancySlider7(QWidget *parent = 0);
    explicit FancySlider7(Qt::Orientation orientation, QWidget *parent = 0);

protected:
    virtual void sliderChange(SliderChange change);
};





class SetPandC : public QPushButton
{
    Q_OBJECT //don't forget this macro, or your signals/slots won't work

public:
   SetPandC(QWidget * parent = 0);
    bool a = false;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

class PLookFix : public QPushButton
{
    Q_OBJECT //don't forget this macro, or your signals/slots won't work

public:
    PLookFix(QWidget * parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
};


class PLookReset : public QPushButton
{
    Q_OBJECT //don't forget this macro, or your signals/slots won't work

public:
    PLookReset(QWidget * parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent *event);
};




//class PushUp : public QPushButton
//{
//    Q_OBJECT //don't forget this macro, or your signals/slots won't work

//public:
//    PushUp(QWidget * parent = 0);
//    bool a = false;

//protected:
//    virtual void mousePressEvent(QMouseEvent *event);
//};

//class PushRight : public QPushButton
//{
//    Q_OBJECT //don't forget this macro, or your signals/slots won't work

//public:
//    PushRight(QWidget * parent = 0);
//    bool a = false;

//protected:
//    virtual void mousePressEvent(QMouseEvent *event);
//};

//class PushDown : public QPushButton
//{
//    Q_OBJECT //don't forget this macro, or your signals/slots won't work

//public:
//    PushDown(QWidget * parent = 0);
//    bool a = false;

//protected:
//    virtual void mousePressEvent(QMouseEvent *event);
//};


#endif // GLWIDGET_H
