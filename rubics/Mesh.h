#ifndef MESH__H
#define MESH__H

#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <vector>

using namespace std;

struct Vertex
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};


QOpenGLTexture* loadTexture(string filename);
QOpenGLShaderProgram* loadShader(string vFilename,string fFilename);



struct Mesh : protected QOpenGLFunctions{
    Mesh();
    ~Mesh();

    void init();

    void draw();

    vector<Vertex> vertices;
    vector<GLushort> indices;


    QOpenGLTexture *texture = nullptr;

    QOpenGLShaderProgram* program = nullptr;

    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;

};





#endif