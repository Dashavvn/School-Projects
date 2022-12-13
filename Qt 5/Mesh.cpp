#include "Mesh.h"


QOpenGLTexture* loadTexture(string filename){
    QOpenGLTexture* texture = new QOpenGLTexture(QImage(filename.c_str()).mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
    return texture;
}


QOpenGLShaderProgram* loadShader(string vFilename,string fFilename){
    QOpenGLShaderProgram* program = new QOpenGLShaderProgram();
    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, vFilename.c_str()))
        return nullptr;

    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, fFilename.c_str()))
        return nullptr;

    if (!program->link())
        return nullptr;

    if (!program->bind())
        return nullptr;
    return program;
}


Mesh::Mesh() 
: indexBuffer(QOpenGLBuffer::IndexBuffer){
    initializeOpenGLFunctions();
    
    // Generate 2 VBOs
    vertexBuffer.create();
    indexBuffer.create();
}

Mesh::~Mesh(){
    vertexBuffer.destroy();
    indexBuffer.destroy();
}

void Mesh::init(){

    vertexBuffer.bind();
    vertexBuffer.allocate(vertices.data(), vertices.size() * sizeof(Vertex));

    indexBuffer.bind();
    indexBuffer.allocate(indices.data(), indices.size() * sizeof(GLushort));

}

void Mesh::draw(){

    vertexBuffer.bind();
    indexBuffer.bind();

    // Offset for position
    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(Vertex));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(Vertex));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_SHORT, nullptr);
}
