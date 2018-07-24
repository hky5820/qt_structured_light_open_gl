#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <QOpenGLShaderProgram>

class Square
{
public:
    Square( QOpenGLShaderProgram *program,
            int vertexAttr, int colorAttr );

    void draw();

private:
    void initVertices();
    void initColors();
    void initList();

//    GLfloat m_vertices[24] = {0,};
//    GLfloat m_colors[24] = {0,};

    std::vector<float> m_vertices;
    std::vector<float> m_colors;

    std::vector<char> m_vertex_list;

    QOpenGLShaderProgram *m_program;
    int m_vertexAttr;
    int m_colorAttr;
};

#endif // SQUARE_H
