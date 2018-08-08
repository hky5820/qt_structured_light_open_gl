#-------------------------------------------------
#
# Project created by QtCreator 2018-07-12T12:04:40
#
#-------------------------------------------------

QT       += core gui opengl
LIBS += -lopengl32 -lglu32 #-L/usr/local/lib -lGLU

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    glwidget.cpp \
    glad/src/glad.c

HEADERS += \
        mainwindow.h \
    glwidget.h \
    fancyslider5.h \
    fancyslider6.h \
    fancyslider7.h \
    fancyslider.h \
    fancyslider2.h \
    fancyslider3.h \
    fancyslider4.h \
    plookreset.h \
    setpandc.h \
    plookfix.h \
    stb_image.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    fshader.frag \
    vshader.vert \
    container.png
