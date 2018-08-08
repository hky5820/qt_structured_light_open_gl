#ifndef GLWIDGET_H
#define GLWIDGET_H

#define STB_IMAGE_IMPLEMENTATION
#define eps 1e-6

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <QTextStream>
#include <QDebug>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <QObject>
#include <QOpenGLWidget>
#include <GL/glu.h>
#include <QSlider>
#include <QTimer>
#include <QWidget>
#include <QtWidgets>
#include <QOpenGLExtraFunctions>

class Shader : protected QOpenGLExtraFunctions
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
        {
        initializeOpenGLFunctions();

            // 1. retrieve the vertex/fragment source code from filePath
            std::string vertexCode;
            std::string fragmentCode;
            std::string geometryCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            std::ifstream gShaderFile;
            // ensure ifstream objects can throw exceptions:
            vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                // open files
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                // read file's buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                // close file handlers
                vShaderFile.close();
                fShaderFile.close();
                // convert stream into string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
                // if geometry shader path is present, also load a geometry shader
                if(geometryPath != nullptr)
                {
                    gShaderFile.open(geometryPath);
                    std::stringstream gShaderStream;
                    gShaderStream << gShaderFile.rdbuf();
                    gShaderFile.close();
                    geometryCode = gShaderStream.str();
                }
            }
            catch (std::ifstream::failure e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            }
            const char* vShaderCode = vertexCode.c_str();
            const char * fShaderCode = fragmentCode.c_str();
            // 2. compile shaders
            unsigned int vertex, fragment;
            int success;
            char infoLog[512];
            // vertex shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            checkCompileErrors(vertex, "VERTEX");
            // fragment Shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            checkCompileErrors(fragment, "FRAGMENT");
            // if geometry shader is given, compile geometry shader
            unsigned int geometry;
            if(geometryPath != nullptr)
            {
                const char * gShaderCode = geometryCode.c_str();
                geometry = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(geometry, 1, &gShaderCode, NULL);
                glCompileShader(geometry);
                checkCompileErrors(geometry, "GEOMETRY");
            }
            // shader Program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            if(geometryPath != nullptr)
                glAttachShader(ID, geometry);
            glLinkProgram(ID);
            checkCompileErrors(ID, "PROGRAM");
            // delete the shaders as they're linked into our program now and no longer necessery
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            if(geometryPath != nullptr)
                glDeleteShader(geometry);

        }
        // activate the shader
        // ------------------------------------------------------------------------
        void use()
        {
            glUseProgram(ID);
        }
        // utility uniform functions
        // ------------------------------------------------------------------------
        void setBool(const std::string &name, bool value)
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }
        // ------------------------------------------------------------------------
        void setInt(const std::string &name, int value)
        {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        // ------------------------------------------------------------------------
        void setFloat(const std::string &name, float value)
        {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }
        // ------------------------------------------------------------------------
        void setVec2(const std::string &name, const glm::vec2 &value)
        {
            glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setVec2(const std::string &name, float x, float y)
        {
            glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
        }
        // ------------------------------------------------------------------------
        void setVec3(const std::string &name, const glm::vec3 &value)
        {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setVec3(const std::string &name, float x, float y, float z)
        {
            glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
        }
        // ------------------------------------------------------------------------
        void setVec4(const std::string &name, const glm::vec4 &value)
        {
            glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
        void setVec4(const std::string &name, float x, float y, float z, float w)
        {
            glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
        }
        // ------------------------------------------------------------------------
        void setMat2(const std::string &name, const glm::mat2 &mat)
        {
            glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat3(const std::string &name, const glm::mat3 &mat)
        {
            glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }
        // ------------------------------------------------------------------------
        void setMat4(const std::string &name, const glm::mat4 &mat)
        {
            glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
        void checkCompileErrors(GLuint shader, std::string type)
        {
            GLint success;
            GLchar infoLog[1024];
            if(type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if(!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if(!success)
                {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                }
            }
        }
    };


class GLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
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
    bool a = false;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

class PLookReset : public QPushButton
{
    Q_OBJECT //don't forget this macro, or your signals/slots won't work

public:
    PLookReset(QWidget * parent = 0);
    bool a = false;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
};

#endif // GLWIDGET_H
