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
#include <QKeyEvent>

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

  QVector3D rv = mouse.unproject(camera,projection,QRect(0,0,width(),height()));

  mouse = QVector3D(point.x(),point.y(),1);
  QVector3D alpha = mouse.unproject(camera,projection,QRect(0,0,width(),height()));

  rv = (alpha-rv)*0.4;
  rv = QVector3D(rv.x(),0-rv.y() ,0);
  return rv;
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
  target = toOpenGL(QVector2D(e->pos().x(),e->pos().y()));

  //topLeft = toOpenGL(QVector2D(0,0));
  //bottomRight = toOpenGL(QVector2D(width(),height()));

}
void MainWidget::keyPressEvent(QKeyEvent *event )
{
  if( event->key() == Qt::Key_A)
  {
    for(int i =0; i < boids.size(); ++i){
      boids[i].arrival(target); //arrival
    }
  }



  if(event->key() == Qt::Key_W)
  {
    for(int i=0; i < boids.size(); ++i){
    if(i != 0){
      boids[i].seek(boids[i-1].location); //wander
    }
    else{
      boids[0].wander(); //wander
    }
  }
}
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
  initializeOpenGLFunctions();

  forcedResize = false;
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  mesh = new Mesh();
  // mesh2 = new Mesh();
  mesh->program = loadShader(":/vshader.glsl",":/fshader.glsl");
  mesh->texture = loadTexture(":/cube.png");
  // mesh2->program = loadShader(":/vshader.glsl",":/fshader.glsl");
  // mesh2->texture = loadTexture(":/cube.png");


  boid.location = QVector3D(0,10,0);

  for(int i =0; i < 8; ++i){
    Boid b;
    b.location = QVector3D(rand()%10,rand()%10,0);
    //   b.MAX_SPEED = rand()%10+1;
    boids.push_back(b);
  }


  target = QVector3D(0,0,0);

  pastTime = QTime::currentTime();

  loadTriangle(mesh);
  mesh->init();


  timer.start(12, this);
}



//! [5]
void MainWidget::resizeGL(int w, int h){
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);

  // Reset projection
  projection.setToIdentity();

  // Set perspective projection
  projection.perspective(45, aspect, 0.1, 100);
  camera.setToIdentity();
  camera.lookAt( QVector3D(0,0,40), QVector3D(0,0,0), QVector3D(0,1,0));
}
//! [5]

void MainWidget::paintGL(){
  // Clear color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QTime now = QTime::currentTime();

  for(int i =0; i < boids.size(); ++i){
    if(i != 0){
     // boids[i].arrival(target); //arrival
      //boids[i].cohesion(boids); //cohesion
      //boids[i].seek(boids[i-1].location); //wander
    boids[i].seek(target);
    }else{

      //boids[i].arrival(target); //arrival
      //boids[0].wander(); //wander
      boids[i].seek(target);  //cohesion
    }
  }
  for(int i =0;i<boids.size();++i){
    boids[i].update((float)pastTime.msecsTo(now)/1000.0f);

    mesh->texture->bind();
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.translate(boids[i].location.x(),boids[i].location.y(), 0.0);
    matrix.rotate(boids[i].getAngle(),0,0,1);

    mesh->program->setUniformValue("mvp_matrix", projection * camera * matrix);
    mesh->program->setUniformValue("texture", 0);
    mesh->draw();
  }

  pastTime = QTime::currentTime();

}
