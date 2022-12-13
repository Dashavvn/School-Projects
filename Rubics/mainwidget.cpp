/****************************************************************************
 **
 ** Copyright (C) 2016 The Qt Company Ltd.
 ** Contact: https://www.qt.io/licensing/
 **
 ** This file is part of the QtCore module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and The Qt Company. For licensing terms
 ** and conditions see https://www.qt.io/terms-conditions. For further
 ** information use the contact form at https://www.qt.io/contact-us.
 **
 ** BSD License Usage
 ** Alternatively, you may use this file under the terms of the BSD license
 ** as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of The Qt Company Ltd nor the names of its
 **     contributors may be used to endorse or promote products derived
 **     from this software without specific prior written permission.
 **
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include "mainwidget.h"

#include <QMouseEvent>
#include <QMessageBox>

#include <cmath>
#include <iostream>
using namespace std;

MainWidget::~MainWidget()
{
  // Make sure the context is current when deleting the texture
  // and the buffers.
  makeCurrent();
  delete mesh;
  doneCurrent();
}


QVector3D MainWidget::toOpenGL(QVector2D point){

  QVector3D mouse = QVector3D(point.x(),point.y(),0);

  QVector3D rv = mouse.unproject(camera.getMatrix(),projection,QRect(0,0,width(),height()));

  mouse = QVector3D(point.x(),point.y(),1);
  QVector3D alpha = mouse.unproject(camera.getMatrix(),projection,QRect(0,0,width(),height()));

  rv = (alpha-rv)*0.4;
  rv = QVector3D(rv.x(),0-rv.y() ,0);
  return rv;
}




void MainWidget::keyPressEvent(QKeyEvent *e){

 QQuaternion axis; 
bool startAnimation = false;

  if((char)e->key() == 'X'){
    axis = QQuaternion::fromAxisAndAngle(1,0,0,90);
  startAnimation = true;  
  }
  else if((char)e->key() == 'Y'){
    axis = QQuaternion::fromAxisAndAngle(0,1,0,90);
  startAnimation = true;  
  }
  else if((char)e->key() == 'Z'){
    axis = QQuaternion::fromAxisAndAngle(0,0,1,90);
  startAnimation = true;  
  }

  if(!spot.animating && startAnimation){
  spot.start = spot.orientation;
  spot.end = spot.orientation*axis;
  spot.alpha = 0;
  spot.animating = true;
}


}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
  target = toOpenGL(QVector2D(e->pos().x(),e->pos().y()));

  //topLeft = toOpenGL(QVector2D(0,0));
  //bottomRight = toOpenGL(QVector2D(width(),height()));

}

void MainWidget::timerEvent(QTimerEvent *){
  /*  if(!forcedResize){
      resize(width()+1,height());
      forcedResize = true;
      resize(width()-1,height());
      }*/

  update();
}

void loadTriangle(Mesh* mesh){
  float s = (float)sqrt(2);

  mesh->vertices = {
    // Vertex data for face 0
    {QVector3D(-s/2, -s/2,  0.0f), QVector2D(0.0f, 0.0f)},  // v0
    {QVector3D( s/2, -s/2,  0.0f), QVector2D(0.33f, 0.0f)}, // v1
    {QVector3D(0.0f,  1.0f,  0.0f), QVector2D(0.0f, 0.5f)},  // v2
  };

  mesh->indices.push_back(0);
  mesh->indices.push_back(1);
  mesh->indices.push_back(2);

}

void MainWidget::initializeGL()
{
  srand(time(0));
  camera.pos = QVector3D(0,4,8);
  camera.focus = QVector3D(0,0,0);

  initializeOpenGLFunctions();

  forcedResize = false;
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
  mesh = new Mesh();
  //mesh = loadOBJ("spot_triangulated.obj");
  mesh = loadOBJ("cube.obj");

  mesh->program = loadShader(":/vshader.glsl",":/fshader.glsl");

//  mesh->texture = loadTexture(":/spot_texture.png");

  mesh->texture = loadTexture(":/cube.png");

  target = QVector3D(0,0,0);


  pastTime = QTime::currentTime();

  mesh->init();

  spot.pos = QVector3D(1,2,0);
  spot.orientation = QQuaternion::fromAxisAndAngle(1,0,0,0);


  timer.start(12, this);
}


QMatrix4x4 Camera::getMatrix(){
  QMatrix4x4 c;
  c.setToIdentity();
  c.lookAt( pos,focus, QVector3D(0,1,0));  
  return c;
}

void Camera::rotate(float degs){
  QMatrix4x4 rot;
  rot.setToIdentity();
  //rotating around y axis not focus
  rot.rotate(degs,0,1,0);
  QVector3D off = pos-focus;
  pos = rot*off + focus;
}


//! [5]
void MainWidget::resizeGL(int w, int h){
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Reset projection
  projection.setToIdentity();

  // Set perspective projection
  projection.perspective(45, aspect, 0.1, 100);

}
//! [5]

void Spot::update(float dt){
  if(alpha < 1.0f){
    orientation = QQuaternion::slerp(start,end,alpha);
    orientation.normalize();
    alpha += dt;
  }
  else{
orientation = end;
animating = false;

  }
}

void MainWidget::paintGL(){
  // Clear color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QTime now = QTime::currentTime();

  float dt = (float)pastTime.msecsTo(now)/1000.0f;
  camera.rotate(90*dt);



  mesh->texture->bind();
  QMatrix4x4 matrix;
  matrix.setToIdentity();
  QQuaternion xaxis = QQuaternion::fromAxisAndAngle(1,0,0,90);
  QQuaternion yaxis = QQuaternion::fromAxisAndAngle(0,1,0,90);

  spot.update(dt);

  spot.orientation.normalize();

  matrix.rotate(spot.orientation);
  matrix.translate(spot.pos);


  mesh->program->setUniformValue("mvp_matrix", projection * camera.getMatrix() * matrix);
  mesh->program->setUniformValue("texture", 0);
  mesh->draw();

  matrix.setToIdentity();
  mesh->program->setUniformValue("mvp_matrix", projection * camera.getMatrix() * matrix);
  mesh->program->setUniformValue("texture", 0);
  mesh->draw();



  pastTime = QTime::currentTime();
}
